namespace
{

	class graph
	{
	private:
		int _capacity;

		bool **_links;
	public:
		graph(int capacity) : _capacity(capacity)
		{
			_links = new bool*[capacity];

			for(int i = 0; i < capacity;i++)
				_links[i] = new bool[capacity];
		}
	};
}