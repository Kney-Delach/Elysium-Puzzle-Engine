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
			static_assert(std::is_base_of<Model::Puzzle, T>::value, "T must derive from interfaces::IComparable");
		public:
			BinarySearchTree() = default;
			~BinarySearchTree() = default;
			void TreeSearch(T problem, Model::PuzzleAttributes& attributes);
		private:
			std::vector<node<T>*>* Expand(node<T>* node);
		};


		template<typename T>
		void BinarySearchTree<T>::TreeSearch(T problem , Model::PuzzleAttributes& attributes)
		{
			std::ios::sync_with_stdio(false);
			std::queue<node<T>*> fringe;
			std::vector<node<T>*> configurationsVector;
			int iteration = 0;

			fringe.emplace(new node<T>(problem, 2));
			configurationsVector.push_back(fringe.front()); //todo: verify this contains the set of non-found configurations

			while (!fringe.empty())
			{
				node<T>* current = fringe.front();
				std::vector<node<T>*>* successors = Expand(fringe.front());
				for (unsigned i = 0; i < successors->size(); i++) 
				{
					if (!(std::any_of(configurationsVector.begin(), configurationsVector.end(), [&](node<T>* val) { return successors->at(i)->CompareTo(*val); })))
					{
						configurationsVector.push_back(successors->at(i)); 
						fringe.push(successors->at(i));
					}
					else
					{
						delete successors->at(i);
					}
				}
				fringe.pop();
				iteration++; 
				std::cout << (iteration) << "\n";
			}

			auto ProcessVector = [&]()
			{
				int size = configurationsVector.size();
				int continuousTotal = 0;
				for (int i = 0; i < size; i++)
				{
					continuousTotal += (*configurationsVector[i]).GetItem().ProcessContinuousValues();
					delete configurationsVector[i];
				}
				attributes.SetContinuousValues(continuousTotal);
			};
			ProcessVector();
		}

		template<typename T>
		std::vector<node<T>*>* BinarySearchTree<T>::Expand(node<T>* pParentNode)
		{
			std::vector<node<T>*>* successors = new std::vector<node<T>*>();
			successors->reserve(4);
			
			// left node
			node<T>* leftNode = new node<T>(*pParentNode);
			if ((leftNode->GetItem().ActionLeft()))
			{
				successors->push_back(&(*leftNode));
			}
			else
			{
				delete leftNode;
			}
			// right node
			node<T>* rightNode = new node<T>(*pParentNode);
			if ((rightNode->GetItem().ActionRight()))
			{
				successors->push_back(&(*rightNode));
			}
			else
			{
				delete rightNode;
			}
			// up node 
			node<T>* upNode = new node<T>(*pParentNode);

			if ((upNode->GetItem().ActionUp()))
			{
				successors->push_back(&(*upNode));
			}
			else
			{
				delete upNode;
			}
			// down node
			node<T>* downNode = new node<T>(*pParentNode);

			if ((downNode->GetItem().ActionDown()))
			{
				successors->push_back(&(*downNode));
			}
			else
			{
				delete downNode;
			}

			return &(*successors);
		}
	}
}