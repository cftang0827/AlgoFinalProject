#ifndef GETPART_H
#define GETPART_H

#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "graph.h"


typedef vector<string> Data;
typedef vector<Data> DataList;

extern DataList list;
extern string alpha, beta, omega;
extern int Alpha, Beta, Omega;
extern vector<Node*> nodeVector;
extern Graph* FINAL;


void getData(char * src);
bool myfunction(Data, Data);
void sortDataList(DataList& );
void string2int(DataList& );
void makeNode(DataList& in);
void makeEdge();
bool overlap(Node* , Node* );
void makeGraph();
bool checkAlpha(Node* , Node* );
bool checkBeta(Node*, Node* );
bool x_overlap(Node* , Node* );
bool y_overlap(Node* , Node* );
bool checkEnd(Node* );
bool myfunction4(Edge* ,Edge* );
void putOtherNodeInTheGraph(Graph* );


#endif // GETPART_H

