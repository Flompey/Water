#pragma once
#include "Source/Iterator/Container/ContainerBase.h"

template<class T, int N>
struct RawVector : public ContainerBase<T>
{
	RawVector(const std::initializer_list<T>& values)
	{
		std::copy(values.begin(), values.end(), this.values);
	}
	RawVector()
	{
		for (int i = 0; i < N; ++i)
		{
			values[i] = (T)0;
		}
	}

	T* GetPointerToData()
	{
		return &values[0];
	}
	const T* GetPointerToData() const
	{
		return &values[0];
	}

	T values[N];
};

template<class T>
struct RawVector<T, 2> : public ContainerBase<T>
{
	RawVector(T x, T y)
		:
		x(x),
		y(y)
	{}
	RawVector() = default;

	T* GetPointerToData()
	{
		return &x;
	}
	const T* GetPointerToData() const
	{
		return &x;
	}

	T x = (T)0;
	T y = (T)0;
};

template<class T>
struct RawVector<T, 3> : public ContainerBase<T>
{
	RawVector(T x, T y, T z)
		:
		x(x),
		y(y),
		z(z)
	{}
	RawVector() = default;

	T* GetPointerToData()
	{
		return &x;
	}
	const T* GetPointerToData() const
	{
		return &x;
	}

	T x = (T)0;
	T y = (T)0;
	T z = (T)0;
};

template<class T>
struct RawVector<T, 4> : public ContainerBase<T>
{
	RawVector(T x, T y, T z, T w)
		:
		x(x),
		y(y),
		z(z),
		w(w)
	{}
	RawVector() = default;

	T* GetPointerToData()
	{
		return &x;
	}
	const T* GetPointerToData() const
	{
		return &x;
	}

	T x = (T)0;
	T y = (T)0;
	T z = (T)0;
	T w = (T)1;
};