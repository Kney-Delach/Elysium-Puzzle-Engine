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
//todo: Mention in README that I am choosing to use templates for this as it allows for the extension of N dimensional puzzles.
//todo: Test if faster to force inline getters and setters.

namespace Elysium
{
	namespace Model
	{
		template <typename T, unsigned U>
		class Puzzle
		{
		public:
			Puzzle();
			~Puzzle() = default;
			Puzzle(const Puzzle<T, U>& src);
			Puzzle<T, U>& operator=(const Puzzle<T, U>& rhs);
			template <typename E,unsigned M>
			friend std::ostream& operator<<(std::ostream& out, const Puzzle<E, M>& puzzle); 
			const bool InsertValue(T newValue);
			void InsertEmptyBlock();
			void SetRevContColCount(T count);
			void SetContColCount(T count);
			void SetRevContRowCount(T count);
			void SetContRowCount(T count);

			const T GetRevContColCount() const;
			const T GetContColCount() const;
			const T GetRevContRowCount() const;
			const T GetContRowCount() const;
			const unsigned GetSize() const;
		private:
			std::vector<T> m_pState;
			T m_RevContCols;
			T m_ContCols;
			T m_RevContRows;
			T m_ContRows;
		};

		template <typename T, unsigned U>
		Puzzle<T,U>::Puzzle() :
			m_RevContCols(0), m_ContCols(0),
			m_RevContRows(0), m_ContRows(0)
		{
			m_pState.reserve(U * U);
		}

		template <typename T, unsigned U>
		Puzzle<T, U>::Puzzle(const Puzzle<T, U>& src) :
			m_pState(src.m_pState), 
			m_RevContCols(src.m_RevContCols),
			m_ContCols(src.m_ContCols),
			m_RevContRows(src.m_RevContRows), 
			m_ContRows(src.m_ContRows)
		{
		}

		template <typename T, unsigned U>
		Puzzle<T,U>& Puzzle<T, U>::operator=(const Puzzle<T,U>& rhs)
		{
			m_pState		= rhs.m_pState;
			m_RevContCols	= rhs.m_RevContCols; 
			m_ContCols		= rhs.m_ContCols;
			m_RevContRows	= rhs.m_RevContRows; 
			m_ContRows		= rhs.m_ContRows;
			return *this;
		}

		template <typename T, unsigned U>
		const bool Puzzle<T, U>::InsertValue(T newValue)
		{
			if (!(std::any_of(m_pState.begin(), m_pState.end(), [&](T val) { return val == newValue; })))
			{
				m_pState.push_back(newValue);
				return true;
			}
			return false;
		}

		template <typename T, unsigned U>
		void Puzzle<T, U>::InsertEmptyBlock()
		{
			m_pState.push_back(22); //todo: Don't reference this value in inversion calculations

		}

		template <typename E, unsigned M>
		std::ostream& operator<<(std::ostream& out, const Puzzle<E,M>& puzzle) //todo: Replace with an faster implementation
		{
			for (unsigned i = 0; i < puzzle.m_pState.size() - 1; i++) 
			{
				out << puzzle.m_pState[i] << " ";
				if ((i + 1) % M == 0)	out << "\n";
			}
			out << " \n";
			return out;
		}

		template <typename T, unsigned U>
		void Puzzle<T, U>::SetRevContColCount(T count)
		{
			m_RevContCols = count;
		}

		template <typename T, unsigned U>
		void Puzzle<T, U>::SetContColCount(T count)
		{
			m_ContCols = count;
		}

		template <typename T, unsigned U>
		void Puzzle<T, U>::SetRevContRowCount(T count)
		{
			m_RevContRows = count;
		}

		template <typename T, unsigned U>
		void Puzzle<T, U>::SetContRowCount(T count)
		{
			m_ContRows = count;
		}

		template <typename T, unsigned U>
		const T Puzzle<T, U>::GetRevContColCount() const
		{
			return m_RevContCols;
		}

		template <typename T, unsigned U>
		const T Puzzle<T, U>::GetContColCount() const
		{
			return m_ContCols;
		}

		template <typename T, unsigned U>
		const T Puzzle<T, U>::GetRevContRowCount() const
		{
			return m_RevContRows;
		}

		template <typename T, unsigned U>
		const T Puzzle<T, U>::GetContRowCount() const
		{
			return m_ContRows;
		}

		template <typename T, unsigned U>
		const unsigned Puzzle<T,U>::GetSize() const
		{
			return U * U;
		}
	}
}