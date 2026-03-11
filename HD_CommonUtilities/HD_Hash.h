#pragma once

#include <functional>

// For now just forwarding to std::hash.
	// * Future project: implement a custom hash function.

#define HD_Hash(a) std::hash<decltype(a)>{}(a)
