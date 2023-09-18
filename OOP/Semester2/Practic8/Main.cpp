#include <string>

#include "SplayTree.hpp"
#include "Residue.hpp"

// Данные о погоде
class Weather
{
public:
	std::string _city; // Город
	bool _clouds;	// Облака
	double _rainfall; // Осадки
	int _temperature; // Температура

	Weather()
	{
		_rainfall = 0.0;
		_temperature = 0;
		_clouds = false;
	}

	Weather(const char* city,bool clouds,double rainfall,int temperature)
	{
		_city = city;
		_clouds = clouds;
		_rainfall = rainfall;
		_temperature = temperature;
	}

	bool operator>(const Weather& weather)
	{
		if(_clouds > weather._clouds)
			return true;
		if(_rainfall > weather._rainfall)
			return true;
		if(_temperature > weather._temperature)
			return true;

		return false;
	}

	bool operator<(const Weather& weather)
	{
		if(_clouds < weather._clouds)
			return true;
		if(_rainfall < weather._rainfall)
			return true;
		if(_temperature < weather._temperature)
			return true;

		return false;
	}

	bool operator==(const Weather& weather)
	{
		return _city == weather._city && _clouds == weather._clouds;
	}

	Weather& operator=(const Weather& weather)
	{
		_city = weather._city;
		_clouds = weather._clouds;
		_rainfall = weather._rainfall;
		_temperature = weather._temperature;

		return *this;
	}

	friend std::ostream& operator<<(std::ostream& stream,const Weather& weather);

	~Weather() { };
};

std::ostream& operator<<(std::ostream& stream,const Weather& weather)
{
	return stream << weather._city << weather._clouds << " (" << weather._rainfall << "%, " << weather._temperature << ")";
}

template<class K,class V>
int get_height(Node<K,V>* node)
{
	int height = -1;
	while(node != nullptr)
	{
		node = node->GetParent();
		height++;
	}
	return height;
}

template<class K,class V>
void print(Node<K,V>* node)
{
	std::cout << std::endl << node->GetKey() << "\tHeight: " << get_height(node);
}

int main()
{
	SplayTree<long long,long long> splay;

	for(long long i = 5000; i < 5010; i++)
		splay.Push(i,get_high_order_element(i));

	// Провожу тест на поисках элементов максимального порядка в колцье
	splay.Push(61LL,get_high_order_element(61LL));
	splay.Push(800LL,get_high_order_element(800LL));
	splay.Push(55450LL,get_high_order_element(55450LL));
	splay.Push(2383254LL,get_high_order_element(2383254LL));
	splay.Push(316030564LL,get_high_order_element(316030564LL));
	splay.Push(730887505LL,get_high_order_element(730887505LL));
	splay.Push(1847653789LL,get_high_order_element(1847653789LL));
	splay.Push(1478783811LL,get_high_order_element(1478783811LL));

	std::cout << "Before:\t\t" << splay << std::endl;

	splay.Remove(splay.Find(2383254LL));
	splay.Remove(splay.Find(5005LL));

	std::cout << "Removed:\t" << splay << std::endl;

	std::ofstream ofs("splay.txt");

	ofs << splay;

	ofs.close();

	SplayTree<long long,long long> splay2;

	std::ifstream ifs("splay.txt");

	ifs >> splay2;

	ifs.close();

	// Проверяю как работает сохранение загрузка
	std::cout << "Loaded:\t\t" << splay2 << std::endl;

	SplayTree<std::string,Weather> weathers_today;

	weathers_today.Push(std::string("Moscow"),Weather("Moscow",false,0.1,18));
	weathers_today.Push(std::string("Balashikha"),Weather("Balashikha",false,0,19));
	weathers_today.Push(std::string("Saint-Petersburg"),Weather("Saint-Petersburg",true,0.8,12));
	weathers_today.Push(std::string("Vladivostok"),Weather("Vladivostok",true,0.3,15));
	weathers_today.Push(std::string("Podolsk"),Weather("Podolsk",true,0.1,16));
	weathers_today.Push(std::string("Bryansk"),Weather("Bryansk",true,0.5,14));
	weathers_today.Push(std::string("Kaliningrad"),Weather("Kaliningrad",true,0,21));

	std::cout << std::endl << "Weather before:" << std::endl;
	weathers_today.InOrder(print);

	std::cout << std::endl << "Start getting:" << std::endl;

	// Проверяю, как меняется структура дерева после обращения к узлу
	std::cout << "Temperature at Moscow:\t" << weathers_today.Find(std::string("Moscow"))->GetValue()._temperature << std::endl;
	std::cout << "Clouds at Saint-Petersburg:\t" << weathers_today.Find(std::string("Saint-Petersburg"))->GetValue()._clouds << std::endl;
	std::cout << "Randfall at Vladivostok:\t" << weathers_today.Find(std::string("Vladivostok"))->GetValue()._rainfall << std::endl;
	std::cout << "Clouds at Moscow:\t" << weathers_today.Find(std::string("Moscow"))->GetValue()._clouds << std::endl;
	std::cout << "Temperature at Saint-Petersburg:\t" << weathers_today.Find(std::string("Saint-Petersburg"))->GetValue()._temperature << std::endl;

	std::cout << std::endl << "Weather after:" << std::endl;
	weathers_today.InOrder(print);

	return 0;
}