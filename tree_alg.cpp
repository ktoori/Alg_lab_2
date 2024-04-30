#include <iostream>
#include <vector>
#include "Figures.h"
#include "MyAlgoritms.h"
#include <algorithm>
#include <chrono>

using namespace std;

Node* BuildTree(int start, int end) {
	if (start == end) {
		Node* node = new Node(start, end);
		return node;
	}

	int mid = (start + end) / 2;
	Node* left = BuildTree(start, mid);
	Node* right = BuildTree(mid + 1, end);

	Node* node = new Node(start, end);
	node->left = left;
	node->right = right;
	return node;
}

Node* UpdateTree(Node* root, int start, int end, int val) {
	if ((start > root->end) || (end < root->start)) {
		return root;
	}
	if ((start <= root->start) && (end >= root->end)) {
		Node* new_root = new Node(root->start, root->end);
		new_root->left = root->left;
		new_root->right = root->right;
		new_root->mod = root->mod + val;
		return new_root;
	}
	Node* new_root = new Node(root->start, root->end);
	new_root->mod = root->mod;
	new_root->left = UpdateTree(root->left, start, end, val);
	new_root->right = UpdateTree(root->right, start, end, val);
	return new_root;
}

int GetAns(Node* root, int y_ind, int count) {
	if (root != NULL) {
		count += root->mod;
		if (root->left != NULL && root->left->start <= y_ind && y_ind <= root->left->end) {
			return GetAns(root->left, y_ind, count);
		}
		else if (root->right != NULL && root->right->start <= y_ind && y_ind <= root->right->end) {
			return GetAns(root->right, y_ind, count);
		}
		else return count;
	}
	return 0;
}

void TreeAlg(vector<Rectangle> rectangles, vector<Point> query) {

	//Для замера времени подготовки
	auto start = std::chrono::steady_clock::now();

	vector<int> x_coord;
	vector<int> y_coord;
	for (Rectangle rec : rectangles) {
		x_coord.push_back(rec.left);
		x_coord.push_back(rec.right);
		y_coord.push_back(rec.bottom);
		y_coord.push_back(rec.top);
	}
	sort(x_coord.begin(), x_coord.end());
	sort(y_coord.begin(), y_coord.end());

	int n = x_coord.size();
	vector<Event> events(n);
	for (Rectangle rec : rectangles) {
		events.push_back(Event(find(x_coord, rec.left), find(y_coord, rec.bottom), find(y_coord, rec.top) - 1, 1));
		events.push_back(Event(find(x_coord, rec.right), find(y_coord, rec.bottom), find(y_coord, rec.top) - 1, -1));
	}
	sort(events.begin(), events.end(), Event());

	vector<Node*> ptree(n);
	ptree[0] = BuildTree(0, n - 1);
	int event_ind = 0;
	for (Event e : events) {
		ptree[e.x] = UpdateTree(ptree[event_ind], e.y1, e.y2, e.state);
		event_ind = e.x;
	}

	//Для замера времени подготовки
	auto finish = std::chrono::steady_clock::now();
	auto prepare_time = std::chrono::duration_cast<std::chrono::microseconds>(finish - start);
	cout << "Tree prepare: " << int(prepare_time.count()) << "\n";

	//Для замера времени обработки запросов
	auto t_start = std::chrono::steady_clock::now();

	for (Point po : query) {
		int x_ind = bin_find(x_coord, 0, n - 1, po.x);
		int y_ind = bin_find(y_coord, 0, n - 1, po.y);

		if ((po.x < x_coord[0]) || (po.y < y_coord[0])) {
			continue;
		}
		if ((po.x > x_coord[n - 1]) || (po.y > y_coord[n - 1])) {
			//cout << 0 << " ";
			continue;
		}
		while (ptree[x_ind] == NULL)
			x_ind = x_ind - 1;

		Node* root = ptree[x_ind];
		int count = GetAns(root, y_ind, 0);
		//cout << count << " ";
	}
	//Для замера времени обработки запросов
	auto t_finish = std::chrono::steady_clock::now();
	auto work_time = std::chrono::duration_cast<std::chrono::microseconds>(t_finish - t_start);
	cout << "Tree work: " << int(work_time.count()) << "\n";
};