#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include "Figures.h"
#include "MyAlgoritms.h"

using namespace std;

void MapAlg(vector<Rectangle> rectangles, vector<Point> query) {

	//Для замера времени подготовки
	auto start = std::chrono::steady_clock::now();

	vector<int> x_coord;
	vector<int> y_coord;
	for (Rectangle rec : rectangles){
		x_coord.push_back(rec.left);
		x_coord.push_back(rec.right);
		y_coord.push_back(rec.bottom);
		y_coord.push_back(rec.top);
	}
	sort(x_coord.begin(), x_coord.end());
	sort(y_coord.begin(), y_coord.end());

	int n = x_coord.size();
	vector<vector<int>> map(n, vector<int>(n, 0));
	for (Rectangle rect : rectangles) {
		int x_id1 = find(x_coord, rect.left);
		int x_id2 = find(x_coord, rect.right);
		int y_id1 = find(y_coord, rect.bottom);
		int y_id2 = find(y_coord, rect.top);
		for (int i = x_id1; i < x_id2; i++) {
			for (int j = y_id1; j < y_id2; j++) {
				map[j][i] += 1;
			}
		}
	}

	//Для замера времени подготовки
	auto finish = std::chrono::steady_clock::now();
	auto prepare_time = std::chrono::duration_cast<std::chrono::microseconds>(finish - start);
	cout << "Map prepare: " << int(prepare_time.count()) << "\n";
	


	//Для замера времени обработки запросов
	auto w_start = std::chrono::steady_clock::now();
	
	for (Point po : query) {
		if ((po.x < x_coord[0]) || (po.y < y_coord[0])) {
			continue;
		}
		if ((po.x >= x_coord[n - 1]) || (po.y >= y_coord[n - 1])) {
			continue;
		}
		int x_ind = bin_find(x_coord, 0, n - 1, po.x);
		int y_ind = bin_find(y_coord, 0, n - 1, po.y);
		map[y_ind][x_ind];
	}

	//Для замера времени обработки запросов
	auto w_finish = std::chrono::steady_clock::now();
	auto work_time = std::chrono::duration_cast<std::chrono::microseconds>(w_finish - w_start);
	cout << "Map work: " << int(work_time.count()) << "\n";
}
