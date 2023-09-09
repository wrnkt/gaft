#pragma once

#include <string>
#include <filesystem>
#include <vector>

#if defined(_WIN32) || defined(_WIN64)
    #define FTAG_WINDOWS
#elif defined(__APPLE__) || defined(__MACH__)
    #define FTAG_MAC
#elif defined(unix) || defined(__unix__) || defined(__unix)
    #define FTAG_UNIX
#endif

