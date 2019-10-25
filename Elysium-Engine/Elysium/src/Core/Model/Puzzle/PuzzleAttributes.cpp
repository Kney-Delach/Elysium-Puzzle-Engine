/**
 * FILENAME		: PuzzleAttributes.h
 * Name			: Ori Lazar
 * Student ID	: b9061712
 * Date			: 15/10/2019
 * Description	: This file contains the implementation for the puzzle attributes container,
 *				  i.e the continuous row/column/reverse counts of a puzzle.
 */
#include "empch.h"
#include "Core/Model/Puzzle/PuzzleAttributes.h"

namespace Elysium
{
	namespace Model
	{
		void PuzzleAttributes::InitAttributes(const std::vector<int>* partialsVector)
		{
			m_ContinuousRows = 0;
			m_PartialIndexes = *partialsVector;
			m_StartConfigPartials.reserve(partialsVector->size());
			for (unsigned i = 0; i < m_StartConfigPartials.capacity(); i++)
				m_StartConfigPartials.emplace_back(0);
			m_ValidTurnsPartials.reserve(partialsVector->size());
			for (unsigned i = 0; i < m_ValidTurnsPartials.capacity(); i++)
				m_ValidTurnsPartials.emplace_back(0);
		}

		void PuzzleAttributes::SetContinuousValues(BigInteger value)
		{
			SetContRows(value);
			SetContCols(value);
			SetContRowsRev(value);
			SetContColsRev(value);
		}
		void PuzzleAttributes::SetPartialAttribute(int index, BigInteger& value)
		{
			if (index >= m_PartialIndexes.size())
			{
				//todo throw an index out of bounds exception
			}
			else
			{
				m_ValidTurnsPartials[index] = value;
			}
		}
		void PuzzleAttributes::SetPartialStartConfigAttribute(int index, BigInteger& value)
		{
			if (index >= m_PartialIndexes.size())
			{
				//todo throw an index out of bounds exception
			}
			else
			{
				m_StartConfigPartials[index] = value;
			}
		}
	}
}