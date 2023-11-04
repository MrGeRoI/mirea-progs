#include <iostream>
#include <queue>
#include <string>

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
	int _birthday,_grade;

	Student()
	{
		_male = 0;
		_birthday = 0;
		_grade = 0;
	}

	Student(const char* firstname,const char* lastname,const char* address,bool male, int birthday,int grade)
	{
		_firstname = firstname;
		_lastname = lastname;
		_address = address;
		_male = male;
		_birthday = birthday;
		_grade = grade;
	}

	Student(const Student& stud)
	{
		_firstname = stud._firstname;
		_lastname = stud._lastname;
		_address = stud._address;
		_male = stud._male;
		_birthday = stud._birthday;
		_grade = stud._grade;
	}

	~Student() { }

	friend ostream& operator << (ostream& s,const Student& value);
	friend istream& operator >> (istream& s, Student& value);

	bool operator < (const Student& stud) const
	{
		if(_birthday < stud._birthday)
			return true;

		if(_lastname < stud._lastname)
			return true;

		if(_firstname < stud._firstname)
			return true;

		return false;
	}

	bool operator > (const Student& stud) const
	{
		if(_birthday > stud._birthday)
			return true;

		if(_lastname > stud._lastname)
			return true;

		if(_firstname > stud._firstname)
			return true;

		return false;
	}

	bool operator == (const Student& stud) const
	{
		return _firstname == stud._firstname &&
			_lastname == stud._lastname &&
			_birthday == stud._birthday;
	}
};

ostream& operator << (ostream& stream,const Student& value)
{
	return stream << value._firstname << ' ' << value._lastname << ' ' << value._address << ' ' << value._male << ' ' << value._birthday << ' ' << value._grade;
}

istream& operator >> (istream& stream, Student& value)
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

	void swap(int index1, int index2);

	T getLeftChild(int index) { return m_pArray[getLeftChildIndex(index)]; }

	T getRightChild(int index) { return m_pArray[getRightChildIndex(index)]; }

	T getParent(int index) { return m_pArray[getParentIndex(index)]; }

	int getLeftChildIndex(int index);

	int getRightChildIndex(int index);

	int getParentIndex(int index);

	void siftUp(int index = -1);

	void siftDown(int index = 0);

	void heapify(int index = 0) { siftDown(index); };

public:
	int getCapacity() { return m_iSize; }
	int getCount() { return m_iLength; }

	T &operator[](int index);

	const T &operator[](int index) const;

	Heap<T>(int memory = 100)
	{
		m_pArray = new T[memory];
		m_iLength = 0;
		m_iSize = memory;
	}

	void push(T N);

	void remove(int index);

	T extractMin();

	void straight(void (*func)(T));

	template <class T1>
	friend ostream &operator<<(ostream &stream, const Heap<T1> &node);

	~Heap() { delete[] m_pArray; };
};

template <class T>
T &Heap<T>::operator[](int index)
{
	if (index < 0 || index >= m_iLength)
		throw out_of_range;

	return m_pArray[index];
}

template <class T>
void Heap<T>::swap(int index1, int index2)
{
	if (index1 < 0 || index1 >= m_iLength)
		throw out_of_range;

	if (index2 < 0 || index2 >= m_iLength)
		throw out_of_range;

	T temp;
	temp = m_pArray[index1];
	m_pArray[index1] = m_pArray[index2];
	m_pArray[index2] = temp;
}

template <class T>
int Heap<T>::getLeftChildIndex(int index)
{
	if (index < 0 || index >= m_iLength)
		throw out_of_range;

	return index * 2 + 1;
}

template <class T>
int Heap<T>::getRightChildIndex(int index)
{
	if (index < 0 || index >= m_iLength)
		throw out_of_range;

	return index * 2 + 2;
}

template <class T>
int Heap<T>::getParentIndex(int index)
{
	if (index <= 0 || index >= m_iLength)
		throw out_of_range;

	if (index % 2 == 0)
		return index / 2 - 1;

	return index / 2;
}

template <class T>
void Heap<T>::siftUp(int index)
{
	if (index == -1)
		index = m_iLength - 1;

	if (index == 0)
		return;

	int parent = getParentIndex(index);

	if (m_pArray[index] < m_pArray[parent])
	{
		swap(index, parent);
		siftUp(parent);
	}
}

template <class T>
void Heap<T>::siftDown(int index)
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

template <class T>
void Heap<T>::push(T N)
{

	if (m_iLength < m_iSize)
	{
		m_pArray[m_iLength] = N;
		m_iLength++;
		siftUp();
	}
}

