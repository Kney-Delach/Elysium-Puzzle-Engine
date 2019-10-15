/**
 * FILENAME		: Random.h
 * Name			: Ori Lazar
 * Student ID	: b9061712
 * Date			: 15/10/2019
 * Description	: This header contains an implementation of a random number generator which produces discrete random numbers. 
 */
#pragma once
#include <stdlib.h>  
#include <time.h>  

namespace Elysium
{
	namespace Utility
	{
		class Random //todo: Implement a template here to fit in with the rest of the system
		{
		public:
			Random() = default;
			~Random() = default;
			void Randomize(unsigned* arr, unsigned size);
		private:
			void Swap(unsigned* a, unsigned* b);
		};

		void Random::Swap(unsigned* valOne, unsigned* valTwo) //todo: Replace this with a bitwise swap.
		{
			unsigned temp = *valOne;
			*valOne = *valTwo;
			*valTwo = temp;
		}

		void Random::Randomize(unsigned* arr, unsigned size)
		{ 
			srand(static_cast<unsigned>(time(NULL)));
			for (int i = size - 1; i > 0; i--)
			{  
				int j = rand() % (i + 1);
				Swap(&arr[i], &arr[j]);
			}
		}
	}
}