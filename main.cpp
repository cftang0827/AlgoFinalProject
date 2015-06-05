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
vector<Graph*> graphVector;
vector<Node*> nodeVector;
vector<Edge*> edgeVector;



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

	Graph a22("ss") ;
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
    makeGraph();
//	cout<<"node array size: "<<nodeVector.size()<<endl;
//	cout<<"graph array size: "<<graphVector.size()<<endl;

    cout<<"show Edge: =========="<<endl;
    sort(edgeVector.begin(),edgeVector.end(),myfunction4);
    for(int i=0;i<edgeVector.size();i++)
    {
        cout<<edgeVector[i]->node[0]->id<<", "<<edgeVector[i]->node[1]->id<<endl;
    }

//    cout<<"----------------------------------"<<endl;
//    cout<<"graph size: "<<graphVector.size()<<endl;
//    for(int i = 0; i< graphVector.size();i++)
//    {
//        for(int j = 0; j<graphVector[i]->nodes.size();j++)
//        {
//            cout<<graphVector[i]->nodes[j]->id<<" ";
//        }
//        cout<<endl;
//    }

    cout<<"Show Part: =========="<<endl;
    for(int i = 0; i< graphVector.size(); i++)
    {
        for(int j = 0; j<graphVector[i]->nodes.size(); j++)
        {
//            cout<<graphVector[i]->nodes[j]->left<<",";
//            cout<<graphVector[i]->nodes[j]->down<<",";
//            cout<<graphVector[i]->nodes[j]->right<<",";
//            cout<<graphVector[i]->nodes[j]->top<<endl;
//            cout<<graphVector[i]->nodes[j]->id<<endl;
            int ttt = graphVector[i]->nodes[j]->id-1;
            graphVector[i]->nodes[j]->left = nodeVector[ttt]->left;
            graphVector[i]->nodes[j]->right = nodeVector[ttt]->right;
            graphVector[i]->nodes[j]->top = nodeVector[ttt]->top;
            graphVector[i]->nodes[j]->down = nodeVector[ttt]->down;

            cout<<nodeVector[ttt]->left<<",";
            cout<<nodeVector[ttt]->down<<",";
            cout<<nodeVector[ttt]->right<<",";
            cout<<nodeVector[ttt]->top<<endl;

//            cout<<"===================="<<endl;
//                        cout<<graphVector[i]->nodes[j]->left<<",";
//                        cout<<graphVector[i]->nodes[j]->down<<",";
//                        cout<<graphVector[i]->nodes[j]->right<<",";
//                        cout<<graphVector[i]->nodes[j]->top<<endl;
//                        cout<<graphVector[i]->nodes[j]->id<<endl;

        }
        cout<<endl;
//        cout<<endl;
    }


    cout<<"================"<<endl;
    for(int i = 0; i< graphVector.size(); i++)
    {
        for(int j = 0; j<graphVector[i]->nodes.size(); j++)
        {
            //            cout<<"===================="<<endl;
              cout<<graphVector[i]->nodes[j]->left<<",";
              cout<<graphVector[i]->nodes[j]->down<<",";
              cout<<graphVector[i]->nodes[j]->right<<",";
              cout<<graphVector[i]->nodes[j]->top<<endl;

        }
        cout<<endl;
    }
}



