#pragma once
#include <vector>
#include <cstddef>
#include <mutex>

class MemoryPool {
public:
	MemoryPool(std::size_t _block_size, int _pre_alloc = 0, int _max_alloc = 0);
	~MemoryPool();

	void* Get();
	void Release(void* _ptr);
	
	std::size_t BlockSize() const {
		return block_size;
	}
	int Allocated() const {
		return allocated;
	}
	int Available() const {
		return static_cast<int>(block_vector.size());
	}

private:
	MemoryPool() = delete;
	MemoryPool(MemoryPool const&) = delete;
	MemoryPool& operator = (MemoryPool const&) = delete;

	void Clear();

	enum {	// Default
		BLOCK_RESERVE = 128,
	};

	using BlockVector = std::vector<char*>;

	std::size_t block_size;
	int max_alloc;
	int allocated;
	BlockVector block_vector;
	std::recursive_mutex _mutex;
};
