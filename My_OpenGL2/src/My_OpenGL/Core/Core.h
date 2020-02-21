#pragma once

#include <iostream>

#define ENABLE_ASSERTS 1
// make a logging library first
#if ENABLE_ASSERTS
	#define CORE_ASSERT(x, ...) { if(!(x)) { CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
	#define ASSERT(x, ...) { if(!(x)) { ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else
	#define CORE_ASSERT(x, ...)
	#define ASSERT(x, ...)
#endif
