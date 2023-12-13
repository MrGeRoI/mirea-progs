#include <iostream>
#include <queue>
#include <string>
#include <list>

#define HEAP_MAX_TREES 64

using namespace std;

class Movie
{
public:
	string _scenarist, _name, _country;
	int _year, _cost, _income;

	Movie()
	{
		_year = 0;
		_cost = 0;
		_income = 0;
	}

	Movie(const char *scenarist, const char *name, const char *country,
		  int year, int cost, int income)
	{
		_scenarist = scenarist;
		_name = name;
		_country = country;
		_year = year;
		_cost = cost;
		_income = income;
	}

	Movie(const Movie &movie)
	{
		_scenarist = movie._scenarist;
		_name = movie._name;
		_country = movie._country;
		_year = movie._year;
		_cost = movie._cost;
		_income = movie._income;
	}

	~Movie() {}

	friend ostream &operator<<(ostream &stream, const Movie &value)
	{
		return stream << value._scenarist << ' ' << value._name << ' ' << value._country << ' '
					  << value._year << ' ' << value._cost << ' ' << value._income;
	}

	friend istream &operator>>(istream &stream, Movie &value)
	{
		return stream >> value._scenarist >> value._name >> value._country >> value._year >> value._cost >> value._income;
	}

	bool operator<(const Movie &movie) const
	{
		if (_income < movie._income)
			return true;

		if (_cost < movie._cost)
			return true;

		if (_year < movie._year)
			return true;

		return false;
	}

	bool operator>(const Movie &movie) const
	{
		if (_income > movie._income)
			return true;

		if (_cost > movie._cost)
			return true;

		if (_year > movie._year)
			return true;

		return false;
	}

	bool operator==(const Movie &movie) const
	{
		return _name == movie._name &&
			   _scenarist == movie._scenarist &&
			   _country == movie._country;
	}
};

template <class T>
class Heap
{
private:
	T *m_pArray;

	int m_iLength;

	int m_iSize;

	void swap(int index1, int index2)
	{
		if (index1 < 0 || index1 >= m_iLength)
			throw out_of_range("");

		if (index2 < 0 || index2 >= m_iLength)
			throw out_of_range("");

		T temp;
		temp = m_pArray[index1];
		m_pArray[index1] = m_pArray[index2];
		m_pArray[index2] = temp;
	}

	T getLeftChild(int index) { return m_pArray[getLeftChildIndex(index)]; }

	T getRightChild(int index) { return m_pArray[getRightChildIndex(index)]; }

	T getParent(int index) { return m_pArray[getParentIndex(index)]; }

	int getLeftChildIndex(int index)
	{
		if (index < 0 || index >= m_iLength)
			throw out_of_range("");

		return index * 2 + 1;
	}

	int getRightChildIndex(int index)
	{
		if (index < 0 || index >= m_iLength)
			throw out_of_range("");

		return index * 2 + 2;
	}

	int getParentIndex(int index)
	{
		if (index <= 0 || index >= m_iLength)
			throw out_of_range("");

		if (index % 2 == 0)
			return index / 2 - 1;

		return index / 2;
	}

	void siftUp(int index = -1)
	{
		if (index == -1)
			index = m_iLength - 1;

		if (index == 0)
			return;

		int m_parent = getParentIndex(index);

		if (m_pArray[index] < m_pArray[m_parent])
		{
			swap(index, m_parent);
			siftUp(m_parent);
		}
	}

	void siftDown(int index = 0)
	{
		if (m_iLength <= 0)
			return;

		int maximum = index;

		int left = getLeftChildIndex(index), right = getRightChildIndex(index);

		if (left < m_iLength && m_pArray[left] < m_pArray[maximum])
			maximum = left;

		if (right < m_iLength && m_pArray[right] < m_pArray[maximum])
			maximum = right;

		if (index != maximum)
		{
			swap(index, maximum);
			siftDown(maximum);
		}
	}

