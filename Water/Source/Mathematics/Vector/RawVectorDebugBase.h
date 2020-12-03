#pragma once
#include "VectorDebugInfo.h"

template<class T>
class RawVectorDebugBase
{
public:
	RawVectorDebugBase() = default;
protected:
	RawVectorDebugBase(const RawVectorDebugBase&){}
	RawVectorDebugBase(RawVectorDebugBase&& other)
	{
		other.mVectorDebugInfo.Deactivate();
	}
	void operator=(const RawVectorDebugBase& other) {}
	RawVectorDebugBase& operator=(RawVectorDebugBase&& other) 
	{
		assert(*this != other);
		other.mVectorDebugInfo.Deactivate();
	}
	~RawVectorDebugBase()
	{
		mVectorDebugInfo.Invalidate();
	}
	void InitializeVectorDebugInfo(T* begin, T* end)
	{
		assert(!mInitialized);
		mInitialized = true;
		mVectorDebugInfo.begin = begin;
		mVectorDebugInfo.end = end;
	}
	VectorDebugInfo<T>* GetVectorDebugInfo()
	{
		assert(mInitialized);
		return &mVectorDebugInfo;
	}
private:
	bool mInitialized = false;
	VectorDebugInfo<T> mVectorDebugInfo;
};
