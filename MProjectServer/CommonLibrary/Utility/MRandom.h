#pragma once
#include <math.h>

template<typename T = struct RandomCalculator>
class MRandom {
public:
	template<typename Type>
	static Type GetRandom() {
		if constexpr (std::is_same_v<T, struct splitmix64>) {
			return T::GetRandom();
		} else if constexpr (std::is_same_v<T, struct splitmix32>) {
			return T::GetRandom();
		} else {
			return 0;
		}
	}
};

// todo ¼öÁ¤
//https://gist.github.com/imneme/6179748664e88ef3c34860f44309fc71
#pragma region splitmix64_32
struct RandomCalculator {};
struct splitmix64 : public RandomCalculator {
	static unsigned long long GetRandom() {
		unsigned long long z = (seed += 0x9e3779b97f4a7c15);
		z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
		z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
		return z ^ (z >> 31);
	}
	static void SetSeed(unsigned long long _seed) {
		seed = _seed;
	}
protected:
	static unsigned long long seed;
};
unsigned long long splitmix64::seed = 1;

struct splitmix32 : public splitmix64 {
	static unsigned long GetRandom() {
		unsigned long long z = (splitmix64::seed += 0x9e3779b97f4a7c15);
		z = (z ^ (z >> 33)) * 0x62A9D9ED799705F5;
		z = (z ^ (z >> 28)) * 0xCB24D0A5C88C35B3;
		return static_cast<unsigned long>(z ^ (z >> 32));
	}
	static void SetSeed(unsigned long long _seed) {
		splitmix64::seed = _seed;
	}
};
#pragma endregion
