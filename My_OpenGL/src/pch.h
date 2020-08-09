#pragma once

// common
#include <iostream>
#include <fstream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

// data structures
#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>

#include "My_OpenGL/Core/Log.h"
//#include "My_OpenGL/Debug/Instrumentor.h"		// Profiling header

// platform specific
#ifdef PLATFORM_WINDOWS
	#include <Windows.h>
#endif