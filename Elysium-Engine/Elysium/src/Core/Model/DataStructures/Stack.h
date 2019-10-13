/**
 * FILENAME		: Stack.h
 * Name			: Ori Lazar
 * Student ID	: b9061712
 * Date			: 13/10/2019
 * Description	: This file contains the implementation of a custom stack template, it is used to store puzzle configurations.
 */
#pragma once
#include "Core/Utility/Asserts.h"

namespace Elysium
{
	namespace Model
	{
		template <typename T>
		class Stack
		{
		public:
			Stack(unsigned capacity = 100);
			~Stack();
			Stack(const Stack<T>& rhs);
			Stack<T>& operator=(const Stack<T>& rhs);
			T* Push(const T& object); 
			void Pop();
			T& Top();
			const unsigned GetCapacity() const;
			const unsigned GetSize() const;
			const bool IsEmpty() const;
			const T& operator[] (unsigned index) const;
		private:
			unsigned m_Capacity;
			unsigned m_Size;
			T* m_pElements;
			Stack();
		};

		template <typename T>
		Stack<T>::Stack(unsigned capacity)
			: m_Capacity(capacity), m_Size(0), m_pElements(new T[capacity])
		{
		}

		template <typename T>
		Stack<T>::Stack(const Stack<T>& rhs)
			: m_Capacity(rhs.m_Capacity), m_Size(rhs.m_Size)
		{
			m_pElements = new T[m_Capacity];
			for (unsigned i = 0; i < m_Capacity; i++)	
				m_pElements[i] = rhs.m_pElements[i];
		}

		template <typename T>
		Stack<T>& Stack<T>::operator=(const Stack<T>& rhs) //todo: Verify copy requirement: [shallow or deep].
		{
			if (this == &rhs) return (*this);
			m_Capacity = rhs.GetCapacity();
			m_Size = rhs.GetSize();
			delete[] m_pElements;
			m_pElements = new T[m_Capacity];
			for (unsigned i = 0; i < m_Size(); i++)
				m_pElements[i] = rhs.m_pElements[i];
			return *this;
		}

		template <typename T>
		Stack<T>::~Stack()
		{
			delete[] m_pElements;
		}

		template <typename T>
		T* Stack<T>::Push(const T& object)
		{
			if (m_Size < m_Capacity)
			{
				m_pElements[m_Size++] = object;
				return &(m_pElements[m_Size - 1]); ;
			}
			return nullptr;
		}

		template <typename T>
		void Stack<T>::Pop()
		{
			if (!IsEmpty())	m_Size--;
		}

		template <typename T>
		T& Stack<T>::Top()
		{
			if (!IsEmpty())	return m_pElements[m_Size - 1];
			ASSERT(NULL, "[Stack<T>::Top] Undefined behaviour path reached!", true);
			//todo: Implement exception here.
		}

		template <typename T>
		const unsigned Stack<T>::GetCapacity() const
		{
			return m_Capacity;
		}

		template <typename T>
		const unsigned Stack<T>::GetSize() const
		{
			return m_Size;
		}

		template <typename T>
		const bool Stack<T>::IsEmpty() const
		{
			return m_Size == 0 ? true : false;
		}

		template <typename T>
		const T& Stack<T>::operator[](unsigned index) const
		{
			if (index < m_Capacity)	return m_pElements[m_Size - 1 - index];
			ASSERT(NULL, "[Stack<T>::[]Operator] Undefined behaviour path reached, attempting to access pointer outside of stack bounds!", true);
			//todo: Implement exception here.
		}

		template <typename T>
		Stack<T>::Stack()
		{
			ASSERT(NULL, "[Stack<T>::Default_Constructor] Undefined behaviour path reached, this constructor should never get called!", true);
			//todo: Implement exception here.
		}
	}
}