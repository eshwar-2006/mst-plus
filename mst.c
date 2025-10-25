#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int u, v;
    int w;
} Edge;

int cmp_edges(const void* a, const void* b) {
    Edge* ea = (Edge*)a;
    Edge* eb = (Edge*)b;
    return ea->w - eb->w;
}

int find(int x, int* parent) {
    if (parent[x] != x) parent[x] = find(parent[x], parent);
    return parent[x];
}

void unite(int a, int b, int* parent, int* rank) {
    int pa = find(a, parent);
    int pb = find(b, parent);
    if (pa == pb) return;
    if (rank[pa] < rank[pb]) {
        parent[pa] = pb;
    } else if (rank[pa] > rank[pb]) {
        parent[pb] = pa;
    } else {
        parent[pb] = pa;
        rank[pa]++;
    }
}

int main(void) {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) {
        fprintf(stderr, "Invalid input: missing n m\n");
        return 1;
    }

    int* node_weight = (int*)malloc((n + 1) * sizeof(int));
    for (int i = 1; i <= n; i++) {
        if (scanf("%d", &node_weight[i]) != 1) {
            fprintf(stderr, "Invalid input: missing node weights\n");
            free(node_weight);
            return 1;
        }
    }

    Edge* edges = (Edge*)malloc(m * sizeof(Edge));
    for (int i = 0; i < m; i++) {
        int u, v, w;
        if (scanf("%d %d %d", &u, &v, &w) != 3) {
            fprintf(stderr, "Invalid input: missing edge data\n");
            free(edges);
            free(node_weight);
            return 1;
        }
        edges[i].u = u;
        edges[i].v = v;
        edges[i].w = w;
    }

    // Kruskal prep
    int* parent = (int*)malloc((n + 1) * sizeof(int));
    int* rank = (int*)malloc((n + 1) * sizeof(int));
    int* included = (int*)calloc(n + 1, sizeof(int)); // 0 or 1

    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    qsort(edges, m, sizeof(Edge), cmp_edges);

    long long total = 0;
    int edges_used = 0;

    for (int i = 0; i < m && edges_used < n - 1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;

        int pu = find(u, parent);
        int pv = find(v, parent);
        if (pu != pv) {
            // include this edge
            total += w;

            // add node weights for first-time inclusion
            if (!included[u]) {
                total += node_weight[u];
                included[u] = 1;
            }
            if (!included[v]) {
                total += node_weight[v];
                included[v] = 1;
            }

            unite(pu, pv, parent, rank);
            edges_used++;
        }
    }

    printf("%lld\n", total);

    free(node_weight);
    free(edges);
    free(parent);
    free(rank);
    free(included);
    return 0;
}
