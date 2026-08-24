#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define INF 999999

int minimumEffortPath(int** heights, int heightsSize, int* heightsColSize) {
    int rows = heightsSize;
    int cols = heightsColSize[0];

    
    int** effort = (int**)malloc(rows * sizeof(int*));
    bool** visited = (bool**)malloc(rows * sizeof(bool*));
    for (int i = 0; i < rows; i++) {
        effort[i] = (int*)malloc(cols * sizeof(int));
        visited[i] = (bool*)malloc(cols * sizeof(bool));
        for (int j = 0; j < cols; j++) {
            effort[i][j] = INF;
            visited[i][j] = false;
        }
    }

    
    effort[0][0] = 0;

   
    int dRow[] = {-1, 1, 0, 0};
    int dCol[] = {0, 0, -1, 1};

   
    for (int count = 0; count < rows * cols; count++) {
        int r = -1, c = -1;
        int minEffort = INF;

        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (!visited[i][j] && effort[i][j] < minEffort) {
                    minEffort = effort[i][j];
                    r = i;
                    c = j;
                }
            }
        }

        
        if (r == -1 || (r == rows - 1 && c == cols - 1)) {
            break;
        }

        visited[r][c] = true;

        
        for (int i = 0; i < 4; i++) {
            int newR = r + dRow[i];
            int newC = c + dCol[i];

            
            if (newR >= 0 && newR < rows && newC >= 0 && newC < cols && !visited[newR][newC]) {
               
                int transitionEffort = abs(heights[r][c] - heights[newR][newC]);
                
                
                int maxRouteEffort = (effort[r][c] > transitionEffort) ? effort[r][c] : transitionEffort;

                
                if (maxRouteEffort < effort[newR][newC]) {
                    effort[newR][newC] = maxRouteEffort;
                }
            }
        }
    }

    int result = effort[rows - 1][cols - 1];

    
    for (int i = 0; i < rows; i++) {
        free(effort[i]);
        free(visited[i]);
    }
    free(effort);
    free(visited);

    return result;
}
