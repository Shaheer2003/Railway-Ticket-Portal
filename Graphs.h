#pragma once
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <windows.h>
#include <string>
#include <string.h>
#include <conio.h>
#include <cstring>
#include <ctime>
#include<time.h>
#include <vector>
#include "PQ.h"
using namespace std;
int c = 105;
class Node {
public:
	int distance;
	int time;
	bool present;
};

class Graph {
public:
	Node** adj_matrix;
	const int vertices = 20;
	const string cities[20] = { "Ecliptica", "Luminastra", "Quantumville", "Radiant-Peak",
	"Nebulora", "Stellaria", "Galactaria", "Astronova", "Celestialis", "Vortexburg",
	"Nebula-Heights", "Astralis", "Cosmosphere", "Galaxy-Haven", "Eclipsara", "Lunaris",
	"Starhaven", "Astrolynx", "Spectra-Springs", "Moonlight-City"
	};
	HashMapTable<string, int, 40> map;

	Graph() {
		for (int i = 0; i <= vertices; i++) {
			map.Insert(cities[i], i);
		}
		adj_matrix = new Node * [vertices];
		for (int i = 0; i < vertices; i++) {
			adj_matrix[i] = new Node[vertices];
			for (int j = 0; j < vertices; j++) {
				adj_matrix[i][j].present = false;
				adj_matrix[i][j].distance = 0;
				adj_matrix[i][j].time = 0;
			}
		}
	}
	void add_edge(int source, int dest) {
		int dist = (rand() + c) % 1000;
		int tim = (rand() + c) % 24 + 1;
		adj_matrix[source][dest].present = true;
		adj_matrix[dest][source].present = true;
		adj_matrix[source][dest].distance = dist;
		adj_matrix[dest][source].distance = dist;
		adj_matrix[source][dest].time = tim;
		adj_matrix[dest][source].time = tim;
	}
	void displayt() {
		for (int i = 0; i < vertices; i++) {
			for (int j = 0; j < vertices; j++) {
				cout << adj_matrix[i][j].time << " ";
			}
			cout << endl;
		}
	}
	void displayd() {
		for (int i = 0; i < vertices; i++) {
			for (int j = 0; j < vertices; j++) {
				cout << adj_matrix[i][j].distance << " ";
			}
			cout << endl;
		}
	}

};
class Trio {
public:
	int distance;
	int time;
	vector<int> predecessor;
};
class Train {
public:
	Graph graph;
	string name;
	int totalSeats = 100;
	Train() {

	}
	Train(string name) {
		this->name = name;
		srand(time(0));
		for (int i = 0; i < graph.vertices; i++) {
			for (int j = 0; j < graph.vertices; j++) {
				if (i != j) {
					graph.add_edge(i, j);
				}
			}
		}
		c += 50;
	}

	// Dijkstra's Algorithm using Priority Queue
	Trio Dijkstra(string cityD, string cityA) {
		int source = -1;
		int dest = -1;
		Trio trio;

		source = graph.map.Access(cityD);
		dest = graph.map.Access(cityA);
		int time = 0;
		// if both source and dest found then break
		if (source == -1 || dest == -1) {
			trio.distance = -1;
			trio.time = -1;
			return trio;
		}

		MinHeapPriorityQueue<int> priorityQueuedistance(graph.vertices);

		vector<int> distance(graph.vertices, INT_MAX);
		vector<int> timm(graph.vertices, INT_MAX);
		vector<int> predecessor1(graph.vertices, -1);

		distance[source] = 0;
		timm[source] = 0;
		priorityQueuedistance.push(source);

		while (priorityQueuedistance.getSize() > 0) {

			int u1 = priorityQueuedistance.pop();

			for (int v = 0; v < graph.vertices; v++) {
				if (graph.adj_matrix[u1][v].present == true) {
					int weight1 = graph.adj_matrix[u1][v].distance;
					int weight2 = graph.adj_matrix[u1][v].time;

					if (distance[v] > distance[u1] + weight1) {
						distance[v] = distance[u1] + weight1;
						timm[v] = timm[u1] + weight2;
						predecessor1[v] = u1;

						priorityQueuedistance.push(v);
					}
				}
			}
		}

		trio.distance = distance[dest];
		trio.predecessor = predecessor1;
		trio.time = timm[dest];

		return trio;
	}

	void print_path(string cityD, string cityA, vector<int>& predecessor) {
		cout << "Shortest Path: ";

		int source = graph.map.Access(cityD);
		int dest = graph.map.Access(cityA);
		int current = dest;
		vector<string> path;

		while (current != source) {
			path.push_back(graph.cities[current]);
			current = predecessor[current];
		}

		// Print the source city
		path.push_back(graph.cities[source]);

		for (int i = path.size() - 1; i >= 0; i--) {
			cout << path[i];
			if (i > 0) {
				cout << " -> ";
			}
		}
		cout << endl;
	}
};
