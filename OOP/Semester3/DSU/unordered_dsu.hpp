#pragma once

#include "dsu.hpp"

namespace
{
	// Неупорядоченная система непересекающихся множеств с улучшенной эвристикой
	class unordered_dsu : protected dsu
	{
	protected:
		std::vector<int> m_rank;	 // Ранги вершин
		std::vector<size_t> m_count; // Мощность множества

	public:
		unordered_dsu(size_t size = 0) : dsu(size),
										 m_rank(size, 0),
										 m_count(size, 1) {}

		unordered_dsu(const unordered_dsu &other) : dsu(other),
													m_rank(other.m_rank),
													m_count(other.m_count) {}

		// Лидер множества {x]} (не контролируется программистом в силу ранговой эвристики)
		int leader(int x) { return dsu::find(x); }

		// То же без сжатия пути
		int leader(int x) const { return dsu::find(x); }

		// Размер подмножества {x}
		size_t count(int x)
		{
			if (x < 0 || x >= m_parent.size())
				throw std::out_of_range("");

			return m_count[leader(x)];
		}

		// То же без сжатия пути
		size_t count(int x) const
		{
			if (x < 0 || x >= m_parent.size())
				throw std::out_of_range("");

			return m_count[leader(x)];
		}

		// Размер структуры
		inline size_t size() const { return dsu::size(); }

		void resize(size_t size)
		{
			if (dsu::size() != size)
			{
				dsu::resize(size);
				m_rank.resize(size);
				m_count.resize(size);
			}
		}

		// Объеденение подмножеств {x} и {y}
		// Имеет в себе ранговую эвристику, из-за которой идёт выбор, кто станет лидером ради улучшения эффективности структуры
		// Возвращает лидера полученного подмножества
		int unite(int x, int y)
		{
			if (x < 0 || x >= m_parent.size() || y < 0 || y >= m_parent.size())
				throw std::out_of_range("");

			x = leader(x);
			y = leader(y);

			if (x == y)
				return x;

			if (m_rank[x] < m_rank[y])
				std::swap(x, y);

			m_count[x] += m_count[y];

			m_parent[y] = x;

			if (m_rank[x] == m_rank[y])
				m_rank[x]++;

			return x;
		}

		// Проверка на содержание x и y в одном множестве
		bool equal(int x, int y) { return dsu::equal(x, y); }

		// То же без сжатия пути
		bool equal(int x, int y) const { return dsu::equal(x, y); }

		void clear()
		{
			dsu::clear();
			m_rank.clear();
			m_count.clear();
		}

		unordered_dsu &operator=(const unordered_dsu &other)
		{
			dsu::operator=(other);
			m_rank = other.m_rank;
			m_parent = other.m_parent;

			return *this;
		}

		~unordered_dsu() {}
	};
}