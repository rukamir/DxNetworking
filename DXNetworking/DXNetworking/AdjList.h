#ifndef ADJLIST_H
#define ADJLIST_H

#include "GraphNode.h"
#include <vector>
#include <map>

using namespace std;
 
//struct List
//{
// Node* l_Node; double l_Weight;
//};

#define AList AdjList::Instance() 

class AdjList
{
public:
	static AdjList* Instance(); 
	map<GraphNode*, vector<GraphNode*>> m_vList;
	std::vector<GraphNode*>				m_vpGraphNodes;

	vector<GraphNode*> GetAdjNodes(GraphNode* A)
		{return m_vList.find(A)->second;}
	vector<int> GetAdjNodesById(int getNodesAdjToId);

	void createSize(vector<GraphNode*> new_list);
	//A<->B
	void ConnectTwoWay(GraphNode* A, GraphNode* B); // two way connection
	//A->B
	void ConnectOneWay(GraphNode* A, GraphNode* B); // single connection
private: 
	AdjList(){}
}; 

#endif