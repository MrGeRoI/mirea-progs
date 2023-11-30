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
		mapped_dsu();

		mapped_dsu(const mapped_dsu &other);

		// Создаёт множество {x} из элемента x
		// Сохраняет новый индекс в хэш-таблицу по значению x с произвольным типом
		// Записывает значение x по полученному индексу
		void make_set(T x);

		// Поиск лидера по значению
		T find(T x);

		// То же без сжатия пути
		T find(T x) const;

		// Сделать элемент y лидером множества {x}
		// Причём происходит объеденение множеств {y} и {x}
		void follow(T x, T y);

		// Проверка на содержание x и y в одном множестве
		bool equal(T x, T y);

		// То же без сжатия пути
		bool equal(T x, T y) const;

		void clear();

		// find() только через оператор
		// Если элемента x нет в структуре, то создаёт его а затем возвращает его же как единственный его элемент подмножества {x}
		T operator[](T x);

		// То же самое без сжатия путей
		const T &operator[](T x) const;

		mapped_dsu &operator=(const mapped_dsu &other);

		// Получения константной ссылки на значения внутри системы непересекающихся множеств
		// Она недоступна к изменению. Пользуйся make_set
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
		m_value.push_back(x);
		m_index.insert(std::pair<T, int>(x, index));
	}

	template <typename T>
	T mapped_dsu<T>::find(T x)
	{
		// Уже проверено исключение
		return m_value[dsu::find(m_index.at(x))];
	}

	template <typename T>
	T mapped_dsu<T>::find(T x) const
	{
		return m_value[dsu::find(m_index.at(x))];
	}

	template <typename T>
	void mapped_dsu<T>::follow(T x, T y)
	{
		dsu::follow(m_index.at(x), m_index.at(y));
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

		return m_value[dsu::find(it->second)];
	}

	template <typename T>
	const T &mapped_dsu<T>::operator[](T x) const
	{
		return m_value[dsu::find(m_index.at(x))];
	}

	template <typename T>
	mapped_dsu<T> &mapped_dsu<T>::operator=(const mapped_dsu<T> &other)
	{
		dsu::operator=(other);

		m_value = other.m_value;
		m_index = other.m_index;

		return *this;
	}

	template <typename T>
	mapped_dsu<T>::~mapped_dsu() {}
}