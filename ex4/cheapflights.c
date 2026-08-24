#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 9999999

int findCheapestPrice(int n, int** flights, int flightsSize, int* flightsColSize, int src, int dst, int k) {
   
    int* prices = (int*)malloc(n * sizeof(int));
    int* temp = (int*)malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++) {
        prices[i] = INF;
    }
    prices[src] = 0;

    
    for (int i = 0; i <= k; i++) {
        
        memcpy(temp, prices, n * sizeof(int));

        for (int j = 0; j < flightsSize; j++) {
            int u = flights[j][0];
            int v = flights[j][1];
            int w = flights[j][2];

            
            if (prices[u] != INF) {
                if (prices[u] + w < temp[v]) {
                    temp[v] = prices[u] + w;
                }
            }
        }
        
        memcpy(prices, temp, n * sizeof(int));
    }

    int result = prices[dst];

    
    free(prices);
    free(temp);

    return (result == INF) ? -1 : result;
}
