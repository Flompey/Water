#pragma once
#include "RawVectorDebugBase.h"
#include "RawVectorReleaseBase.h"

#ifdef DEBUG
template<class T>
using RawVectorBase = RawVectorDebugBase<T>;
#else
template<class T>
using RawVectorBase = RawVectorReleaseBase<T>;
#endif

template<class T, int N>
struct RawVector : public RawVectorBase<T>
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
struct RawVector<T, 2> : public RawVectorBase<T>
{
	RawVector(T x, T y)
		:
		x(x),
		y(y)
	{}
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
struct RawVector<T, 3> : public RawVectorBase<T>
{
	RawVector(T x, T y, T z)
		:
		x(x),
		y(y),
		z(z)
	{}

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
struct RawVector<T, 4> : public RawVectorBase<T>
{
	RawVector(T x, T y, T z, T w)
		:
		x(x),
		y(y),
		z(z),
		w(w)
	{}
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