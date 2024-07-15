#pragma once
#include<stdio.h>

const int LENGTH = 10;

struct vector2 {
	float x;
	float y;
};

class Snake;

class SnakeNode {
private:
	vector2 pos;
	SnakeNode* next;

public:
	SnakeNode(vector2 p) :pos(p), next(0) {};

	vector2 GetPos() { return pos; };
	SnakeNode* GetNext() { return next; };

	friend class Snake;
};

class Snake {
private:
	SnakeNode* first;

public:
	Snake() :first(0) {};
	void InsertHead(vector2 pos);
	void DeleteLast();
	int SearchNode(vector2 pos);
	int SearchBodyNode(vector2 pos);

	SnakeNode* GetFirst() { return first; };
};
