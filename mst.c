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
    if (scanf("%d %d", &n, &m) != 2) return 1;

    int* node_weight = (int*)malloc((n + 1) * sizeof(int));
    for (int i = 1; i <= n; i++) scanf("%d", &node_weight[i]);

    Edge* edges = (Edge*)malloc(m * sizeof(Edge));
    for (int i = 0; i < m; i++) scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);

    int* parent = (int*)malloc((n + 1) * sizeof(int));
    int* rank = (int*)malloc((n + 1) * sizeof(int));
    int* included = (int*)calloc(n + 1, sizeof(int));

    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    qsort(edges, m, sizeof(Edge), cmp_edges);

    long long mst_weight = 0;
    int edges_used = 0;

    for (int i = 0; i < m && edges_used < n - 1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;

        int pu = find(u, parent);
        int pv = find(v, parent);
        if (pu != pv) {
            mst_weight += w;
            if (!included[u]) { mst_weight += node_weight[u]; included[u] = 1; }
            if (!included[v]) { mst_weight += node_weight[v]; included[v] = 1; }
            unite(pu, pv, parent, rank);
            edges_used++;
        }
    }

    printf("%lld\n", mst_weight);
    fflush(stdout);

    free(node_weight);
    free(edges);
    free(parent);
    free(rank);
    free(included);

    return 0;
}
