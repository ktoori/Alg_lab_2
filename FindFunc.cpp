#include <iostream>
#include <vector>
#include "Figures.h"
#include "MyAlgoritms.h"

int find(vector<int> vec, int val) {
	int i = 0;
	while (val != vec[i]) i++;
	return i;
}

int bin_find(vector<int> vec, int l, int r, int val) {
	if (l > r) {
		return l - 1;
	}
	int mid = (l + r) / 2;
	if (val == vec[mid]) {
		return mid;
	}
	else if (val < vec[mid]) {
		return bin_find(vec, l, mid - 1, val);
	}
	else {
		return bin_find(vec, mid + 1, r, val);
	}
}