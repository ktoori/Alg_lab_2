#include <iostream>
#include <vector>
#include "Figures.h"
#include "MyAlgoritms.h"

using namespace std;

void BruteAlg(vector<Rectangle> rectangles, vector<Point> query){
	for (Point po : query) {
		int count = 0;
		for (auto& rec : rectangles) {
			if ((rec.left <= po.x) && (rec.bottom <= po.y) && (rec.right > po.x) && (rec.top > po.y)) {
				count++;
			}
		}
	}
}