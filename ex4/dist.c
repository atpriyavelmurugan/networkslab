#include <stdio.h>
#include <string.h>
#define MAX 10
#define INF 999
int n;
char name[MAX][20];
/* Direct link cost */
int linkCost[MAX][MAX];

/* Minimum distance to destination */
int cost[MAX][MAX];

/* First hop in the shortest path */
int nextHop[MAX][MAX];

/* =========================================================
   Find router index using router name
   ========================================================= */
int findRouter(char rname[])
{
    for (int i = 0; i < n; i++)
    {
        if (strcmp(name[i], rname) == 0)
            return i;
    }
    return -1;
}
/* =========================================================
   Display routing table
   ========================================================= */
void displayMatrix(const char *title)
{
    printf("\n\n========================================================\n");
    printf("                %s\n", title);
    printf("========================================================\n");
    printf("\n%-12s", "Router");
    for (int j = 0; j < n; j++)
        printf("%-8s", name[j]);
    printf("\n");
    printf("--------------------------------------------------------\n");
    for (int i = 0; i < n; i++)
    {
        printf("%-12s", name[i]);
        for (int j = 0; j < n; j++)
        {
            if (cost[i][j] >= INF)
                printf("%-8s", "INF");
            else
                printf("%-8d", cost[i][j]);
        }
        printf("\n");
    }
}
/* =========================================================
   Initialize routing tables
   ========================================================= */
void initializeTables()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            /* Initially, shortest cost is direct link cost */
            cost[i][j] = linkCost[i][j];
            if (i == j)
            {
                nextHop[i][j] = i;
            }
            else if (linkCost[i][j] < INF)
            {
                /* Destination is directly connected */
                nextHop[i][j] = j;
            }
            else
            {
                nextHop[i][j] = -1;
            }
        }
    }
}
/* =========================================================
   Distance Vector Routing Algorithm
   ========================================================= */
void distanceVector()
{
    int updated;
    do
    {
        updated = 0;
        for (int i = 0; i < n; i++)
        {
            /* Check every direct neighbor */
            for (int j = 0; j < n; j++)
            {
                if (i == j || linkCost[i][j] >= INF)
                    continue;
                /* Check every destination */
                for (int k = 0; k < n; k++)
                {
                    if (i == k)
                        continue;
                    /*
                       Cost through neighbor j:
                       i -> j + j -> k
                    */
                    if (cost[j][k] < INF &&
                        linkCost[i][j] + cost[j][k] < cost[i][k])
                    {
                        cost[i][k] =
                            linkCost[i][j] + cost[j][k];
                        /*
                           The first hop from i
                           towards k is j.
                        */
                        nextHop[i][k] = j;

                        updated = 1;
                    }
                }
            }
        }

    } while (updated);
}
/* =========================================================
   Read input
   ========================================================= */
void readInput()
{
    printf("========================================================\n");
    printf("          DISTANCE VECTOR ROUTING ALGORITHM\n");
    printf("========================================================\n");
    printf("\nEnter number of routers: ");
    scanf("%d", &n);
    printf("\nEnter router names:\n");
    for (int i = 0; i < n; i++)
        scanf("%s", name[i]);
    printf("\nEnter the cost matrix:\n");
    printf("(Enter 0 for same router and -1 for no direct link)\n\n");
    for (int i = 0; i < n; i++)
    {
        printf("Enter row for %s: ", name[i]);
        for (int j = 0; j < n; j++)
        {
            int value;
            scanf("%d", &value);
            if (i == j)
            {
                linkCost[i][j] = 0;
            }
            else if (value == -1)
            {
                linkCost[i][j] = INF;
            }
            else
            {
                linkCost[i][j] = value;
            }
        }
    }
}

/* =========================================================
   Update an edge
   ========================================================= */
