#pragma once

#include <unordered_map>

#include "dsu.hpp"

namespace
{
	// Обобщённая система непересекающихся множеств на хэш-таблице
	template <typename T>
	class mapped_dsu : protected dsu
	{
	private:
		std::unordered_map<T, int> m_index; // Индексы элементов, соответсвующих данным элементов
		std::vector<T> m_value;				// Данные элементов, соответвующие их индексам в dsu

	public:
		// В конструкторе не нужен размер, он будет увеличиваться по мере добавления элементов
		mapped_dsu() : dsu(0) {}

		mapped_dsu(const mapped_dsu &other) : dsu(other),
											  m_value(other.m_value),
											  m_index(other.m_index) {}

		// Создаёт множество {x} из элемента x
		// Сохраняет новый индекс в хэш-таблицу по значению x с произвольным типом
		// Записывает значение x по полученному индексу
		void make_set(const T &x)
		{
			typename std::unordered_map<T, int>::iterator it = m_index.find(x);

			if (it != m_index.end())
				return;

			int index = static_cast<int>(m_parent.size());

			m_parent.push_back(index);
			m_value.push_back(x);
			m_index.insert(std::pair<T, int>(x, index));
		}

		// Поиск лидера по значению
		// Уже проверено исключение
		const T &find(const T &x) { return m_value[dsu::find(m_index.at(x))]; }

		// То же без сжатия пути
		const T &find(const T &x) const { return m_value[dsu::find(m_index.at(x))]; }

		// Сделать элемент y лидером множества {x}
		// Причём происходит объеденение множеств {y} и {x}
		void follow(const T &x, const T &y) { dsu::follow(m_index.at(x), m_index.at(y)); }

		// Проверка на содержание x и y в одном множестве
		bool equal(const T &x, const T &y) { return dsu::equal(m_index.at(x), m_index.at(y)); }

		// То же без сжатия пути
		bool equal(const T &x, const T &y) const { return dsu::equal(m_index.at(x), m_index.at(y)); }

		void clear()
		{
			dsu::clear();

			m_index.clear();
			m_value.clear();
		}

		// Получения константной ссылки на значения внутри системы непересекающихся множеств
		// Она недоступна к изменению. Пользуйся make_set
		const std::vector<T> &values() const { return m_value; }

		// find() только через оператор
		// Если элемента x нет в структуре, то создаёт его а затем возвращает его же как единственный его элемент подмножества {x}
		T operator[](T x)
		{
			typename std::unordered_map<T, int>::iterator it = m_index.find(x);

			if (it == m_index.end())
			{
				make_set(x);
				return x;
			}

			return m_value[dsu::find(it->second)];
		}

		// То же самое без сжатия путей и без создания элемента в случае его отсутсвия
		const T &operator[](const T &x) const { return m_value[dsu::find(m_index.at(x))]; }

		mapped_dsu &operator=(const mapped_dsu &other)
		{
			dsu::operator=(other);

			m_value = other.m_value;
			m_index = other.m_index;

			return *this;
		}

		~mapped_dsu() {}
	};
}