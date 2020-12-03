#pragma once
#include "VectorDebugInfo.h"

template<class T>
class VectorIteratorDebugBase
{
protected:
	void SetVectorDebugInfo(VectorDebugInfo<T>* vectorDebugInfo)
	{
		mVectorDebugInfo = vectorDebugInfo;
	}
	const VectorDebugInfo<T>* const GetVectorDebugInfo() const
	{
		return mVectorDebugInfo ? mVectorDebugInfo : nullptr;
	}
	void Invalidate()
	{
		mVectorDebugInfo = nullptr;
	}
	bool IsValid()
	{
		return mVectorDebugInfo;
	}
	void AddToContainer(VectorIterator<T>* iterator)
	{
		assert(mVectorDebugInfo);
		mVectorDebugInfo->AddIterator(iterator);
	}
	void RemoveFromContainer(VectorIterator<T>* iterator)
	{
		assert(mVectorDebugInfo);
		mVectorDebugInfo->RemoveIterator(iterator);
	}
private:
	VectorDebugInfo<T>* mVectorDebugInfo;
	// "VectorDebugInfo" needs to be able to call Invalidate()
	friend class VectorDebugInfo<T>;
};