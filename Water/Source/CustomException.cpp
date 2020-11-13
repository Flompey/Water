#include "CustomException.h"

CustomException::CustomException(const std::string& message, const std::string& filename, int lineNumber)
	:
	std::exception(message.c_str()),
	mFilename(filename),
	mLineNumber(lineNumber)
{
	mFullMessage =
		"Filename: " + mFilename + "\n"
		"Line number: " + std::to_string(mLineNumber) + "\n" + 
		 std::string(std::exception::what());
}

const char* CustomException::what() const
{
	return mFullMessage.c_str();
}