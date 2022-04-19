#pragma once
#include <vector>
#include <cstddef>
#include <mutex>
#include <atomic>

#define MEMORY_POOL_PREALLOC 1024

template<typename T, typename M = std::_Mutex_base>
class MemoryPool {
private:
	struct FBlock {
		FBlock() {
			memory.next = this + 1;
		}
		explicit FBlock(FBlock* _next) {
			memory.next = _next;
		}
		union {
			char buffer[sizeof(T)];
			FBlock* next;
		} memory;
	private:
		FBlock(FBlock const&) = delete;
		FBlock& operator = (FBlock const&) = delete;
	};

public:
	using MutexType = M;
	using Bucket = FBlock*;
	using Buckets = std::vector<Bucket>;

	/// <param name="_blocks_per_bucket">각 버킷에 포함된 블록 수를 지정</param>
	/// <param name="_bucket_pre_alloc">Bucket Pointer 공간 지정</param>
	/// <param name="_max_alloc">최대 허용 풀 크기</param>
	MemoryPool(std::size_t _blocks_per_bucket = MEMORY_POOL_PREALLOC, std::size_t _bucket_pre_alloc = 10, std::size_t _max_alloc = 0) 
		: blocks_per_bucket(_blocks_per_bucket), max_alloc(_max_alloc), available(0) {
		if (blocks_per_bucket < 2) {
			throw;
		}
		buckets.reserve(_bucket_pre_alloc);
		Resize();
	}

	~MemoryPool() {
		Clear();
	}

	void* Get() {
		Bucket bucket;
		{
			std::lock_guard<MutexType> lock(mutex);
			if (header == nullptr) {
				Resize();
			}
			bucket = header;
			header = header->memory.next;
		}
		--available;
		return bucket;
	}

	template<typename P>
	void Release(P* _ptr) {
		if (nullptr == _ptr) {
			return;
		}
		++available;
		std::lock_guard<MutexType> lock(mutex);
		header = new (_ptr) FBlock(header);
	}

	std::size_t BlockSize() const {
		return sizeof(FBlock);
	}

	std::size_t Allocated() const {
		return buckets.size() * blocks_per_bucket;
	}

	std::size_t Available() const {
		return available;
	}

private:
	MemoryPool(MemoryPool const&) = delete;
	MemoryPool& operator = (MemoryPool const&) = delete;

	void Resize() {
		if (buckets.size() == buckets.capacity()) {
			std::size_t new_size = buckets.capacity() * 2;
			if (max_alloc != 0 && new_size > max_alloc) {
				throw std::bad_alloc();
			}
			buckets.reserve(new_size);
		}
		buckets.emplace_back(new FBlock[blocks_per_bucket]);
		header = buckets.back();
		header[blocks_per_bucket - 1].memory.next = nullptr;
		available.store(available.load() + static_cast<int>(blocks_per_bucket));
	}

	void Clear() {
		typename Buckets::iterator it = buckets.begin();
		typename Buckets::iterator end = buckets.end();
		for (; it != end; ++it) {
			delete[] * it;
		}
	}

private:
	const std::size_t blocks_per_bucket;
	Buckets buckets;
	Bucket header;
	std::size_t max_alloc;
	std::atomic<int> available;
	mutable MutexType mutex;
};
