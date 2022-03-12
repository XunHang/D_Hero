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
