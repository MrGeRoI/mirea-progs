#pragma once

#include <stdexcept>
#include <vector>
#include <fstream>

namespace
{
	// Система непересекающихся множеств на массиве
	class dsu
	{
	protected:
		std::vector<int> m_parent; // Родители вершин

	public:
		dsu(size_t size = 0) : m_parent(size)
		{
			for (int i = 0; i < size; i++)
				m_parent[i] = i;
		}

		dsu(const dsu &other) : m_parent(other.m_parent) {}

		// Текущий представитель множества {x}
		// + эвристика сжатия пути
		int find(int x)
		{
			if (x < 0 || x >= m_parent.size())
				throw std::out_of_range("");

			int p = m_parent[x];

			if (x == p)
				return x;

			return (m_parent[x] = find(p));
		}

		// Текущий представитель множества {x}
		// без сжатия пути
		int find(int x) const
		{
			if (x < 0 || x >= m_parent.size())
				throw std::out_of_range("");

			int p = m_parent[x];

			if (x == p)
				return x;

			return find(p);
		}

		// Размер структуры
		inline size_t size() const { return m_parent.size(); }

		void resize(size_t size)
		{
			if (m_parent.size() != size)
				m_parent.resize(size);
		}

		// Сделать элемент y лидером множества {x}
		// Причём происходит объеденение множеств {y} и {x}
		void follow(int x, int y)
		{
			if (x < 0 || x >= m_parent.size() || y < 0 || y >= m_parent.size())
				throw std::out_of_range("");

			x = find(x);
			y = find(y);

			if (x == y)
				return;

			m_parent[x] = y;
		}

		// Проверка на содержание x и y в одном множестве
		bool equal(int x, int y)
		{
			if (x < 0 || x >= m_parent.size() || y < 0 || y >= m_parent.size())
				throw std::out_of_range("");

			return find(x) == find(y);
		}

		// То же самое без сжатия путей
		bool equal(int x, int y) const
		{
			if (x < 0 || x >= m_parent.size() || y < 0 || y >= m_parent.size())
				throw std::out_of_range("");

			return find(x) == find(y);
		}

		// Очистить структуру
		void clear() { m_parent.clear(); }

		// find() только через оператор
		int operator[](int x) { return find(x); }

		// То же самое без сжатия путей
		int operator[](int x) const { return find(x); }
		
		dsu &operator=(const dsu &other)
		{
			m_parent = other.m_parent;

			return *this;
		}

		~dsu() {}
	};
}