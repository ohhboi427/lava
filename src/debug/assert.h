#pragma once

#include "../core/logger.h"
#include "../core/macros.h"

#ifdef LAVA_DEBUG
#  define LAVA_ASSERT_NO_MSG(cond) { if(!(cond)) { __debugbreak(); } }
#  define LAVA_ASSERT_MSG(cond, msg) { if(!(cond)) { LAVA_LOGGER.critical(msg); __debugbreak(); } }

#  define LAVA_GET_ASSERT(cond, arg1, arg2, ...) arg2

#  define LAVA_ASSERT(...) LAVA_EXPAND(LAVA_GET_ASSERT(__VA_ARGS__, LAVA_ASSERT_MSG, LAVA_ASSERT_NO_MSG)(__VA_ARGS__))
#else
#  define LAVA_ASSERT(...)
#endif // LAVA_DEBUG
