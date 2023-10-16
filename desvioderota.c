// Dijkstra Algorithm
int dijkstra(int origin, int destination) {
    cost[origin] = 0;
    enqueue(origin);
    while (!isEmpty()) {
        int i = dequeue();
        for (int j = 0; j < numCities; j++) {
            if (graph[i][j] != INT_MAX && cost[j] > cost[i] + graph[i][j]) {
                cost[j] = cost[i] + graph[i][j];
                enqueue(j);
            }
        }
    }
    return cost[destination];
}