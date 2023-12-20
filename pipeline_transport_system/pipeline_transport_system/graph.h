#pragma once
#include <unordered_set>
#include <set>
#include <vector>
#include <queue>
#include "app.h"



class Graph {

public:

	Graph(App& app);
	int getValue(std::vector<int> arr, int index);
	int getIndex(App& app, int value);

	bool hasCycle(int vertex, std::unordered_set<int>& visited, std::unordered_set<int>& recStack) const;
	bool isDAG() const;
	void dfs(int v, std::vector<bool>& visited, std::vector<int>& order);
	std::vector<int> topologicalSort();

	double shortest_path(App& app, int start, int end);

	bool bfsDinitz(int source, int sink, std::vector<int>& level);

	double dfsDinitz(int u, int sink, double flow, std::vector<int>& level, std::vector<int>& start);

	double dinitz_algorithm(App& app, int st, int end);
private:
	size_t V = 0;
	std::vector<std::vector<double>> capacity;
	std::vector<int> vertices;
	std::unordered_map<int, Edge> edges;
	std::vector<std::vector<bool>> adj;
    std::vector<std::vector<Edge>> adj_list;
	std::vector<double> distances;
	

};
