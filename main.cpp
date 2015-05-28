#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "graph.h"
#include <cmath>


using namespace std;

typedef vector<string> Data;
typedef vector<Data> DataList;

//function declaration
void getData();
bool myfunction(Data, Data);
void sortDataList(DataList& );
void string2int(DataList& );
void makeNode(DataList& in);
void makeEdge();
bool overlap(Node* a, Node* b);
void makeGraph();
bool checkAlpha(Node* a, Node* b);
bool checkBeta(Node*a, Node* b);
bool x_overlap(Node* a, Node* b);
bool y_overlap(Node* a, Node* b);
bool checkEnd(Node* a);
bool myfunction4(Edge* a,Edge* b);

DataList list;
string alpha, beta, omega;
int Alpha, Beta, Omega;
vector<Graph*> graphArray;
vector<Node*> nodeArray;
vector<Edge*> edgeArray;



int main()
{
	getData();
	sortDataList(list);
//	for(int i = 0;i<list.size();i++)
//	{
//		for(int j=0;j<list[i].size();j++)
//		{
//			cout<<setw(5)<<list[i][j]<<" ";
//		}
//		cout<<endl;
//	}

	Graph a22("ss") ;
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
    makeGraph();
//	cout<<"node array size: "<<nodeArray.size()<<endl;
//	cout<<"graph array size: "<<graphArray.size()<<endl;

//    cout<<"show edge: "<<endl;
//    sort(edgeArray.begin(),edgeArray.end(),myfunction4);
//    for(int i=0;i<edgeArray.size();i++)
//    {
//        cout<<edgeArray[i]->node[0]->id<<", "<<edgeArray[i]->node[1]->id<<endl;
//    }

//    cout<<"----------------------------------"<<endl;
//    cout<<"graph size: "<<graphArray.size()<<endl;
//    for(int i = 0; i< graphArray.size();i++)
//    {
//        for(int j = 0; j<graphArray[i]->nodes.size();j++)
//        {
//            cout<<graphArray[i]->nodes[j]->id<<" ";
//        }
//        cout<<endl;
//    }


    for(int i = 0; i< graphArray.size(); i++)
    {
        for(int j = 0; j<graphArray[i]->nodes.size(); j++)
        {
//            cout<<graphArray[i]->nodes[j]->left<<",";
//            cout<<graphArray[i]->nodes[j]->down<<",";
//            cout<<graphArray[i]->nodes[j]->right<<",";
//            cout<<graphArray[i]->nodes[j]->top<<endl;
//            cout<<graphArray[i]->nodes[j]->id<<endl;
            int ttt = graphArray[i]->nodes[j]->id-1;
            cout<<nodeArray[ttt]->left<<",";
            cout<<nodeArray[ttt]->down<<",";
            cout<<nodeArray[ttt]->right<<",";
            cout<<nodeArray[ttt]->top<<endl;

        }
        cout<<endl;
//        cout<<endl;
    }
	
}



//get data from test.txt to DataList datastructure
void getData()
{
    fstream fs ("..//test.txt" ,fstream::in);
	string line;
	
	while(getline(fs,line))
	{	
		int a = line[0];
		string num;
		num.clear();
		Data d;
		d.clear();
		if(a>=48 && a<=57)
		{
			for(int i=0; i< line.size(); i++)
			{
				if((int)line[i]>=48 && (int)line[i]<=57 && i < line.size()-1)
				{
					num.push_back(line[i]);
				}else if((int)line[i] == 44 )
				{
					d.push_back(num);
					num.clear();
				}else if(i == line.size()-1)
				{
					num.push_back(line[i]);
					d.push_back(num);
					num.clear();
					list.push_back(d);
					d.clear();
				}
			}
		}
		else if(a==65)
		{
			for(int i=0;i<line.size();i++)
			{
				if(line[i]>=48 && line[i]<=57)
				{
					alpha.push_back(line[i]);
				}
			}
		}
		else if(a==66)
		{
			for(int i=0;i<line.size();i++)
			{
				if(line[i]>=48 && line[i]<=57)
				{
					beta.push_back(line[i]);
				}
			}
		}
		else if(a==79)
		{
			for(int i=0;i<line.size();i++)
			{
				if(line[i]>=48 && line[i]<=57)
				{
					omega.push_back(line[i]);
				}
			}
		}
	}
}


