#include <vector>

namespace utils
{
	class bitSet
	{
		private :
		std::vector<bool> _bits;
		public :
		bool get(int pos)
		{
			return pos < _bits.size() && _bits[pos];
		}
		void set(int pos)
		{
			ensure(pos);
			_bits[pos] = true;
		}
		
		void ensure(int pos)
		{
			if (pos >= _bits.size())
			{
				_bits.resize(pos + 64);
			}
		}

	};
}