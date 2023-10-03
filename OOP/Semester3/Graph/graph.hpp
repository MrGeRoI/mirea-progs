#include <vector>
#include <iostream>

using namespace std;

namespace Untitled
{
	template<class T>
	class NodeGraph;

	template<class T>
	class Node
	{
		friend class NodeGraph;

	private:
		T _data;
		vector<Node*> _neighbours;

	public:
		Node(T data) { _data = data; }
		Node(const Node& other) { _data = other._data; }

		Node& operator=(const Node& other) { _data = other._data; }

		const vector<Node*>& Neighbours() const { return _neighbours; }
		vector<Node*>& Neighbours() { return _neighbours; }

		Link(Node* node)
		{
			_neighbours.push_back(node);
			node->_neighbours.push_back(this);
		}

		const T& operator*() const { return _data; }
		T& operator*() { return _data; }
	};

	template<class T>
	class NodeGraph
	{
	protected:
		vector<Node<T>> _nodes;

	public:
		const vector<Node<T>*>& Nodes() const { return _nodes; }
		vector<Node<T>*>& Nodes() { return _nodes; }
	};
}