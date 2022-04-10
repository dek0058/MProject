#pragma once
#include <memory>
#include <atomic>
#include <shared_mutex>
#include <type_traits>
#include <cstdint>
#include <cstddef>
#include <algorithm>
#include <cassert>

template<bool> class CircularBuffer_Atomic;
using CircularBuffer_A = CircularBuffer_Atomic<true>;

template<typename> class CircularBuffer_Mutex;
using CircularBuffer_M = CircularBuffer_Mutex<std::shared_mutex>;


template<typename T>
class TCircularBuffer {
public:
	template<typename U>
	bool Get(U& _x) {
		return Get(&_x, 1);
	}

	template<typename U>
	bool Get(U* _x, size_t _n) {
		static_assert(std::is_trivially_copyable<U>::value, "[TCircularBuffer] U must be trivially copyable");
		T* self = static_cast<T*>(this);
		return self->GetBytes(_x, _n * sizeof(U));
	}

	template<typename U>
	bool Peek(U& _x) {
		return Peek(&_x, 1);
	}

	template<typename U>
	bool Peek(U* _x, size_t _n) {
		static_assert(std::is_trivially_copyable<U>::value, "[TCircularBuffer] U must be trivially copyable");
		T* self = static_cast<T*>(this);
		return self->PeekBytes(_x, _n * sizeof(U));
	}

	template<typename U>
	bool Put(U const& _x) {
		return Put(&_x, 1);
	}

	template<typename U>
	bool Put(U const* _x, size_t _n) {
		static_assert(std::is_trivially_copyable<U>::value, "[TCircularBuffer] U must be trivially copyable");
		T* self = static_cast<T*>(this);
		return self->PutBytes(_x, _n * sizeof(U));
	}
};

template<bool Atomic>
class CircularBuffer_Atomic final : private TCircularBuffer<CircularBuffer_Atomic<Atomic>> {
	typedef TCircularBuffer<CircularBuffer_Atomic<Atomic>> Base;
	friend Base;
	template<typename> friend class CircularBuffer_Mutex;

public:
	explicit CircularBuffer_Atomic(size_t _capacity) : capacity(_capacity + 1), buffer_data(new uint8_t[capacity]) { ; }
	~CircularBuffer_Atomic() { ; }

	size_t Capacity() const {
		return capacity - 1;
	}

	size_t UsedSize() const {
		size_t const bp = begin_ptr, ep = end_ptr, c = capacity;
		return ep + (ep < bp ? c : 0) - bp;
	}
	bool Discard(size_t _len) {
		return GetBytes(nullptr, _len, true);
	}
	using Base::Get;
	using Base::Peek;

	size_t FreeSize() const {
		size_t const bp = begin_ptr, ep = end_ptr, c = capacity;
		return bp + (bp <= ep ?  c : 0) - ep - 1;
	}
	using Base::Put;

private:
	bool GetBytes(void* _data, size_t _len) {
		return GetBytes(_data, _len, true);
	}
	bool GetBytes(void* _data, size_t _len, bool _advp) {
		if (UsedSize() < _len) {
			return false;
		}

		size_t const bp = begin_ptr, c = capacity;
		uint8_t const* src = buffer_data.get();
		uint8_t* dst = (uint8_t*)_data;

		if (_data) {
			size_t const tail_len = std::min(_len, c - bp);
			if constexpr(Atomic) {
				std::atomic_thread_fence(std::memory_order_acquire);
			}
			std::copy_n(&src[bp], tail_len, dst);
			std::copy_n(src, _len - tail_len, dst + tail_len);
		}

		if (_advp) {
			begin_ptr = (bp + _len) < c ? (bp + _len) : (bp + _len - c);
		}
		return true;
	}
	bool PeekBytes(void* _data, size_t _len) {
		auto* nc_this = const_cast<CircularBuffer_Atomic<Atomic>*>(this);
		return nc_this->GetBytes(_data, _len, false);
	}
	bool PutBytes(void const* _data, size_t _len) {
		if (FreeSize() < _len) {
			return false;
		}

		size_t const ep = end_ptr, c = capacity;
		uint8_t const* src = (uint8_t const*)_data;
		uint8_t* dst = buffer_data.get();

		size_t const tail_len = std::min(_len, c - ep);
		std::copy_n(src, tail_len, &dst[ep]);
		std::copy_n(src + tail_len, _len - tail_len, dst);
		if constexpr (Atomic) {
			std::atomic_thread_fence(std::memory_order_release);
		}

		end_ptr = (ep + _len) < c ? (ep + _len) : (ep + _len - c);
		return true;
	}

private:
	size_t capacity{ 0 };
	std::conditional_t<Atomic, std::atomic<size_t>, size_t> begin_ptr{ 0 }, end_ptr{ 0 };
	std::unique_ptr<uint8_t[]> buffer_data{};
};

