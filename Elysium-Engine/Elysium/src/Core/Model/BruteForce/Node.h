#pragma once
#include <algorithm>
#include <type_traits>
#include "Core/Model/BruteForce/IComparable.h"

namespace Elysium
{
	namespace Brute
	{
#pragma region NODE_DECLARATION
		template <typename T>
		struct node
		{
			static_assert(std::is_base_of<IComparable, T>::value, "[node<T>]: T must derive from interfaces::IComparable");
		public:
			node(T& item, node* pLeftChild, node* pRightChild);
			~node();
			const T& GetItem() const;
			node<T>** GetLeftChild();
			node<T>** GetRightChild();
			auto GetItemValue();
			void SetRightChild(node<T>* pNode);
			void SetLeftChild(node<T>* pNode);
			bool IsLeaf() const;
			int GetHeight() const;
			const int CompareTo(const T& rhs);
		protected:
			T m_Item;
			node* m_LeftChild;
			node* m_RightChild;
		};
#pragma endregion NODE_DECLARATION

#pragma region NODE_CONSTRUCTOR
		// ----------------- Constructor / Destructor ----------------- //

		template <typename T>
		node<T>::node(T& item, node* pLeftChild, node* pRightChild)
			: m_Item(item), m_LeftChild(pLeftChild), m_RightChild(pRightChild)
		{
		}

		template <typename T>
		node<T>::~node()
		{
		}
#pragma endregion NODE_CONSTRUCTOR

#pragma region NODE_GETTERS
		// ----------------- Getter Methods ----------------- //

		template <typename T>
		const T& node<T>::GetItem() const
		{
			return m_Item;
		}

		template <typename T>
		node<T>** node<T>::GetLeftChild()
		{
			return &m_LeftChild;
		}

		template <typename T>
		node<T>** node<T>::GetRightChild()
		{
			return &m_RightChild;
		}

		template <typename T>
		auto node<T>::GetItemValue()
		{
			return m_Item.GetValue();
		}
#pragma endregion NODE_GETTERS

#pragma region NODE_SETTERS
		// ----------------- Setter Methods ----------------- // 

		template <typename T>
		void node<T>::SetRightChild(node<T>* pNode)
		{
			m_RightChild = pNode;
		}

		template <typename T>
		void node<T>::SetLeftChild(node<T>* pNode)
		{
			m_LeftChild = pNode;
		}
#pragma endregion NODE_SETTERS

#pragma region NODE_UTILITIES
		// ----------------- Utility Methods ----------------- //

		template <typename T>
		bool node<T>::IsLeaf() const
		{
			return (m_LeftChild == nullptr) && (m_RightChild == nullptr);
		}

		template <typename T>
		int node<T>::GetHeight() const
		{
			// ternary operator usage, results in more efficient implementation 
			return std::max(
				((m_LeftChild == nullptr) ? 0 : 1 + m_LeftChild->GetHeight()),
				((m_RightChild == nullptr) ? 0 : m_RightChild->GetHeight())
			);
		}

		template<typename T>
		const int node<T>::CompareTo(const T& rhs)
		{
			return m_Item.CompareTo(rhs);
		}
#pragma endregion NODE_UTILITIES
	}
}
