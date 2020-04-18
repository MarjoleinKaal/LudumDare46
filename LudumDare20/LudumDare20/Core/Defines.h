#pragma once
#include <cassert>

#define ASSERT(expression) assert(expression)
#define ASSERT_MSG(expression, msg) assert(expression && msg);