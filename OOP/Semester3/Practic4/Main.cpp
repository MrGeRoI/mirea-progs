#include <string>

#include "../Student.hpp"
#include "SplayTree.hpp"
#include "MultiTree.hpp"

using namespace std;

template <class K, class V>
void print(Node<K, V> *node)
{
	cout << endl
		 << node->GetKey() << node->GetValue() << endl;
}

int main()
{
	// Дерево с итератором
	Tree<string, Student> tree;

	tree.Push("Danaya",Student("Danya","Lykov","Branks",true,2007,8));
	tree.Push("Sanya",Student("Sanya","Lazarev","Moscow",true,2005,6));
	tree.Push("Malysh",Student("Yarik","Malysh","Zamkad",true,2004,5));
	tree.Push("German",Student("German","Zaycev","Krasnodar",true,2004,4));
	tree.Push("Senya",Student("Senya","Lenin","Penza",true,2004,3));
	tree.Push("Pepsi",Student("Ksusha","Egorova","Zamkad",false,2004,2));

	// Вывод по порядку
	for(TreeIterator<string, Student> it = tree.begin();it != tree.end(); it++)
		cout << (*it).GetValue() << endl;

	Student found = tree.Find("Malysh")->GetValue();

	// Расширяющиеся дерево (элементы с одинаковыми ключами хранятся справа)
	SplayTree<string, Student> stree;

	tree.Push("KMBO001",Student("Yarik","Malysh","Zamkad",true,2004,5));
	tree.Push("KMBO002",Student("Danya","Lykov","Branks",true,2007,8));
	tree.Push("KMBO003",Student("Sanya","Lazarev","Moscow",true,2005,6));
	tree.Push("KMBO004",Student("German","Zaycev","Krasnodar",true,2004,4));
	tree.Push("KMBO005",Student("Senya","Lenin","Penza",true,2004,3));
	tree.Push("KMBO006",Student("Ksusha","Egorova","Zamkad",false,2004,2));

	// Обращаемся к узлам
	tree.Find("KMBO006"); 
	tree.Find("KMBO001");
	tree.Find("KMBO006");
	tree.Find("KMBO001");
	tree.Find("KMBO006");
	tree.Find("KMBO002");
	tree.Find("KMBO001");

	// Теперь в корне и  его окрестности находятся значения, к которым чаще всего обращались
	cout << tree.GetRoot()->GetValue() << ", " <<
		tree.GetRoot()->GetRight()->GetValue() <<
		tree.GetRoot()->GetLeft()->GetValue() << endl;

	// Дерево с повторяющимися ключами по списку
	MultiTree<int, string> mtree;

	mtree.Push(3, "hello");
	mtree.Push(3, "hello2");
	mtree.Push(3, "hello3");

	mtree.Push(4, "world");

	IteratedLinkedList<string> elems = mtree[3];

	cout << elems << endl; // "hello", "hello2", "hello3"

	return 0;
}