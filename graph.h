#ifndef GRAPH_H
#define GRAPH_H

#include <algorithm>
#include <vector>
#include <map>
#include <string>
#include <cstring>
#include <fstream>

#define DIS_INF 2147483647

using namespace std;

class Node;
class CC;

class Edge{

	public:
		Edge(Node *a, Node *b);
		Node* node[2];
		Node *getNeighbor(Node *n);
		bool operator < (const Edge& rhs) const;
};

class Node{

	public:
		Node(const int& i);
		void addEdge(Edge *e);
		void sortEdge();

		int id;
        int color;
		bool traveled;
		int left;
		int right;
		int top;	
		int down;
        bool inTheGraph;
        /*void initNode()*/
		vector<Edge *> edge;
		int f;
		int d;
		Node *prev;
		int heap_idx;
};

class Graph{

	public:
		Graph(const string& n);

		~Graph();
        vector<CC *> connected;
		void addEdge(const int& v1, const int& v2);
        void addEdge(Node* v1, Node* v2);
		void sortEdgesOfNode();
        void sortNodesByDegree();
        void sortNodesByID();
		void init();
		Node * getNodeById(const int& id);
		map<int, Node *> nodesMap;
        vector<Node *> nodes;
		vector<Edge *> edges;
		string name;
};

//CC->Connected component
class CC{

    public:
        CC(const string& n);

        ~CC();

        void addEdge(Node* v1, Node* v2);
        void sortEdgesOfNode();
        void sortNodesByDegree();
        void sortNodesByID();
        void init();
        Node * getNodeById(const int& id);
        map<int, Node *> nodesMap;
        vector<Node *> nodes;
        vector<Edge *> edges;
        string name;
        bool colorable;
};


#endif
