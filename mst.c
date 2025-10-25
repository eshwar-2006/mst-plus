#include <stdio.h>
// Your MST code here

int main() {
    int mst_weight = 0;
int included[MAX] = {0};

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
