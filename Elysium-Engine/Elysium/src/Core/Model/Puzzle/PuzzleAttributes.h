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
			void SetContinuousValues(unsigned long long value);
			void SetPartialAttribute(int index, unsigned long long& value);
			void SetPartialStartConfigAttribute(int index, unsigned long long& value);

			inline friend std::ostream& operator<<(std::ostream& out, const PuzzleAttributes& attributes);
			inline friend std::istream& operator>>(std::istream& in, PuzzleAttributes& attributes);
		private: 
			__forceinline void PuzzleAttributes::SetContRows(unsigned long long value)
			{
				m_ContinuousRows = value;
			}
			__forceinline void PuzzleAttributes::SetContCols(unsigned long long value)
			{
				m_ContinuousCols = value;
			}
			__forceinline void PuzzleAttributes::SetContRowsRev(unsigned long long value)
			{
				m_ContinuousRowsRev = value;
			}
			__forceinline void PuzzleAttributes::SetContColsRev(unsigned long long value)
			{
				m_ContinuousColsRev = value;
			}
		private:
			unsigned long long m_ContinuousRows = -1;
			unsigned long long m_ContinuousCols = 0;
			unsigned long long m_ContinuousRowsRev = 0;
			unsigned long long m_ContinuousColsRev = 0;
			std::vector<int> m_PartialIndexes;
			std::vector<unsigned long long> m_StartConfigPartials;
			std::vector<unsigned long long> m_ValidTurnsPartials;
		};

		std::ostream& operator<<(std::ostream& out,const PuzzleAttributes& attributes)
		{

			if (attributes.m_ContinuousRows == -1) return out;
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