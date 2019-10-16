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
		class Puzzle
		{
		public:
			Puzzle() = default;
			Puzzle(int size);
			Puzzle(int size, int* values);
			~Puzzle() = default;
			Puzzle(const Puzzle& src);
			Puzzle& operator=(const Puzzle& rhs);
			friend std::ostream& operator<<(std::ostream& out, const Puzzle& puzzle);
			friend std::istream& operator>>(std::istream& in, Puzzle& puzzle);
			const bool InsertValue(int newValue);
			void InsertEmptyBlock();
			const int GetSize() const;
		private:
			int m_Size; //todo: Check if to move this further down for faster access 
			std::vector<int> m_State; //todo: Replace this with a matrix maybe? 
			PuzzleAttributes m_Attributes;
		};


	}
}