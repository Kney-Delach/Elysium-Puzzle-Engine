/**
 * FILENAME		: Timer.h
 * Name			: Ori Lazar
 * Student ID	: b9061712
 * Date			: 23/10/2019
 * Description	: This file contains the implementation of a timer to benchmark the time taken to search for solutions in the brute force implementation. 
                  This can be used in the extension of this engine, so I am not removing it.
 */
#pragma once
#include <iostream>
#include <chrono>

namespace Elysium
{
	namespace Utility
	{
		class Timer
		{
		public:
			Timer()
			{
				std::cout << "Timer Constructed\n";
				m_StartTimepoint = std::chrono::high_resolution_clock::now();
			}
			~Timer()
			{
				auto endTimepoint = std::chrono::high_resolution_clock::now();
				auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
				auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();
				auto duration = end - start;
				double ms = duration * 0.0001;
				int micro = 230;
				std::cout << duration << (char)micro << "s (" << ms << "ms)\n";
				std::cout << ms << "ms\n";
			}
		private:
			std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
		};
	}
}