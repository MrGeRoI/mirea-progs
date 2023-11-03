#include <stdexcept>

namespace
{
	template <typename T = unsigned>
	class dsu
	{
	protected:
		T *_parent;
		int *_rank;
		size_t *_size;

		const size_t _capacity;

	public:
		dsu(size_t size);

		T root(T x);

		T root(T x) const;

		size_t size(T x);

		size_t size(T x) const;

		void unite(T x, T y);

		bool equal(T x, T y);

		bool equal(T x, T y) const;

		T operator[](T x);

		T operator[](T x) const;

		~dsu();
	};

	template <typename T>
	dsu<T>::dsu(size_t capacity) : _capacity(capacity)
	{
		_parent = new T[capacity];
		_rank = new int[capacity];
		_size = new size_t[capacity];

		for (T i = 0; i < capacity; i++)
		{
			_parent[i] = i; // Родитель
			_rank[i] = 0;	// Ранг
			_size[i] = 1;	// Размер
		}
	}

	template <typename T>
	T dsu<T>::root(T x)
	{
		if (x < 0 || x >= _capacity)
			throw std::out_of_range("");

		T p = _parent[x];

		if (x == p)
			return x;

		return (_parent[x] = root(p));
	}

	template <typename T>
	T dsu<T>::root(T x) const
	{
		if (x < 0 || x >= _capacity)
			throw std::out_of_range("");

		T p = _parent[x];

		if (x == p)
			return x;

		return root(p);
	}

	template <typename T>
	size_t dsu<T>::size(T x)
	{
		if (x < 0 || x >= _capacity)
			throw std::out_of_range("");

		return _size[root(x)];
	}

	template <typename T>
	size_t dsu<T>::size(T x) const
	{
		if (x < 0 || x >= _capacity)
			throw std::out_of_range("");

		return _size[root(x)];
	}

	template <typename T>
	void dsu<T>::unite(T x, T y)
	{
		if (x < 0 || x >= _capacity || y < 0 || y >= _capacity)
			throw std::out_of_range("");

		x = root(x);
		y = root(y);

		if (x == y)
			return;

		if (_rank[x] < _rank[y])
			std::swap(x, y);

		_size[x] += _size[y];

		_parent[y] = x;

		if (_rank[x] == _rank[y])
			_rank[x]++;
	}

	template <typename T>
	bool dsu<T>::equal(T x, T y)
	{
		if (x < 0 || x >= _capacity || y < 0 || y >= _capacity)
			throw std::out_of_range("");

		return root(x) == root(y);
	}

	template <typename T>
	bool dsu<T>::equal(T x, T y) const
	{
		if (x < 0 || x >= _capacity || y < 0 || y >= _capacity)
			throw std::out_of_range("");

		return root(x) == root(y);
	}

	template <typename T>
	T dsu<T>::operator[](T x)
	{
		return root(x);
	}

	template <typename T>
	T dsu<T>::operator[](T x) const
	{
		return root(x);
	}

	template <typename T>
	dsu<T>::~dsu()
	{
		delete[] _parent;
		delete[] _rank;
		delete[] _size;
	}
}