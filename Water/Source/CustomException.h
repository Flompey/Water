#pragma once
#include "PrecompiledHeader.h"
#include <exception>

#define CreateCustomException(message) CustomException(message, __FILE__, __LINE__)

class CustomException : public std::exception
{
public:
	CustomException(const std::string& message, const std::string& filename, int lineNumber);

	const char* what() const override;
private:
	std::string mFilename;
	int mLineNumber = 0;
	
	std::string mFullMessage;
};