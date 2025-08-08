#include<stdio.h>
#include<string.h>

void topologicalSort(int n, int arr[n][n], char str[n][20]);


int main() {
    int n, e;
    printf("Enter number of nodes: ");
    scanf("%d", &n);
    printf("Enter number of edges: ");
    scanf("%d", &e);

    char str[n][20];
    int arr[n][n];

    for (int i = 0; i < n; i++)
    {
        printf("Enter node-%d: ", i + 1);
        scanf("%s", str[i]);
    }
    

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            arr[i][j] = 0;

    for (int i = 0; i < e; i++) {
        char a[20], b[20];
        printf("Edge-%d: \nStart node: ", i + 1);
        scanf("%s", a);
        printf("End node: ");
        scanf("%s", b);

        int a_idx = -1, b_idx = -1;
        for (int k = 0; k < n; k++) {
            if (strcmp(str[k], a) == 0) a_idx = k;
            if (strcmp(str[k], b) == 0) b_idx = k;
        }
        if (a_idx != -1 && b_idx != -1)
            arr[a_idx][b_idx] = 1;
        else
            printf("Invalid node name in edge input!\n");
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d\t", arr[i][j]);
        printf("\n");   
    }

    topologicalSort(n, arr, str);

    for (int k = 0; k < n; k++) {
        int in = 0, out = 0;
        for (int i = 0; i < n; i++) {
            if (arr[k][i] == 1) out++;
        }
        for (int i = 0; i < n; i++) {
            if (arr[i][k] == 1) in++;
        }
        printf("Node: %s In: %d Out: %d\n", str[k], in, out);
    }

    return 0;
}

void topologicalSort(int n, int arr[n][n], char str[n][20]) {
    int in_degree[n];
    for (int i = 0; i < n; i++) {
        in_degree[i] = 0;
        for (int j = 0; j < n; j++) {
            if (arr[j][i] == 1)
                in_degree[i]++;
        }
    }

    int queue[n], front = 0, rear = 0;
    for (int i = 0; i < n; i++) {
        if (in_degree[i] == 0)
            queue[rear++] = i;
    }

    int count = 0;
    int topo_order[n];
    while (front < rear) {
        int u = queue[front++];
        topo_order[count++] = u;
        for (int v = 0; v < n; v++) {
            if (arr[u][v] == 1) {
                in_degree[v]--;
                if (in_degree[v] == 0)
                    queue[rear++] = v;
            }
        }
    }

    if (count != n) {
        printf("Graph has a cycle. Topological sort not possible.\n");
    } else {
        printf("Topological Sort: ");
        for (int i = 0; i < n; i++)
            printf("%s ", str[topo_order[i]]);
        printf("\n");
    }
}