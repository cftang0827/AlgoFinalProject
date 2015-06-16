#include "dfs.h"
#include "graph.h"
//Node* gg;
int time1;

void DFS(Graph *p)
{
    for(int i = 0; i<p->nodes.size(); i++)
    {
        p->nodes[i]->color = 0;
//        p->nodes[i]->prev = DIS_INF;
    }
    time1 = 0;

    for(int i = 0; i<p->nodes.size();i++)
    {
        if(p->nodes[i]->color == 0)
        {
            cout<<endl;
//            cout<<"nodes id draw: "<<p->nodes[i]->id+1<<endl;
            cout<<p->nodes[i]->left<<" ";
            cout<<p->nodes[i]->down<<" ";
            cout<<p->nodes[i]->right<<" ";
            cout<<p->nodes[i]->top<<endl;
            dfs_visit(p,p->nodes[i]);

        }
    }
}

//gray = -1
//white = 0;
//black = 1;

void dfs_visit(Graph* p, Node* in)
{
    time1 = time1 + 1;
    in->d = time1;
    in->color = -1;
//    cout<<"aa"<<in->edge.size()<<endl;
    for(int i = 0; i<in->edge.size();i++)
    {
        if(in->edge[i]->getNeighbor(in)->color == 0)
        {

            CC* c1 = new CC("1");

            in->edge[i]->getNeighbor(in)->prev = in;
//            cout<<"nodes id draw: "<<in->edge[i]->getNeighbor(in)->id+1<<endl;
            cout<<p->nodes[in->edge[i]->getNeighbor(in)->id]->left<<" ";
            cout<<p->nodes[in->edge[i]->getNeighbor(in)->id]->down<<" ";
            cout<<p->nodes[in->edge[i]->getNeighbor(in)->id]->right<<" ";
            cout<<p->nodes[in->edge[i]->getNeighbor(in)->id]->top<<endl;
            dfs_visit(p,in->edge[i]->getNeighbor(in));
        }
        in->color = 1;
        time1 = time1 + 1;
        in->f = time1;
    }

}
