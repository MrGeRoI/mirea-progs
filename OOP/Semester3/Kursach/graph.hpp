#include <vector>
#include <iostream>

using namespace std;

template<class T>
class Graph
{
	class Node;

private:
	vector<Node> _nodes;

public:

	class Node
	{
		T _data;
	}
}