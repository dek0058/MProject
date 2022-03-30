#pragma once

// Prevent copy construction and assignment for a class.
#define DELETE_REFERENCE_CREATOR(ClassName) \
private: \
	ClassName(ClassName const&) = delete; \
	ClassName& operator = (ClassName const&) = delete;