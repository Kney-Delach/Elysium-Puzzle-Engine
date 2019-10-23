/**
 * FILENAME		: Puzzle.h
 * Name			: Ori Lazar
 * Student ID	: b9061712
 * Date			: 12/10/2019
 * Description	: This cpp file contains the template implementation of the puzzle structure, which contains the attributes of the puzzle.
 *				  The values of puzzle are stored inside a std::vector.
 * Note			: The empty square is denoted as the integer value 22, this is so that it does not interfere with inversion calculation
 *				  for configuration validation which is a potential extension of this project.
 */
#include "empch.h"
#include "Core/Model/Puzzle/Puzzle.h"

namespace Elysium
{
	namespace Model
	{
		Puzzle::Puzzle(int size) 
			: m_Size(size), m_Attributes(PuzzleAttributes()), m_BlankPosition(std::make_pair((m_Size - 1), (m_Size - 1)))
		{
			m_State.reserve(m_Size * m_Size);
		}

		Puzzle::Puzzle(int size, int* values) 
			: m_Size(size), m_Attributes(PuzzleAttributes()), m_BlankPosition(std::make_pair((m_Size - 1), (m_Size - 1)))
		{
			for (int i = 0; i < m_Size * m_Size - 1; i++)
			{
				m_State.push_back(values[i]);
			}
			InsertEmptyBlock();
		}

		Puzzle::Puzzle(const Puzzle& src)
		{
			m_Size = src.m_Size;
			m_State.clear();	//todo: Verify if this is necessary.
			m_State = src.m_State; //todo: Verify this works.
			m_Attributes = src.m_Attributes;
			m_BlankPosition = src.m_BlankPosition;
		}

		Puzzle& Puzzle::operator=(const Puzzle& rhs)
		{
			m_Size = rhs.m_Size;
			m_State.clear();	//todo: Verify if this is necessary.
			m_State = rhs.m_State;
			m_Attributes = rhs.m_Attributes;
			m_BlankPosition = rhs.m_BlankPosition;

			return *this;
		}

		const bool Puzzle::InsertValue(int newValue) //todo: Replace with emplace back for variadric arguments for speed increase?
		{
			if (!(std::any_of(m_State.begin(), m_State.end(), [&](int val) { return val == newValue; })))
			{
				m_State.push_back(newValue); //todo: Verify that this is as fast as emplace_back
				return true;
			}
			return false;
		}

		std::ostream& operator<<(std::ostream& out, const Puzzle& puzzle)
		{
			for (unsigned i = 0; i < puzzle.m_State.size()- 1; i++)
			{
				out << puzzle.m_State[i] << " ";
				if (((i + 1) % puzzle.m_Size )== 0)		out << "\n";
			}
			out << " \n";
			out << puzzle.m_Attributes;
			return out;
		}

		std::istream& operator>>(std::istream& in, Puzzle& puzzle)
		{
			int temp;
			for (int i = 0; i < (puzzle.m_Size * puzzle.m_Size - 1); i++)
			{
				in >> temp;
				puzzle.m_State.push_back(temp);
			}
			puzzle.InsertEmptyBlock();
			return in;
		}

		const int Puzzle::GetSize() const
		{
			return m_Size * m_Size;
		}

		void Puzzle::RunPuzzleSolver(const std::vector<int>* partialsVector)
		{
			m_Attributes.InitAttributes(partialsVector);
			ProcessPuzzle();
		}

		void Puzzle::ProcessPuzzle()
		{
			m_Attributes.SetContinuousValues(GetConsecutiveCount(m_State, m_Size));
		}

		int Puzzle::operator()(int rowPos, int colPos) //todo: Test this function
		{
			//todo: Implement error checking.
			if((0 <= rowPos < m_Size) && (0 <= colPos < m_Size))
				return m_State[rowPos*m_Size + colPos];
			else
			{
				return -1; //todo: Implement error handling mechanisms
			}
		}

