#include <vector>
#include <iostream>

using namespace std;

template<class T>
class Graph
{
public:
	class Node;

private:
	vector<Node> _nodes;

public:
	class Node
	{
		friend class Graph;

	private:
		T _data;
		vector<Node*> _neighbours;

	public:
		Node(T data) { _data = data; }
		Node(const Node& other) { _data = other._data; }

		Node& operator=(const Node& other) { _data = other._data; }

		T GetData() const { return _data; }
		void SetData(T data) { _data = data; }

		const vector<Node*>& GetNeighbours() const { return _neighbours; }
		vector<Node*>& GetNeighbours() { return _neighbours; }

		Link(Node* node)
		{
			_neighbours.push_back(node);
			node->_neighbours.push_back(this);
		}

		const T& operator*() const { return _data; }
		T& operator*() { return _data; }
	}

	const vector<Node*> GetNodes() const { return _nodes; }
	vector<Node*>& GetNodes() { return _nodes; }
};