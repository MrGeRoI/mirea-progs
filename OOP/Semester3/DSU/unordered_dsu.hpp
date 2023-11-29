#include "dsu.hpp"

namespace
{
	class unordered_dsu : public dsu
	{
	protected:
		std::vector<int> m_rank; // Ранги вершин

	public:
		unordered_dsu(size_t size = 0);

		unordered_dsu(const dsu &other);

		int leader(int x);

		int leader(int x) const;

		size_t count(int x);

		size_t count(int x) const;

		inline size_t size() const;

		void resize(size_t size);

		int unite(int x, int y);

		bool equal(int x, int y);

		bool equal(int x, int y) const;

		void clear();

		int operator[](int x);

		int operator[](int x) const;

		unordered_dsu &operator=(const unordered_dsu &other);

		~unordered_dsu();
	};
}