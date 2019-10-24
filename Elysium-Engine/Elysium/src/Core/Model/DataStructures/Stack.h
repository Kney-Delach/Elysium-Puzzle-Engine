/**
 * FILENAME		: Stack.h
 * Name			: Ori Lazar
 * Student ID	: b9061712
 * Date			: 13/10/2019
 * Description	: This file contains the implementation of a custom stack template, it is used to store puzzle configurations.
                  This stack is implemented as a hybrid with deque insertion, which was necessary for serialization.
 */
#pragma once
#include "Core/Utility/Asserts.h"
#include "Core/Utility/InputHandler.h"
#include "Core/Exceptions/ElysiumExceptions.h"

namespace Elysium
{
	using namespace Exceptions;
	namespace Model
	{
		template <typename T>
		class Stack
		{
		public:
			Stack(int capacity = 10, int elementSize = 4);
			~Stack();
			Stack(const Stack<T>& rhs);
			Stack<T>& operator=(const Stack<T>& rhs);
			T* Push(const T& object);
			T* PushFront(const T& object) noexcept(false);// throw (StackOutOfBoundsAccessException);
			__forceinline void Pop();
			__forceinline T& Top() const;
			void SetCapacity(int capacity); 
			const int GetCapacity() const;
			const int GetSize() const;
			int GetElementSize() const; 
			const bool IsEmpty() const;
			T& operator[] (int index) const noexcept(false);// throw (StackOutOfBoundsAccessException);
			template <typename E> friend std::ostream& operator<<(std::ostream& out, Stack<E>& stack);
			template <typename E> friend std::istream& operator>>(std::istream& in, Stack<E>& stack);
		private:
			Stack() = delete;
			void ExpandStack();
		private:
			int m_Capacity;
			int m_Size;
			T* m_pElements;
			int m_ElementSize = 0; 
		};

		template <typename T>
		Stack<T>::Stack(int capacity, int elementSize)
			: m_Capacity(capacity), m_Size(0), m_pElements(new T[m_Capacity]), m_ElementSize(elementSize)
		{
			ASSERT(m_Capacity <= 0,"[Elysium::Model::Stack::Constructor] - Capacity should not be non-positive!",true) //todo: Potentially replace with an exception.
		}

		template <typename T>
		Stack<T>::~Stack()
		{
			delete[] m_pElements;
		}

		template <typename T>
		Stack<T>::Stack(const Stack<T>& rhs)
			: m_Capacity(rhs.m_Capacity), m_Size(rhs.m_Size), m_pElements(new T[m_Capacity]), m_ElementSize(rhs.m_ElementSize)
		{
			for (int i = 0; i < m_Capacity; i++)	
				m_pElements[i] = rhs.m_pElements[i];
		}

		template <typename T>
		Stack<T>& Stack<T>::operator=(const Stack<T>& rhs)
		{
			if (this == &rhs) return (*this);
			m_Capacity = rhs.GetCapacity();
			m_Size = rhs.GetSize();
			m_ElementSize = rhs.GetElementSize();
			delete[] m_pElements;
			m_pElements = new T[m_Capacity];
			for (int i = 0; i < m_Size; i++)
				m_pElements[i] = rhs.m_pElements[i];
			return *this;
		}

		template <typename T>
		T* Stack<T>::Push(const T& object)
		{
			if (m_Size < m_Capacity)
			{
				m_pElements[m_Size++] = object; //todo: Optimize: Performing a deep copy, implement emplace back instead.
				return &(m_pElements[m_Size - 1]);
			}
			ExpandStack();
			m_pElements[m_Size++] = object;
			return &(m_pElements[m_Size - 1]);
		}


		template <typename T>
		T* Stack<T>::PushFront(const T& object) noexcept(false) //throw (StackOutOfBoundsAccessException)
		{
			if (!(m_Size < m_Capacity))
				throw StackOutOfBoundsAccessException("[Stack::PushFront] - Attempting to push too much data onto the stack.", __FILE__, __LINE__, __FUNCTION__);
			m_Size++;
			m_pElements[m_Capacity-m_Size] = object; 
			return &(m_pElements[(m_Capacity-m_Size)]);
		}

		template <typename T>
		__forceinline void Stack<T>::Pop()
		{
			if (!IsEmpty())	m_Size--;
		}

		template <typename T>
		__forceinline T& Stack<T>::Top() const noexcept(false) //throw (StackOutOfBoundsAccessException)
		{
			if (IsEmpty())	
				throw StackOutOfBoundsAccessException("[Stack::Top] - Attempting to access data from the top of the stack whilst the stack is empty.", __FILE__, __LINE__, __FUNCTION__);
			return m_pElements[m_Size - 1];
		}

		template<typename T>
		void Stack<T>::SetCapacity(int capacity)
		{
			delete[] m_pElements;
			m_Capacity = capacity;
			m_Size = 0;
			m_pElements = new T[m_Capacity];
		}

		template <typename T>
		const int Stack<T>::GetCapacity() const
		{
			return m_Capacity;
		}

		template <typename T>
		const int Stack<T>::GetSize() const
		{
			return m_Size;
		}

		template <typename T>
		int Stack<T>::GetElementSize() const
		{
			return m_ElementSize;
		}

		template <typename T>
		const bool Stack<T>::IsEmpty() const
		{
			return m_Size == 0 ? true : false;
		}

		template <typename T>
		T& Stack<T>::operator[](int index) const noexcept(false) //throw (StackOutOfBoundsAccessException)
		{
			if (!(index < m_Capacity))	
				throw StackOutOfBoundsAccessException("[Stack::[]] - Attempting to access data from an index in the stack which hasn't been initialized.", __FILE__, __LINE__, __FUNCTION__);
			return m_pElements[m_Size - 1 - index];
		}

		template <typename T>
		void Stack<T>::ExpandStack()
		{
			Stack<T> temp = *this;
			delete[] m_pElements;
			m_Capacity = 2 * m_Capacity;

			m_pElements = new T[m_Capacity];
			for (int i = 0; i < m_Size; i++)
				m_pElements[i] = temp.m_pElements[i];
		}

		template<typename E>
		std::ostream& operator<<(std::ostream& out, Stack<E>& stack)
		{
			int stackSize = stack.m_Size;
			try
			{
				out << stack.m_Size << "\n";
				for (int i = 0; i < stackSize; i++)
				{
					out << stack.Top() << "\n";
					stack.Pop();
				}
				stack.m_Size = stackSize;
				return out;
			}catch(const StackOutOfBoundsAccessException& soe)
			{
				stack.m_Size = stackSize;
				LOG_EXCEPTION(soe)
				out << "\n\nStackOutOfBoundsException occured during writing of stack.\n\n";
				return out;
			}
		}

		template<typename E>
		std::istream& operator>>(std::istream& in, Stack<E>& stack)
		{
			try
			{
				int puzzleSize = Utility::InputHandler::HandleInput("Enter the dimension value of the configurations in the file:\n-> ", 10000, 2); 	//todo: Validate dimension.
				std::string line;
				int numberOfConfigs;
				in >> numberOfConfigs;
				stack.SetCapacity(numberOfConfigs);
				stack.m_ElementSize = puzzleSize;
				for (int i = 0; i < numberOfConfigs; i++)
				{
					E* element = stack.PushFront(E(puzzleSize));
					in >> *element;
				}
				return in;
			}catch(const StackOutOfBoundsAccessException& soe)
			{
				LOG_EXCEPTION(soe)
				return in;
			}
		}
	}
}
