#pragma once


#include "Core/Model/BruteForce/Node.h"

namespace Elysium
{
	namespace Brute 
	{
#pragma region BST_DECLARATION
		template <typename T>
		class BinarySearchTree
		{
			static_assert(std::is_base_of<IComparable, T>::value, "T must derive from interfaces::IComparable");
		public:
			BinarySearchTree();
			~BinarySearchTree();
			bool InsertLeaf(T& value);
			bool SearchTree(const T& value) const;
			void PrintTree();
		private:
			node<T>* s_Root;
			node<T>* CreateLeaf(T& value); //todo: [optimization] change this to pass by reference?
			void _TerminateTree(node<T>** pNode);
			__forceinline bool _InsertLeaf(T& value, node<T>** pNode);
			__forceinline void _PrintTree(node<T>* pNode);
			bool _SearchTree(node<T>* pNode, const T& value) const;
		};
#pragma endregion BST_DECLARATION

#pragma region BST_CONSTRUCTOR
		template <typename T>
		BinarySearchTree<T>::BinarySearchTree() : s_Root(nullptr)
		{
		}
#pragma endregion BST_CONSTRUCTOR

#pragma region BST_TERMINATION
		template <typename T>
		BinarySearchTree<T>::~BinarySearchTree()
		{
			try
			{
				_TerminateTree(&s_Root);
			}
			catch (...)
			{
				std::cout << "An exception has been thrown\n"; //todo: Implement exception.
			}

		}

		template<typename T>
		void BinarySearchTree<T>::_TerminateTree(node<T>** ppNode)
		{
			if (*ppNode != nullptr)
			{
				if ((*ppNode)->GetLeftChild() != nullptr)
				{
					_TerminateTree((*ppNode)->GetLeftChild());
					(*ppNode)->SetLeftChild(nullptr);
				}

				if ((*ppNode)->GetRightChild() != nullptr)
				{
					_TerminateTree((*ppNode)->GetRightChild());
					(*ppNode)->SetRightChild(nullptr);
				}
				delete* ppNode;
				*ppNode = nullptr;
			}
		}
#pragma endregion BST_TERMINATION

#pragma region BST_INSERTION

		template <typename T>
		node<T>* BinarySearchTree<T>::CreateLeaf(T& value)
		{
			node<T>* newNode = new node<T>(value, nullptr, nullptr);
			return newNode;
		}

		template <typename T>
		bool BinarySearchTree<T>::InsertLeaf(T& value)
		{
			return _InsertLeaf(value, &s_Root);
		}

		template <typename T>
		__forceinline bool BinarySearchTree<T>::_InsertLeaf(T& value, node<T>** ppNode)
		{
			//todo: test which condition being first results in a more efficient implementation.
			if (*ppNode == nullptr)
			{
				*ppNode = CreateLeaf(value);
				return true;
			}
			const int result = (*ppNode)->CompareTo(value);
			if (result > 0)
			{
				_InsertLeaf(value, (*ppNode)->GetLeftChild());
			}
			else if (result < 0)
			{
				_InsertLeaf(value, (*ppNode)->GetRightChild());
			}
			else if (result == 0)
			{
				std::cout << "\n[Insertion Failure, Value:" << value.GetValue() << "]: The tree already contains a node with this value. \n";
			}
			return false;

		}
#pragma endregion BST_INSERTION

#pragma region BST_SEARCH
		template <typename T>
		bool BinarySearchTree<T>::SearchTree(const T& value) const
		{
			if (s_Root != nullptr)
			{
				return _SearchTree(s_Root, value);
			}
			return false;
		}

		template <typename T>
		bool BinarySearchTree<T>::_SearchTree(node<T>* pNode, const T& value) const
		{
			if (pNode != nullptr)
			{
				const int result = pNode->CompareTo(value);

				if (result > 0)
					return _SearchTree(*(pNode->GetLeftChild()), value);
				else if (result < 0)
					return _SearchTree(*(pNode->GetRightChild()), value);
				else if (result == 0)
				{
					std::cout << "\nValue Found!\n";
					return true;
				}
			}
			std::cout << "\nObject Not Found.\n";
			return false;


		}
#pragma endregion BST_SEARCH

#pragma region BST_PRINTING
		template <typename T>
		void BinarySearchTree<T>::PrintTree()
		{
			_PrintTree(s_Root);
			std::cout << "\n";
		}

		template <typename T>
		void BinarySearchTree<T>::_PrintTree(node<T>* pNode)
		{
			if (pNode != nullptr)
			{
				std::cout << "Value: " << pNode->GetItemValue() << " IsLeaf: " << pNode->IsLeaf() << "\n";

				if (pNode->GetLeftChild() != nullptr)
				{
					_PrintTree(*(pNode->GetLeftChild()));
				}
				if (pNode->GetRightChild() != nullptr)
				{
					_PrintTree(*(pNode->GetRightChild()));
				}
			}
		}
#pragma endregion BST_PRINTING
	}
}