	void heapify(int index = 0) { siftDown(index); };

public:
	int getCapacity() { return m_iSize; }
	int getCount() { return m_iLength; }

	T &operator[](int index)
	{
		if (index < 0 || index >= m_iLength)
			throw out_of_range("");

		return m_pArray[index];
	}

	const T &operator[](int index) const;

	Heap<T>(int memory = 100)
	{
		m_pArray = new T[memory];
		m_iLength = 0;
		m_iSize = memory;
	}

	void push(T N)
	{

		if (m_iLength < m_iSize)
		{
			m_pArray[m_iLength] = N;
			m_iLength++;
			siftUp();
		}
	}

	void remove(int index);

	T extractMin()
	{

		T res = m_pArray[0];
		swap(0, m_iLength - 1);
		m_iLength--;
		heapify();
		return res;
	}

	void straight(void (*func)(T))
	{
		for (int i = 0; i < m_iLength; i++)
			func(m_pArray[i]);
	}

	template <class T1>
	friend ostream &operator<<(ostream &stream, const Heap<T1> &node);

	~Heap() { delete[] m_pArray; };
};

template <class T>
void Heap<T>::remove(int index)
{
	if (index < 0 || index >= m_iLength)
		throw out_of_range("");

	if (index >= m_iLength - 1)
	{
		m_iLength--;
		return;
	}

	swap(index, m_iLength - 1);
	m_iLength--;
	siftUp(index);
	siftDown(index);
}

template <class T>
ostream &operator<<(ostream &stream, const Heap<T> &heap)
{
	for (int i = 0; i < heap.m_iLength; i++)
		stream << heap.m_pArray[i] << ' ';

	return stream;
}
template <class T>
class FibonacciHeap
{
public:
	struct Node
	{
	public:
		typename list<Node *>::iterator m_current;
		typename list<Node *>::iterator m_parent;

		list<Node *> m_children; // Список содержащий указатели на дочерние узлы текущего узла.

		int m_degree;
		T m_value;
	};

protected:
	list<Node *> m_heap;
	typename list<Node *>::iterator m_maximum;

	void consolidate()
	{
		vector<Node *> degreeTable(m_heap.size() + 1, nullptr);

		typename list<Node *>::iterator it = m_heap.begin();
		while (it != m_heap.end())
		{
			Node *x = *it;
			int m_degree = x->m_degree;

			while (degreeTable[m_degree] != nullptr)
			{
				Node *y = degreeTable[m_degree];
				if (x->m_value < y->m_value)
					swap(x, y);

				link(x, y);

				degreeTable[m_degree] = nullptr;
				m_degree++;
			}
			degreeTable[m_degree] = x;
			++it;
		}

		m_heap.clear();
		m_maximum = m_heap.end();
		for (int i = 0; i < degreeTable.size(); ++i)
		{
			if (degreeTable[i] != nullptr)
			{
				degreeTable[i]->m_current = m_heap.insert(m_heap.end(), degreeTable[i]);
				if (m_maximum == m_heap.end() || degreeTable[i]->m_value > (*m_maximum)->m_value)
					m_maximum = degreeTable[i]->m_current;
			}
		}
	}

	void link(Node *m_parent, Node *child)
	{
		m_parent->m_children.push_back(child);

		if (!child->m_children.empty())
			m_parent->m_children.splice(m_parent->m_children.end(), child->m_children);

		m_parent->m_degree += child->m_degree;
		child->m_children.clear();
		m_parent->m_degree++;
	}

public:
	FibonacciHeap<T>()
	{
		m_heap.clear();
		m_maximum = m_heap.end();
	}

	virtual ~FibonacciHeap()
	{
		if (!m_heap.empty())
		{
			for (typename list<Node *>::iterator it = m_heap.begin(); it != m_heap.end(); ++it)
				delete *it;

			m_heap.clear();
		}
	}

