#pragma once

#include <stdint.h>
#include <iostream>

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#define NUTCRACKER_VERSION "0.04"

#ifndef SQ_VERSION_MAJOR
	#define SQ_VERSION_MAJOR 2
#endif

#ifndef SQ_VERSION_MINOR
	#define SQ_VERSION_MINOR 1
#endif

#ifdef SQ64
	using WordT  = int64_t;
	using UWordT = uint64_t;
#else
	using WordT  = int32_t;
	using UWordT = uint32_t;
#endif

#ifdef NDEBUG
	inline bool g_DebugMode = false;
#else
	inline bool g_DebugMode = true;
#endif
