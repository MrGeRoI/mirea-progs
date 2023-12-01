#include <iostream>
#include <vector>
#include <queue>
#include <windows.h>

using namespace std;


class DijkstraExeption : public exception
{
public:
    virtual const char* what() const noexcept { return "The Edje Weight cannot be Negative!"; };
};

class BellmanFordExeption : public exception
{
public:
    virtual const char* what() const noexcept { return "Graph contains negative weight cycle!"; };
};



void print(const vector<int>& a)
{
    for (int x : a)
    cout << x << ' ';
    cout << '\n';
}


struct Flight
{
public:
    int lenght;
    int price;

    Flight(int len = 0.0, int pr = 0)
    {
        lenght = len;
        price = pr;
    }
};

class Aviacompany
{
private:
    vector<vector<Flight>> matrix;
public:
    Aviacompany(int points) : matrix(points)
    {
    for (int i = 0; i < points; i++)
        matrix[i].resize(points);
}

    Aviacompany(vector<vector<Flight>> flights) : matrix(flights) {}

    int edjes(bool x)
    {
        int n = matrix.size();
        int e = 0;
        if (x==0){
        for(int i = 0; i<n; i++)
        {
            for (int j=0; j<n; j++)
            {
                if(matrix[i][j].lenght!=0)
                    e++;
            }
        }}
        
        if (x==1){
        for(int i = 0; i<n; i++)
        {
            for (int j=0; j<n; j++)
            {
                if(matrix[i][j].price!=0)
                    e++;
            }
        }}
        return e;
    }
    
    
    void Dijkstra(int start, int to, vector<int>& pat, vector<int>& lens, bool a)
	{
        int n = matrix.size();

        // Массив для хранения времени до каждой вершины
        vector<int> time(n, 1000000);

        // Приоритетная очередь для хранения вершин с наименьшим временем
        priority_queue<pair<int, int>> pq;

        // Инициализация начальной вершины
        time[start] = 0;
        pq.push({ 0, start });

        // Массив для хранения предыдущей вершины
        vector<int> prev(n, -1);

        if (a == 1) //lenght
        {
            while (!pq.empty())
            {
                int u = pq.top().second;
                pq.pop();

            // Обход смежных вершин
            for (int v = 0; v < n; ++v)
            {
                if (matrix[u][v].lenght < 0)
                    throw DijkstraExeption();
                if (matrix[u][v].lenght > 0) // Проверка наличия рейса между вершинами
                {
                    int newTime = time[u] + matrix[u][v].lenght;
            
                    // Обновление времени до вершины, если найден более короткий путь
                    if (newTime < time[v])
                    {
                        time[v] = newTime;
                        prev[v] = u;
                        pq.push({ time[v], v });
                    }
                }
            }
        }
        }
        if (a == 0) //price
        {
            while (!pq.empty())
            {
                int v = pq.top().second;
                    pq.pop();
        
                    // Обход смежных вершин
                    for (int u = 0; u < n; ++u)
                    {
                        if (matrix[u][v].lenght < 0)
                            throw DijkstraExeption();
                        if (matrix[u][v].price > 0) // Проверка наличия рейса между вершинами
                        {
                            int newTime = time[v] + matrix[u][v].price;
        
                            // Обновление времени до вершины, если найден более короткий путь
                            if (newTime < time[u])
                            {
                                time[u] = newTime;
                                prev[u] = v;
                                pq.push({ time[u], u });
                            }
                        }
                    }
            }
        }
        vector<int> path;
        for (int i = to-1; i != -1; i = prev[i])
        {
            path.push_back(i+1);
        } 

		lens = time;
		pat = path;

	}
	void BestPrice(int start, int to)
	{
	    vector<int> path, lens;
		Dijkstra(start, to, path, lens, 1);
		cout << "The Best Price:" << '\n' << "Path: ";
	    print(path);
	    cout << "Path Lengths: ";
	    print(lens);
	    cout << '\n';
	}
	void BestLenght(int start, int to)
	{
		vector<int> path, lens;
		Dijkstra(start, to, path, lens, 0);
		cout << "The Best Length:" << '\n' << "Path: ";
	    print(path);
	    cout << "Path Lengths: ";
	    print(lens);
	    cout << '\n';
	}

    
    vector<vector<int>> WeightedList(bool x) 
    {
        
    vector<vector<int>> weightedList(edjes(x));
    int n = 0;
    for (int i = 0; i < matrix.size(); i++) 
        {
            for (int j = i+1; j < matrix[i].size(); j++) 
            {
                if (matrix[i][j].price != 0) 
                {
                    weightedList[n].push_back(i);
                    weightedList[n].push_back(j);
                    weightedList[n].push_back(matrix[i][j].price);
                    n++;
                }
                
            }
                
        }
    return weightedList;
    }
    
