#include "graph.h"
#include <iostream>


Edge::Edge(Node *a, Node *b)
{
	if ( a->id <= b->id ) { node[0] = a; node[1] = b; }
	else { node[0] = b; node[1] = a; }
}

bool Edge::operator < (const Edge& rhs) const{

	int id1a = node[0]->id;
	int id1b = node[1]->id;

	int id2a = rhs.node[0]->id;
	int id2b = rhs.node[1]->id;


	if ( id1a == id2a ) return id1b < id2b;
	if ( id1a == id2b ) return id1b < id2a;
	if ( id1b == id2a ) return id1a < id2b;
	if ( id1b == id2b ) return id1a < id2a;
    return true;
}
Node * Edge::getNeighbor(Node *n)
{
	if ( node[0] == n ) return node[1];
	if ( node[1] == n ) return node[0];

	return 0;	
}




Node::Node(const int& i)
{
	id = i;
	traveled = false;
    inTheGraph = false;
    color = 0;
	d = DIS_INF;
	prev = 0;
}

void Node::addEdge(Edge *e)
{
	edge.push_back(e);
}

bool edgeComp( const Edge* A, const Edge* B ){
	if ( (*A) < (*B) ) return true;
	return false;
}


void Node::sortEdge()
{
    sort(edge.begin(), edge.end(), edgeComp);
}


Graph::Graph(const string& n)
{
	name = n;
}


Graph::~Graph()
{
	vector<Edge *>::iterator itE;
	for ( itE = edges.begin() ; itE != edges.end() ; itE++ )
	{
		delete (*itE);
		(*itE) = 0;
	}
	
	map<int, Node *>::iterator itN;
	for ( itN = nodesMap.begin() ; itN != nodesMap.end() ; itN++ )
	{
		delete (*itN).second;
		(*itN).second = 0;
	}

    vector<Node *>::iterator itN2;
	for ( itN2 = nodes.begin() ; itN2 != nodes.end() ; itN2++ )
	{
		(*itN2) = 0;
	}

}
		
void Graph::addEdge(Node* v1, Node* v2)
{
    map<int, Node *>::iterator it = nodesMap.find(v1->id);
    if ( it == nodesMap.end() )
    {
        this->nodesMap[v1->id] = v1;
        this->nodes.push_back(v1);
        v1->inTheGraph = true;
    }

    it = nodesMap.find(v2->id);
    if ( it == nodesMap.end() )
    {
        this->nodesMap[v2->id] = v2;
        this->nodes.push_back(v2);
        v2->inTheGraph = true;
    }

    Edge *e = new Edge(v1, v2);
    this->edges.push_back(e);

    v1->edge.push_back(e);
    v2->edge.push_back(e);
}
//void Graph::addEdge(const int& v1, const int& v2)
//{
//	Node *a, *b;
//	map<int, Node *>::iterator it = nodesMap.find(v1);
//	if ( it != nodesMap.end() )
//		a = (*it).second;
//	else
//	{
//		a = new Node(v1);
//		nodesMap[v1] = a;
//        nodes.push_back(a);
//	}

//	it = nodesMap.find(v2);
//	if ( it != nodesMap.end() )
//		b = (*it).second;
//	else
//	{
//		b = new Node(v2);
//		nodesMap[v2] = b;
//        nodes.push_back(b);
//	}

//	Edge *e = new Edge(a, b);
//	edges.push_back(e);

//	a->edge.push_back(e);
//	b->edge.push_back(e);

//}


void Graph::sortEdgesOfNode()
{
	map<int, Node *>::iterator it;
	for ( it = nodesMap.begin() ; it != nodesMap.end() ; it++ )
	{
		Node *node = (*it).second;
		node->sortEdge();
	}

}



bool NodeCompByD( const Node* A, const Node* B ){
	if ( A->edge.size() > B->edge.size() ) 
        return true;
    else if (A->edge.size() == B->edge.size()) {
        if (A->id < B->id) 
            return true;
        else 
            return false;
    }
    else
        return false;
}

