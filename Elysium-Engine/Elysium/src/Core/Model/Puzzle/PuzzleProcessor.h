/**
 * FILENAME		: PuzzleProcessor.h
 * Name			: Ori Lazar
 * Student ID	: b9061712
 * Date			: 13/10/2019
 * Description	: This header contains the template implementation of the puzzle processor structure,
 *				  it stores a reference to all of the puzzles inserted into the system in a stack structure
 *				  which is planned to be utilized to output the data to streams.
 */
#pragma once
#include "Core/Model/DataStructures/Stack.h"
#include <iostream>

namespace Elysium
{
	namespace Model
	{
		template <typename T>
		class PuzzleProcessor
		{
		public:
			PuzzleProcessor(int capacity = 100); 
			~PuzzleProcessor() = default;
			T* InsertPuzzle(const T&  object);

			template <typename E>
			friend std::ostream& operator<<(std::ostream& out, PuzzleProcessor<E>& processor);
		private:
			Stack<T> m_Stack;
		};

		template <typename T>
		PuzzleProcessor<T>::PuzzleProcessor(int capacity) : m_Stack(capacity)
		{
		}

		template <typename T>
		T* PuzzleProcessor<T>::InsertPuzzle(const T& object)
		{
			return m_Stack.Push(object);
		}

		template <typename E>
		std::ostream& operator<<(std::ostream& out, PuzzleProcessor<E>& processor)
		{
			unsigned size = processor.m_Stack.GetSize();
			out << size << "\n";
			for (unsigned  i = 0; i < size; i++)
			{
				out << processor.m_Stack.Top() << "\n";
				processor.m_Stack.Pop();
			}
			return out;
		}
	}
}