    vector<vector<int>> OrientWeightedList(bool x) 
    {
        vector<vector<int>> weightedList(edjes(x));
        if (x==0){ //lenght
        int n = 0;
        for (int i = 0; i < matrix.size(); i++) 
            {
                for (int j = 0; j < matrix[i].size(); j++) 
                {
                    if (matrix[i][j].lenght != 0) 
                    {
                        weightedList[n].push_back(i);
                        weightedList[n].push_back(j);
                        weightedList[n].push_back(matrix[i][j].lenght);
                        n++;
                    }
                }
            }}

        if (x==1){ //price
        int n = 0;
        for (int i = 0; i < matrix.size(); i++) 
            {
                for (int j = 0; j < matrix[i].size(); j++) 
                {
                    if (matrix[i][j].price != 0) 
                    {
                        weightedList[n].push_back(i);
                        weightedList[n].push_back(j);
                        weightedList[n].push_back(matrix[i][j].price);
                        n++;
                    }
                }
            }}
        return weightedList;
    }
    

    vector<int> BellmanFord(int start, bool x)
    {
        vector<vector<int>> graph = OrientWeightedList(x);
        cout << "Adjacency List" << '\n';
        for (int i = 0; i < graph.size(); i++) 
        {
            print(graph[i]);
        }
        // инициализируем расстояние до всех вершин
        int v = matrix.size();
        int p = edjes(x);
        
        
        vector<int> dis(v, 100000);
        // инициализируем начальную вершину
        dis[start] = 0;
        
        for (int i = 0; i < v - 1; i++) 
        {
            for (int j = 0; j < p; j++) 
            {
                if (dis[graph[j][0]] != 1000000 && dis[graph[j][0]] + graph[j][2] < dis[graph[j][1]])
                    dis[graph[j][1]] = dis[graph[j][0]] + graph[j][2];
            }
        }
        for (int i = 0; i < p; i++) {
            int x = graph[i][0];
            int y = graph[i][1];
            int weight = graph[i][2];
            if (dis[x] != 1000000 && dis[x] + weight < dis[y])
                throw BellmanFordExeption();
        }
        cout << "Path Lengths  " << start << ":    ";
        return dis;
    }
    
    
    
    void Floyd(bool x)
    {
        int inf = 100000;
        int v = matrix.size();
        
        vector<vector<int>> graph(v);
        if (x==0){
        for (int i = 0; i<v; i++)
        {
            for (int j = 0; j<v; j++)
            {
                if (matrix[i][j].lenght == 0)
                    graph[i].push_back(inf);
                else graph[i].push_back(matrix[i][j].lenght);
            }        
        }}
        if (x==1){
        for (int i = 0; i<v; i++)
        {
            for (int j = 0; j<v; j++)
            {
                if (matrix[i][j].price == 0)
                    graph[i].push_back(inf);
                else graph[i].push_back(matrix[i][j].price);
            }        
        }}

        for (int k = 0; k < v; k++) 
        {
            for (int i = 0; i < v; i++) 
            {
                for (int j = 0; j < v; j++) 
                {
                    if (graph[i][j] > (graph[i][k] + graph[k][j]) && (graph[k][j] != inf && graph[i][k] != inf))
                        {graph[i][j] = graph[i][k] + graph[k][j];}
                }
            }
        }
        cout << "The Path Matrix: " << '\n';
        for(int i = 0; i<v; i++)
        {
            for(int j = 0; j<v; j++)
            {
                if (i == j) {graph[i][j] = 0;}
                if (graph[i][j] == inf)
                    cout << "inf" << "  ";
                else cout << graph[i][j] << "    ";
            }
            cout << '\n';
        }
        cout << '\n';
    }
    
    
    friend ostream& operator<<(ostream& stream, const Flight& flight);
    
    
};


