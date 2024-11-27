#pragma once
#include <mcs/common/linker.hpp>
#include <cstring>

#ifdef _OS_WINDOWS
#   define COPY_MEMORY(dst, src, size) memcpy_s(dst, size, src, size)
#else
#   define COPY_MEMORY(dst, src, size) memcpy(dst, src, size)
#endif