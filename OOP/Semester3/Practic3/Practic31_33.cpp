#include <iostream>
#include <queue>
#include <string>
#include <list>

#define HEAP_MAX_TREES 64

using namespace std;

/*«Школьник».
Минимальный набор полей: фамилия,
имя, пол, класс, дата рождения, адрес.*/
class Student
{
public:
	string _firstname, _lastname, _address;
	bool _male;
	int _birthday, _grade;

	Student()
	{
		_male = 0;
		_birthday = 0;
		_grade = 0;
	}

	Student(const char *firstname, const char *lastname, const char *address, bool male, int birthday, int grade)
	{
		_firstname = firstname;
		_lastname = lastname;
		_address = address;
		_male = male;
		_birthday = birthday;
		_grade = grade;
	}

	Student(const Student &stud)
	{
		_firstname = stud._firstname;
		_lastname = stud._lastname;
		_address = stud._address;
		_male = stud._male;
		_birthday = stud._birthday;
		_grade = stud._grade;
	}

	~Student() {}

	friend ostream &operator<<(ostream &s, const Student &value);
	friend istream &operator>>(istream &s, Student &value);

	bool operator<(const Student &stud) const
	{
		if (_birthday < stud._birthday)
			return true;

		if (_lastname < stud._lastname)
			return true;

		if (_firstname < stud._firstname)
			return true;

		return false;
	}

	bool operator>(const Student &stud) const
	{
		if (_birthday > stud._birthday)
			return true;

		if (_lastname > stud._lastname)
			return true;

		if (_firstname > stud._firstname)
			return true;

		return false;
	}

	bool operator==(const Student &stud) const
	{
		return _firstname == stud._firstname &&
			   _lastname == stud._lastname &&
			   _birthday == stud._birthday;
	}
};

ostream &operator<<(ostream &stream, const Student &value)
{
	return stream << value._firstname << ' ' << value._lastname << ' ' << value._address << ' ' << value._male << ' ' << value._birthday << ' ' << value._grade;
}

istream &operator>>(istream &stream, Student &value)
{
	return stream >> value._firstname >> value._lastname >> value._address >> value._male >> value._birthday >> value._grade;
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
	priority_queue<Student> pqueue_stud;

	pqueue_stud.push(Student("Danya", "Lykov", "Branks", true, 2007, 8));
	pqueue_stud.push(Student("Sanya", "Lazarev", "Moscow", true, 2005, 6));
	pqueue_stud.push(Student("Yarik", "Malysh", "Zamkad", true, 2004, 5));
	pqueue_stud.push(Student("German", "Zaycev", "Krasnodar", true, 2004, 4));
	pqueue_stud.push(Student("Senya", "Lenin", "Penza", true, 2004, 3));
	pqueue_stud.push(Student("Ksusha", "Egorova", "Zamkad", false, 2004, 2));

	print_queue(pqueue_stud); // Вывод по приоритету

	Heap<Student> heap_stud;

	heap_stud.push(Student("Danya", "Lykov", "Branks", true, 2007, 8));
	heap_stud.push(Student("Sanya", "Lazarev", "Moscow", true, 2005, 6));
	heap_stud.push(Student("Yarik", "Malysh", "Zamkad", true, 2004, 5));
	heap_stud.push(Student("German", "Zaycev", "Krasnodar", true, 2004, 4));
	heap_stud.push(Student("Senya", "Lenin", "Penza", true, 2004, 3));
	heap_stud.push(Student("Ksusha", "Egorova", "Zamkad", false, 2004, 2));

	heap_stud.remove(3);

	cout << heap_stud.extractMin(); // German

	FibonacciHeap<Student> FibonacciHeap_stud;

	FibonacciHeap_stud.push(Student("Danya", "Lykov", "Branks", true, 2007, 8));
	FibonacciHeap_stud.push(Student("Sanya", "Lazarev", "Moscow", true, 2005, 6));
	FibonacciHeap_stud.push(Student("Yarik", "Malysh", "Zamkad", true, 2004, 5));
	FibonacciHeap_stud.push(Student("German", "Zaycev", "Krasnodar", true, 2004, 4));
	FibonacciHeap_stud.push(Student("Senya", "Lenin", "Penza", true, 2004, 3));
	FibonacciHeap_stud.push(Student("Ksusha", "Egorova", "Zamkad", false, 2004, 2));

	cout << FibonacciHeap_stud.extractMaximum() << FibonacciHeap_stud.extractMaximum(); // Malysh, German

	return 0;
}