template <class T>
void Heap<T>::remove(int index)
{
	if (index < 0 || index >= m_iLength)
		throw out_of_range;

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
T Heap<T>::extractMin()
{

	T res = m_pArray[0];
	swap(0, m_iLength - 1);
	m_iLength--;
	heapify();
	return res;
}

template <class T>
void Heap<T>::straight(void (*func)(T))
{
	for (int i = 0; i < m_iLength; i++)
		func(m_pArray[i]);
}

template <class T>
ostream &operator<<(ostream &stream, const Heap<T> &heap)
{
	for (int i = 0; i < heap.m_iLength; i++)
		stream << heap.m_pArray[i] << ' ';

	return stream;
}

template <class T>
class FibonacciHeap;

template <class T>
struct HeapNode
{
public:
	HeapNode<T> *m_pPrevious, *m_pNext, *m_pChild, *m_pParent;

	T m_priority;
	int m_iDegree;
	bool m_bMarked;
};
/*
template <class T>
class HeapNode
{
private:
	HeapNode<T> *m_pPrevious, *m_pNext, , *m_pChild, *m_pParent;

	T m_priority;
	int m_iDegree;
	bool m_bMarked;
public:
	friend class FibonacciHeap<T>;

	HeapNode<T> *getPrev() { return m_pPrevious; }
	HeapNode<T> *getNext() { return m_pNext; }
	HeapNode<T> *getChild() { return m_pChild; }
	HeapNode<T> *getParent() { return m_pParent; }

	T getPriority() { return m_priority; }

	bool isMarked() { return m_bMarked; }
};
*/
template <class T>
class FibonacciHeap
{
protected:
	HeapNode<T> *m_pRoot;

public:
	FibonacciHeap();

	virtual ~FibonacciHeap();

	virtual void push(T priority);

	virtual void merge(FibonacciHeap &other);

	virtual bool isEmpty() const;

	virtual T maximum() const;

	virtual T extractMaximum();

private:
	void delete_(HeapNode<T> *node);

	void addChild(HeapNode<T> *parent, HeapNode<T> *child);

	void unMarkAndUnParentAll(HeapNode<T> *node);

	HeapNode<T> *merge(HeapNode<T> *a, HeapNode<T> *b);

	HeapNode<T> *removeMaximum(HeapNode<T> *node);
};

template <class T>
FibonacciHeap<T>::FibonacciHeap() : m_pRoot(nullptr) {}

template <class T>
FibonacciHeap<T>::~FibonacciHeap()
{
	if (m_pRoot)
		delete_(m_pRoot);
}

template <class T>
void FibonacciHeap<T>::push(T priority)
{
	HeapNode<T> *node = new HeapNode<T>;
	node->m_priority = priority;
	node->m_pPrevious = node->m_pNext = node;
	node->m_iDegree = 0;
	node->m_bMarked = false;
	node->m_pChild = nullptr;
	node->m_pParent = nullptr;

	m_pRoot = merge(m_pRoot, node);
}

template <class T>
void FibonacciHeap<T>::merge(FibonacciHeap &other)
{
	m_pRoot = merge(m_pRoot, other.m_pRoot);
	other.m_pRoot = nullptr;
}

template <class T>
bool FibonacciHeap<T>::isEmpty() const
{
	return m_pRoot == nullptr;
}

template <class T>
T FibonacciHeap<T>::maximum() const
{
	return m_pRoot->m_priority;
}

template <class T>
T FibonacciHeap<T>::extractMaximum()
{
	HeapNode<T> *old = m_pRoot;
	m_pRoot = removeMaximum(m_pRoot);
	T ret = old->m_priority;
	delete old;
	return ret;
}

template <class T>
HeapNode<T> *FibonacciHeap<T>::merge(HeapNode<T> *a, HeapNode<T> *b)
{
	if (a == nullptr)
		return b;
	if (b == nullptr)
		return a;
	// делаем a бОльшим из двух
	if (a->m_priority < b->m_priority)
	{
		HeapNode<T> *temp = a;
		a = b;
		b = temp;
	}

	HeapNode<T> *an = a->m_pNext;
	HeapNode<T> *bp = b->m_pPrevious;

	a->m_pNext = b;
	b->m_pPrevious = a;

	an->m_pPrevious = bp;
	bp->m_pNext = an;

	return a;
}

template <class T>
void FibonacciHeap<T>::delete_(HeapNode<T> *node)
{
	if (node != nullptr)
	{
		HeapNode<T> *c = node;

		do
		{
			HeapNode<T> *d = c;

			c = c->m_pNext;

			delete_(d->m_pChild);

			delete d;
		} while (c != node);
	}
}

template <class T>
void FibonacciHeap<T>::addChild(HeapNode<T> *parent, HeapNode<T> *child)
{
	HeapNode<T> *oldChild = parent->m_pChild;

	if (oldChild == nullptr)
	{
		parent->m_pChild = child;
		child->m_pParent = parent;

		return;
	}

	HeapNode<T> *next = oldChild->m_pNext;

	if (next)
	{
		next->m_pPrevious = child;
		child->m_pNext = next;
	}

	oldChild->m_pNext = child;
	child->m_pPrevious = oldChild;
}

template <class T>
void FibonacciHeap<T>::unMarkAndUnParentAll(HeapNode<T> *node)
{
	if (node == nullptr)
		return;

	HeapNode<T> *c = node;

	do
	{
		c->m_bMarked = false;
		c->m_pParent = nullptr;
		c = c->m_pNext;
	} while (c != node);
}

template <class T>
HeapNode<T> *FibonacciHeap<T>::removeMaximum(HeapNode<T> *node)
{
	if (node == nullptr)
		return node;

	unMarkAndUnParentAll(node->m_pChild);

	if (node->m_pNext == node)
		// один узел
		node = node->m_pChild;
	else
	{
		// много узлов, удалить максимум из списка и объединить node->m_pNext, node->m_pChild (левый ребенок поднялся вверх)
		HeapNode<T> *child = node->m_pChild,
					*childPrev = child->m_pPrevious;

		if(childPrev)
		{
			merge(childPrev,childNext);
			addChild(childPrev);
		}

		merge(node->m_pNext,child);
	}

	// Консолидация

	HeapNode<T> *trees[HEAP_MAX_TREES] = {nullptr};

	while (true)
	{
		if (trees[node->m_iDegree] != nullptr)
		{
			HeapNode<T> *t = trees[node->m_iDegree];
			if (t == node)
				break;
			trees[node->m_iDegree] = nullptr;
			if (node->m_priority > t->m_priority)
			{
				t->m_pPrevious->m_pNext = t->m_pNext;
				t->m_pNext->m_pPrevious = t->m_pPrevious;
				addChild(node, t);
			}
			else
			{
				t->m_pPrevious->m_pNext = t->m_pNext;
				t->m_pNext->m_pPrevious = t->m_pPrevious;
				if (node->m_pNext == node)
				{
					t->m_pNext = t->m_pPrevious = t;
					addChild(t, node);
					node = t;
				}
				else
				{
					node->m_pPrevious->m_pNext = t;
					node->m_pNext->m_pPrevious = t;
					t->m_pNext = node->m_pNext;
					t->m_pPrevious = node->m_pPrevious;
					addChild(t, node);
					node = t;
				}
			}
			continue;
		}
		else
		{
			trees[node->m_iDegree] = node;
		}
		node = node->m_pNext;
	}

	return node;
}

template<typename T>
void print_queue(T& q)
{
	while (!q.empty())
	{
		cout << q.top() << " ";
		q.pop();
	}

	cout << '\n';
}

int main(int argc, char* argv[])
{
	priority_queue<Student> pqueue_stud;
	
	pqueue_stud.push(Student("Danya","Lykov","Branks",true,2007,8));
	pqueue_stud.push(Student("Sanya","Lazarev","Moscow",true,2005,6));
	pqueue_stud.push(Student("Yarik","Malysh","Zamkad",true,2004,5));
	pqueue_stud.push(Student("German","Zaycev","Krasnodar",true,2004,4));
	pqueue_stud.push(Student("Senya","Lenin","Penza",true,2004,3));
	pqueue_stud.push(Student("Ksusha","Egorova","Zamkad",false,2004,2));

	print_queue(pqueue_stud); // Вывод по приоритету

	Heap<Student> heap_stud;

	heap_stud.push(Student("Danya","Lykov","Branks",true,2007,8));
	heap_stud.push(Student("Sanya","Lazarev","Moscow",true,2005,6));
	heap_stud.push(Student("Yarik","Malysh","Zamkad",true,2004,5));
	heap_stud.push(Student("German","Zaycev","Krasnodar",true,2004,4));
	heap_stud.push(Student("Senya","Lenin","Penza",true,2004,3));
	heap_stud.push(Student("Ksusha","Egorova","Zamkad",false,2004,2));

	heap_stud.remove(3);

	cout << heap_stud.extractMin(); // German

	FibonacciHeap<Student> fibheap_stud;

	fibheap_stud.push(Student("Danya","Lykov","Branks",true,2007,8));
	fibheap_stud.push(Student("Sanya","Lazarev","Moscow",true,2005,6));
	fibheap_stud.push(Student("Yarik","Malysh","Zamkad",true,2004,5));
	fibheap_stud.push(Student("German","Zaycev","Krasnodar",true,2004,4));
	fibheap_stud.push(Student("Senya","Lenin","Penza",true,2004,3));
	fibheap_stud.push(Student("Ksusha","Egorova","Zamkad",false,2004,2));

	cout << fibheap_stud.extractMaximum() << fibheap_stud.extractMaximum(); // Malysh, German

	return 0;
}