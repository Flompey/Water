#pragma once
#include "VectorDebugInfo.h"

template<class T>
class RawVectorReleaseBase
{
protected:
	void InitializeVectorDebugInfo(T* begin, T* end) noexcept
	{
	}
	VectorDebugInfo<T>* GetVectorDebugInfo() noexcept
	{
		return nullptr;
	}
};