ostream& operator<<(ostream& stream, const Flight& flight)
{
    stream << flight.lenght << ' ' << flight.price;
    return stream;
}


int main(int argc, char* argv[])
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    //  Булево значение 0 - для поиска пути по lenght, 1 - price
    setlocale(LC_ALL, "Russian");
    
    Aviacompany avia({
        {Flight(), Flight(7,7), Flight(9,0), Flight(0,0), Flight(0,4), Flight(14,0)},
        {Flight(7,7), Flight(), Flight(10,5), Flight(15,0), Flight(0,0), Flight(0,2)},
        {Flight(9,0), Flight(10,5), Flight(), Flight(11,11), Flight(0,0), Flight(2,6)},
        {Flight(0,0), Flight(15,0), Flight(11,11), Flight(), Flight(6,8), Flight(0,9)},
        {Flight(0,4), Flight(0,0), Flight(0,0), Flight(6,8), Flight(), Flight(9,3)},
        {Flight(14,0), Flight(0,2), Flight(2,6), Flight(0,9), Flight(9,3), Flight()}
    });
 
 
    Aviacompany avia2({
        {Flight(), Flight(4,7), Flight(5,0), Flight(0,0)},
        {Flight(0,7), Flight(), Flight(0,5), Flight(0,0)},
        {Flight(0,0), Flight(0,5), Flight(), Flight(3,11)},
        {Flight(0,0), Flight(-10,0), Flight(0,11), Flight()},
    });
    
    Aviacompany avia3({
        {Flight(), Flight(4,7), Flight(5,0), Flight(0,0)},
        {Flight(0,7), Flight(), Flight(5,5), Flight(0,0)},
        {Flight(0,0), Flight(0,5), Flight(), Flight(3,11)},
        {Flight(0,0), Flight(-10,0), Flight(0,11), Flight()},
    });
    
    cout << "Dijkstra Algorithm" << '\n';
    avia.BestLenght(0, 4);
	avia.BestPrice(0, 5);
    
    cout << "Bellman-Ford Algorithm" << '\n';
    print(avia2.BellmanFord(0, 0));
    cout << '\n' << '\n';
    
    cout << "Graph contains negative weight cycle" << '\n';
    print(avia3.BellmanFord(0, 0));
    cout << endl;
    
    Aviacompany avia4({
        {Flight(), Flight(5,5), Flight(0,0), Flight(0,0)},
        {Flight(0,0), Flight(), Flight(3,5), Flight(0,3)},
        {Flight(0,-3), Flight(0,0), Flight(), Flight(1,0)},
        {Flight(0,2), Flight(0,0), Flight(0,-5), Flight()},
    });
    
    Aviacompany avia5({
        {Flight(), Flight(8,5), Flight(5,0)},
        {Flight(3,0), Flight(), Flight(0,5)},
        {Flight(0,-3), Flight(2,0), Flight()}
    });
    
    
    cout << "Floyd Algorithm" << '\n';
    avia4.Floyd(0);
    avia4.Floyd(1);
    
    cout << "Floyd Algorithm from 1 Chapter: " << '\n';
    avia5.Floyd(0);
 
}