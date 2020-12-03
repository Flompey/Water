#pragma once
#include "VectorIteratorDebugBase.h"
#include "VectorIteratorReleaseBase.h"

#ifdef DEBUG
template<class T>
using VectorIteratorBase = VectorIteratorDebugBase<T>;
#else
template<class T>
using VectorIteratorBase = VectorIteratorReleaseBase<T>;
#endif

template<class T>
class VectorIterator : public VectorIteratorBase<T>
{
public:
	using iterator_category = std::random_access_iterator_tag;
	using value_type = T;
	using difference_type = ptrdiff_t;
	using pointer = T*;
	using reference = T&;

	VectorIterator(T* pointer, VectorDebugInfo<T>* vectorDebugInfo)
	{
		Base::SetVectorDebugInfo(vectorDebugInfo);
		Base::AddToContainer(this);
		assert(pointer);
		assert(pointer >= VectorIteratorDebugBase<T>::GetVectorDebugInfo()->begin);
		assert(pointer <= VectorIteratorDebugBase<T>::GetVectorDebugInfo()->end);
		mPointer = pointer;
		
	}
	VectorIterator(const VectorIterator& other)
		:
		Base(other),
		mPointer(other.mPointer)
	{
		if (Base::IsValid())
		{
			Base::AddToContainer(this);
		}
	}
	VectorIterator() = default;
	~VectorIterator()
	{
		if (Base::IsValid())
		{
			Base::RemoveFromContainer(this);
		}
	}
	[[nodiscard]] bool operator==(const VectorIterator& other) const
	{
		assert(Base::IsValid());
		return mPointer == other.mPointer;
	}
	[[nodiscard]] bool operator!=(const VectorIterator& other) const
	{
		return !(mPointer == other.mPointer);
	}

	[[nodiscard]] T& operator*() const
	{
		assert(mPointer <= VectorIteratorDebugBase<T>::GetVectorDebugInfo()->end);
		return *mPointer;
	}
	[[nodiscard]] T& operator->() const
	{
		assert(mPointer <= VectorIteratorDebugBase<T>::GetVectorDebugInfo()->end);
		return *mPointer;
	}

	VectorIterator& operator++()
	{
		assert(mPointer <= VectorIteratorDebugBase<T>::GetVectorDebugInfo()->end);
		mPointer++;
		return *this;
	}
	VectorIterator operator++(int)
	{
		assert(mPointer <= VectorIteratorDebugBase<T>::GetVectorDebugInfo()->end);
		VectorIterator temporary = *this;
		++(*this);
		return temporary;
	}

	// LegacyBidirectionalIterator operations
	VectorIterator& operator--()
	{
		assert(mPointer > VectorIteratorDebugBase<T>::GetVectorDebugInfo()->begin);
		mPointer--;
		return *this;
	}
	VectorIterator operator--(int)
	{
		// The assertion occurs inside operator--
		VectorIterator temporary = *this;
		--(*this);
		return temporary;
	}

	// LegacyRandomAccessIterator operations
	VectorIterator& operator+=(difference_type value)
	{
		assert(mPointer + value >= VectorIteratorDebugBase<T>::GetVectorDebugInfo()->begin);
		assert(mPointer + value <= VectorIteratorDebugBase<T>::GetVectorDebugInfo()->end);
		mPointer += value;
		return *this;
	}
	VectorIterator& operator-=(difference_type value)
	{
		// The assertion occurs inside operator+=
		return (*this) += -value;
	}
	[[nodiscard]] VectorIterator operator+(difference_type value) const
	{
		// The assertion occurs inside operator+=
		VectorIterator temporary = *this;
		temporary += value;
		return temporary;
	}
	[[nodiscard]] VectorIterator operator-(difference_type value) const
	{
		// The assertion occurs inside operator+
		return (*this) + (-value);
	}
	[[nodiscard]] difference_type operator-(const VectorIterator& other) const
	{
		return difference_type(mPointer - other.mPointer);
	}

	[[nodiscard]] T& operator[](difference_type index) const
	{
		assert(mPointer + index >= VectorIteratorDebugBase<T>::GetVectorDebugInfo()->begin);
		assert(mPointer + index < VectorIteratorDebugBase<T>::GetVectorDebugInfo()->end);
		return *(mPointer + index);
	}

	[[nodiscard]] bool operator<(const VectorIterator& other) const
	{
		return mPointer < other.mPointer;
	}
	[[nodiscard]] bool operator>(const VectorIterator& other) const
	{
		return mPointer > other.mPointer;
	}
	[[nodiscard]] bool operator<=(const VectorIterator& other) const
	{
		return mPointer <= other.mPointer;
	}
	[[nodiscard]] bool operator>=(const VectorIterator& other) const
	{
		return mPointer >= other.mPointer;
	}
private:
	using Base = VectorIteratorBase<T>;
	friend class VectorDebugInfo<T>;
	T* mPointer = nullptr;
};

template<class T>
VectorIterator<T> operator+(ptrdiff_t value,
							VectorIterator<T> iterator)
{
	iterator += value;
	return iterator;
}

template<class T>
VectorIterator<T> operator-(ptrdiff_t value,
							VectorIterator<T> iterator)
{
	iterator -= value;
	return iterator;
}
