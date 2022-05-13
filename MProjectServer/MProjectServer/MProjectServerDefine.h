#pragma once
#include "GlobalDefine.h"

enum class ThreadType : byte {
	Main,
};

class IThread {
public:
	virtual ThreadType GetThreadType() const = 0;
};

