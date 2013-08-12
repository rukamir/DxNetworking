#include "AdjList.h"

AdjList* AdjList::Instance()
{
     static AdjList instance;
     return &instance;
}

vector<int> AdjList::GetAdjNodesById(int getNodesAdjToId)
{
	GraphNode* checkNode = NULL;
	vector<GraphNode*>::iterator i = m_vpGraphNodes.begin();
	for (; i != m_vpGraphNodes.end(); ++i)
	{
		if (getNodesAdjToId == (*i)->GetId() )
		{
			checkNode = (*i);
		}
	}

	vector<GraphNode*> adjListToId = m_vList.find(checkNode)->second;
	vector<GraphNode*>::iterator j = adjListToId.begin();
	vector<int> adjIdList;
	for (; j != adjListToId.end(); j++)
	{
		adjIdList.push_back( (*j)->GetId() );
	}

	return adjIdList;
}

void AdjList::createSize(vector<GraphNode*> new_list)
{
	vector<GraphNode*>::iterator i = new_list.begin();
	for (; i != new_list.end(); i++)
	{
		//insert a Node* in the map->first
		//for future access
		m_vList.insert( make_pair( *i, vector<GraphNode*>() ) );
	}
	m_vpGraphNodes = new_list;
}

void AdjList::ConnectTwoWay(GraphNode* A, GraphNode* B)
{
	// connects nodes in both directions
	//A->B
	ConnectOneWay(A, B);
	//B->A
	ConnectOneWay(B, A);
}

void AdjList::ConnectOneWay(GraphNode* A, GraphNode* B)
{
	//connects A->B
	int numOfConnections = m_vList.find(A)->second.size();
	bool found = false;

	// Used to cycle through A's list of connections
	for(int i = 0; i < numOfConnections; i++)
	{
		// if B is not found in list of A's connections
		// found is false
		if(m_vList.find(A)->second.at(i)/*[A->nodeID][i]*/ == B)
		{
			found = true;
			break;
		}
		else 
			found = false;
	}

	// add B to A's node list
	if(!found)
		m_vList.find(A)->second.push_back(B);//[A->nodeID].push_back(B);
}