		int Puzzle::GetConsecutiveCount(std::vector<int> puzzle, int consecutiveValue) //todo: Move this somewhere else.
		{
			if (puzzle.empty())
				return 0;
			int consCount = 0;
			std::sort(puzzle.begin(), puzzle.end());
			for (int i = 0; i < puzzle.size(); i++)
			{
				if (i == puzzle.size() - consecutiveValue)
					break;
				bool consecutive = true;
				for (int j = 0; j < consecutiveValue-1; j++)
				{
					if ((puzzle[i+j] + 1 - puzzle[i+j + 1]) != 0)
					{
						consecutive = false;
						break;
					}
				}
				if(consecutive)
					consCount++; 
			}
			return consCount;  //todo: Verify this returns correctly
		}
		int Puzzle::CompareTo(const Brute::IComparable& rhs)
		{
			const Puzzle* rhsPuzzle = static_cast<const Puzzle*>(&rhs); //todo: Verify this casts the memory address of the Comparable object
			ASSERT(!(rhsPuzzle->m_Size == m_Size), "[IComparable::Puzzle] - Puzzles being compared must be of the same size.", true) //todo: Verify this asserts correctly, maybe replace with exception.
				if (m_State == rhsPuzzle->m_State)
					return 1;
			return 0;
		}

		bool Puzzle::ActionUp()
		{
			if (m_BlankPosition.first >= (m_Size - 1))
				return false;
			m_State.at(m_BlankPosition.first * m_Size + m_BlankPosition.second) = m_State.at((m_BlankPosition.first + 1) * m_Size + m_BlankPosition.second);
			m_BlankPosition.first = m_BlankPosition.first + 1;
			m_State.at(m_BlankPosition.first * m_Size + m_BlankPosition.second) = -1;
			return true;
		}

		bool Puzzle::ActionDown()
		{
			if (m_BlankPosition.first <= 0)
				return false;
			m_State.at(m_BlankPosition.first * m_Size + m_BlankPosition.second) = m_State.at((m_BlankPosition.first - 1) * m_Size + m_BlankPosition.second);
			m_BlankPosition.first = m_BlankPosition.first - 1;
			m_State.at(m_BlankPosition.first * m_Size + m_BlankPosition.second) = -1;
			return true;
		}

		bool Puzzle::ActionRight()
		{
			if (m_BlankPosition.second >= (m_Size - 1))
				return false;
			m_State.at(m_BlankPosition.first * m_Size + m_BlankPosition.second) = m_State.at(m_BlankPosition.first * m_Size + m_BlankPosition.second + 1);
			m_BlankPosition.second = m_BlankPosition.second + 1;
			m_State.at(m_BlankPosition.first * m_Size + m_BlankPosition.second) = -1;
			return true;
		}

		bool Puzzle::ActionLeft()
		{
			if(m_BlankPosition.second <= 0)
				return false;
			m_State.at(m_BlankPosition.first * m_Size + m_BlankPosition.second) = m_State.at(m_BlankPosition.first * m_Size + m_BlankPosition.second-1);
			m_BlankPosition.second = m_BlankPosition.second - 1;
			m_State.at(m_BlankPosition.first * m_Size + m_BlankPosition.second) = -1;
			return true;
		}

		bool Puzzle::IsRowContinuous(int rowNumber) const
		{
			int rowIndex = rowNumber * m_Size;
			for (int i = 0; i < m_Size-1; i++)
			{
				if (!((m_State[rowIndex + i] - m_State[rowIndex + (i + 1)]) == -1))
					return false;
			}
			return true;
		}
		int Puzzle::ProcessContinuousValues()
		{
			if (!(m_BlankPosition.first == (m_Size - 1) && m_BlankPosition.second == (m_Size - 1)))
				return 0;
			else
			{
				int totalContinuous = 0; 
				for (int i = 0; i < m_Size; i++)
				{
					if (IsRowContinuous(i))
						totalContinuous++;
				}
				return totalContinuous;
			}
		}
	}
}
