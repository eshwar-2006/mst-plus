#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Edge structure
typedef struct {
    int u, v, w;
} Edge;

int parent[MAX];       // Union-Find parent array
int node_weight[MAX];  // Node weights

// Union-Find functions
int find(int x) {
    if(parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void union_set(int a, int b) {
    a = find(a);
    b = find(b);
    if(a != b) parent[b] = a;
}

// Comparison function for qsort
int cmp(const void *a, const void *b) {
    return ((Edge*)a)->w - ((Edge*)b)->w;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m); // number of nodes and edges

    // Initialize Union-Find and node weights
    for(int i = 1; i <= n; i++) {
        parent[i] = i;
        node_weight[i] = 0;
    }

    Edge edges[m];
    for(int i = 0; i < m; i++){
        int u, v, w, wu, wv;
        scanf("%d %d %d %d %d", &u, &v, &w, &wu, &wv);
        edges[i].u = u;
        edges[i].v = v;
        edges[i].w = w;

        node_weight[u] = wu;
        node_weight[v] = wv;
    }

    // Sort edges by weight
    qsort(edges, m, sizeof(Edge), cmp);

    int mst_weight = 0;
    int included[MAX] = {0};

    for(int i = 0; i < m; i++){
        int u = edges[i].u;
        int v = edges[i].v;

        if(find(u) != find(v)){
            union_set(u, v);
            mst_weight += edges[i].w;
            if(!included[u]) { mst_weight += node_weight[u]; included[u]=1; }
            if(!included[v]) { mst_weight += node_weight[v]; included[v]=1; }
        }
    }

    printf("%d\n", mst_weight);
    return 0;
}
