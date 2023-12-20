#include <set>
#include <unordered_set>

#include "app.h"
#include "graph.h"

Graph::Graph(App& app) : edges(app.getEdges()) {
	std::set<int> vert;
	for (const auto& [id, edge] : edges) {
		vert.insert(edge.start);
		vert.insert(edge.end);
	}
	for (int i : vert) {
		vertices.push_back(i);
	}
	V = vertices.size();
	adj.resize(V, std::vector<bool>(V, false));
	adj_list.resize(V);
	capacity.resize(V, std::vector<double>(V, 0.0));

	for (auto& [id, edge] : edges) {
		int i = getIndex(app, edge.start);
		int j = getIndex(app, edge.end);
		edge.weight = app.getPipes().at(id).getWeight();
		adj[i][j] = true;
		capacity[i][j] = app.getPipes().at(id).getCapacity();
		adj_list[i].push_back(edge);
		edge.capacity = app.getPipes().at(id).getCapacity();
	}
}

int Graph::getValue(std::vector<int> arr, int index) {
	return arr[index];
}

int Graph::getIndex(App& app, int value) {

	std::vector<int> array;
	for (auto& [id, edge] : app.getStations()) {
		array.push_back(id);
	}
	for (int i = 0; i < array.size(); i++) {
		if (array[i] == value) {
			return i;
		}
	}
}

bool Graph::hasCycle(int vertex, std::unordered_set<int>& visited, std::unordered_set<int>& recStack) const {
	visited.insert(vertex);

	for (const auto& [pipe_id, edge] : edges) {
		if (edge.start == vertex) {
			recStack.insert(vertex);
		}
		else if (edge.end == vertex) {
			if (recStack.find(edge.end) != recStack.end()) {
				recStack.erase(vertex);
				return true;
			}
		}
	}

	return false;
}

bool Graph::isDAG() const {
	std::unordered_set<int> visited;
	std::unordered_set<int> recStack;

	for (const auto& [pipe_id, edge] : edges) {
		int vertex = edge.start;
		if (visited.find(vertex) == visited.end() && hasCycle(vertex, visited, recStack)) {
			return false;
		}
	}

	return true;
}

void Graph::dfs(int v, std::vector<bool>& visited, std::vector<int>& order) {
	visited[v] = true;

	for (int u = 0; u < adj[v].size(); u++) {
		if (adj[v][u] && !visited[u]) {
			dfs(u, visited, order);
		}
	}

	order.push_back(getValue(vertices, v));
}

std::vector<int> Graph::topologicalSort() {
	if (edges.empty()) {
		std::cout << "The graph is empty. You can't do topological sorting" << std::endl;
		return {};
	}
	if (!isDAG()) {
		std::cout << "The graph contains a cycle. You can't do topological sorting" << std::endl;
		return {};
	}

	int V = adj.size();
	std::vector<bool> visited(V, false);
	std::vector<int> order;

	for (int v = 0; v < V; ++v) {
		if (!visited[v]) {
			dfs(v, visited, order);
		}
	}

	std::reverse(order.begin(), order.end());

	return order;
}
double Graph::shortest_path(App& app, int start, int end) {

	int s = getIndex(app, start);
	int n = adj_list.size();
	distances.assign(app.getStations().size(), DBL_MAX);
	distances[s] = 0;

	std::vector<int> path;
	path.push_back(start);

	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

	pq.push({ 0, s });

	while (!pq.empty()) {
		int u = pq.top().second;
		int d = pq.top().first;
		pq.pop();

		if (d > distances[u]) continue;

		for (Edge& e : adj_list[u]) {
			int ve = e.end;
			int v = getIndex(app, ve);
			int w = e.weight;
			if (w != 0 && distances[u] + w < distances[v]) {
				path.push_back(v);
				distances[v] = distances[u] + w;
				pq.push({ distances[v], v });
			}
		}
	}
	std::vector<int> array;
	for (auto& [id, edge] : app.getStations()) {
		array.push_back(id);
	}
	for (int i = 0; i < path.size(); i++) {
		path[i] = getValue(array, path[i]);
	}
	std::reverse(path.begin(), path.end());

	std::vector<double> final_path;

	int index = getIndex(app, end);

	return distances[index];


}

bool Graph::bfsDinitz(int source, int sink, std::vector<int>& level) {
	level.assign(V, -1);
	level[source] = 0;
	std::queue<int> q;
	q.push(source);

	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int v = 0; v < V; ++v) {
			if (level[v] < 0 && capacity[u][v] > 0) {
				level[v] = level[u] + 1;
				q.push(v);
			}
		}
	}

	return level[sink] >= 0;
}

double Graph::dfsDinitz(int u, int sink, double flow, std::vector<int>& level, std::vector<int>& start) {
	if (u == sink) {
		return flow;
	}

	for (int& v = start[u]; v < V; ++v) {
		if (capacity[u][v] > 0 && (level[u] + 1 == level[v])) {
			double currFlow = std::min(flow, capacity[u][v]);
			double minPathFlow = dfsDinitz(v, sink, currFlow, level, start);

			if (minPathFlow > 0) {
				capacity[u][v] -= minPathFlow;
				capacity[v][u] += minPathFlow;
				return minPathFlow;
			}
		}
	}

	return 0;
}

double Graph::dinitz_algorithm(App& app, int st, int end) {
	double maxFlow = 0;

	std::vector<int> level(V, -1);
	std::vector<int> start(V, 0);

	int source = getIndex(app, st);
	int sink = getIndex(app, end);

	while (bfsDinitz(source, sink, level)) {
		start.assign(V, 0);
		while (double flow = dfsDinitz(source, sink, std::numeric_limits<int>::max(), level, start)) {
			maxFlow += flow;
		}
	}

	return maxFlow;
}