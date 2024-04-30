#pragma once

class Point {
public:
	int x, y;
	Point(){
		x = 0;
		y = 0;
	}
	Point(int x_, int y_){
		x = x_;
		y = y_;
	}
};

class Rectangle {
public:
	int left, bottom, right, top;
	Rectangle(int l, int b, int r, int t){
		left = l;
		bottom = b;
		right = r;
		top = t;
	}
};

class Node {
public:
	int start, end, mod;
	Node* left;
	Node* right;

	Node(int start_, int end_) {
		start = start_;
		end = end_;
		mod = 0;
		left = NULL;
		right = NULL;
	}
};

class Event {
public:
	int x, y1, y2, state;
	Event() {
		x = 0;
		y1 = 0;
		y2 = 0;
		state = 0;
	};
	Event(int x_, int y1_, int y2_, int state_) {
		x = x_;
		y1 = y1_;
		y2 = y2_;
		state = state_;
	}
	bool operator()(const Event& a, const Event& b) const
	{
		return a.x < b.x;
	}

};