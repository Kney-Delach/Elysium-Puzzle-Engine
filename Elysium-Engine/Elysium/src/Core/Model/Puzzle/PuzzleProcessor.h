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
#include <iostream>
#include "Core/Model/DataStructures/Stack.h"
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
			PuzzleProcessor(const PuzzleProcessor<T>& src) = delete;
			PuzzleProcessor<T>& operator=(const PuzzleProcessor<T>& rhs) = delete;
			T* InsertPuzzle(const T& object);
			T* InsertPuzzleFront(const T& object);
			void SetSize(unsigned capacity);
			template <typename E> friend std::ostream& operator<<(std::ostream& out, PuzzleProcessor<E>& processor);
			template <typename E> friend std::istream& operator>>(std::istream& out, PuzzleProcessor<E>& processor);
		private:
			Stack<T> m_Stack; //todo: Replace with std stack for faster implementation, as can use their EmplaceBack functionality.
		};

		template <typename T>
		PuzzleProcessor<T>::PuzzleProcessor(unsigned capacity) : m_Stack(capacity)
		{
		}

		template <typename T>
		T* PuzzleProcessor<T>::InsertPuzzle(const T& object) //todo: Replace with EmplaceBack function.
		{
			return m_Stack.Push(std::forward<const T&>(object));
		}

		template <typename T>
		T* PuzzleProcessor<T>::InsertPuzzleFront(const T& object) //todo: Replace with EmplaceBack function.
		{
			return m_Stack.PushFront(std::forward<const T&>(object));
		}
		template<typename T>
		void PuzzleProcessor<T>::SetSize(unsigned capacity)
		{
			m_Stack.SetCapacity(capacity);
		}


		template <typename E>
		std::ostream& operator<<(std::ostream & out, PuzzleProcessor<E> & processor) //todo: Implement a check whether writing solution or configs
		{
			unsigned size = processor.m_Stack.GetSize();
			out << size << "\n";
			for (unsigned i = 0; i < size; i++)
			{
				out << processor.m_Stack.Top() << "\n";
				processor.m_Stack.Pop();
			}
			return out;
		}
		template<typename E>
		std::istream& operator>>(std::istream& in, PuzzleProcessor<E>& processor)
		{
			std::string line;
			int numberOfConfigs;
			in >> numberOfConfigs;
			std::cout << numberOfConfigs << "\n";
			processor.m_Stack.SetCapacity(numberOfConfigs);
			for (int i = 0; i < numberOfConfigs; i++)
			{
				E* element = processor.InsertPuzzleFront(E());
				in >> *element;
			}
			return in;
		}
	}
}