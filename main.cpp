#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "graph.h"

using namespace std;

typedef vector<string> Data;
typedef vector<Data> DataList;

//function declaration
void getData();
bool myfunction(Data, Data);
void sortDataList(DataList& );
void string2int(DataList& );
void makeGraph(DataList& );

DataList list;
string alpha, beta, omega;
vector<Graph*> graphArray;
vector<Node*> nodeArray;

int main()
{
	getData();
	sortDataList(list);
	for(int i = 0;i<list.size();i++)
	{
		for(int j=0;j<list[i].size();j++)
		{
			cout<<setw(5)<<list[i][j]<<" ";
		}
		cout<<endl;
	}
	Graph a;
	cout<<"alpha: "<<alpha<<endl;
	cout<<"beta: "<<beta<<endl;
	cout<<"omega: "<<omega<<endl; 
	
}



//get data from test.txt to DataList datastructure
void getData()
{
	fstream fs ("test.txt" ,fstream::in);
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



/*
void string2int(DataList& a)
{
	for(int i = 0;i<a.size();i++)
	{
		for(int j=0;j<a[i].size();j++)
		{
			
		}
		cout<<endl;
	}
}*/

void makeNode(DataList& in)
{
	for(int i = 0; i< in.size(); i++)
	{
		Node* temp;
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
		temp->left = left2;
		temp->down = down2;
		temp->top = top2;
		temp->right = right2;

	}
}