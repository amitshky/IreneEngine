#pragma once

#include <memory>

#ifdef _WIN32
	/* Windows x64/x86 */
	#ifdef _WIN64
		/* Windows x64  */
		#define PLATFORM_WINDOWS
	#else
		/* Windows x86 */
		#error "x86 Builds are not supported!"
	#endif
#endif

// DLL support
#ifdef PLATFORM_WINDOWS
	#if DYNAMIC_LINK
		#ifdef GE_BUILD_DLL
			#define MY_OPENGL_API __declspec(dllexport)
		#else
			#define MY_OPENGL_API __declspec(dllimport)
		#endif
	#else
		#define MY_OPENGL_API
	#endif
#else
	#error My_OpenGL only supports Windows!
#endif

#ifdef DEBUG
	#define ENABLE_ASSERTS
#endif

#ifdef ENABLE_ASSERTS
	#define CORE_ASSERT(x, ...) { if(!(x)) { CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
	#define ASSERT(x, ...) { if(!(x)) { CLIENT_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else
	#define CORE_ASSERT(x, ...)
	#define ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace irene {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}