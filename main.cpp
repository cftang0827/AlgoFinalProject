#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "graph.h"
#include <cmath>
#include "dfs.h"
#include "getpart.h"

using namespace std;

typedef vector<string> Data;
typedef vector<Data> DataList;

int main()
{
	getData();
	sortDataList(list);

    cout<<"show Node: =========="<<endl;
    for(int i = 0;i<list.size();i++)
    {
        for(int j=0;j<list[i].size();j++)
        {
            cout<<setw(5)<<list[i][j]<<" ";
        }
        cout<<endl;
    }


    cout<<"show Parameter: =========="<<endl;
	cout<<"alpha: "<<alpha<<endl;
	cout<<"beta: "<<beta<<endl;
	cout<<"omega: "<<omega<<endl; 

	stringstream a,b,o;
	a<<alpha;
	b<<beta;
	o<<omega;
	a>>Alpha;
	b>>Beta;
	o>>Omega;
	makeNode(list);
    makeEdge();


    putOtherNodeInTheGraph(FINAL);

    cout<<"GRAPH FINAL!!"<<endl;

    cout<<"Edges number: "<<FINAL->edges.size()<<endl;
    for(int i = 0; i<FINAL->edges.size();i++)
    {
        cout<<FINAL->edges[i]->node[0]->id<<", "<<FINAL->edges[i]->node[1]->id<<endl;
    }


    cout<<"Nodes number: "<<FINAL->nodes.size();
    cout<<endl;
    cout<<"NODES"<<endl;
    FINAL->sortNodesByID();
    for(int i = 0; i<FINAL->nodes.size();i++)
    {

        cout<<FINAL->nodes[i]->id<<endl;
        cout<<FINAL->nodes[i]->left<<" ";
        cout<<FINAL->nodes[i]->down<<" ";
        cout<<FINAL->nodes[i]->right<<" ";
        cout<<FINAL->nodes[i]->top<<endl;


    }





    //dfs

    system("PAUSE");
    DFS(FINAL);



    cout<<"FINAL->connected.size(): "<<FINAL->connected.size()<<endl;
    cout<<"FINAL edge size: "<<FINAL->edges.size()<<endl;
    cout<<"FINAL edge: "<<endl;
    system("PAUSE");
    for(int i = 0 ; i<FINAL->connected.size(); i++)
    {
        cout<<FINAL->connected[i]->nodes.size()<<endl;
    }





}
