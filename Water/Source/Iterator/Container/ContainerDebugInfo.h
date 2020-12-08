#pragma once

template<class T>
class RandomAccessIteratorDebugBase;

// Contains information used by iterators in debug mode
template<class T>
class ContainerDebugInfo
{
public:
	ContainerDebugInfo() = default;
	// One should not be able to copy nor move a "ContainerDebugInfo" 
	// instance, since it contains pointers to the container's local data
	ContainerDebugInfo(const ContainerDebugInfo& other) = delete;
	ContainerDebugInfo& operator=(const ContainerDebugInfo& other) = delete;

	~ContainerDebugInfo()
	{
		InvalidateIterators();
	}
	void AddIterator(RandomAccessIteratorDebugBase<T>* iterator)
	{
		// Make sure that we have not added this iterator already
		assert(std::find(mActiveIterators.begin(), 
			mActiveIterators.end(), iterator) == mActiveIterators.end());
		mActiveIterators.push_back(iterator);
	}
	void RemoveIterator(RandomAccessIteratorDebugBase<T>* iterator)
	{
		size_t count = mActiveIterators.remove(iterator);
		// Make sure we removed precisely one iterator
		assert(count == 1);
	}
private:
	void InvalidateIterators()
	{
		for (auto& iterator : mActiveIterators)
		{
			iterator->RemoveContainer();
		}
	}
public:
	T* begin = nullptr;
	T* end = nullptr;
private:
	// All the current iterators that points to data inside the associated
	// container. The only reason they are stored is to be able to, for debug purposes,
	// invalidate them.
	std::list<RandomAccessIteratorDebugBase<T>*> mActiveIterators;
};