//get data from test.txt to DataList datastructure
void getData()
{
    fstream fs ("..//iccad2015_input.case3" ,fstream::in);
	string line;
	
	while(getline(fs,line))
	{	
		int a = line[0];
		string num;
		num.clear();
		Data d;
		d.clear();
        if((a>=48 && a<=57) || a == 45)
		{
			for(int i=0; i< line.size(); i++)
			{
                if(((int)line[i]>=48 && (int)line[i]<=57 && i < line.size()-1) || (int)line[i]==45  )
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

        if(in[i][0][0] == '-')
        {
            string temp0 = in[i][0];
            temp0.erase(temp0.begin());
            left1<<temp0;
            left1>>left2;
            left2 = (-1)*left2;
        }
        else
        {
            left1<<in[i][0];
            left1>>left2;
        }

        if(in[i][1][0] == '-')
        {
            string temp1 = in[i][1];
            temp1.erase(temp1.begin());
            down1<<temp1;
            down1>>down2;
            down2 = (-1)*down2;
        }else
        {
            down1<<in[i][1];
            down1>>down2;
        }

        if(in[i][3][0] == '-')
        {
            string temp3 = in[i][3];
            temp3.erase(temp3.begin());
            top1<<temp3;
            top1>>top2;
            top2 = (-1)*top2;
        }else
        {
            top1<<in[i][3];
            top1>>top2;
        }

        if(in[i][2][0] == '-')
        {
            string temp2 = in[i][2];
            temp2.erase(temp2.begin());
            right1<<temp2;
            right1>>right2;
            right2 = (-1)*right2;
        }else
        {
            right1<<in[i][2];
            right1>>right2;
        }





//        if(in[i][2][0] != '-' || in[i][0][0] != '-' || in[i][3][0] != '-' || in[i][1][0] != '-')
//        {
//            left1<<in[i][0];
//            down1<<in[i][1];
//            top1<<in[i][3];
//            right1<<in[i][2];


//            left1>>left2;
//            down1>>down2;
//            right1>>right2;
//            top1>>top2;
//        }





//        left1>>left2;
//		down1>>down2;
//		right1>>right2;
//		top1>>top2;

//        cout<<"in[i][0] = "<<in[i][0]<<endl;
//        cout<<"right2= "<<right2<<endl;




////        cout<<"12341234               "<<in[i][0][0]<<endl;
//        if(in[i][0][0] == '-')
//        {
//            in[i][0].erase(0);
////            cout<<"fuck"<<endl;
////            left2 = (-1)*left2;
//        }else if(in[i][1][0] == '-')
//        {
//            in[i][1].erase(0);
////            cout<<"fuck"<<endl;
////            down2 = (-1)*down2;
//        }else if(in[i][3][0] == '-')
//        {
//            in[i][3].erase(0);
////            cout<<"fuck"<<endl;
////            top2 = (-1)*top2;
//        }else if(in[i][2][0] == '-')
//        {
//            in[i][2].erase(0);
////            cout<<"fuck"<<endl;
////            right2 = (-1)*right2;
//        }else
//        {

//            left1<<in[i][0];
//            down1<<in[i][1];
//            top1<<in[i][3];
//            right1<<in[i][2];
//            left1>>left2;
//            down1>>down2;
//            right1>>right2;
//            top1>>top2;

//        }

//        cout<<"left2 = "<<left2<<endl;
//        cout<<"right2 = "<<right2<<endl;
//        cout<<"top2 = "<<top2<<endl;
//        cout<<"down2 = "<<down2<<endl;
//        cout<<endl;
        cout<<"rectangle('Position',["<<left2<<" "<<down2;
        cout<<" "<<abs(right2 - left2)<<" ";
        cout<<abs(top2-down2)<<"])"<<endl;



//         cout<<"left2================= "<<left2<<endl;
//         cout<<"right2================= "<<right2<<endl;
		temp->left = left2;
		temp->down = down2;
		temp->top = top2;
		temp->right = right2;
		
        nodeVector.push_back(temp);
	}
}


void makeEdge()
{
//	Graph* temp = new Graph("1");
	bool flag;
	int i;
    for(i = 0; i < nodeVector.size()-1; i++)
    {
//        cout<<"@@@@@@@@@@@@@@@@@@@@@@@"<<nodeVector[i]->left<<endl;
//        cout<<"iteration "<<i+1<<endl;
		flag = false;
        for(int j = i+1; j<nodeVector.size(); j++)
		{	
            if(overlap(nodeVector[i],nodeVector[j]))
			{
                if(checkAlpha(nodeVector[i], nodeVector[j]) )
				{
//                    cout<<"checkalpha OK"<<"i="<<i+1<<"j="<<j+1<<endl;
                    if(!x_overlap(nodeVector[i], nodeVector[j]))
					{
                        Edge* t = new Edge(nodeVector[i],nodeVector[j]);
//						temp->addEdge(nodeVector[i]->id,nodeVector[j]->id);
                        edgeVector.push_back(t);
//                        cout<<"x----"<<endl;
//                        cout<<"i= "<<i+1<<endl;
//                        cout<<"j= "<<j+1<<endl;
						flag = true;
					}
				}
                if(checkBeta(nodeVector[i], nodeVector[j]))
				{
//                    cout<<"checkbeta OK"<<"i="<<i+1<<"j="<<j+1<<endl;
                    if(!y_overlap(nodeVector[i], nodeVector[j]))
					{
                         Edge* t = new Edge(nodeVector[i],nodeVector[j]);
//                        temp->addEdge(nodeVector[i]->id,nodeVector[j]->id);
                         edgeVector.push_back(t);
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
//			graphVector.push_back(temp);
//			temp = new Graph("2");
//		}
	}
//	cout<<"size "<<temp->edges.size()<<endl;
//    cout<<"edgeSize: "<<edgeVector.size()<<endl;
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
        for(int j = a->id+1; j< nodeVector.size(); j++)
        {
            if(overlap(nodeVector[i],nodeVector[j]))
            {
                if(checkBeta(nodeVector[i],nodeVector[j]))
                {
                    if(!x_overlap(nodeVector[i], nodeVector[j]))
                    {
                        flag1 = false;
//                        cout<<"checkEnd at(beta) "<<i+1<<","<<j+1<<endl;

                    }
                }
                if(checkAlpha(nodeVector[i],nodeVector[j]))
                {
                    if(!y_overlap(nodeVector[i], nodeVector[j]))
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
    bool *checkIfInGraph = new bool[nodeVector.size()];
    for(int i = 0; i<nodeVector.size();i++)
    {
        checkIfInGraph[i] = false;
        cout<<"YOYOYOYOYOYOYOYOYO"<<endl;
    }
    sort(edgeVector.begin(),edgeVector.end(),myfunction4);
//    Graph* temp = new Graph("0");
//    temp->addEdge(e);
    vector<Node*> checker;
//    temp->addEdge(edgeVector[0]->node[0]->id,edgeVector[0]->node[1]->id);
    checker.push_back(edgeVector[0]->node[0]);
    checker.push_back(edgeVector[0]->node[1]);
    Graph* temp = new Graph("0");
    temp->addEdge(edgeVector[0]->node[0]->id,edgeVector[0]->node[1]->id);
    checkIfInGraph[edgeVector[0]->node[0]->id] = true;
    checkIfInGraph[edgeVector[0]->node[1]->id] = true;


    for(int i = 1; i<edgeVector.size();i++)
    {
//        cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~"<<edgeVector[i]->node[0]->left<<endl;
//        cout<<"----------aaa-------------"<<edgeVector[i]->node[0]->id<<", "<<edgeVector[i]->node[1]->id<<endl;
        bool flag = false;
        for(int j = 0; j<i ; j++)
        {
            if(edgeVector[i]->node[0]->id == edgeVector[j]->node[0]->id || edgeVector[i]->node[0]->id == edgeVector[j]->node[1]->id || edgeVector[i]->node[1]->id == edgeVector[j]->node[0]->id || edgeVector[i]->node[1]->id == edgeVector[j]->node[1]->id)
            {

                temp->addEdge(edgeVector[i]->node[0]->id,edgeVector[i]->node[1]->id);
//                cout<<"FUCK OFF!"<<endl;
                checkIfInGraph[edgeVector[i]->node[0]->id] = true;
                checkIfInGraph[edgeVector[i]->node[1]->id] = true;
                flag = true;
                goto yo;
            }

        }

        yo:
        if(!flag)
        {

            graphVector.push_back(temp);
            temp = new Graph("1");
            temp->addEdge(edgeVector[i]->node[0]->id,edgeVector[i]->node[1]->id);
            checkIfInGraph[edgeVector[i]->node[0]->id] = true;
            checkIfInGraph[edgeVector[i]->node[1]->id] = true;
//            cout<<"FUCK OFF!"<<endl;

        }

    }
    graphVector.push_back(temp);

    for(int i = 0; i<nodeVector.size(); i++)
    {
        if(!checkIfInGraph[i])
        {
            temp = new Graph("5");
            temp->nodes.push_back(nodeVector[i]);
            graphVector.push_back(temp);
        }
    }



}

bool myfunction4(Edge* a,Edge* b)
{
    return (a->node[0]->id<b->node[0]->id);
}
