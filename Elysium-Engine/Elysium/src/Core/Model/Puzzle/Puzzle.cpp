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
			for (int i = 0; i < m_Size * m_Size - 1; ++i)
			{
				m_State.push_back(values[i]);
			}
			m_State.push_back(m_Size * m_Size + m_Size+1);
		}

		Puzzle::Puzzle(const Puzzle& src)
		{
			m_State.clear();	//todo: Verify if this is necessary.
			m_State = src.m_State; //todo: Verify this works.
			m_Size = src.m_Size;
			m_Attributes = src.m_Attributes;
		}

		Puzzle& Puzzle::operator=(const Puzzle& rhs)
		{
			m_State.clear();	//todo: Verify if this is necessary.
			m_State = rhs.m_State;
			m_Size = rhs.m_Size;
			m_Attributes = rhs.m_Attributes;
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

		void Puzzle::InsertEmptyBlock()
		{
			m_State.push_back((m_Size*m_Size + m_Size+1)); //todo: Verify this value isn't referenced in the inversion calculations.
		}

		std::ostream& operator<<(std::ostream& out, const Puzzle& puzzle)
		{
			for (unsigned i = 0; i < puzzle.m_State.size() - 1; i++)
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
			in >> puzzle.m_Attributes;
			return in;
		}

		const int Puzzle::GetSize() const
		{
			return m_Size * m_Size;
		}
	}
}