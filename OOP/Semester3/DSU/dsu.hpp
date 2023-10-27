#include <vector>
#include <map>
#include <stdexcept>
#include <unordered_map>

namespace
{
	template <typename T>
	class dsu
	{
	protected:
		struct node
		{
		public:
			node *_parent;
			int _rank,_size;

			node(T val)
			{
				_parent = val;

				_rank = 0;
			}
		};

		node **_root;
		size_t _count;

		std::unordered_map<T, node> _dsu;

		node *find_node(node *current)
		{
			if (current->_parent == current)
				return current;

			return find_node(current._parent);
		}

	public:
		dsu(){};

		void unite_sets(T major, T minor)
		{
			node &a = _dsu.at(major);
			node &b = _dsu.at(minor);
		
			if (a._parent == b._parent)
				return;

			if (a._rank < b._rank)
				std::swap(a, b);

			b._parent = major;

			if (a._rank == b._rank)
				a._rank++;
		}

		void make_set(T value)
		{
			_dsu[value]._parent = value;
		}

		T find_set(T value)
		{
			node &data = _dsu.at(value);

			if (value == data._parent)
				return value;

			return data._parent = find_set(data._parent);
		}

		T find_set(T value) const
		{
			node &data = _dsu.at(value);

			if (value == data._parent)
				return value;

			return find_set(data._parent);
		}

		T &operator[](T value);

		T &at(T value);
		const T &at(T value) const;
	};

	// find_set/make_set
	template <typename T>
	T &dsu<T>::operator[](T value)
	{
		node &data = _dsu[value];

		if (value == data._parent)
			return data._parent;

		return operator[](data._parent);
	}

	template <typename T>
	T &dsu<T>::at(T value)
	{
		try
		{
			return _dsu.at(value);
		}
		catch (const std::out_of_range &out)
		{
			throw out;
		}

		throw std::invalid_argument("T &dsu<T>::at(T value)");
	}

	template <typename T>
	const T &dsu<T>::at(T value) const
	{
		try
		{
			return _dsu.at(value);
		}
		catch (const std::out_of_range &out)
		{
			throw out;
		}

		throw std::invalid_argument("T &dsu<T>::at(T value)");
	}

}