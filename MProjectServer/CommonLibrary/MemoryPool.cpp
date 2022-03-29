#include "MemoryPool.h"
#include "MProjectServerDefine.h"

MemoryPool::MemoryPool(std::size_t _block_size, int _pre_alloc, int _max_alloc)
	: block_size(_block_size), max_alloc(_max_alloc), allocated(_pre_alloc) {
	assert(max_alloc == 0 || max_alloc >= allocated);
	assert(allocated >= 0 && max_alloc >= 0);

	int r = BLOCK_RESERVE;
	if (allocated > r) {
		r = allocated;
	}
	if (max_alloc > 0 && max_alloc < r) {
		r = max_alloc;
	}
	block_vector.reserve(r);

	try {
		for (int i = 0; i < allocated; ++i) {
			block_vector.emplace_back(new char[block_size]);
		}
	}
	catch (...) {
		Clear();
		throw;
	}
}

MemoryPool::~MemoryPool() {
	Clear();
}

void* MemoryPool::Get() {
	std::lock_guard<std::recursive_mutex> lock_guard(_mutex);
	if (true == block_vector.empty()) {
		if (max_alloc == 0 || allocated < max_alloc) {
			++allocated;
			return new char[block_size];
		} else {
			throw; // Out of memory...
		}
	} else {
		char* ptr = block_vector.back();
		block_vector.pop_back();
		return ptr;
	}
	return nullptr;
}

void MemoryPool::Release(void* _ptr) {
	std::lock_guard<std::recursive_mutex> lock_guard(_mutex);
	try {
		block_vector.emplace_back(reinterpret_cast<char*>(_ptr));
	} catch(...) {
		delete[] reinterpret_cast<char*>(_ptr);
	}
}

void MemoryPool::Clear() {
	for (auto p : block_vector) {
		delete[] p;
	}
	block_vector.clear();
}
