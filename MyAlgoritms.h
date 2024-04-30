#pragma once
#include "Figures.h"
#include <vector>

using namespace std;

void BruteAlg(vector<Rectangle> rectangles, vector<Point> query);
void MapAlg(vector<Rectangle> rectangles, vector<Point> query);
void TreeAlg(vector<Rectangle> rectangles, vector<Point> query);

int find(vector<int> vec, int val);
int bin_find(vector<int> vec, int l, int r, int val);
Node* BuildTree(int start, int end);
Node* UpdateTree(Node* root, int start, int end, int val);
