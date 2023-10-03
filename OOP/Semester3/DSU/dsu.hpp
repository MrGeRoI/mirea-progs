#include <vector>
#include <map>

namespace untitled
{
	template <typename T>
	class dsu
	{
	protected:
		struct union_node
		{
		private:
			T _value;

			union_node *_parent;

		public:
			union_node(T val)
			{
				_value = val;
				_parent = this;
				_left = _right = nullptr;
			}

			T &operator*() { return _value; }
			union_node *&parent() { return _parent; }
			union_node *&left() { return _left; }
			union_node *&right() { return _right; }

			const T &operator*() const { return _value; }
			const union_node *&parent() const { return _parent; }
			const union_node *&left() const { return _left; }
			const union_node *&right() const { return _right; }
		}

		std::vector<union_node *>
			_parent;

		union_node *find(T value) { return find(value, _parent); }

		union_node *find(T value, union_node *node);

		void add(union_node *parent)
		{
		}

	public:
		// union в C++ ключевое слово, так что нельзя называть
		void union_(T major, T minor)
		{
			for (union_node *node : _parent)
				if (*node == major)
					add(major, minor);
		}

		void make_set(T value)
		{
			// Если он уже есть в каком-то дереве, то поставить его в корень
		}

		void reassign_set(T value)
		{

		}
 
		T find(T value)
		{
		}

		T &operator[](T value);

		T &at(T value);
		const T &at(T value) const;
	};

	template <typename T>
	T &dsu<T>::operator[](T value)
	{
		union_node *node = find(value);

		if (node)
			return *node;

		make_set(value);

		return value;
	}

	template <typename T>
	T &dsu<T>::at(T value)
	{
		union_node *node = find(value);

		if (node)
			return *node;

		throw std::invalid_argument("T &dsu<T>::at(T value)");
	}

	template <typename T>
	const T &dsu<T>::at(T value) const
	{
		union_node *node = find(value);

		if (node)
			return *node;

		throw std::invalid_argument("T &dsu<T>::at(T value)");
	}

	
}