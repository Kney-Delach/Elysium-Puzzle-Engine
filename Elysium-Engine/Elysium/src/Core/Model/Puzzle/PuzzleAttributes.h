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
#include <boost/multiprecision/cpp_int.hpp>
namespace Elysium
{
	namespace Model
	{
		using  BigInteger = boost::multiprecision::cpp_int;

		class PuzzleAttributes
		{
		public:
			PuzzleAttributes() = default;
			~PuzzleAttributes() = default;
			void InitAttributes(const std::vector<int>* partialsVector);
			void SetContinuousValues(BigInteger value);
			void SetPartialAttribute(int index, BigInteger& value);
			void SetPartialStartConfigAttribute(int index, BigInteger& value);
			inline friend std::ostream& operator<<(std::ostream& out, const PuzzleAttributes& attributes);
			inline friend std::istream& operator>>(std::istream& in, PuzzleAttributes& attributes);
		private: 
			__forceinline void PuzzleAttributes::SetContRows(BigInteger value)
			{
				m_ContinuousRows = value;
			}
			__forceinline void PuzzleAttributes::SetContCols(BigInteger value)
			{
				m_ContinuousCols = value;
			}
			__forceinline void PuzzleAttributes::SetContRowsRev(BigInteger value)
			{
				m_ContinuousRowsRev = value;
			}
			__forceinline void PuzzleAttributes::SetContColsRev(BigInteger value)
			{
				m_ContinuousColsRev = value;
			}
		private:
			BigInteger m_ContinuousRows = -1;
			BigInteger m_ContinuousCols = 0;
			BigInteger m_ContinuousRowsRev = 0;
			BigInteger m_ContinuousColsRev = 0;
			std::vector<int> m_PartialIndexes;
			std::vector<BigInteger> m_StartConfigPartials;
			std::vector<BigInteger> m_ValidTurnsPartials;
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