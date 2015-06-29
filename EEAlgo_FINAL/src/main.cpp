#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "graph.h"
#include <cmath>
#include "getpart.h"
#include <queue>

using namespace std;

typedef vector<string> Data;
typedef vector<Data> DataList;
int innerprod(int *vec1,int *vec2,int demension);
void sortCCByVeclen(vector<CC*> &clraC);

int main(int argc,char * argv[])
{
	//以下部分為湯智帆所做
	getData(argv[1]);
	sortDataList(list);
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


	FINAL->sortNodesByID();
	
	//以下部分為徐喆所做
	
	
	//BFS to figure out each cc and whether they are 2-colorable
	std::stringstream ccname;

	FINAL->init();

	FINAL->sortNodesByID();
	FINAL->sortEdgesOfNode();

	queue<Node *> Q;
	Node *temNod, *temNod2; 
	Edge *temEdg;
	int t,s;
	t = 0;
	for(int j = 0;j < FINAL->nodes.size();j++){
		if(FINAL->nodes[j]->traveled == false){
			temNod = FINAL->nodes[j];
			Q.push(temNod);

			CC* newcc = new CC(t);
			FINAL->cc.push_back(newcc);
			FINAL->cc[t]->nodes.push_back(temNod);
			FINAL->cc[t]->colorable = true;
			temNod->traveled = true;
			temNod->color = 0;
			while(!Q.empty()){
				temNod = Q.front();
				Q.pop();
				for(int i = 0; i < temNod->edge.size();i++){
					temEdg = temNod->edge[i];
					temNod2 = temEdg->getNeighbor(temNod);
				//if not visited before
					if(temNod2->traveled == false){
						temNod2->traveled = true;
						temNod2->color = 1-temNod->color;
				

						Q.push(temNod2);
						FINAL->cc[t]->nodes.push_back(temNod2);
					}
					//else,the neighbor has been colored
					else{
						if(temNod2->color + temNod->color != 1){
							FINAL->cc[t]->colorable = false;
						}
					}
				}//for
			}//while
			if(FINAL->cc[t]->colorable){
				for(int k = 0;k < FINAL->cc[t]->nodes.size();k++){
					if(FINAL->CBleft == FINAL->CBright &&FINAL->CBright == FINAL->CBtop &&FINAL->CBtop== FINAL->CBdown){
						FINAL->CBleft = FINAL->cc[t]->nodes[k]->left;
						FINAL->CBright = FINAL->cc[t]->nodes[k]->right; 
						FINAL->CBtop = FINAL->cc[t]->nodes[k]->top; 
						FINAL->CBdown = FINAL->cc[t]->nodes[k]->down;
						
					}
					else{
						if(FINAL->cc[t]->nodes[k]->left < FINAL->CBleft){
						
							FINAL->CBleft = FINAL->cc[t]->nodes[k]->left; 
						
						}
						if(FINAL->cc[t]->nodes[k]->right > FINAL->CBright){
						
							FINAL->CBright = FINAL->cc[t]->nodes[k]->right; 
						
						}
						if(FINAL->cc[t]->nodes[k]->top > FINAL->CBtop){
						
							FINAL->CBtop = FINAL->cc[t]->nodes[k]->top; 
						
						}
						if(FINAL->cc[t]->nodes[k]->down < FINAL->CBdown){
						
							FINAL->CBdown = FINAL->cc[t]->nodes[k]->down; 
						
						}
					}
				}
			}
			t++;//next FINAL->cc
		}//if
	}//for
	

	int ccnum = FINAL->cc.size();
	int V,H,nodesnum,vl,wd,ht;

	if((FINAL->CBright - FINAL->CBleft)%Omega == 0){
		H = (FINAL->CBright - FINAL->CBleft)/Omega;
	}else{
		H = (FINAL->CBright - FINAL->CBleft)/Omega + 1;
	}
	if((FINAL->CBtop - FINAL->CBdown)%Omega == 0){
		V = (FINAL->CBtop - FINAL->CBdown)/Omega;
	}else{
		V = (FINAL->CBtop - FINAL->CBdown)/Omega + 1;
	}

	//to hold the bounds of windows
	int* right = new int[H];
	int* left = new int[H];
	int* top = new int[V];
	int* down = new int[V];
	//to hold the color-difference vertor,and only take 2-colorable connected component into account
	vector<CC*> ColorableC;
	int validid = 0;
	for(int i = 0;i < ccnum;i++){
		if(FINAL->cc[i]->colorable){
			FINAL->cc[i]->vecid = validid;
			validid++;
			ColorableC.push_back(FINAL->cc[i]);
		}
	}
	//number of 2-colorable cc
	int vccnum;
	vccnum = ColorableC.size();
//	cout << "In total " << vccnum << "colorable ccs" << endl;
	int ** vec = new int*[vccnum];
	for(int i = 0;i < vccnum; i++){
		vec[i] = new int[V*H];
	}
	//initializing vector
	for(int i = 0;i < vccnum;i++){
		for(int j = 0;j < V*H ;j++){
			vec[i][j] = 0;
		}
	}
	//length of each vector,unused
	int *veclen = new int[vccnum];
	for(int i = 0;i < vccnum;i++){
		veclen[i] = 0;
	}
	for(int h = 0;h < H - 1;h++){
		left[h] = FINAL->CBleft + h*Omega;
		right[h] = FINAL->CBleft + (h + 1)*Omega;
	}
	right[H-1] = FINAL->CBright;
	left[H - 1] = FINAL->CBright - Omega;
	for(int v = 0;v < V - 1;v++){
		down[v] = FINAL->CBdown + v*Omega;
		top[v] = FINAL->CBdown + (v + 1)*Omega;
	}
	top[V-1] = FINAL->CBtop;
	down[V - 1] = FINAL->CBtop - Omega;
	for(int cn = 0;cn < vccnum;cn++){
		nodesnum = ColorableC[cn]->nodes.size();
		for(int n = 0;n < nodesnum;n++){
			temNod = ColorableC[cn]->nodes[n];

			for(int h = (temNod->left - FINAL->CBleft)/Omega; temNod->right > left[h] && h < H; h++){
				for(int v = (temNod->down - FINAL->CBdown)/Omega; temNod->top > down[v] && v < V;v++){

					wd = ((temNod->right < right[h])?temNod->right:right[h]) - ((temNod->left > left[h])?temNod->left:left[h]);
					ht = ((temNod->top < top[v])?temNod->top:top[v]) - ((temNod->down > down[v])?temNod->down:down[v]);
					s = wd*ht;
					//if colored color 0,let the contribution to be positive
					if(!temNod->color){
						//the cnth connected component's contribution to the v*H+h th window
						//attention to our mapping formula:for the h,v window,we store its data into [v*H+h]
						vec[cn][v*H+h] += s;
					}
					//else let the contribution to be negative
					else{
						vec[cn][v*H+h] -= s;
					}
				}//for v
			}//for h
		}//for n
	}//for cn
	//computing veclen for every 2-colorable cc
	for(int i = 0;i < vccnum;i++){
		vl = 0;
		for(int j = 0;j < V*H; j++){
			vl += vec[i][j] * vec[i][j];
		}
		ColorableC[i]->veclen = vl;
	}
	//sort the vectors by vector length
	sortCCByVeclen(ColorableC);
	int *totalvec = new int[V*H];
	//for the longest vector,don't change the original coloring.
	ColorableC[0]->reverse = false;
	int tempid;
	for(int i = 0;i < V*H; i++){
		tempid = ColorableC[0]->vecid;
		totalvec[i] = vec[tempid][i];
	}
	for(int i = 1;i < vccnum; i++){
		tempid = ColorableC[i]->vecid;
		//if inner product is negative,then the coloring is to some degree a good plan ,since it "counteract" the total result,else we should reverse the direction of this vector;
		if(innerprod(totalvec,vec[tempid],V*H) > 0){
			ColorableC[i]->reverse = true;
			for(int j = 0; j < V*H;j++){
				vec[tempid][j] = -vec[tempid][j];
			}
		}
		for(int j = 0; j < V*H;j++){
			totalvec[j] += vec[tempid][j];
		}
	}//for, all cc
	for(int i = 0;i < vccnum;i++){
		if(ColorableC[i]->reverse == true){

			nodesnum = ColorableC[i]->nodes.size();
			for(int j = 0;j < nodesnum;j++){

				ColorableC[i]->nodes[j]->color = 1-ColorableC[i]->nodes[j]->color;
			}
		}
		else{

			nodesnum = ColorableC[i]->nodes.size();
			for(int j = 0;j < nodesnum;j++){

			}
		}
	}
	//calculating color density
	int *Asize = new int[H*V];
	int *Bsize = new int[H*V];
	for(int i = 0; i < H*V;i++){
		Asize[i] = 0;
		Bsize[i] = 0;
	}
	for(int cn = 0;cn < vccnum;cn++){
		nodesnum = ColorableC[cn]->nodes.size();
		for(int n = 0;n < nodesnum;n++){
			temNod = ColorableC[cn]->nodes[n];
			for(int h = (temNod->left - FINAL->CBleft)/Omega; temNod->right > left[h] && h < H; h++){
				for(int v = (temNod->down - FINAL->CBdown)/Omega; temNod->top > down[v] && v < V;v++){
					wd = ((temNod->right < right[h])?temNod->right:right[h]) - ((temNod->left > left[h])?temNod->left:left[h]);
					ht = ((temNod->top < top[v])?temNod->top:top[v]) - ((temNod->down > down[v])?temNod->down:down[v]);
					s = wd*ht;
					//if colored color 0,that is A,add Asize

					if(!temNod->color){
						//the cnth connected component's contribution to the v*H+h th window
						//vec[cn][v*H+h] = (min(node.right,right[h]) - max(node.left,left[h]))*(min(node.top,top[v]) - max.)
						Asize[v*H+h] += s;
					}
					//else let the contribution to be negative
					else{
						Bsize[v*H+h] += s;
					}
				}//for v
			}//for h
		}//for n
	}
	for(int i = 0; i < H*V;i++){

	}
	//writing into outputfile
	fstream fout;
	fout.open(argv[2],ios::out);
	for(int v = 0;v < V;v++){

		for(int h = 0;h < H;h++){
			fout << "WIN[" << v*H + h << "]=" <<left[h] << "," << down[v] << ","<< right[h] << "," << top[v] << "(" << ((double)Asize[v*H+h]*100)/(Omega*Omega) << " " << ((double)Bsize[v*H+h]*100)/(Omega*Omega) << ")" << endl;
		}
	}
	for(int i = 0;i < ccnum; i++){
		fout << "GROUP" << endl;
		if(FINAL->cc[i]->colorable){
			//print color A
			t = 1;
			for(int j = 0;j < FINAL->cc[i]->nodes.size();j++){
				if(!FINAL->cc[i]->nodes[j]->color){
					fout << "CA[" << t << "]=" << FINAL->cc[i]->nodes[j]->left << "," << FINAL->cc[i]->nodes[j]->down << ","<< FINAL->cc[i]->nodes[j]->right << ","<< FINAL->cc[i]->nodes[j]->top << endl;
					t++;
				}
			}
			//print color B
			t = 1;
			for(int j = 0;j < FINAL->cc[i]->nodes.size();j++){
				if(FINAL->cc[i]->nodes[j]->color){
					fout << "CB[" << t << "]=" << FINAL->cc[i]->nodes[j]->left << "," << FINAL->cc[i]->nodes[j]->down << ","<< FINAL->cc[i]->nodes[j]->right << ","<< FINAL->cc[i]->nodes[j]->top << endl;
					t++;
				}
			}

		}//end if colorable
		//eles not 2-colorable
		else{
			for(int j = 0,t = 1;j < FINAL->cc[i]->nodes.size();j++,t++){
					fout << "NO[" << t << "]=" << FINAL->cc[i]->nodes[j]->left << "," << FINAL->cc[i]->nodes[j]->down << ","<< FINAL->cc[i]->nodes[j]->right << ","<< FINAL->cc[i]->nodes[j]->top << endl;
			}
		}
	}
	fout.close();
	
	
	
	//以下部分為湯智帆所做
	///CHECKER FOR LEGAL COLORING!!!!     
	
	for(int i = 0; i<FINAL->cc.size(); i++)
	{
		for(int j = 0; j<FINAL->cc[i]->nodes.size(); j++)
		{
			cout<<FINAL->cc[i]->nodes[j]->left<<" ";
			cout<<FINAL->cc[i]->nodes[j]->down<<" ";
			cout<<FINAL->cc[i]->nodes[j]->right<<" ";
			cout<<FINAL->cc[i]->nodes[j]->top;
			cout<<endl;
		}
		cout<<endl;
	}
	
	for(int i = 0; i<FINAL->cc.size(); i++ )
	{
		for(int j = 0; j<FINAL->cc[i]->edges.size(); j++)
		{
			cout<<FINAL->cc[i]->edges[j]->node[0]<<" ";
			cout<<FINAL->cc[i]->edges[j]->node[1]<<endl;
		}
	}
	

	
	for(int i = 0; i<FINAL->cc.size();i++)
	{
		if(FINAL->cc[i]->colorable == 0)
		{
			for(int j = 0 ; j < FINAL->cc[i]->nodes.size(); j++)
			{
				FINAL->cc[i]->nodes[j]->color = -5;
			}
		}
	}
	
	
	for(int i = 0; i<FINAL->edges.size();i++)
	{
		cout<<FINAL->edges[i]->node[0]->id<<" ";
		cout<<FINAL->edges[i]->node[1]->id<<endl;
	}
	
	bool correct = true;
	for(int i = 0 ;i<FINAL->edges.size(); i++)
	{
		
		int nodeA = FINAL->edges[i]->node[0]->id;
		int nodeB = FINAL->edges[i]->node[1]->id;
		
		cout<<"color A: "<<FINAL->getNodeById(nodeA)->color<<endl;
		cout<<"color B: "<<FINAL->getNodeById(nodeB)->color<<endl;
		cout<<endl;
		
		int cA = FINAL->getNodeById(nodeA)->color;
		int cB = FINAL->getNodeById(nodeB)->color;
		
		if(cA != -5 && cB != -5 )
		{
			if(cA == cB)
			{
				correct = false;
			}
		}
		
	
		if(!correct)
		{
			cout<<"ERROR COLORING!!!"<<endl;
			
		}
		
	}
	
	
	
	if(!correct)
	{
		cout<<"ERROR COLORING!!!"<<endl;
			
	}else{
		cout<<"CORRECT COLORING!!!"<<endl;
	}
	
	
	
}

int innerprod(int *vec1,int *vec2,int demension){
	int r = 0;
	for(int i = 0;i < demension;i++){
		r += vec1[i] * vec2[i];
	}
	return r;
}

