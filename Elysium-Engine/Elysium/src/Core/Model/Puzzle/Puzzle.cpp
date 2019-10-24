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
			: m_Size(size), m_Attributes(PuzzleAttributes())
		{
			m_State.reserve(m_Size * m_Size);
		}

		Puzzle::Puzzle(int size, int* values) 
			: m_Size(size), m_Attributes(PuzzleAttributes())
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
			m_State.clear();
			m_State = src.m_State;
			m_Attributes = src.m_Attributes;
		}

		Puzzle& Puzzle::operator=(const Puzzle& rhs)
		{
			m_Size = rhs.m_Size;
			m_State.clear();
			m_State = rhs.m_State;
			m_Attributes = rhs.m_Attributes;
			return *this;
		}

		bool Puzzle::InsertValue(int newValue)
		{
			if (!(std::any_of(m_State.begin(), m_State.end(), [&](int val) { return val == newValue; })))
			{
				m_State.push_back(newValue);
				return true;
			}
			return false;
		}

		void Puzzle::RunPuzzleSolver(std::vector<int>* partialsVector)
		{
			m_Attributes.InitAttributes(partialsVector);
			CalculateContinuousData();
			for (unsigned i = 0; i < partialsVector->size(); i++)
			{
				BigInteger configPartialValue = CalculateStartConfigPartial((*partialsVector)[i]);;
				m_Attributes.SetPartialStartConfigAttribute(i, configPartialValue);

				BigInteger turnsPartialValue = CalculatePartialValue((*partialsVector)[i]);
				m_Attributes.SetPartialAttribute(i, turnsPartialValue);
			}
		}

		BigInteger Puzzle::Factorial(const int x) //todo: Alter this into a recursive solution
		{
			BigInteger facSum = 1;
			for (int count = x; count > 0; count--)
				facSum = facSum * count;
			return facSum;
		}

		BigInteger Puzzle::GetConsecutiveCount(std::vector<int> puzzle, int consecutiveValue) const
		{
			if (puzzle.empty())
				return 0;
			BigInteger consCount = 0;
			std::sort(puzzle.begin(), puzzle.end());
			for (unsigned i = 0; i < puzzle.size()-(consecutiveValue-1); i++)
			{				
				if ((puzzle[i] - puzzle[i + consecutiveValue - 1]) == (1-consecutiveValue))
					consCount += 1;
			}
			return consCount;
		}

		BigInteger Puzzle::CalculateStartConfigPartial(int consecutiveValue) const
		{
			BigInteger consCount = 0;

			for (int i = 0; i < m_Size; i++) //todo: optimize this row search
			{
				int totalContinuous = 0; 
				for (int j = 0; j < m_Size-1; j++)
				{
					if ((m_State[i * m_Size + j] - m_State[i * m_Size + j + 1]) == -1)
						totalContinuous += 1;
					else
						totalContinuous = 0;

					if (totalContinuous == (consecutiveValue - 1))
					{
						consCount += 1;
						totalContinuous--;
					}
				}
			}
			for (int i = 0; i < m_Size; i++) //todo: optimize this reverse row search
			{
				int totalContinuous = 0;
				for (int j = 0; j < m_Size - 1; j++)
				{
					if ((m_State[i * m_Size + (m_Size - j- 1)] - m_State[i * m_Size + (m_Size  - j - 2)]) == -1)
						totalContinuous += 1;
					else
						totalContinuous = 0;

					if (totalContinuous == (consecutiveValue - 1))
					{
						consCount += 1;
						totalContinuous--;
					}
				}
			}
			for (int i = 0; i < m_Size; i++) //todo: optimize this column search
			{
				int totalContinuous = 0;
				for (int j = 0; j < m_Size - 1; j++)
				{
					if ((m_State[i + m_Size * j] - m_State[i + m_Size * (j + 1)]) == -1)
						totalContinuous += 1;
					else
						totalContinuous = 0;

					if (totalContinuous == (consecutiveValue - 1))
					{
						consCount += 1;
						totalContinuous--;
					}
				}
			}
			for (int i = 0; i < m_Size; i++) //todo: optimize this reverse column search
			{
				int totalContinuous = 0;
				for (int j = 0; j < m_Size - 1; j++)
				{
					if ((m_State[i + m_Size * (m_Size - 1 - j)] - m_State[i + m_Size * (m_Size - 2 - j)]) == -1)
						totalContinuous += 1;
					else
						totalContinuous = 0;

					if (totalContinuous == (consecutiveValue - 1))
					{
						consCount += 1;
						totalContinuous--;
					}
				}
			}

			return consCount;
		}
		std::ostream& operator<<(std::ostream& out, const Puzzle& puzzle)
		{
			for (unsigned i = 0; i < puzzle.m_State.size() - 1; i++)
			{
				out << puzzle.m_State[i] << " ";
				if (((i + 1) % puzzle.m_Size) == 0)		out << "\n";
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
	}
}