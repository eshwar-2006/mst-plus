#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int u, v, w;
} Edge;

int parent[MAX];
int node_weight[MAX];
int included[MAX];

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

int cmp(const void *a, const void *b) {
    return ((Edge*)a)->w - ((Edge*)b)->w;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for(int i=1; i<=n; i++){
        parent[i] = i;
        included[i] = 0;
    }

    // Read node weights separately
    for(int i=1; i<=n; i++){
        scanf("%d", &node_weight[i]);
    }

    Edge edges[m];
    for(int i=0; i<m; i++){
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    qsort(edges, m, sizeof(Edge), cmp);

    int mst_weight = 0;

    for(int i=0; i<m; i++){
        int u = edges[i].u;
        int v = edges[i].v;
        if(find(u) != find(v)){
            union_set(u,v);
            mst_weight += edges[i].w;
            if(!included[u]) { mst_weight += node_weight[u]; included[u]=1; }
            if(!included[v]) { mst_weight += node_weight[v]; included[v]=1; }
        }
    }

    printf("%d\n", mst_weight);
    return 0;
}
