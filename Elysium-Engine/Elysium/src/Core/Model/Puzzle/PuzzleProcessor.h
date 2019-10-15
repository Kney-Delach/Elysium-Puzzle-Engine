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
//todo: Implement an EmplaceBack function to forward the construction of a puzzle directly to the stack, rather than producing a copy.

namespace Elysium
{
	namespace Model
	{
		template <typename T>
		class PuzzleProcessor 
		{
		public:
			PuzzleProcessor(unsigned capacity = 100);
			~PuzzleProcessor() = default;
			PuzzleProcessor(const PuzzleProcessor<T>& src);
			PuzzleProcessor<T>& operator=(const PuzzleProcessor<T>& rhs);
			T* InsertPuzzle(const T&  object);
			void ProcessPuzzles();//todo: Implement choice flags.
			template <typename E> friend std::ostream& operator<<(std::ostream& out, PuzzleProcessor<E>& processor);
		private:
			Stack<T> m_Stack; //todo: Replace with std stack for faster implementation, as can use their EmplaceBack functionality.
		};

		template <typename T>
		PuzzleProcessor<T>::PuzzleProcessor(unsigned capacity) : m_Stack(capacity)
		{
		}

		template <typename T>
		PuzzleProcessor<T>::PuzzleProcessor(const PuzzleProcessor<T>& src) //todo: Implement this copy constructor.
		{
		}

		template <typename T>
		PuzzleProcessor<T>& PuzzleProcessor<T>::operator=(const PuzzleProcessor<T>& rhs) //todo: Implement this assignment operator.
		{
		}

		template <typename T>
		T* PuzzleProcessor<T>::InsertPuzzle(const T& object) //todo: Replace with EmplaceBack function.
		{
			return m_Stack.Push(std::forward<const T&>(object));
		}

		template<typename T>
		void PuzzleProcessor<T>::ProcessPuzzles()
		{
			std::cout << *this; //todo: Implement calls to further process functionality here.
		}

		template <typename E>
		std::ostream& operator<<(std::ostream& out, PuzzleProcessor<E>& processor) //todo: Implement a check whether writing solution or configs
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