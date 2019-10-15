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

namespace Elysium
{
	namespace Model
	{
		template <typename T, unsigned U>
		class Puzzle
		{
		public:
			Puzzle();
			Puzzle(T* values);
			~Puzzle() = default;
			Puzzle(const Puzzle<T, U>& src);
			Puzzle<T, U>& operator=(const Puzzle<T, U>& rhs);
			template <typename E,unsigned M>
			friend std::ostream& operator<<(std::ostream& out, const Puzzle<E, M>& puzzle);
			template <typename E, unsigned M>
			friend std::istream& operator>>(std::istream& in, Puzzle<E, M>& puzzle);
			const bool InsertValue(T newValue);
			void InsertEmptyBlock();
			const unsigned GetSize() const;
		private:
			std::vector<T> m_State; //todo: Replace this with a matrix maybe? 
			PuzzleAttributes m_Attributes;
		};

		template <typename T, unsigned U>
		Puzzle<T, U>::Puzzle() : m_Attributes(PuzzleAttributes())
		{
			m_State.reserve(U * U);
		}

		template <typename T, unsigned U>
		Puzzle<T, U>::Puzzle(T* values)
		{
			for (int i = 0; i < U*U-1; ++i)
			{
				m_State.push_back(values[i]);
			}
			m_State.push_back(22); 
		}

		template <typename T, unsigned U>
		Puzzle<T, U>::Puzzle(const Puzzle<T, U>& src)
		{
			m_State.clear();	//todo: Verify if this is necessary.
			m_State(src.m_State);
		}

		template <typename T, unsigned U>
		Puzzle<T,U>& Puzzle<T, U>::operator=(const Puzzle<T,U>& rhs)
		{
			m_State.clear();	//todo: Verify if this is necessary.
			m_State = rhs.m_State;
			return *this;
		}

		template <typename T, unsigned U>
		const bool Puzzle<T, U>::InsertValue(T newValue) //todo: Replace with emplace back for variadric arguments for speed increase?
		{
			if (!(std::any_of(m_State.begin(), m_State.end(), [&](T val) { return val == newValue; })))
			{
				m_State.push_back(newValue); //todo: Verify that this is as fast as emplace_back
				return true;
			}
			return false;
		}

		template <typename T, unsigned U>
		void Puzzle<T, U>::InsertEmptyBlock()
		{
			m_State.push_back(22); //todo: Verify this value isn't referenced in the inversion calculations.
		}

		template <typename E, unsigned M>
		std::ostream& operator<<(std::ostream& out, const Puzzle<E,M>& puzzle) 
		{
			for (unsigned i = 0; i < puzzle.m_State.size() - 1; i++)
			{
				out << puzzle.m_State[i] << " ";
				if ((i + 1) % M == 0)	out << "\n";
			}
			out << " \n";
			out << puzzle.m_Attributes;
			return out;
		}

		template <typename E, unsigned M>
		std::istream& operator>>(std::istream& in, Puzzle<E, M>& puzzle)
		{
			E temp;
			for (int i = 0; i < (M*M-1); i++)
			{
				in >> temp;
				puzzle.InsertValue(temp);
			}
			puzzle.InsertEmptyBlock();
			in >> puzzle.m_Attributes;
			return in;
		}

		template <typename T, unsigned U>
		const unsigned Puzzle<T,U>::GetSize() const
		{
			return U * U;
		}
	}
}