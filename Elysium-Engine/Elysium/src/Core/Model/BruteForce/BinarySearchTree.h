/**
 * FILENAME		: BinarySearchTree.h
 * Name			: Ori Lazar
 * Student ID	: b9061712
 * Date			: 23/10/2019
 * Description	: This file contains the implementation of a Tree to search for the number of continuous rows and columns 
                  of a nxn configuration, note, it takes a very long time to process currently and should be optimized.
 */
#pragma once
#include <queue>
#include "Core/Model/Puzzle/PuzzleAttributes.h"
#include "Core/Utility/Timer.h"
//todo: Optimize brute force.

namespace Elysium
{
	namespace Brute
	{
		template <typename T>
		class BinarySearchTree
		{
			static_assert(std::is_base_of<Model::Puzzle, T>::value, "T must derive from Model::Puzzle.");
		public:
			BinarySearchTree() = default;
			~BinarySearchTree() = default;
			void TreeSearch(T problem, Model::PuzzleAttributes& attributes);
		private:
			std::vector<T*>* Expand(T* node);
		};

		template<typename T>
		void BinarySearchTree<T>::TreeSearch(T problem , Model::PuzzleAttributes& attributes)
		{
			std::ios::sync_with_stdio(false);
			std::queue<T*> fringe;
			std::vector<T*> configurationsVector;
			fringe.emplace(new T(problem));
			configurationsVector.emplace_back(fringe.front()); 
			int iteration = 0; 
			{
				Utility::Timer localTimer;
				while (!fringe.empty())
				{
					T* current = fringe.front();
					std::vector<T*>* successors = Expand(current);
					for (unsigned i = 0; i < successors->size(); i++)
					{
						if (!(std::any_of(configurationsVector.begin(), configurationsVector.end(), [&](T* val) { return (*successors)[i]->CompareTo(*val); })))
						{
							configurationsVector.push_back((*successors)[i]);
							fringe.push((*successors)[i]);
						}
						else
						{
							delete (*successors)[i];
						}
					}
					fringe.pop();
					std::cout << ++iteration << "\n";
				}
			}
			auto ProcessVector = [&]()
			{
				int size = configurationsVector.size();
				int continuousTotal = 0;
				for (int i = 0; i < size; i++)
				{
					continuousTotal += (*configurationsVector[i]).ProcessContinuousValues();
					delete configurationsVector[i];
				}
				attributes.SetContinuousValues(continuousTotal);
			};
			ProcessVector();
		}

		template<typename T>
		std::vector<T*>* BinarySearchTree<T>::Expand(T* pParentNode)
		{
			std::vector<T*>* successors = new std::vector<T*>();
			successors->reserve(4);
			
			if (pParentNode->CanGoLeft())
			{
				successors->emplace_back(new T(*pParentNode, ActionDirection::LEFT));
			}
			if (pParentNode->CanGoRight())
			{
				successors->emplace_back(new T(*pParentNode, ActionDirection::RIGHT));
			}
			if (pParentNode->CanGoUp())
			{
				successors->emplace_back(new T(*pParentNode, ActionDirection::UP));
			}
			if (pParentNode->CanGoDown())
			{
				successors->emplace_back(new T(*pParentNode, ActionDirection::DOWN));
			}
			return &(*successors);
		}
	}
}