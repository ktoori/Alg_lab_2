#include <iostream>
#include <vector>
#include "Figures.h"
#include "MyAlgoritms.h"
#include <chrono>
#include <cmath>

using namespace std;

unsigned long int powmod(unsigned long int num, unsigned long int pow, unsigned long int mod)
{
	if (pow == 0)
		return 1;

	if (pow % 2 == 0) {
		long long z = powmod(num, pow / 2, mod);
		return (z * z) % mod;
	}
	else {
		long long z = powmod(num, (pow - 1) / 2, mod);
		return (num * z * z) % mod;
	}
}

int main(){
	vector<Rectangle> rectangles = {};
	vector<Point> queries = {};
	for (int N = 11; N < pow(2, 10);) {
		for (int i = 1; i < N; i++) {
			rectangles.push_back(Rectangle(10 * i, 10 * i, 10 * (2*N - i), 10 * (2*N - i)));
		}
		for (int j = 0; j < 1000; j++) {
			queries.push_back(Point(powmod(2693 * j, 31, 20 * N), powmod(2693 * j, 31, 20 * N)));
			//cout << powmod(2693 * j, 31, 20 * N) << " " << powmod(2693 * j, 31, 20 * 10000);
		}

		cout << "Number of rectangles: " << N-1 << " ";
		
		auto start1 = std::chrono::steady_clock::now();
		BruteAlg(rectangles, queries);
		auto finish1 = std::chrono::steady_clock::now();
		auto func_time_1 = std::chrono::duration_cast<std::chrono::microseconds>(finish1 - start1);
		cout << "Brute Alg: " << int(func_time_1.count()) << "\n";
		
		auto start2 = std::chrono::steady_clock::now();
		MapAlg(rectangles, queries);
		auto finish2 = std::chrono::steady_clock::now();
		auto func_time_2 = std::chrono::duration_cast<std::chrono::microseconds>(finish2 - start2);
		cout << "Map Alg: " << int(func_time_2.count()) << "\n";
		
		auto start3 = std::chrono::steady_clock::now();
		TreeAlg(rectangles, queries);
		auto finish3 = std::chrono::steady_clock::now();
		auto func_time_3 = std::chrono::duration_cast<std::chrono::microseconds>(finish3 - start3);
		cout << "Tree Alg: " << int(func_time_3.count()) << "\n";
		N += 30;
	}
}
