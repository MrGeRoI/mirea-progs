#include <chrono>

#include "dermo.hpp"
#include "unordered_dsu.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	
	// Замеры
	for (int i = 0; i < 20; i++)
	{
		LinMatrix<TEST_DIM> matrix;

		uniform_real_distribution<double> unif(-100.0, 100.0);
		default_random_engine re;

		for (int j = 0; j < TEST_DIM; j++)
			for (int k = 0; k < TEST_DIM; k++)
				matrix.setValue(j, k, unif(re));

		double eigenvalue = 1.0;
		LinVector<TEST_DIM> eigenvector;

		auto begin = chrono::steady_clock::now();

		powerIteration(matrix, eigenvalue, eigenvector, 100'000, __DBL_EPSILON__);

		auto end = chrono::steady_clock::now();
		int len = chrono::duration_cast<chrono::milliseconds>(end - begin).count();

		tsum += len;
		tmin = std::min(tmin,len);
		tmax = std::max(tmax,len);

		cout << "Elapsed: " << len << " ms\n";
	}
	
	return 0;
}