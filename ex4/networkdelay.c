#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INF 999999

int networkDelayTime(int** times, int timesSize, int* timesColSize, int n, int k) {

    int** adj = (int**)malloc((n + 1) * sizeof(int*));
    for (int i = 0; i <= n; i++) {
        adj[i] = (int*)malloc((n + 1) * sizeof(int));
        for (int j = 0; j <= n; j++) {
            adj[i][j] = (i == j) ? 0 : INF;
        }
    }

    
    for (int i = 0; i < timesSize; i++) {
        int u = times[i][0];
        int v = times[i][1];
        int w = times[i][2];
        adj[u][v] = w;
    }

  
    int* dist = (int*)malloc((n + 1) * sizeof(int));
    bool* visited = (bool*)calloc((n + 1), sizeof(bool));
    
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
    }
    
   
    dist[k] = 0;

   
    for (int count = 1; count <= n; count++) {
        int u = -1;
        int minDist = INF;

        
        for (int i = 1; i <= n; i++) {
            if (!visited[i] && dist[i] < minDist) {
                minDist = dist[i];
                u = i;
            }
        }

       
        if (u == -1) break;

        visited[u] = true;

       
        for (int v = 1; v <= n; v++) {
            if (!visited[v] && adj[u][v] != INF) {
                if (dist[u] + adj[u][v] < dist[v]) {
                    dist[v] = dist[u] + adj[u][v];
                }
            }
        }
    }

    
    int maxDelay = 0;
    for (int i = 1; i <= n; i++) {
        if (dist[i] == INF) {
            maxDelay = -1; 
            break;
        }
        if (dist[i] > maxDelay) {
            maxDelay = dist[i];
        }
    }

    
    for (int i = 0; i <= n; i++) {
        free(adj[i]);
    }
    free(adj);
    free(dist);
    free(visited);

    return maxDelay;
}
