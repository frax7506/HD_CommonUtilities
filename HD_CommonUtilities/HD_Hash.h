#pragma once

#include <functional>

// For now just forwarding to std::hash.
	// * Future project: implement a custom hash function.

template<typename T>
size_t HD_Hash(const T& aDataToHash)
{
	return std::hash<T>{}(aDataToHash);
}
