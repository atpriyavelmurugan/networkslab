#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct Edge {
    int to;
    bool is_original; 
    struct Edge* next;
} Edge;


void addEdge(Edge** adj, int u, int v, bool is_original) {
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->to = v;
    newEdge->is_original = is_original;
    newEdge->next = adj[u];
    adj[u] = newEdge;
}

int minReorder(int n, int** connections, int connectionsSize, int* connectionsColSize) {
    
    Edge** adj = (Edge**)calloc(n, sizeof(Edge*));
    
    for (int i = 0; i < connectionsSize; i++) {
        int u = connections[i][0];
        int v = connections[i][1];
        
        addEdge(adj, u, v, true);
        
        addEdge(adj, v, u, false);
    }

    
    int* queue = (int*)malloc(n * sizeof(int));
    bool* visited = (bool*)calloc(n, sizeof(bool));
    int head = 0, tail = 0;
    int change_count = 0;

    
    queue[tail++] = 0;
    visited[0] = true;

    
    while (head < tail) {
        int curr = queue[head++];

        Edge* edge = adj[curr];
        while (edge != NULL) {
            int neighbor = edge->to;
            
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                
               
                if (edge->is_original) {
                    change_count++;
                }
                
                queue[tail++] = neighbor;
            }
            edge = edge->next;
        }
    }

   
    for (int i = 0; i < n; i++) {
        Edge* edge = adj[i];
        while (edge != NULL) {
            Edge* temp = edge;
            edge = edge->next;
            free(temp);
        }
    }
    free(adj);
    free(queue);
    free(visited);

    return change_count;
}
