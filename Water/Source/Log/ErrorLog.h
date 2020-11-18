#pragma once

#define ERROR_LOGGING 1

#if ERROR_LOGGING
#define ERROR_LOG(message) std::cerr \
<< "{" << std::endl << "Error:" << std::endl << message << std::endl \
<< std::endl << "Caught at: " << std::endl << "Filename: " << __FILE__ << std::endl \
<< "Line number: " << __LINE__ << std::endl << "}" << std::endl << std::endl;
#else
#define ERROR_LOG(message)
#endif