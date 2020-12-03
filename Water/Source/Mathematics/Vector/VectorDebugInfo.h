#pragma once

template<class T>
class VectorIterator;

// Contains information used by iterators in debug mode
template<class T>
class VectorDebugInfo
{
public:
	~VectorDebugInfo()
	{
		for (auto& iterator : mActiveIterators)
		{
			iterator->Invalidate();
		}
	}
	void Invalidate()
	{
		begin = nullptr;
		end = nullptr;
	}
	bool IsActive()
	{
		return begin == nullptr;
	}
	void AddIterator(VectorIterator<T>* iterator)
	{
		// Make sure that we have not added this iterator already
		assert(std::find(mActiveIterators.begin(), 
			mActiveIterators.end(), iterator) == mActiveIterators.end());
		mActiveIterators.push_back(iterator);
	}
	void RemoveIterator(VectorIterator<T>* iterator)
	{
		size_t count = mActiveIterators.remove(iterator);
		assert(count == 1);
	}
public:
	T* begin = nullptr;
	T* end = nullptr;
private:
	std::list<VectorIterator<T>*> mActiveIterators;
};