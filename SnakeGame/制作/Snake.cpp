#include"Snake.h"

void Snake::InsertHead(vector2 pos)
{
	SnakeNode* newNode = new SnakeNode(pos);
	newNode->next = first;
	first = newNode;
}

void Snake::DeleteLast()
{
	if (first == 0)
	{
		return;
	}

	SnakeNode* secondLast = first;
	while (secondLast->next->next != 0)
	{
		secondLast = secondLast->next;
	}

	delete (secondLast->next);
	secondLast->next = NULL;
}
int Snake::SearchNode(vector2 pos)
{
	if (first == 0)
	{
		return -1;
	}

	SnakeNode* current = first;

	int i = 0;
	while (current->next != 0)
	{
		if ((current->pos.x + LENGTH > pos.x && pos.x > current->pos.x - LENGTH) &&
			(current->pos.y + LENGTH > pos.y && pos.y > current->pos.y - LENGTH))
		{
			return i;
		}
		current = current->next;
		i++;
	}
	return -1;
}
int Snake::SearchBodyNode(vector2 pos)
{
	if (first == 0)
	{
		return -1;
	}

	SnakeNode* current = first->next;
	int i = 0;
	while (current->next != 0)
	{
		if ((current->pos.x + LENGTH > pos.x && pos.x > current->pos.x - LENGTH) &&
			(current->pos.y + LENGTH > pos.y && pos.y > current->pos.y - LENGTH))
		{
			return i;
		}
		current = current->next;
		i++;
	}
	return -1;
}
