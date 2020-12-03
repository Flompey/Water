#pragma once
#include "VectorDebugInfo.h"

template<class T>
class VectorIteratorReleaseBase
{
protected:
	void SetVectorDebugInfo(VectorDebugInfo<T>* vectorDebugInfo) noexcept
	{
	}
	bool IsValid() noexcept
	{
		return false;
	}
	void AddToContainer(VectorIterator<T>* iterator) noexcept
	{
	}
	void RemoveFromContainer(VectorIterator<T>* iterator) noexcept
	{
	}
};