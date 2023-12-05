#include <iostream>
#include <queue>
#include <string>
#include <list>

#define HEAP_MAX_TREES 64

using namespace std;

class Airlines
{
public:
	string _name, _i_code, _country, _site_add;
	int _num_lines, _rating;

	Airlines()
	{
		_num_lines = 0;
		_rating = 0;
	}

	Airlines(const char *name, const char *i_code, const char *country, const char *site_add,
			 int num_lines, int rating)
	{
		_name = name;
		_i_code = i_code;
		_country = country;
		_site_add = site_add;
		_num_lines = num_lines;
		_rating = rating;
	}

	Airlines(const Airlines &airlines)
	{
		_name = airlines._name;
		_i_code = airlines._i_code;
		_country = airlines._country;
		_site_add = airlines._site_add;
		_num_lines = airlines._num_lines;
		_rating = airlines._rating;
	}

	~Airlines() {}

	friend ostream &operator<<(ostream &s, const Airlines &value);
	friend istream &operator>>(istream &s, Airlines &value);

	bool operator<(const Airlines &airlines) const
	{
		if (_rating < airlines._rating)
			return true;

		if (_num_lines < airlines._num_lines)
			return true;

		return false;
	}

	bool operator>(const Airlines &airlines) const
	{
		if (_rating > airlines._rating)
			return true;

		if (_num_lines > airlines._num_lines)
			return true;

		return false;
	}

	bool operator==(const Airlines &airlines) const
	{
		return _name == airlines._name &&
			   _i_code == airlines._i_code &&
			   _country == airlines._country;
	}
};

ostream &operator<<(ostream &stream, const Airlines &value)
{
	return stream << value._name << ' ' << value._i_code << ' ' << value._country << ' '
				  << value._site_add << ' ' << value._num_lines << ' ' << value._rating;
}

istream &operator>>(istream &stream, Airlines &value)
{
	return stream >> value._name >> value._i_code >> value._country >> value._site_add >> value._num_lines >> value._rating;
}

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
	priority_queue<Airlines> pqueue_air;

	pqueue_air.push(Airlines("FreeFlight", "ABC123", "USA", "www.freeflight.com", 200, 4));
	pqueue_air.push(Airlines("SkyExpress", "DEF456", "Canada", "www.skyexpress.com", 150, 3));
	pqueue_air.push(Airlines("GlobalWings", "GHI789", "UK", "www.globalwings.com", 180, 5));
	pqueue_air.push(Airlines("FlyHigh", "JKL012", "Australia", "www.flyhigh.com", 250, 4));
	pqueue_air.push(Airlines("AirConnect", "MNO345", "Germany", "www.airconnect.com", 180, 4));
	pqueue_air.push(Airlines("SwiftFlyers", "PQR678", "France", "www.swiftflyers.com", 220, 3));

	print_queue(pqueue_air); // Вывод по приоритету

	Heap<Airlines> heap_air;

	heap_air.push(Airlines("FreeFlight", "ABC123", "USA", "www.freeflight.com", 200, 4));
	heap_air.push(Airlines("SkyExpress", "DEF456", "Canada", "www.skyexpress.com", 150, 3));
	heap_air.push(Airlines("GlobalWings", "GHI789", "UK", "www.globalwings.com", 180, 5));
	heap_air.push(Airlines("FlyHigh", "JKL012", "Australia", "www.flyhigh.com", 250, 4));
	heap_air.push(Airlines("AirConnect", "MNO345", "Germany", "www.airconnect.com", 180, 4));
	heap_air.push(Airlines("SwiftFlyers", "PQR678", "France", "www.swiftflyers.com", 220, 3));

	heap_air.remove(3);

	cout << heap_air.extractMin() << endl;

	FibonacciHeap<Airlines> fibheap_air;

	fibheap_air.push(Airlines("FreeFlight", "ABC123", "USA", "www.freeflight.com", 200, 4));
	fibheap_air.push(Airlines("SkyExpress", "DEF456", "Canada", "www.skyexpress.com", 150, 3));
	fibheap_air.push(Airlines("GlobalWings", "GHI789", "UK", "www.globalwings.com", 180, 5));
	fibheap_air.push(Airlines("FlyHigh", "JKL012", "Australia", "www.flyhigh.com", 250, 4));
	fibheap_air.push(Airlines("AirConnect", "MNO345", "Germany", "www.airconnect.com", 180, 4));
	fibheap_air.push(Airlines("SwiftFlyers", "PQR678", "France", "www.swiftflyers.com", 220, 3));

	cout << fibheap_air.extractMaximum() << fibheap_air.extractMaximum() << endl;

	return 0;
}