//Sort data 
void sortDataList(DataList&  a)
{
	sort(a.begin(),a.end(),myfunction);
}


bool myfunction(Data a, Data b)
{
	stringstream aa;
	stringstream bb;
	int a1, b1;
	aa<<a[0];
	bb<<b[0];
	aa>>a1;
	bb>>b1;
	return (a1<b1);
}

void makeNode(DataList& in)
{
	for(int i = 0; i< in.size(); i++)
	{
		Node* temp = new Node(i+1);
		stringstream left1,down1,top1,right1;
		int left2,down2,top2,right2;
		left1<<in[i][0];
		down1<<in[i][1];
		top1<<in[i][3];
		right1<<in[i][2];
		left1>>left2;
		down1>>down2;
		right1>>right2;
		top1>>top2;

//         cout<<"left2================= "<<left2<<endl;
//         cout<<"right2================= "<<right2<<endl;
		temp->left = left2;
		temp->down = down2;
		temp->top = top2;
		temp->right = right2;
		
		nodeArray.push_back(temp);
	}
}


void makeEdge()
{
//	Graph* temp = new Graph("1");
	bool flag;
	int i;
	for(i = 0; i < nodeArray.size()-1; i++)
    {
//        cout<<"@@@@@@@@@@@@@@@@@@@@@@@"<<nodeArray[i]->left<<endl;
//        cout<<"iteration "<<i+1<<endl;
		flag = false;
		for(int j = i+1; j<nodeArray.size(); j++)
		{	
			if(overlap(nodeArray[i],nodeArray[j]))
			{
				if(checkAlpha(nodeArray[i], nodeArray[j])  )
				{
//                    cout<<"checkalpha OK"<<"i="<<i+1<<"j="<<j+1<<endl;
					if(!x_overlap(nodeArray[i], nodeArray[j]))
					{
                        Edge* t = new Edge(nodeArray[i],nodeArray[j]);
//						temp->addEdge(nodeArray[i]->id,nodeArray[j]->id);
                        edgeArray.push_back(t);
//                        cout<<"x----"<<endl;
//                        cout<<"i= "<<i+1<<endl;
//                        cout<<"j= "<<j+1<<endl;
						flag = true;
					}
				}
				if(checkBeta(nodeArray[i], nodeArray[j]))
				{
//                    cout<<"checkbeta OK"<<"i="<<i+1<<"j="<<j+1<<endl;
					if(!y_overlap(nodeArray[i], nodeArray[j]))
					{
                         Edge* t = new Edge(nodeArray[i],nodeArray[j]);
//                        temp->addEdge(nodeArray[i]->id,nodeArray[j]->id);
                         edgeArray.push_back(t);
//                        cout<<"y----"<<endl;
//                        cout<<"i= "<<i+1<<endl;
//                        cout<<"j= "<<j+1<<endl;
						flag = true;
					}
				}
				
			}

		}

		


//		if(!flag)
//		{
//			cout<<"lalalalalalalallalalalalalala"<<endl;
//			graphArray.push_back(temp);
//			temp = new Graph("2");
//		}
	}
//	cout<<"size "<<temp->edges.size()<<endl;
//    cout<<"edgeSize: "<<edgeArray.size()<<endl;
}




bool overlap(Node* a, Node* b)
{
	vector<int> x;
	vector<int> y;
	x.push_back(a->left);
	x.push_back(a->right);
	x.push_back(b->left);
	x.push_back(b->right);

	y.push_back(a->top);
	y.push_back(a->down);
	y.push_back(b->top);
	y.push_back(b->down);

	sort(x.begin(),x.end());
	sort(y.begin(),y.end());

	if(x[0] == a->left && x[1] == b->left)
	{
		return true;
	}else if(x[0] == b->left && x[1] == a->left)
	{
		return true;
	}else if(y[0] == a->down && y[1] == b->down)
	{
		return true;
	}else if(y[0] == b->down && y[1] == a->down)
	{
		return true;
	}else 
	{
		return false;
	}
}

