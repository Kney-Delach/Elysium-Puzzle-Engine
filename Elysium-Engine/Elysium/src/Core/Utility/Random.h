/**
 * FILENAME		: Random.h
 * Name			: Ori Lazar
 * Student ID	: b9061712
 * Date			: 15/10/2019
 * Description	: This header contains an implementation of a random number generator which produces discrete random numbers. 
 */
#pragma once
#include <ctime>  

namespace Elysium
{
	namespace Utility
	{
		class Random
		{
		public:
			static void Randomize(int* arr, int size);
		private:
			static void Swap(int* a, int* b);
			Random() = default;
			~Random() = default;
		};

		inline void Random::Swap(int* valOne, int* valTwo) //todo: Replace this with a bitwise swap.
		{
			int temp = *valOne;
			*valOne = *valTwo;
			*valTwo = temp;
		}

		inline void Random::Randomize(int* arr, int size)
		{ 
			srand(static_cast<int>(time(NULL)));
			for (int i = size - 1; i > 0; i--)
			{  
				int j = rand() % (i + 1);
				Swap(&arr[i], &arr[j]);
			}
		}
	}
}