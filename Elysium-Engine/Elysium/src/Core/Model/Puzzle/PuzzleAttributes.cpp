#include "empch.h"
#include "Core/Model/Puzzle/PuzzleAttributes.h"

namespace Elysium
{
	namespace Model
	{
		void PuzzleAttributes::InitAttributes(const std::vector<int>* partialsVector)
		{
			m_ContinuousRows = 0;
			m_PartialIndexes = *partialsVector;
			m_StartConfigPartials.reserve(partialsVector->size());
			for (unsigned i = 0; i < m_StartConfigPartials.capacity(); i++)
				m_StartConfigPartials.emplace_back(0);
			m_ValidTurnsPartials.reserve(partialsVector->size());
			for (unsigned i = 0; i < m_ValidTurnsPartials.capacity(); i++)
				m_ValidTurnsPartials.emplace_back(0);
		}
	}
}