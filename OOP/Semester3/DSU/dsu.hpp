#pragma once

#include <stdexcept>
#include <vector>

namespace
{
	// Система непересекающихся множеств на массиве
	class dsu
	{
	protected:
		std::vector<int> m_parent; // Родители вершин

	public:
		dsu(size_t size = 0);

		dsu(const dsu &other);

		// Текущий представитель множества {x}
		// + эвристика сжатия пути
		int find(int x);

		// Текущий представитель множества {x}
		// без сжатия пути
		int find(int x) const;

		// Размер структуры
		inline size_t size() const;

		void resize(size_t size);

		// Сделать элемент y лидером множества {x}
		// Причём происходит объеденение множеств {y} и {x}
		void follow(int x, int y);

		// Проверка на содержание x и y в одном множестве
		bool equal(int x, int y);

		// То же самое без сжатия путей
		bool equal(int x, int y) const;

		// Очистить структуру
		void clear();

		// find() только через оператор
		int operator[](int x);

		// То же самое без сжатия путей
		int operator[](int x) const;

		dsu &operator=(const dsu &other);

		~dsu();
	};

	dsu::dsu(size_t size) : m_parent(size)
	{
		for (int i = 0; i < size; i++)
		{
			m_parent[i] = i;
		}
	}

	dsu::dsu(const dsu &other) : m_parent(other.m_parent) {}

	int dsu::find(int x)
	{
		if (x < 0 || x >= m_parent.size())
			throw std::out_of_range("");

		int p = m_parent[x];

		if (x == p)
			return x;

		return (m_parent[x] = find(p));
	}

	int dsu::find(int x) const
	{
		if (x < 0 || x >= m_parent.size())
			throw std::out_of_range("");

		int p = m_parent[x];

		if (x == p)
			return x;

		return find(p);
	}

	size_t dsu::size() const
	{
		return m_parent.size();
	}

	void dsu::resize(size_t size)
	{
		if (m_parent.size() != size)
		{
			m_parent.resize(size);
		}
	}

	void dsu::follow(int x, int y)
	{
		if (x < 0 || x >= m_parent.size() || y < 0 || y >= m_parent.size())
			throw std::out_of_range("");

		x = find(x);
		y = find(y);

		if (x == y)
			return;

		m_parent[x] = y;
	}

	bool dsu::equal(int x, int y)
	{
		if (x < 0 || x >= m_parent.size() || y < 0 || y >= m_parent.size())
			throw std::out_of_range("");

		return find(x) == find(y);
	}

	bool dsu::equal(int x, int y) const
	{
		if (x < 0 || x >= m_parent.size() || y < 0 || y >= m_parent.size())
			throw std::out_of_range("");

		return find(x) == find(y);
	}

	void dsu::clear()
	{
		m_parent.clear();
	}

	int dsu::operator[](int x)
	{
		return find(x);
	}

	int dsu::operator[](int x) const
	{
		return find(x);
	}

	dsu &dsu::operator=(const dsu &other)
	{
		m_parent = other.m_parent;

		return *this;
	}

	dsu::~dsu() {}

}