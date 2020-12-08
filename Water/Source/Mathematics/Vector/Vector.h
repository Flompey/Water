#pragma once
#include "RawVector.h"
#include "Source/Iterator/RandomAccessIterator.h"

template<class T, int N>
requires (N >= 2)
class BasicVector : public RawVector<T, N>
{
public:
	using Iterator = RandomAccessIterator<T>;
	template<class... ArgTypes>
	requires(sizeof...(ArgTypes) == N)
	BasicVector(ArgTypes... arguments)
		:
		Base{ arguments... }
	{
		Base::InitializeContainerDebugInfo(Base::GetPointerToData(), Base::GetPointerToData() + N);
	}

	// Any time we construct a "BasicVector" we need to initialize the container info, hence
	// we overload the copy and default constructors
	BasicVector()
	{
		Base::InitializeContainerDebugInfo(Base::GetPointerToData(), Base::GetPointerToData() + N);
	}
	BasicVector(const BasicVector& other)
		:
		Base(other)
	{
		Base::InitializeContainerDebugInfo(Base::GetPointerToData(), Base::GetPointerToData() + N);
	}
	
	[[nodiscard]] Iterator begin()
	{
		return Iterator(Base::GetPointerToData(), Base::GetContainerDebugInfo());
	}
	[[nodiscard]] Iterator end()
	{
		return Iterator(Base::GetPointerToData()+N, Base::GetContainerDebugInfo());
	}

	[[nodiscard]] T& operator[](size_t index)
	{
		return Base::GetPointerToData()[index];
	}
	[[nodiscard]] const T& operator[](size_t index) const
	{
		return Base::GetPointerToData()[index];
	}

	[[nodiscard]] T GetLengthSquared() const
	{
		T lengthSquared = (T)0;
		for (int i = 0; i < N; ++i)
		{
			lengthSquared += pow((*this)[i], 2);
		}
		return lengthSquared;
	}
	[[nodiscard]] T GetLength() const
	{
		return sqrt(GetLengthSquared());
	}
	void Normalize()
	{
		(*this) /= GetLength();
	}
	[[nodiscard]] BasicVector GetNormalized()
	{
		BasicVector temporary = *this;
		return temporary.Normalize();
	}
	[[nodiscard]] T Dot(const BasicVector& other) const
	{
		T dot = (T)0;
		for (int i = 0; i < N; ++i)
		{
			dot += (*this)[i] * other[i];
		}
		return dot;
	}
	[[nodiscard]] BasicVector Cross(const BasicVector& other) const
	{
		static_assert(N == 3,
			"You only cross vectors of size 3");
		const Base& otherBase = other;
		return BasicVector(Base::y * otherBase.z - Base::z * otherBase.y,
						   Base::z * otherBase.x - Base::x * otherBase.z,
						   Base::x * otherBase.y - Base::y * otherBase.x);
	}

	BasicVector& operator+=(const BasicVector& other)
	{
		for (int i = 0; i < N; ++i)
		{
			(*this)[i] += other[i];
		}
	}
	BasicVector& operator-=(const BasicVector& other)
	{
		for (int i = 0; i < N; ++i)
		{
			(*this)[i] -= other[i];
		}
	}
	BasicVector& operator*=(T value)
	{
		for (int i = 0; i < N; ++i)
		{
			(*this)[i] *= value;
		}
	}
	BasicVector& operator/=(T value)
	{
		for (int i = 0; i < N; ++i)
		{
			(*this)[i] /= value;
		}
	}

	[[nodiscard]] BasicVector operator+(const BasicVector& other) const
	{
		BasicVector sum;
		for (int i = 0; i < N; ++i)
		{
			sum[i] = (*this)[i] + other[i];
		}
		return sum;
	}
	[[nodiscard]] BasicVector operator-(const BasicVector& other) const
	{
		BasicVector difference;
		for (int i = 0; i < N; ++i)
		{
			difference[i] = (*this)[i] - other[i];
		}
		return difference;
	}
	[[nodiscard]] BasicVector operator*(T value) const
	{
		BasicVector product;
		for (int i = 0; i < N; ++i)
		{
			product[i] = (*this)[i] * value;
		}
		return product;
	}
	[[nodiscard]] BasicVector operator/(T value) const
	{
		BasicVector quotient;
		for (int i = 0; i < N; ++i)
		{
			quotient[i] = (*this)[i] / value;
		}
		return quotient;
	}
private:
	using Base = RawVector<T, N>;
};

template<class T, int N>
std::ostream& operator<<(std::ostream& ostream, const BasicVector<T, N>& vector)
{
	return ostream << vector.GetString();
}

template<class T>
using BasicVector2 = BasicVector<T, 2>;

template<class T>
using BasicVector3 = BasicVector<T, 3>;

template<class T>
using BasicVector4 = BasicVector<T, 4>;

using Vector2 = BasicVector2<float>;
using Vector3 = BasicVector3<float>;
using Vector4 = BasicVector4<float>;