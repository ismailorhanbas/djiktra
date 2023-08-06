#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

// Graph class
class Graph {
private:
    int num_vertices;
    vector<vector<int>> adjacency_list;

public:
    Graph(int num_vertices) : num_vertices(num_vertices) {
        adjacency_list.resize(num_vertices);
    }

    void addEdge(int from, int to, int weight) {
        adjacency_list[from].push_back(to);
        adjacency_list[from].push_back(weight);
    }

    int V() const { return num_vertices; }

    vector<int> neighbors(int vertex) const {
        return vector<int>(adjacency_list[vertex].begin(), adjacency_list[vertex].end());
    }
};

// Shortest Path Algorithm
class ShortestPath {
private:
    const Graph& graph;

public:
    ShortestPath(const Graph& graph) : graph(graph) {}

    vector<int> dijkstra(int source) {
        int num_vertices = graph.V();
        vector<int> distances(num_vertices, INT_MAX);
        distances[source] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({ 0, source });

        while (!pq.empty()) {
            int current_vertex = pq.top().second;
            int current_distance = pq.top().first;
            pq.pop();

            if (current_distance > distances[current_vertex]) continue;

            for (int i = 0; i < graph.neighbors(current_vertex).size(); i += 2) {
                int neighbor = graph.neighbors(current_vertex)[i];
                int edge_weight = graph.neighbors(current_vertex)[i + 1];

                int new_distance = current_distance + edge_weight;
                if (new_distance < distances[neighbor]) {
                    distances[neighbor] = new_distance;
                    pq.push({ new_distance, neighbor });
                }
            }
        }

        return distances;
    }
};

int main() {
    int num_vertices = 6;
    Graph graph(num_vertices);
    graph.addEdge(0, 1, 7);
    graph.addEdge(0, 2, 9);
    graph.addEdge(1, 2, 10);
    graph.addEdge(1, 3, 15);
    graph.addEdge(2, 4, 11);
    graph.addEdge(3, 4, 6);
    graph.addEdge(3, 5, 9);

    ShortestPath shortest_path_algo(graph);
    vector<int> distances = shortest_path_algo.dijkstra(0);

    int destination = 5;
    cout << "Shortest Distance from 0 to " << destination << ": " << distances[destination] << endl;

    return 0;
}
