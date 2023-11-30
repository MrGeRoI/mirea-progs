#include <iostream>
#include <vector>
#include <queue>

using namespace std;

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
    vector<int> path;

public:
    Aviacompany(int points) : matrix(points)
    {
        for (int i = 0; i < points; i++)
            matrix[i].resize(points);
    }

    Aviacompany(vector<vector<Flight>> flights) : matrix(flights) {}

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

        if (a == 1)
        {
            while (!pq.empty())
            {
                int u = pq.top().second;
                pq.pop();

                // Обход смежных вершин
                for (int v = 0; v < n; ++v)
                {
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
        if (a == 0)
        {
            while (!pq.empty())
            {
                int v = pq.top().first;
                pq.pop();

                // Обход смежных вершин
                for (int u = 0; u < n; ++u)
                {
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
        for (int i = to; i != -1; i = prev[i])
        {
            path.push_back(i + 1);
        }
        lens = time;
        pat = path;

    }
    void BestPrice(int start, int to, vector<int>& pat, vector<int>& lens)
    {
        Dijkstra(start, to, pat, lens, 1);
    }
    void BestLenght(int start, int to, vector<int>& pat, vector<int>& lens)
    {
        Dijkstra(start, to, pat, lens, 0);
    }

    friend ostream& operator<<(ostream& stream, const Flight& flight);

};
ostream& operator<<(ostream& stream, const Flight& flight)
{
    stream << flight.lenght << ' ' << flight.price;
    return stream;
}

void print(const vector<int>& a)
{
    for (int x : a)
        cout << x << ' ';
    cout << '\n';
}


int main(int argc, char* argv[])
{
    Aviacompany avia({
     {Flight(), Flight(7,7), Flight(9,0), Flight(0,0), Flight(0,4), Flight(14,0)},
     {Flight(7,7), Flight(), Flight(10,5), Flight(15,0), Flight(0,0), Flight(0,2)},
     {Flight(9,0), Flight(10,5), Flight(), Flight(11,11), Flight(0,0), Flight(2,6)},
     {Flight(0,0), Flight(15,0), Flight(11,11), Flight(), Flight(6,8), Flight(0,9)},
     {Flight(0,4), Flight(0,0), Flight(0,0), Flight(6,8), Flight(), Flight(9,3)},
     {Flight(14,0), Flight(0,2), Flight(2,6), Flight(0,9), Flight(9,3), Flight()}
        });

    vector<int> path_price, lens_price;
    vector<int> path_lenght, lens_lenght;
    avia.BestLenght(0, 4, path_lenght, lens_lenght);
    avia.BestPrice(0, 5, path_price, lens_price);

    cout << "Best Price:" << '\n';
    print(path_price);
    print(lens_price);
    cout << "Best Lenght:" << '\n';
    print(path_lenght);
    print(lens_lenght);

    cout << endl;
}