bool x_overlap(Node* a, Node* b)
{
	vector<int> x;
	// vector<int> y;
	x.push_back(a->left);
	x.push_back(a->right);
	x.push_back(b->left);
	x.push_back(b->right);

	// y.push_back(a->top);
	// y.push_back(a->down);
	// y.push_back(b->top);
	// y.push_back(b->down);

	sort(x.begin(),x.end());
	// sort(y.begin(),y.end());

	if(x[0] == a->left && x[1] == b->left)
	{
		return true;
	}else if(x[0] == b->left && x[1] == a->left)
	{
		return true;
	}else 
	{
		return false;
	}
}


bool y_overlap(Node* a, Node* b)
{
	vector<int> y;
	y.push_back(a->top);
	y.push_back(a->down);
	y.push_back(b->top);
	y.push_back(b->down);
	sort(y.begin(),y.end());
	if(y[0] == a->down && y[1] == b->down)
	{
		return true;
	}else if(y[0] == b->down && y[1] == a->down)
	{
		return true;
	}else 
	{
		return false;
	}


}


bool checkAlpha(Node* a, Node* b)
{
	if(abs(a->right - b->left) < Alpha  ||  abs(a->left - b->right) < Alpha  ||  abs(a->right - b->right) < Alpha  ||   abs(a->left - b->left) < Alpha)   
	{
		return true;
	}else{
		return false;
	}
}

bool checkBeta(Node*a, Node* b)
{
	if(abs(a->top - b->down) < Beta  || abs(a->down - b->top) < Beta  ||   abs(a->top - b->top) < Beta  ||  abs(a->down - b->down) < Beta  )
	{
		return true;
	}else 
	{
		return false;
	}
}



bool checkEnd(Node* a)
{
    bool flag1 = true;
    for(int i = 0; i< a->id-1; i++)
    {
        for(int j = a->id+1; j< nodeArray.size(); j++)
        {
            if(overlap(nodeArray[i],nodeArray[j]))
            {
                if(checkBeta(nodeArray[i],nodeArray[j]))
                {
                    if(!x_overlap(nodeArray[i], nodeArray[j]))
                    {
                        flag1 = false;
//                        cout<<"checkEnd at(beta) "<<i+1<<","<<j+1<<endl;

                    }
                }
                if(checkAlpha(nodeArray[i],nodeArray[j]))
                {
                    if(!y_overlap(nodeArray[i], nodeArray[j]))
                    {
                        flag1 = false;
//                        cout<<"checkEnd at(alpha) "<<i+1<<","<<j+1<<endl;

                    }
                }
            }
        }
    }

    return flag1;
}


void makeGraph()
{
    sort(edgeArray.begin(),edgeArray.end(),myfunction4);
//    Graph* temp = new Graph("0");
//    temp->addEdge(e);
    vector<Node*> checker;
//    temp->addEdge(edgeArray[0]->node[0]->id,edgeArray[0]->node[1]->id);
    checker.push_back(edgeArray[0]->node[0]);
    checker.push_back(edgeArray[0]->node[1]);
    Graph* temp = new Graph("0");
    for(int i = 1; i<edgeArray.size();i++)
    {
//        cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~"<<edgeArray[i]->node[0]->left<<endl;
//        cout<<"----------aaa-------------"<<edgeArray[i]->node[0]->id<<", "<<edgeArray[i]->node[1]->id<<endl;
        bool flag = false;
        for(int j = 0; j<i ; j++)
        {
            if(edgeArray[i]->node[0]->id == edgeArray[j]->node[0]->id || edgeArray[i]->node[0]->id == edgeArray[j]->node[1]->id || edgeArray[i]->node[1]->id == edgeArray[j]->node[0]->id || edgeArray[i]->node[1]->id == edgeArray[j]->node[1]->id)
            {

                temp->addEdge(edgeArray[i]->node[0]->id,edgeArray[i]->node[1]->id);
//                cout<<"FUCK OFF!"<<endl;
                flag = true;
                goto yo;
            }

        }





        yo:
        if(!flag)
        {

            graphArray.push_back(temp);
            temp = new Graph("1");
            temp->addEdge(edgeArray[i]->node[0]->id,edgeArray[i]->node[1]->id);
//            cout<<"FUCK OFF!"<<endl;

        }

    }
    graphArray.push_back(temp);

}

bool myfunction4(Edge* a,Edge* b)
{
    return (a->node[0]<b->node[0]);
}
