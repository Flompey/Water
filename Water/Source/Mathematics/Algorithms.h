#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

template<class T>
requires(std::is_floating_point_v<T>)
std::string ConvertFloatingPointToRoundedString(const T value, const size_t decimalCount)
{
	std::string string = std::to_string(value);
	const size_t decimalPointPos = string.find('.');
	if (decimalPointPos != std::string::npos)
	{
		string = string.substr(0, decimalPointPos + decimalCount + 1);
	}
	return string;
}

template<class T>
requires(std::is_floating_point_v<T>)
T Round(const T value, const size_t decimalCount)
{
	T adjuster = (T)std::pow(10.0, (double)decimalCount);
	return std::floor(value * adjuster + (T)0.5) / adjuster;
}

template<class T>
requires(std::is_floating_point_v<T>)
T ConvertDegreesToRadians(T degrees)
{
	return (degrees / (T)360) * (T)2 * (T)M_PI;
}
