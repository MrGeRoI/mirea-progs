#pragma once

#include "dsu.hpp"

namespace
{
	// Система участков массива (подотрезков)
	template <typename T>
	class sub
	{
	private:
		dsu m_end;				// Содержит в себе границу каждого заполненного участка (закрашенного подотрезка). Каждый подотрезок это подмножество в dsu
		std::vector<T> m_value; // Значения массива

	public:
		// Создаёт массив указаной длины
		sub(size_t size) : m_end(size + 1),
						   m_value(size) {}

		sub(const sub<T> &other) : m_end(other.m_end),
								   m_value(other.m_value) {}

		// Заполнить участов [x;y) значением value
		// x - включается в участок, а y - нет.
		void fill(int x, int y, const T &value)
		{
			if (x < 0 || x >= m_end.size() || y < 0 || y > m_end.size())
				throw std::out_of_range("");

			if (x >= y)
				return;

			for (int i = x; i < y; i = m_end.find(i))
			{
				m_value[i] = value;

				m_end.follow(i, i + 1);
			}
		}

		// Получить значение в позиции x
		const T &find(int x) const
		{
			if (x < 0 || x >= m_end.size())
				throw std::out_of_range("");

			return m_value[x];
		}

		// Весь массив
		const std::vector<T> &values() const { return m_value; }

		// Длина массива
		size_t size() const { return m_end.size() - 1; }

		void resize(size_t size)
		{
			if ((m_end.size() - 1) != size)
			{
				m_end.resize(size + 1);
				m_value.resize(size);
			}
		}
		void clear()
		{
			m_end.clear();
			m_value.clear();
		}

		// Эквивалент для find() только через оператор
		const T &operator[](int x) const
		{
			return m_value[x];
		}

		sub &operator=(const sub<T> &other)
		{
			m_end = other.m_end;
			m_value = other.m_value;
		}

		~sub() {}
	};
}