#pragma once
#include "RandomAccessIteratorDebugBase.h"
#include "RandomAccessIteratorReleaseBase.h"
#include "IteratorMacro.h"

#if ENABLE_ITERATOR_ERROR_CHECKING
template<class T>
using RandomAccessIteratorBase = RandomAccessIteratorDebugBase<T>;
#else
template<class T>
using RandomAccessIteratorBase = RandomAccessIteratorReleaseBase<T>;
#endif

#if ENABLE_ITERATOR_ERROR_CHECKING
#define ASSERT_POINTER_IS_GREATER_THAN_BEGIN(pointer) \
	assert(pointer > RandomAccessIteratorDebugBase<T>::GetContainerDebugInfo()->begin)
#define ASSERT_POINTER_IS_GEQUAL_TO_BEGIN(pointer) \
	assert(pointer >= RandomAccessIteratorDebugBase<T>::GetContainerDebugInfo()->begin)
#define ASSERT_POINTER_IS_LESS_THAN_END(pointer) \
	assert(pointer < RandomAccessIteratorDebugBase<T>::GetContainerDebugInfo()->end)
#define ASSERT_POINTER_IS_LEQUAL_TO_END(pointer) \
	assert(pointer <= RandomAccessIteratorDebugBase<T>::GetContainerDebugInfo()->end)
#else
#define ASSERT_POINTER_IS_GREATER_THAN_BEGIN(pointer)
#define ASSERT_POINTER_IS_GEQUAL_TO_BEGIN(pointer)
#define ASSERT_POINTER_IS_LESS_THAN_END(pointer)
#define ASSERT_POINTER_IS_LEQUAL_TO_END(pointer)
#endif
template<class T>
class RandomAccessIterator : public RandomAccessIteratorBase<T>
{
public:
	using iterator_category = std::random_access_iterator_tag;
	using value_type = T;
	using difference_type = ptrdiff_t;
	using pointer = T*;
	using reference = T&;

	RandomAccessIterator(T* pointer, ContainerDebugInfo<T>* vectorDebugInfo)
	{
		Base::SetContainerDebugInfo(vectorDebugInfo);
		Base::AddToContainer();
		assert(pointer);
		ASSERT_POINTER_IS_GEQUAL_TO_BEGIN(pointer);
		ASSERT_POINTER_IS_LEQUAL_TO_END(pointer);
		mPointer = pointer;
		
	}
	RandomAccessIterator() = default;
	~RandomAccessIterator()
	{
		if (Base::HasContainer())
		{
			Base::RemoveFromContainer();
		}
	}

	[[nodiscard]] bool operator==(const RandomAccessIterator& other) const
	{
		assert(IsCompatible(other));
		return mPointer == other.mPointer;
	}
	[[nodiscard]] bool operator!=(const RandomAccessIterator& other) const
	{
		// The assertion occurs inside operator==
		return !(mPointer == other.mPointer);
	}

	[[nodiscard]] T& operator*() const
	{
		assert(Base::HasContainer());
		ASSERT_POINTER_IS_GEQUAL_TO_BEGIN(mPointer);
		ASSERT_POINTER_IS_LESS_THAN_END(mPointer);
		return *mPointer;
	}
	[[nodiscard]] T& operator->() const
	{
		// The assertion occurs inside operator*
		return *(*this);
	}

	RandomAccessIterator& operator++()
	{
		assert(Base::HasContainer());
		ASSERT_POINTER_IS_LESS_THAN_END(mPointer);
		mPointer++;
		return *this;
	}
	RandomAccessIterator operator++(int)
	{
		// The assertion occurs inside operator++
		RandomAccessIterator temporary = *this;
		++(*this);
		return temporary;
	}

	// LegacyBidirectionalIterator operations
	RandomAccessIterator& operator--()
	{
		assert(Base::HasContainer());
		ASSERT_POINTER_IS_GREATER_THAN_BEGIN(mPointer);
		mPointer--;
		return *this;
	}
	RandomAccessIterator operator--(int)
	{
		// The assertion occurs inside operator--
		RandomAccessIterator temporary = *this;
		--(*this);
		return temporary;
	}

	// LegacyRandomAccessIterator operations
	RandomAccessIterator& operator+=(difference_type value)
	{
		assert(Base::HasContainer());
		ASSERT_POINTER_IS_GEQUAL_TO_BEGIN(mPointer + value);
		ASSERT_POINTER_IS_LEQUAL_TO_END(mPointer + value);
		mPointer += value;
		return *this;
	}
	RandomAccessIterator& operator-=(difference_type value)
	{
		// The assertion occurs inside operator+=
		return (*this) += -value;
	}
	[[nodiscard]] RandomAccessIterator operator+(difference_type value) const
	{
		// The assertion occurs inside operator+=
		RandomAccessIterator temporary = *this;
		temporary += value;
		return temporary;
	}
	[[nodiscard]] RandomAccessIterator operator-(difference_type value) const
	{
		// The assertion occurs inside operator+=
		return (*this) + (-value);
	}
	[[nodiscard]] difference_type operator-(const RandomAccessIterator& other) const
	{
		assert(IsCompatible(other));
		return difference_type(mPointer - other.mPointer);
	}

	[[nodiscard]] T& operator[](difference_type index) const
	{
		assert(Base::HasContainer());
		ASSERT_POINTER_IS_GEQUAL_TO_BEGIN(mPointer);
		ASSERT_POINTER_IS_LESS_THAN_END(mPointer);
		return *(mPointer + index);
	}

	[[nodiscard]] bool operator<(const RandomAccessIterator& other) const
	{
		assert(IsCompatible(other));
		return mPointer < other.mPointer;
	}
	[[nodiscard]] bool operator>(const RandomAccessIterator& other) const
	{
		// The assertion occurs inside operator<
		return other < *this;
	}
	[[nodiscard]] bool operator<=(const RandomAccessIterator& other) const
	{
		// The assertion occurs inside operator<
		return !(*this > other);
	}
	[[nodiscard]] bool operator>=(const RandomAccessIterator& other) const
	{
		// The assertion occurs inside operator<
		return !(*this < other);
	}

	private:
		bool IsCompatible(const RandomAccessIterator& other) const
		{
			return Base::GetContainerDebugInfo() == other.GetContainerDebugInfo();
		}
private:
	using Base = RandomAccessIteratorBase<T>;
	friend class ContainerDebugInfo<T>;
	T* mPointer = nullptr;
};

template<class T>
RandomAccessIterator<T> operator+(ptrdiff_t value,
	RandomAccessIterator<T> iterator)
{
	iterator += value;
	return iterator;
}

template<class T>
RandomAccessIterator<T> operator-(ptrdiff_t value,
	RandomAccessIterator<T> iterator)
{
	iterator -= value;
	return iterator;
}
