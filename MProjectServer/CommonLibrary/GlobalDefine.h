﻿/*****************************************************************//**
 * \file   GlobalDefine.h
 * \brief  
 * 
 * \author dek0058
 * \date   2022-11-02
 *********************************************************************/
#pragma once

#define WIN32_LEAN_AND_MEAN

#include <sdkddkver.h>
#include <iostream>
#include <fstream>
#include <chrono>

#include <memory>
#include <memory_resource>
#include <algorithm>
#include <atomic>
#include <optional>

#include <thread>
#include <future>
#include <mutex>
#include <functional>
#include <exception>
#include <coroutine>

#include <vector>
#include <array>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
#include <forward_list>
#include <span>

#include "String/String.h"	// include string, locale, format

// variable define
//typedef char				char;
typedef unsigned char		byte;
//typedef short				short;
typedef unsigned short		ushort;
//typedef int				int;
typedef unsigned int		uint;
//typedef long				long;
typedef unsigned long		ulong;
typedef long long			decimal;
typedef unsigned long long	udecimal;
//typedef float				float;
//typedef double			real;


//template<class T>
//using vectory = std::vector<T>;
//template<class T>
//using array = std::array<T>;
//template<class T>
//using map = std::map<T>;

template <class Key, class T, class Hash = std::hash<Key>, class Pred = std::equal_to<Key>>
using hashmap = std::unordered_map<Key, T, Hash, Pred>;

//template<class T>
//using set = std::set<T>;