	Node *push(T value)
	{
		Node *add = new Node;

		add->m_value = value;
		add->m_degree = 0;
		add->m_children.clear();
		add->m_parent = add->m_children.end();
		add->m_current = m_heap.insert(m_heap.end(), add);

		if (m_heap.size() == 1 || (add->m_value > (*m_maximum)->m_value))
			m_maximum = add->m_current;

		return add;
	}

	void merge(FibonacciHeap &other)
	{
		m_heap.splice(m_heap.end(), other.m_heap);

		if ((*other.m_maximum)->m_value > (*m_maximum)->m_value)
			m_maximum = other.m_maximum;
	}

	bool isEmpty() const { return m_heap.empty(); }

	T extractMaximum()
	{
		if (m_heap.empty())
			throw runtime_error("Heap is empty");

		Node *maxNode = *m_maximum;
		T maxValue = maxNode->m_value;

		if (!maxNode->m_children.empty())
			m_heap.splice(m_heap.end(), maxNode->m_children);

		m_heap.erase(maxNode->m_current);
		delete maxNode;

		if (!m_heap.empty())
			consolidate();
		else
			m_maximum = m_heap.end();

		return maxValue;
	}
};

template <typename T>
void print_queue(T &q)
{
	while (!q.empty())
	{
		cout << q.top() << " ";
		q.pop();
	}

	cout << '\n';
}

int main(int argc, char *argv[])
{
	priority_queue<Movie> pqueue_movie;

	pqueue_movie.push(Movie("Quentin Tarantino", "Pulp Fiction", "USA", 1994, 8000000, 214000000));
	pqueue_movie.push(Movie("Christopher Nolan", "Inception", "USA", 2010, 160000000, 829895144));
	pqueue_movie.push(Movie("Martin Scorsese", "The Wolf of Wall Street", "USA", 2013, 100000000, 392000694));
	pqueue_movie.push(Movie("Denis Villeneuve", "Blade Runner 2049", "Canada", 2017, 150000000, 259239658));
	pqueue_movie.push(Movie("Greta Gerwig", "Little Women", "USA", 2019, 40000000, 218000000));
	pqueue_movie.push(Movie("Bong Joon-ho", "Parasite", "South Korea", 2019, 11000000, 258800000));

	print_queue(pqueue_movie); // Вывод по приоритету

	Heap<Movie> heap_movie;

	heap_movie.push(Movie("Quentin Tarantino", "Pulp Fiction", "USA", 1994, 8000000, 214000000));
	heap_movie.push(Movie("Christopher Nolan", "Inception", "USA", 2010, 160000000, 829895144));
	heap_movie.push(Movie("Martin Scorsese", "The Wolf of Wall Street", "USA", 2013, 100000000, 392000694));
	heap_movie.push(Movie("Denis Villeneuve", "Blade Runner 2049", "Canada", 2017, 150000000, 259239658));
	heap_movie.push(Movie("Greta Gerwig", "Little Women", "USA", 2019, 40000000, 218000000));
	heap_movie.push(Movie("Bong Joon-ho", "Parasite", "South Korea", 2019, 11000000, 258800000));

	heap_movie.remove(3);

	cout << heap_movie.extractMin() << endl;

	FibonacciHeap<Movie> fibheap_movie;

	fibheap_movie.push(Movie("Quentin Tarantino", "Pulp Fiction", "USA", 1994, 8000000, 214000000));
	fibheap_movie.push(Movie("Christopher Nolan", "Inception", "USA", 2010, 160000000, 829895144));
	fibheap_movie.push(Movie("Martin Scorsese", "The Wolf of Wall Street", "USA", 2013, 100000000, 392000694));
	fibheap_movie.push(Movie("Denis Villeneuve", "Blade Runner 2049", "Canada", 2017, 150000000, 259239658));
	fibheap_movie.push(Movie("Greta Gerwig", "Little Women", "USA", 2019, 40000000, 218000000));
	fibheap_movie.push(Movie("Bong Joon-ho", "Parasite", "South Korea", 2019, 11000000, 258800000));

	cout << fibheap_movie.extractMaximum() << fibheap_movie.extractMaximum() << endl;

	return 0;
}