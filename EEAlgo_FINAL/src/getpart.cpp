//以下部分為湯智帆所做
//包含MATLAB畫圖部分

#include "getpart.h"
#include <iostream>


DataList list;
string alpha, beta, omega;
int Alpha, Beta, Omega;
vector<Node*> nodeVector;
//最終圖形的資訊都在這裡
Graph* FINAL = new Graph("FINAL");

void getData(char * src)
{
    
   fstream fs (src,fstream::in);

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


        // 使用MATLAB畫圖!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


        //        cout<<"rectangle('Position',["<<left2<<" "<<down2;
        //        cout<<" "<<abs(right2 - left2)<<" ";
        //        cout<<abs(top2-down2)<<"])"<<endl;

        //         cout<<"left2================= "<<left2<<endl;
        //         cout<<"right2================= "<<right2<<endl;
        temp->left = left2;
        temp->down = down2;
        temp->top = top2;
        temp->right = right2;
        temp->id = i;
        nodeVector.push_back(temp);
        //        FINAL->nodes.push_back(temp);
    }
}

//製作edge
void makeEdge()
{
    //	Graph* temp = new Graph("1");
    bool flag;
    int i;
    for(i = 0; i < nodeVector.size()-1; i++)
    {
        flag = false;
        for(int j = i+1; j<nodeVector.size(); j++)
        {
            if(overlap(nodeVector[i],nodeVector[j]))
            {
                if(checkAlpha(nodeVector[i], nodeVector[j]) )
                {
                    if(!x_overlap(nodeVector[i], nodeVector[j]))
                    {
//                        cout<<"addEdge"<<endl;
                        FINAL->addEdge(nodeVector[i],nodeVector[j]);
                        flag = true;
                    }
                }
                if(checkBeta(nodeVector[i], nodeVector[j]))
                {
                    if(!y_overlap(nodeVector[i], nodeVector[j]))
                    {
//                        cout<<"addEdge"<<endl;
                        FINAL->addEdge(nodeVector[i],nodeVector[j]);
                        flag = true;
                    }
                }

            }

        }

    }
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
    x.push_back(a->left);
    x.push_back(a->right);
    x.push_back(b->left);
    x.push_back(b->right);

    sort(x.begin(),x.end());

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
                    }
                }
                if(checkAlpha(nodeVector[i],nodeVector[j]))
                {
                    if(!y_overlap(nodeVector[i], nodeVector[j]))
                    {
                        flag1 = false;
                    }
                }
            }
        }
    }

    return flag1;
}




bool myfunction4(Edge* a,Edge* b)
{
    return (a->node[0]->id<b->node[0]->id);
}


void putOtherNodeInTheGraph(Graph* p)
{
    for(int i = 0; i< nodeVector.size(); i++)
    {
        if(!nodeVector[i]->inTheGraph)
        {
            p->nodes.push_back(nodeVector[i]);
        }
    }
}





