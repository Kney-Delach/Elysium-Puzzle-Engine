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
#include "Core/Model/BruteForce/IComparable.h"
 //todo: Replace InsertValue function with emplace_back function, using variadric arguments.
 //todo: Optimize ProcessContinuousValues and IsRowContinuous, as these are used for the (currently) too slow brute force search.

namespace Elysium
{
	namespace Model
	{
		enum ActionDirection { LEFT, RIGHT, UP, DOWN};

		class Puzzle : public Brute::IComparable
		{
		public:
			Puzzle() = default;
			~Puzzle() = default;
			Puzzle(int size);
			Puzzle(int size, int* values);
			Puzzle(const Puzzle& src);
			Puzzle(const Puzzle& src, const ActionDirection direction);
			Puzzle& operator=(const Puzzle& rhs);
			bool InsertValue(int newValue); 
			int GetSize() const;
			void RunPuzzleSolver(const std::vector<int>* partialsVector);
			int ProcessContinuousValues() const;
			void ActionUp();
			void ActionDown();
			void ActionRight();
			void ActionLeft();
			virtual int CompareTo(const IComparable& rhs) override;
			friend std::ostream& operator<<(std::ostream& out, const Puzzle& puzzle);
			friend std::istream& operator>>(std::istream& in, Puzzle& puzzle);
			__forceinline void InsertEmptyBlock()
			{
				m_State.push_back(INT_MAX);
			}
			__forceinline bool CanGoUp() const
			{
				return !(m_BlankPosition.first >= (m_Size - 1));
			}
			__forceinline bool CanGoDown() const
			{
				return !(m_BlankPosition.first <= 0);
			}
			__forceinline bool CanGoRight() const
			{
				return !(m_BlankPosition.second >= (m_Size - 1));
			}
			__forceinline bool CanGoLeft() const
			{
				return !(m_BlankPosition.second <= 0);
			}
			__forceinline PuzzleAttributes& GetAttributes()
			{
				return m_Attributes;
			}
			__forceinline std::pair<int, int>& GetBlankPosition()
			{
				return m_BlankPosition;
			}
			unsigned long long Factorial(const int x);
		private:
			void ProcessPuzzleLocalContinuousData();
			unsigned long long GetConsecutiveCount(std::vector<int> puzzle, int consecutiveValue) const;
			bool IsRowContinuous(int rowNumber) const;
		private:
			std::vector<int> m_State;
			int m_Size;
			std::pair<int, int> m_BlankPosition;
			PuzzleAttributes m_Attributes;
		};
	}
}