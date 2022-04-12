#pragma once
#include <boost/noncopyable.hpp>
#include <assert.h>

namespace {
	class SingletonModule : public boost::noncopyable {
		bool& GetLock() {
			static bool lock = false;
			return lock;
		}
	public:
		void Lock() {
			GetLock() = true;
		}
		void Unlock() {
			GetLock() = false;
		}
		bool IsLocked() {
			return GetLock();
		}
	};

	static inline SingletonModule& GetSingletonModule() {
		static SingletonModule m;
		return m;
	}

	template<typename T>
	class TSingletonCore : public T {
		static bool& GetIsDestroyed() {
			static bool is_destroyed_flag = false;
			return is_destroyed_flag;
		}

	public:
		TSingletonCore() {
			assert(!IsDestroyed());
		}
		~TSingletonCore() {
			GetIsDestroyed() = true;
		}
		static bool IsDestroyed() {
			return GetIsDestroyed();
		}
	};
}

template<typename T>
class TSingleton {
public:
	static T& GetMutableInstance() {
		assert(!GetSingletonModule().IsLocked());
		return GetInstance();
	}
	static T const& GetConstInstance() {
		return GetInstance();
	}
	static bool IsDestroyed() {
		return TSingletonCore<T>::IsDestroyed();
	}

private:
	static T* instance;
	static void Use(T const&) {}
	static T& GetInstance() {
		assert(!IsDestroyed());
		static TSingletonCore<T> t;
		if (instance) Use(*instance);
		return static_cast<T&>(t);
	}

protected:
	TSingleton() {}
};

template<typename T>
T* TSingleton<T>::instance = &TSingleton<T>::GetInstance();
