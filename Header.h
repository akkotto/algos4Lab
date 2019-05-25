#pragma once
#define MAXCOST 100000000
#include "List.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

class Ford
{
public:
	struct Node {
		string a;
		string b;
		int cost;
		
		Node(string a1, string b1, int c1) { a = a1; b = b1; cost = c1; };
		Node() { cost = MAXCOST; };
	};

	struct Node2 {
		string a;
		int cost;

		friend bool operator == (const Node2& first, const Node2& second)
		{
			return first.a == second.a;
		}
		Node2(string a1, int cost1) { a = a1; cost = cost1; };
		Node2() { };
	};

	List<Node> listEdges; 
	List<Node2> listVertices;

	void readFile(string path);
	void split(string line);
	void test(string path);
	int find(string vertex);
	int min(int a, int b);
	int belmonFord(string a, string b, string path);
};

int Ford::find(string vertex)
{
	int index = -1;
	for (size_t i = 0; i < listVertices.get_size(); i++)
	{
		if (listVertices.at(i)->a == vertex)
			index = i;
	}
	return index;
}

void Ford::test(string path)
{
	readFile(path);
	for (size_t i = 0; i < listEdges.get_size(); i++)
		cout << listEdges.at(i)->a << ":::" << listEdges.at(i)->b << ":::" << listEdges.at(i)->cost << endl;
}

void Ford::readFile(string path)
{
	ifstream in("source.txt");
	string line;
	if (in.is_open())
		while (getline(in, line)) split(line);
}

void Ford::split(string line)
{
	if (line.length() > 0)
	{
		int startPos = 0;
		string output[4];
		for (int i = 0; i < 3; i++)
		{
			while (line[startPos] != ';')
			{
				output[i].push_back(line[startPos]);
				startPos++;
			}
			startPos++;
		}
		while (line[startPos] != '\0')
		{
			output[3].push_back(line[startPos]);
			startPos++;
		}
		for (int i = 0; i < 2; i++)
		{
			if (find(output[i]) == -1)
				listVertices.push_back(Node2(output[i], MAXCOST));
		}
		if (output[2] != "N/A")
			listEdges.push_back(Node(output[0], output[1], stoi(output[2])));
		if (output[3] != "N/A")
			listEdges.push_back(Node(output[1], output[0], stoi(output[3])));
	}
}

int Ford::min(int a, int b)
{
	if (a < b)
		return a;
	else
		return b;
}

int Ford::belmonFord(string a, string b, string path)
{
	readFile(path);
	int startIndex = find(a);
	int endIndex = find(b);
	listVertices.at(startIndex)->cost = 0;
	for (size_t i = 0; i < listVertices.get_size() - 1; ++i)
		for (size_t j = 0; j < listEdges.get_size(); ++j)
				listVertices.at(find(listEdges.at(j)->b))->cost = min(listVertices.at(find(listEdges.at(j)->b))->cost, listVertices.at(find(listEdges.at(j)->a))->cost + listEdges.at(j)->cost);
	return listVertices.at(endIndex)->cost;
}


