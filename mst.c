#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int u, v;
    int w;
} Edge;

// Comparison function for qsort
int cmp_edges(const void *a, const void *b) {
    return ((Edge*)a)->w - ((Edge*)b)->w;
}

// Union-Find functions
int find(int x, int* parent) {
    if (parent[x] != x)
        parent[x] = find(parent[x], parent);
    return parent[x];
}

void unite(int a, int b, int* parent, int* rank) {
    int pa = find(a, parent);
    int pb = find(b, parent);
    if (pa == pb) return;
    if (rank[pa] < rank[pb])
        parent[pa] = pb;
    else if (rank[pa] > rank[pb])
        parent[pb] = pa;
    else {
        parent[pb] = pa;
        rank[pa]++;
    }
}

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    // Read node weights
    int* node_weight = (int*)malloc((n + 1) * sizeof(int));
    for (int i = 1; i <= n; i++) {
        if (scanf("%d", &node_weight[i]) != 1) {
            fprintf(stderr, "Invalid node weight\n");
            free(node_weight);
            return 1;
        }
    }

    // Read edges
    Edge* edges = (Edge*)malloc(m * sizeof(Edge));
    for (int i = 0; i < m; i++) {
        if (scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w) != 3) {
            fprintf(stderr, "Invalid edge data\n");
            free(node_weight);
            free(edges);
            return 1;
        }
    }

    // Initialize Union-Find
    int* parent = (int*)malloc((n + 1) * sizeof(int));
    int* rank = (int*)malloc((n + 1) * sizeof(int));
    int* included = (int*)calloc(n + 1, sizeof(int));

    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    // Sort edges by weight
    qsort(edges, m, sizeof(Edge), cmp_edges);

    long long mst_weight = 0;
    int edges_used = 0;

    // Kruskal's algorithm
    for (int i = 0; i < m && edges_used < n - 1; i++) {
        int u = edges[i].u;
        int v = edg
fflush(stdout);
printf("%lld\n", mst_weight);
fflush(stdout);

