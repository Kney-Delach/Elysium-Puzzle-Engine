/**
 * FILENAME		: Puzzle.h
 * Name			: Ori Lazar
 * Student ID	: b9061712
 * Date			: 12/10/2019
 * Description	: This header contains the template implementation of the puzzle structure, which contains the attributes of the puzzle.
 *				  The values of puzzle are stored inside a std::vector.
 * Note			: The empty square is denoted as the integer value 22, this is so that it does not interfere with inversion calculation  
 *				  for configuration validation which is a potential extension of this project.
 */
#pragma once
#include <vector>
#include "Core/Model/Puzzle/PuzzleAttributes.h"
#include "Core/Model/BruteForce/IComparable.h"
#include <limits>
#include <math.h>

namespace Elysium
{
	namespace Model
	{
		enum ActionDirection { LEFT, RIGHT, UP, DOWN};

		class Puzzle : public Brute::IComparable
		{
		public:
			Puzzle() = default;
			Puzzle(int size);
			Puzzle(int size, int* values);
			~Puzzle() = default;
			Puzzle(const Puzzle& src);
			Puzzle(const Puzzle& src, const ActionDirection direction);

			Puzzle& operator=(const Puzzle& rhs);
			const bool InsertValue(int newValue);
			const int GetSize() const;
			void RunPuzzleSolver(const std::vector<int>* partialsVector);
			void ProcessPuzzle();
			void ActionUp();
			void ActionDown();
			void ActionRight();
			void ActionLeft();
			__forceinline void InsertEmptyBlock()
			{
				m_State.push_back(-1);
			}
			__forceinline bool CanGoUp()
			{
				if (m_BlankPosition.first >= (m_Size - 1))
					return false;
				return true;
			}
			__forceinline bool CanGoDown()
			{
				if (m_BlankPosition.first <= 0)
					return false;
				return true;
			}
			__forceinline bool CanGoRight()
			{
				if (m_BlankPosition.second >= (m_Size - 1))
					return false;
				return true;
			}
			__forceinline bool CanGoLeft()
			{
				if (m_BlankPosition.second <= 0)
					return false;
				return true;
			}
			int ProcessContinuousValues(); 
			bool IsRowContinuous(int rowNumber) const;
			virtual int CompareTo(const IComparable& rhs) override;
			inline std::vector<int> GetState()
			{
				return m_State;
			}
			inline PuzzleAttributes& GetAttributes()
			{
				return m_Attributes;
			}
			inline std::pair<int, int>& GetBlankPosition()
			{
				return m_BlankPosition;
			}
			friend std::ostream& operator<<(std::ostream& out, const Puzzle& puzzle);
			friend std::istream& operator>>(std::istream& in, Puzzle& puzzle);
		private:
			int GetConsecutiveCount(std::vector<int> puzzle, int consecutiveValue);
		private:
			std::vector<int> m_State;
			int m_Size;
			unsigned long long m_UId;
			std::pair<int, int> m_BlankPosition;
			PuzzleAttributes m_Attributes;
		};
	}
}