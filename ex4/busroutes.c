
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_STOPS 1000000


typedef struct {
    int *data;
    int size;
    int capacity;
} IntList;

void append(IntList *list, int val) {
    if (list->size >= list->capacity) {
        list->capacity = list->capacity == 0 ? 4 : list->capacity * 2;
        list->data = (int *)realloc(list->data, list->capacity * sizeof(int));
    }
    list->data[list->size++] = val;
}

int numBusesToDestination(int** routes, int routesSize, int* routesColSize, int source, int target) {
    
    if (source == target) return 0;

   
    IntList* stopToBuses = (IntList*)calloc(MAX_STOPS, sizeof(IntList));
    
    for (int i = 0; i < routesSize; i++) {
        for (int j = 0; j < routesColSize[i]; j++) {
            int stop = routes[i][j];
            append(&stopToBuses[stop], i);
        }
    }

    
    int* queueBus = (int*)malloc(routesSize * sizeof(int));
    int* queueCount = (int*)malloc(routesSize * sizeof(int));
    int head = 0, tail = 0;

    
    bool* visitedBuses = (bool*)calloc(routesSize, sizeof(bool));
    
    bool* visitedStops = (bool*)calloc(MAX_STOPS, sizeof(bool));

    
    IntList sourceBuses = stopToBuses[source];
    visitedStops[source] = true;
    for (int i = 0; i < sourceBuses.size; i++) {
        int bus = sourceBuses.data[i];
        queueBus[tail] = bus;
        queueCount[tail] = 1; 
        visitedBuses[bus] = true;
        tail++;
    }

    
    int result = -1; 
    while (head < tail) {
        int currBus = queueBus[head];
        int currCount = queueCount[head];
        head++;

        
        for (int i = 0; i < routesColSize[currBus]; i++) {
            int stop = routes[currBus][i];

            
            if (stop == target) {
                result = currCount;
                break;
            }

            
            if (!visitedStops[stop]) {
                visitedStops[stop] = true;
                IntList nextBuses = stopToBuses[stop];
                for (int j = 0; j < nextBuses.size; j++) {
                    int nBus = nextBuses.data[j];
                    if (!visitedBuses[nBus]) {
                        visitedBuses[nBus] = true;
                        queueBus[tail] = nBus;
                        queueCount[tail] = currCount + 1; 
                        tail++;
                    }
                }
            }
        }
        if (result != -1) break;
    }

    
    for (int k = 0; k < MAX_STOPS; k++) {
        if (stopToBuses[k].data) {
            free(stopToBuses[k].data);
        }
    }
    free(stopToBuses);
    free(queueBus);
    free(queueCount);
    free(visitedBuses);
    free(visitedStops);

    return result;
}

   