void updateEdge()
{
    char node1[20];
    char node2[20];
    printf("UPDATE EDGE\n");
    printf("\nEnter first node: ");
    scanf("%s", node1);
    printf("Enter second node: ");
    scanf("%s", node2);

    int u = findRouter(node1);
    int v = findRouter(node2);

    if (u == -1 || v == -1)
    {
        printf("\nInvalid router name!\n");
        return;
    }

    if (u == v)
    {
        printf("\nA router cannot be connected to itself.\n");
        return;
    }

    printf("\nCurrent cost between %s and %s = ",
           node1, node2);

    if (linkCost[u][v] >= INF)
        printf("No direct link\n");
    else
        printf("%d\n", linkCost[u][v]);

    int newCost;

    printf("\nEnter new cost: ");
    scanf("%d", &newCost);

    if (newCost <= 0)
    {
        printf("\nInvalid cost! Cost must be greater than 0.\n");
        return;
    }

    /*
       REPLACE the old direct cost with the new cost.
       No subtraction is performed.
    */
    linkCost[u][v] = newCost;
    linkCost[v][u] = newCost;

    printf("\nEdge %s-%s updated successfully.\n",
           node1, node2);

    /*
       Reinitialize the routing table using
       the NEW direct-link costs.
    */
    initializeTables();

    /*
       Recalculate shortest paths.
    */
    distanceVector();

    printf("\nRouting tables recalculated successfully.\n");
}


/* =========================================================
   Find shortest path, cost and next hops
   ========================================================= */
void findShortestPath()
{
    char sourceName[20];
    char destinationName[20];
    printf("TO FIND SHORTEST PATH\n");
    printf("\nEnter starting node: ");
    scanf("%s", sourceName);
    printf("Enter ending node: ");
    scanf("%s", destinationName);
    int source = findRouter(sourceName);
    int destination = findRouter(destinationName);
    if (source == -1)
    {
        printf("\nInvalid starting node!\n");
        return;
    }
    if (destination == -1)
    {
        printf("\nInvalid ending node!\n");
        return;
    }
    /* Same source and destination */
    if (source == destination)
    {
        printf("\nStarting Node : %s\n", sourceName);
        printf("Ending Node   : %s\n", destinationName);
        printf("Shortest Path : %s\n", sourceName);
        printf("Total Cost    : 0\n");
        return;
    }
    /* No path */
    if (cost[source][destination] >= INF)
    {
        printf("\nNo path exists between %s and %s.\n",
               sourceName, destinationName);
        return;
    }
    printf("\nStarting Node : %s\n", sourceName);
    printf("Ending Node   : %s\n", destinationName);
    /* =====================================================
       Print shortest path
       ===================================================== */

    printf("Shortest Path : ");

    int current = source;

    printf("%s", name[current]);

    while (current != destination)
    {
        int next = nextHop[current][destination];

        if (next == -1)
        {
            printf("\nPath cannot be determined.\n");
            return;
        }

        printf(" -> %s", name[next]);

        current = next;
    }

    printf("\nTotal Cost    : %d\n",
           cost[source][destination]);


    /* =====================================================
       Print next hop for nodes in the shortest path
       ===================================================== */

    printf("\nNext Hop:\n");

    current = source;

    while (current != destination)
    {
        int next = nextHop[current][destination];

        if (next == -1)
        {
            printf("Path cannot be determined.\n");
            return;
        }

        printf("%s -> %s\n",
               name[current],
               name[next]);

        current = next;
    }
}
int main()
{
    char choice;

    /* Read network */
    readInput();

    /* Initialize routing tables */
    initializeTables();

    /* Display initial routing table */
    displayMatrix("INITIAL ROUTING TABLE");

    /* Run Distance Vector */
    distanceVector();

    /* Display final routing table */
    displayMatrix("FINAL ROUTING TABLE");
    /* =====================================================
       Find shortest path and update edges
       ===================================================== */
    do
    {
        /* Find shortest path */
        findShortestPath();

        printf("\n\nDo you want to update an edge? (y/n): ");
        scanf(" %c", &choice);

        if (choice == 'y' || choice == 'Y')
        {
            /* Update direct edge */
            updateEdge();

            /* Display recalculated shortest-distance table */
            displayMatrix("UPDATED ROUTING TABLE");
        }
    } while (choice == 'y' || choice == 'Y');
    /* Program termination */
    printf("PROGRAM TERMINATED\n");
    return 0;
}
