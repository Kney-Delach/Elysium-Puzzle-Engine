#pragma once

namespace Elysium
{
	namespace Brute
	{
		/**
		 * @Interface Comparable
		 * @Returns int > 0 if greater than rhs.
		 * @Returns int < 0 if less than rhs.
		 * @Returns 0 if equal to rhs.
		*/
		class IComparable
		{
		public:
			virtual ~IComparable() {}
			virtual int CompareTo(const IComparable& rhs) = 0;
		};
	}
}
