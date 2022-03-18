#pragma once

#ifdef DH_PLATFORM_WINDOWS
	#ifdef DH_BUILD_DLL
		#define DH_API __declspec(dllexport)
	#else
		#define DH_API __declspec(dllimport)
	#endif
#else
	#error Please Define Platform.(Only support Windows)
#endif

// ASSERTION
#ifdef DH_ENABLE_ASSERTS
#ifdef DH_PLATFORM_WINDOWS
#define DH_ASSERT(x,...) {if (!(x)) { DH_ERROR("Assertion Failed! {0}", __VA_ARGS__); __debugbreak(); } }
#define DH_CORE_ASSERT(x,...) {if (!(x)) { DH_CORE_ERROR("Assertion Failed! {0}", __VA_ARGS__); __debugbreak(); } }
#endif
#else
#define DH_ASSERT(x,...)
#define DH_CORE_ASSERT(x,...)
#endif

#define BIT(x) (1<<x)

#define DH_BIND_EVENT_FN(x,y) std::bind(&x::y, this, std::placeholders::_1)