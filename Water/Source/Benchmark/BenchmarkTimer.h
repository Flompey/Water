#pragma once
#include <chrono>
#include "BenchmarkManager.h"
#include <thread>

namespace benchmark
{
	template<class T>
	concept Clock = requires
	{
		typename T::rep;
		typename T::period;
		typename T::duration;
		typename T::time_point;
		T::is_steady;
		T::now();
	};

	template<Clock C>
	class BasicTimer
	{
	public:
		BasicTimer(const std::string& name)
			:
			mName(name)
		{
			mStartTimePoint = mClock.now();
		}
		~BasicTimer()
		{
			const auto startDuration = 
				std::chrono::duration_cast<std::chrono::microseconds>(mStartTimePoint.time_since_epoch());
			const auto endDuration = 
				std::chrono::duration_cast<std::chrono::microseconds>(mClock.now().time_since_epoch());

			const long long duration = (endDuration - startDuration).count();
			const long long startTimepoint = startDuration.count();

			// We hash the thread id in order to convert it to an unsigned int
			const unsigned int hashedThreadId = (unsigned int)std::hash<std::thread::id>()(std::this_thread::get_id());
			benchmark::Manager::Get().Benchmark(
				benchmark::data::Timing{ mName, startTimepoint, duration, hashedThreadId });
		}
		// One should not be able to copy nor move a "BasicTimer" instance
		BasicTimer(const BasicTimer& other) = delete;
		BasicTimer& operator=(const BasicTimer& other) = delete;
		BasicTimer(BasicTimer&& other) = delete;
		BasicTimer& operator=(BasicTimer&& other) = delete;
	private:
		C mClock;
		typename C::time_point mStartTimePoint;
		std::string mName;
	};

	using Timer = BasicTimer<std::chrono::high_resolution_clock>;
}