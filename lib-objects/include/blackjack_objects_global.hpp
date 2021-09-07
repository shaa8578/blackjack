#pragma once

#include <memory>

//------------------------------------------------------------------------------
#if defined(_MSC_VER)
#define BLACKJACK_EXPORT __declspec(dllexport)
#define BLACKJACK_IMPORT __declspec(dllimport)
#elif defined(__GNUC__) || defined(__clang__)
#define BLACKJACK_EXPORT __attribute__((visibility("default")))
#define BLACKJACK_IMPORT __attribute__((visibility("default")))
#else
#error Defines EXPORT/IMPORT not defined
#endif

//------------------------------------------------------------------------------
#if defined(BLACKJACK_LIBRARY)
#define LIB_BLACKJACK_SHARED BLACKJACK_EXPORT
#else
#define LIB_BLACKJACK_SHARED BLACKJACK_IMPORT
#endif
