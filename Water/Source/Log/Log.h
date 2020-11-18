#pragma once

#define LOGGING 1

#if LOGGING
#define LOG(message) std::cout << message
#else
#define LOG(message)
#endif