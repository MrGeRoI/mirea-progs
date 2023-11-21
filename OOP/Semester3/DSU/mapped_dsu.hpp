#include <unordered_map>

#include "dsu.hpp"

namespace
{
	template <typename T>
	class mapped_dsu : public dsu
	{
	private:
		std::unordered_map<T, int> m_index;
		std::vector<T> m_value;

	public:
		mapped_dsu();

		mapped_dsu(const mapped_dsu &other);

		void make_set(T x);

		T leader(T x);

		T leader(T x) const;

		size_t count(T x);

		size_t count(T x) const;

		T unite(T x, T y);

		bool equal(T x, T y);

		bool equal(T x, T y) const;

		void clear();

		T operator[](T x);

		const T &operator[](T x) const;

		mapped_dsu &operator=(const mapped_dsu &other);

		const std::vector<T> &values() const;

		~mapped_dsu();
	};

	template <typename T>
	mapped_dsu<T>::mapped_dsu() : dsu(0) {}

	template <typename T>
	mapped_dsu<T>::mapped_dsu(const mapped_dsu &other) : dsu(other)
	{
		m_value = other.m_value;
		m_index = other.m_index;
	}

	template <typename T>
	void mapped_dsu<T>::make_set(T x)
	{
		typename std::unordered_map<T, int>::iterator it = m_index.find(x);

		if (it != m_index.end())
			return;

		int index = static_cast<int>(m_parent.size());

		m_parent.push_back(index);
		m_rank.push_back(0);
		m_count.push_back(1);

		m_value.push_back(x);
		m_index.insert(std::pair<T, int>(x, index));
	}

	template <typename T>
	T mapped_dsu<T>::leader(T x)
	{
		// Уже проверено исключение
		return m_value[dsu::leader(m_index.at(x))];
	}

	template <typename T>
	T mapped_dsu<T>::leader(T x) const
	{
		return m_value[dsu::leader(m_index.at(x))];
	}

	template <typename T>
	size_t mapped_dsu<T>::count(T x)
	{
		return dsu::count(m_index.at(x));
	}

	template <typename T>
	size_t mapped_dsu<T>::count(T x) const
	{
		return dsu::count(m_index.at(x));
	}

	template <typename T>
	T mapped_dsu<T>::unite(T x, T y)
	{
		return m_value[dsu::unite(m_index.at(x), m_index.at(y))];
	}

	template <typename T>
	bool mapped_dsu<T>::equal(T x, T y)
	{
		return dsu::equal(m_index.at(x), m_index.at(y));
	}

	template <typename T>
	bool mapped_dsu<T>::equal(T x, T y) const
	{
		return dsu::equal(m_index.at(x), m_index.at(y));
	}

	template <typename T>
	void mapped_dsu<T>::clear()
	{
		dsu::clear();

		m_index.clear();
		m_value.clear();
	}

	template <typename T>
	const std::vector<T> &mapped_dsu<T>::values() const { return m_value; }

	template <typename T>
	T mapped_dsu<T>::operator[](T x)
	{
		typename std::unordered_map<T, int>::iterator it = m_index.find(x);

		if (it == m_index.end())
		{
			make_set(x);
			return x;
		}

		return m_value[dsu::leader(it->second)];
	}

	template <typename T>
	const T &mapped_dsu<T>::operator[](T x) const
	{
		return m_value[dsu::leader(m_index.at(x))];
	}

	template <typename T>
	mapped_dsu<T> &mapped_dsu<T>::operator=(const mapped_dsu<T> &other)
	{
		dsu::operator=(other);

		size_t other_size = other.m_parent.size();

		for (int i = 0; i < other_size; i++)
		{
			m_value[i] = other.m_value[i];
			m_index[i] = other.m_index[i];
		}

		return *this;
	}

	template <typename T>
	mapped_dsu<T>::~mapped_dsu() {}
}