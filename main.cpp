#include "greedy_face_greedy.h"
#include <stdio.h>
#include <vector>
#define MAX_NODE 1000

void init(struct coordinate (&input)[MAX_NODE],std::vector<class GFG> &node);
int main()  {
    freopen("a.txt", "r", stdin);
    freopen("b.txt", "w", stdout);
    struct coordinate input[MAX_NODE];
    std::vector<class GFG> node;
    init(input,node);

    //flattening the grath
    for (int i = 0; i < node.size();i++)
        node[i].flattening();

    int source, distination;
    int test;
    scanf("%d", &test); 
    for (int i = 0; i < test; i++) {
        scanf("%d%d", &source, &distination);
        run_gfg(source, distination, node);
    }
    return 0;
}

//setting the neighbor node
void init(struct coordinate (&input)[MAX_NODE],std::vector<class GFG> &node) {
    int total_node;
    scanf("%d", &total_node);

    for (int i = 0; i < total_node;i++)
        scanf("%d%lf%lf", &input[i].id, &input[i].x, &input[i].y);

    for (int i = 0; i < total_node; i++) {
        GFG trans(input[i]);
        node.push_back(trans);
        for (int j = 0; j < total_node; j++)
            if (i!=j && (input[i]^input[j]) < 1 )   {
                struct coordinate tr;
                tr = input[j];
                node[i].push_nearby(tr);
            }
    }
}




