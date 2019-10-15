/**
 * FILENAME		: PuzzleAttributes.h
 * Name			: Ori Lazar
 * Student ID	: b9061712
 * Date			: 15/10/2019
 * Description	: This file contains the implementation for the puzzle attributes container, 
 *				  i.e the continuous data of a puzzle.
 */
#pragma once

class PuzzleAttributes
{
public:
	PuzzleAttributes(int cRow = 0, int cCols = 0, int cRowRev = 0,int cColRev = 0) 
		: m_ContinuousRows(cRow),    m_ContinuousCols(cCols), m_ContinuousRowsRev(cRowRev), m_ContinuousColsRev(cColRev) {};
	~PuzzleAttributes() = default;
	friend std::ostream& operator<<(std::ostream& out, const PuzzleAttributes attributes); 

private:
	int m_ContinuousRows;
	int m_ContinuousCols;
	int m_ContinuousRowsRev;
	int m_ContinuousColsRev;
};

std::ostream& operator<<(std::ostream& out, const PuzzleAttributes attributes) //todo: Replace with an faster implementation.
{
	out << "row = " << attributes.m_ContinuousRows << "\ncolumn = " << attributes.m_ContinuousCols 
	<< "\nreverse row = " << attributes.m_ContinuousRowsRev << "\nreverse column = " << attributes.m_ContinuousColsRev << "\n";
	return out;
}