/**
 * FILENAME		: PuzzleAttributes.h
 * Name			: Ori Lazar
 * Student ID	: b9061712
 * Date			: 15/10/2019
 * Description	: This file contains the implementation for the puzzle attributes container, 
 *				  i.e the continuous row/column/reverse counts of a puzzle.
 */
#pragma once
#include <vector>

namespace Elysium
{
	namespace Model
	{
		class PuzzleAttributes
		{
		public:
			PuzzleAttributes() = default;
			~PuzzleAttributes() = default;
			void InitAttributes(const std::vector<int>* partialsVector);
			inline friend std::ostream& operator<<(std::ostream& out, const PuzzleAttributes& attributes);
			inline friend std::istream& operator>>(std::istream& in, PuzzleAttributes& attributes);
			void SetContinuousValues(int value);

		private: //todo: inline functionality
			void SetContRows(int value);
			void SetContCols(int value);
			void SetContRowsRev(int value);
			void SetContColsRev(int value);
			int m_ContinuousRows = -1; //todo: Replace this with arrays for N size cases
			int m_ContinuousCols = 0;
			int m_ContinuousRowsRev = 0;
			int m_ContinuousColsRev = 0;
			std::vector<int> m_PartialIndexes;
			std::vector<int> m_StartConfigPartials;
			std::vector<int> m_ValidTurnsPartials;
		};

		std::ostream& operator<<(std::ostream& out,const PuzzleAttributes& attributes) //todo: Replace with an faster implementation.
		{

			if (attributes.m_ContinuousRows == -1) return out;	//Todo: Replace with the following if doesn't work. "attributes.NotProcessed()"
			out << "row = " << attributes.m_ContinuousRows << "\ncolumn = " << attributes.m_ContinuousCols
				<< "\nreverse row = " << attributes.m_ContinuousRowsRev << "\nreverse column = " << attributes.m_ContinuousColsRev << "\n";

			if (attributes.m_PartialIndexes.empty())
				return out;
			out << "(total for row & column, including reverse, in this configuration)\n";
			for (unsigned i = 0; i < attributes.m_PartialIndexes.size(); i++)
			{
				out << attributes.m_PartialIndexes[i] << " = " << attributes.m_StartConfigPartials[i] << "\n";
			}
			out << "(total for row & column, including reverse, for all valid turns)\n";
			for (unsigned i = 0; i < attributes.m_PartialIndexes.size(); i++)
			{
				out << attributes.m_PartialIndexes[i] << " = " << attributes.m_ValidTurnsPartials[i] << "\n";
			}
			return out;
		}

		std::istream& operator>>(std::istream& in, PuzzleAttributes& attributes)
		{
			return in;
		}
	}
}