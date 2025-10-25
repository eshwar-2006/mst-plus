#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int u, v;
    int w;
} Edge;

// Comparison function for qsort
int cmp_edges(const void* a, const void* b) {
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

int main(void) {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) {
        fprintf(stderr, "Invalid input: missing n m\n");
        return 1;
    }

    int* node_weight = (int*)malloc((n + 1) * sizeof(int));
    for (int i = 1; i <= n; i++) {
        if (scanf("%d", &nod
