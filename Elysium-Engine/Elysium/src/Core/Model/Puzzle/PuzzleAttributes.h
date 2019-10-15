/**
 * FILENAME		: PuzzleAttributes.h
 * Name			: Ori Lazar
 * Student ID	: b9061712
 * Date			: 15/10/2019
 * Description	: This file contains the implementation for the puzzle attributes container, 
 *				  i.e the continuous row/column/reverse counts of a puzzle.
 */
#pragma once
//todo: Implement getters and setters for attributes.

namespace Elysium
{
	namespace Model
	{
		class PuzzleAttributes
		{
		public:
			PuzzleAttributes(int cRow = -1, int cCols = 0, int cRowRev = 0, int cColRev = 0) :
				m_ContinuousRows(cRow), m_ContinuousCols(cCols), m_ContinuousRowsRev(cRowRev), m_ContinuousColsRev(cColRev)	{}
			~PuzzleAttributes() = default;
			friend std::ostream& operator<<(std::ostream& out, const PuzzleAttributes& attributes);
			friend std::istream& operator>>(std::istream& in, PuzzleAttributes& attributes);
			__forceinline bool NotProcessed() const { return m_ContinuousRows == -1 ? true : false; }
		private:
			int m_ContinuousRows;
			int m_ContinuousCols;
			int m_ContinuousRowsRev;
			int m_ContinuousColsRev;
		};

		std::ostream& operator<<(std::ostream& out,const PuzzleAttributes& attributes) //todo: Replace with an faster implementation.
		{
			if (attributes.NotProcessed()) return out;
			out << "row = " << attributes.m_ContinuousRows << "\ncolumn = " << attributes.m_ContinuousCols
				<< "\nreverse row = " << attributes.m_ContinuousRowsRev << "\nreverse column = " << attributes.m_ContinuousColsRev << "\n";
			return out;
		}
		std::istream& operator>>(std::istream& in, PuzzleAttributes& attributes)
		{
			attributes.m_ContinuousRows = 0;
			return in;
		}
	}
}