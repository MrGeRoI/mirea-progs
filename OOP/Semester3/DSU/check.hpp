#pragma once

#include <vector>
#include <list>

class dsu_1
{
private:
	std::vector<int> m_component;
	std::vector<int> m_count;

public:
	dsu_1(size_t size) : m_component(size), m_count(size)
	{
		for (int i = 0; i < size; i++)
		{
			m_component[i] = i;
			m_count[i] = 1;
		}
	}

	dsu_1(const dsu_1 &other) : m_component(other.m_component), m_count(other.m_count) {}

	int count(int c) const { return m_count[c]; }

	// O(1)
	bool equal(int x, int y) const
	{
		return m_component[x] == m_component[y];
	}

	// O(n)
	void unite(int x, int y)
	{
		if (m_count[x] < m_count[y])
			std::swap(x, y);

		int old = m_component[y], replace = m_component[x];

		m_count[replace] += m_count[old];
		m_count[old] = 0;

		for (int i = 0; i < m_component.size(); i++)
			if (m_component[i] == old)
				m_component[i] = replace;
	}
};

class dsu_2
{
public:
	using component = std::vector<int>;

private:
	std::list<component> m_component;

public:
	dsu_2() {}

	dsu_2(const dsu_2 &other) : m_component(other.m_component) {}

	void make_set(int x)
	{
		for (std::list<component>::const_iterator it = m_component.begin(); it != m_component.end(); it++)
			for (component::const_iterator it2 = it->begin(); it2 != it->end(); it2++)
				if (*it2 == x)
					return;

		component comp;
		comp.push_back(x);
		m_component.push_back(comp);
	}

	// O(n)
	bool equal(int x, int y) const
	{
		for (std::list<component>::const_iterator it = m_component.begin(); it != m_component.end(); it++)
		{
			bool foundX = false, foundY = false;

			for (component::const_iterator it2 = it->begin(); it2 != it->end(); it2++)
			{
				if (*it2 == x)
					foundX = true;
				else if (*it2 == y)
					foundY = true;

				if (foundX && foundY)
					return true;
			}

			if (foundX || foundY)
				return false;
		}

		return false;
	}

	// O(n)
	void unite(int x, int y)
	{
		std::list<component>::iterator itSetX = m_component.end(), itSetY = m_component.end();

		for (std::list<component>::iterator it = m_component.begin(); it != m_component.end(); it++)
		{
			for (component::iterator it2 = it->begin(); it2 != it->end(); it2++)
			{
				if (*it2 == x)
					itSetX = it;

				if (*it2 == y)
					itSetY = it;
			}

			if (itSetX != m_component.end() && itSetY != m_component.end())
			{
				if(itSetX->size() > itSetY->size())
					std::swap(itSetX,itSetY);

				itSetY->reserve(itSetY->size() + itSetX->size());
				itSetY->insert(itSetY->end(),itSetX->begin(),itSetX->end());

				m_component.erase(itSetX);

				return;
			}
		}
	}
};

class dsu_3
{
private:
	std::vector<int> m_parent;

public:
	dsu_3(size_t size) : m_parent(size)
	{
		for (int i = 0; i < size; i++)
			m_parent[i] = i;
	}

	dsu_3(const dsu_3 &other) : m_parent(other.m_parent) {}

	int find(int x) const
	{
		int p = m_parent[x];

		if (x == p)
			return x;

		return find(p);
	}

	// O(n)
	bool equal(int x, int y) const
	{
		return find(x) == find(y);
	}

	// O(n)
	void follow(int x, int y)
	{
		x = find(x);
		y = find(y);

		if (x == y)
			return;

		m_parent[x] = y;
	}
};