void Graph::sortNodesByDegree()
{
    sort(nodes.begin(), nodes.end(), NodeCompByD);
}

bool CCCompByVecLen(const CC* A,const CC* B){
	if(A->veclen < B->veclen) return true;
	else return false;
}

void sortCCByVeclen(vector<CC*> &clraC){
	sort(clraC.begin(),clraC.end(), CCCompByVecLen);
}

bool NodeCompByID( const Node* A, const Node* B ){
	if ( A->id < B->id ) return true;
    else return false;
}

void Graph::sortNodesByID()
{
    sort(nodes.begin(), nodes.end(), NodeCompByID);
}
void Graph::init()
{
	map<int, Node *>::iterator itN;
	for ( itN = nodesMap.begin() ; itN != nodesMap.end() ; itN++ )
	{
		Node *node = (*itN).second;
		node->traveled = false;
		node->d = DIS_INF;
		node->prev = 0;
        node->color = -1;
	}
	CBleft = CBright = CBtop = CBdown = 0;
}

Node * Graph::getNodeById(const int& id)
{
	return nodesMap[id];
}

///////////////////////////////////////////////////////////////////////
//////////////ccccccccccc//////////////////
///
///
///
///
///
///


CC::CC(const int& n)
{
    id = n;
    colorable = false;
	reverse = false;
}


CC::~CC()
{
    vector<Edge *>::iterator itE;
    for ( itE = edges.begin() ; itE != edges.end() ; itE++ )
    {
        delete (*itE);
        (*itE) = 0;
    }

    map<int, Node *>::iterator itN;
    for ( itN = nodesMap.begin() ; itN != nodesMap.end() ; itN++ )
    {
        delete (*itN).second;
        (*itN).second = 0;
    }

    vector<Node *>::iterator itN2;
    for ( itN2 = nodes.begin() ; itN2 != nodes.end() ; itN2++ )
    {
        (*itN2) = 0;
    }
}


void CC::addEdge(Node* v1, Node* v2)
{
//    Node *a, *b;
//    cout<<"@@@@@@@@@@@@@@@@@@@"<<endl;
    map<int, Node *>::iterator it = nodesMap.find(v1->id);
    if ( it == nodesMap.end() )
    {
        this->nodesMap[v1->id] = v1;
        this->nodes.push_back(v1);
        v1->inTheGraph = true;
    }

    it = nodesMap.find(v2->id);
    if ( it == nodesMap.end() )
    {
        this->nodesMap[v2->id] = v2;
        this->nodes.push_back(v2);
        v2->inTheGraph = true;
    }

    Edge *e = new Edge(v1, v2);
//    cout<<"aaaaaaaaaaaaa"<<endl;
    this->edges.push_back(e);

    v1->edge.push_back(e);
    v2->edge.push_back(e);



}


void CC::sortEdgesOfNode()
{
    map<int, Node *>::iterator it;
    for ( it = nodesMap.begin() ; it != nodesMap.end() ; it++ )
    {
        Node *node = (*it).second;
        node->sortEdge();
    }

}



//bool NodeCompByD( const Node* A, const Node* B ){
//    if ( A->edge.size() > B->edge.size() )
//        return true;
//    else if (A->edge.size() == B->edge.size()) {
//        if (A->id < B->id)
//            return true;
//        else
//            return false;
//    }
//    else
//        return false;
//}

void CC::sortNodesByDegree()
{
    sort(nodes.begin(), nodes.end(), NodeCompByD);
}


//bool NodeCompByID( const Node* A, const Node* B ){
//    if ( A->id < B->id ) return true;
//    else return false;
//}

void CC::sortNodesByID()
{
    sort(nodes.begin(), nodes.end(), NodeCompByID);
}
void CC::init()
{
    map<int, Node *>::iterator itN;
    for ( itN = nodesMap.begin() ; itN != nodesMap.end() ; itN++ )
    {
        Node *node = (*itN).second;
        node->traveled = false;
        node->d = DIS_INF;
        node->prev = 0;
        node->color = -1;
    }

}

Node * CC::getNodeById(const int& id)
{
    return nodesMap[id];
}