template<typename Mutex>
class CircularBuffer_Mutex final : private TCircularBuffer<CircularBuffer_Mutex<Mutex>> {
	typedef TCircularBuffer<CircularBuffer_Mutex<Mutex>> Base;
	friend Base;

public:
	explicit CircularBuffer_Mutex(size_t _capacity) : buffer(_capacity) { ; }
	~CircularBuffer_Mutex() { ; }

	size_t Capacity() const {
		return buffer.Capacity();
	}

	size_t UsedSize() const {
		std::shared_lock<Mutex> lock(mutex);
		return buffer.UsedSize();
	}
	bool Discard(size_t _len) {
		std::shared_lock<Mutex> lock(mutex);
		return buffer.Discard(_len);
	}
	using Base::Get;
	using Base::Peek;

	size_t FreeSize() const {
		std::shared_lock<Mutex> lock(mutex);
		return buffer.FreeSize();
	}
	using Base::Put;

private:
	bool GetBytes(void* _data, size_t _len) {
		std::shared_lock<Mutex> lock(mutex);
		return buffer.GetBytes(_data, _len);
	}
	bool PeekBytes(void* _data, size_t _len) {
		std::shared_lock<Mutex> lock(mutex);
		auto& nc_buffer = const_cast<CircularBuffer_Atomic<false>&> (buffer);
		return nc_buffer.PeekBytes(_data, _len);
	}
	bool PutBytes(void const* _data, size_t _len) {
		bool good = false;
		size_t old_capacity = buffer.Capacity();
		size_t new_capacity = UsedSize() + _len;
		if (new_capacity <= old_capacity) {
			std::shared_lock<Mutex> lock(mutex);
			good = buffer.PutBytes(_data, _len);
		} else {
			std::shared_lock<Mutex> lock(mutex);
			Grow(new_capacity);
			good = buffer.PutBytes(_data, _len);
		}
		assert(good);
		return true;
	}
	void Grow(size_t _new_capacity) {
		size_t old_capacity = buffer.Capacity();
		size_t new_capacity = (old_capacity < 16) ? 16 : old_capacity;
		while (new_capacity < _new_capacity) {
			if (new_capacity > std::numeric_limits<size_t>::max() / 3) {
				throw std::bad_alloc();
			}
			new_capacity = new_capacity * 3 / 2;
		}

		size_t len = buffer.UsedSize();
		std::unique_ptr<uint8_t[]> new_data(new uint8_t[new_capacity + 1]);
		
		{
			size_t const bp = buffer.begin_ptr;
			uint8_t const* src = buffer.buffer_data.get();
			uint8_t* dst = new_data.get();

			size_t const tail_len = std::min(len, old_capacity + 1 - bp);
			std::copy_n(&src[bp], tail_len, dst);
			std::copy_n(src, len - tail_len, dst + tail_len);
		}

		buffer.capacity = new_capacity + 1;
		buffer.begin_ptr = 0;
		buffer.end_ptr = len;
		buffer.buffer_data = std::move(new_data);
	}

private:
	CircularBuffer_Atomic<false> buffer;
	mutable Mutex mutex;
};
