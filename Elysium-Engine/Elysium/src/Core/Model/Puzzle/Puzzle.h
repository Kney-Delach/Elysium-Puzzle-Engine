/**
 * FILENAME		: Puzzle.h
 * Name			: Ori Lazar
 * Student ID	: b9061712
 * Date			: 12/10/2019
 * Description	: This header contains the template implementation of the puzzle structure, which contains the attributes of the puzzle.
 *				  The values of puzzle are stored inside a std::vector.
 */
#pragma once
#include <vector>
#include "Core/Model/Puzzle/PuzzleAttributes.h"
#include <iostream> //todo: remove me

namespace Elysium
{
	namespace Model
	{
		class Puzzle
		{
		public:
			Puzzle() = default;
			~Puzzle() = default;
			Puzzle(int size);
			Puzzle(int size, int* values);
			Puzzle(const Puzzle& src);
			Puzzle& operator=(const Puzzle& rhs);
			bool InsertValue(int newValue); 
			void RunPuzzleSolver(std::vector<int>* partialsVector);
			__forceinline void InsertEmptyBlock()
			{
				m_State.push_back(INT_MAX);
			}
			friend std::ostream& operator<<(std::ostream& out, const Puzzle& puzzle);
			friend std::istream& operator>>(std::istream& in, Puzzle& puzzle);
		private:
			unsigned long long Factorial(const int x); //todo: Optimize with threading
			__forceinline void CalculateContinuousData()
			{
				m_Attributes.SetContinuousValues((CalculatePartialValue(m_Size)/4ull));//3ull * (Factorial((m_Size * m_Size - (m_Size + 1))) * (GetConsecutiveCount(m_State, m_Size)) / 2ull));
			}
			__forceinline unsigned long long CalculatePartialValue(int partialValue)
			{
				unsigned long long partialLong = static_cast<unsigned long long>(partialValue);
				int partialSizeArrangements = (m_Size - partialValue + 1) * m_Size - 1; // partialLong*(m_Size - partialLong + 1)*(m_Size - partialLong + 1) - 1;
				//unsigned long long partialSizeArrangements = ((m_Size - partialValue + 1) * m_Size) - 1; // partialLong*(m_Size - partialLong + 1)*(m_Size - partialLong + 1) - 1;
				unsigned long long consecutiveCount = GetConsecutiveCount(m_State, partialValue);
				unsigned long long otherValueArrangements = Factorial(m_Size*m_Size - partialValue - 1);
				return (4ull*(static_cast<unsigned long long>(partialSizeArrangements) * consecutiveCount * otherValueArrangements)/2ull);
			}
			unsigned long long CalculateStartConfigPartial(int consecutiveValue) const;
			unsigned long long GetConsecutiveCount(std::vector<int> puzzle, int consecutiveValue) const;
		private:
			int m_Size;
			std::vector<int> m_State;
			PuzzleAttributes m_Attributes;
		};
	}
}