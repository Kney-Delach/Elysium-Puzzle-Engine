#pragma once
#include <algorithm>
#include <type_traits>
#include <vector>

#include "IComparable.h"

namespace Elysium
{
	namespace Brute
	{
		template <typename T>
		struct node
		{
			static_assert(std::is_base_of<Model::Puzzle, T>::value, "T must derive from interfaces::IComparable");
		public:
			node(T& item, int possibleChildren);
			node(const node<T>& src); //todo: verify this copy constructor works
			~node();
			__forceinline T& GetItem();
			void AddChild(node<T>* pNode);
			node<T>** GetChildAtIndex(int index);
			void SetChildAtIndex(int index, node<T>* value);
			int GetChildrenSize() const; 
			const int CompareTo(node<T>& rhs);
			template <typename E>
			friend std::ostream& operator<<(std::ostream& out, const node<E>& value);
		protected:
			T m_Item;
			std::vector<node<T>*> m_Children;
		};

		template <typename T>
		node<T>::node(T& item, int possibleChildren)
			: m_Item(item)
		{
			m_Children.reserve(possibleChildren);
		}

		template<typename T>
		inline node<T>::node(const node<T>& src)
		{
			m_Item = src.m_Item;
			m_Children.reserve(2);
		}

		template <typename T>
		node<T>::~node() //todo: Implement memory removal
		{
		}

		template <typename T>
		__forceinline T& node<T>::GetItem()
		{
			return m_Item;
		}

		template <typename T>
		void node<T>::AddChild(node<T>* pNode)
		{
			m_Children.push_back(pNode);
		}

		template <typename T>
		node<T>** node<T>::GetChildAtIndex(int index)
		{
			return &(m_Children[index]);
		}

		template<typename T>
		inline void node<T>::SetChildAtIndex(int index, node<T>* value)
		{
			//todo: Implement error handling mechanisms
			m_Children[index] = value;
		}


		template <typename T>
		inline int node<T>::GetChildrenSize() const
		{
			return m_Children.size();
		}

		template <typename T>
		const int node<T>::CompareTo(node<T>& rhs)
		{
			return m_Item.CompareTo(rhs.GetItem());
		}

		template <typename E>
		std::ostream& operator<<(std::ostream& out, const node<E>& value)
		{
			out << "Node Item: " << value.m_Item;
			out << " \n";
			return out;
		}
	}
}