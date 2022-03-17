#pragma once
#include <boost/serialization/singleton.hpp>

template<class T>
class TSingleton {
public:
	TSingleton(TSingleton<T> const&) = delete;
	TSingleton(TSingleton<T>&&) = delete;
	TSingleton& operator = (TSingleton<T> const&) = delete;
	TSingleton& operator = (TSingleton<T>&&) = delete;
};