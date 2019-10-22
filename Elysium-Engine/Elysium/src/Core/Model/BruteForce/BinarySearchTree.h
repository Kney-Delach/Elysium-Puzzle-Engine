#pragma once
#include <queue>

#include "Core/Model/BruteForce/Node.h"
#include "Core/Model/Puzzle/PuzzleAttributes.h"

namespace Elysium
{
	namespace Brute 
	{
		template <typename T>
		class BinarySearchTree
		{
			static_assert(std::is_base_of<IComparable, T>::value, "T must derive from interfaces::IComparable");
		public:
			BinarySearchTree(T root, int puzzleSize,Model::PuzzleAttributes& attributes); 
			~BinarySearchTree();
			bool InsertLeaf(T& value);

			void CalculateAttributes();
			void PrintTree();
		private:
			node<T>* CreateChildren(T& value);
			void TerminateTree(node<T>** pNode);
			__forceinline bool _InsertLeaf(T& value, node<T>** pNode);
			__forceinline void _PrintTree(node<T>* pNode);
			bool _SearchTree(node<T>* pNode, const T& value) const;
		private:
			node<T>* s_Root; //todo: verify this makes a copy
			Model::PuzzleAttributes* m_Attributes;
		};

		template <typename T>
		BinarySearchTree<T>::BinarySearchTree(T root, int puzzleSize, Model::PuzzleAttributes& attributes) : m_Attributes(&attributes)
		{
			s_Root = new node<T>(root, 2); //todo: Verify this initializes correctly.
		}

		template <typename T>
		BinarySearchTree<T>::~BinarySearchTree()
		{
			try
			{
				TerminateTree(&s_Root);
			}
			catch (...)
			{
				std::cout << "An exception has been thrown\n"; //todo: Implement exception.
			}
		}

		template<typename T>
		void BinarySearchTree<T>::TerminateTree(node<T>** ppNode)
		{
			if (*ppNode != nullptr)
			{
				for (int i = 0; i < (*ppNode)->GetChildrenSize(); i++)
				{
					if ((*ppNode)->GetChildAtIndex(i) != nullptr)
					{
						TerminateTree((*ppNode)->GetChildAtIndex(i));
						(*ppNode)->SetChildAtIndex(i, nullptr);
					}
				}
				delete* ppNode;
				*ppNode = nullptr;
			}
		}

		template<typename T>
		void BinarySearchTree<T>::CalculateAttributes()
		{
			InsertLeaf();
			//std::priority_queue<node<T>*> priorityQueue;

			//priorityQueue.push(s_Root);
			//
			//while (!priorityQueue.empty()) //todo: abstract into print queue function
			//{
			//	//todo: generate children
			//	
			//	std::cout << *(static_cast<node<T>*>(priorityQueue.top())) << " ";
			//	priorityQueue.pop();
			//}
		}

		// ------------------------------ Clean this area ------------------------------


		template <typename T>
		node<T>* BinarySearchTree<T>::CreateChildren(T& value)
		{
			//todo: calculate the possible children
			int numberOfMoves = 4;
			node<T>* newNode = new node<T>(value, numberOfMoves);

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
			if (*ppNode == nullptr)
			{
				//todo: Implement error handling mechanisms
				*ppNode = CreateChildren(value);
				return true;
			}
			for (int i = 0; i < (*ppNode)->GetChildrenSize(); i++)
			{
				if ((*ppNode)->GetChildAtIndex(i) != nullptr)
				{
					_InsertLeaf((*ppNode)->GetChildAtIndex(i));
				}
			}
			return false;

		}

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
				std::cout << "Value: " << pNode->GetItem() << "\n";

				for (int i = 0; i < (*ppNode)->GetChildrenSize(); i++)
				{
					if ((*ppNode)->GetChildAtIndex(i) != nullptr)
					{
						_PrintTree((*ppNode)->GetChildAtIndex(i));
					}
				}
			}
		}
	}
}