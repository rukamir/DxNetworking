#include "GraphMap.h"
#include "AdjList.h"

GraphMap::GraphMap()
{
}

GraphMap::~GraphMap()
{
	for(const auto &GraphNode : m_vGraphNodes)
	{
		delete GraphNode;
	}
	m_vGraphNodes.clear();
}

GraphNode* GraphMap::CreateGraphNode(int id, D3DXVECTOR3 pos)
{
	GraphNode* node = new GraphNode(id, pos);
	//m_vGraphNodes.push_back(node);
	m_vGraphNodes.push_back( node );
	AList->createSize(m_vGraphNodes);
	return node;
}

void GraphMap::SetUpAdjList()
{
	//AList->createSize(m_vGraphNodes);
}

void GraphMap::ConnectGraphNodes(GraphNode* A, GraphNode* B, bool twoWay)
{
	if(!twoWay)
		AList->ConnectOneWay(A, B);
	else
		AList->ConnectTwoWay(A, B);
}

void GraphMap::ConnectGraphNodes(int aID, int bID, bool twoWay)
{
	GraphNode *A=NULL, *B=NULL;

	// Find GraphNodes by ID
	for(const auto &GraphNode : m_vGraphNodes)
	{
		if(GraphNode->GetId() == aID)
			A = GraphNode;
		else if(GraphNode->GetId() == bID)
			B = GraphNode;

		// Once both are found leave loop
		if (A != NULL && B != NULL)
			break;
	}

	if(!twoWay)
		AList->ConnectOneWay(A, B);
	else
		AList->ConnectTwoWay(A, B);
}

bool PreventDuplicate(VectGraphNodes* graph, GraphNode* addThis)
{
	// Search for node already in graph
	VectGraphNodes::iterator i = graph->begin();
	for(; i != graph->end(); i++)
	{
		if ( (*i) == addThis)
			return false;
	}

	// If node was not found add and return true
	graph->push_back(addThis);
	return true;
}

//void GraphMap::SetInfluence(int nodeIdToInfluence, float influence)
//{
//	GraphNode *thisNode, *mainNode = GetNodeById(nodeIdToInfluence);
//	mainNode->SetInfluence(influence);
//	thisNode = mainNode;
//
//	// Nodes to be influenced
//	std::vector<GraphNode*> influenceList = AList->GetAdjNodes(thisNode);
//	std::vector<GraphNode*> list2, list3;
//
//	while(true)
//	{
//		// Grab all Adjacent nodes with no Influence
//		for(const auto &GraphNode1 : influenceList)
//		{
//			for(const auto &GraphNode2 : AList->GetAdjNodes(GraphNode1))
//			{
//				// Only grab is influence is 0
//				if(GraphNode2->GetInfluence() == 0.0)
//					PreventDuplicate(&list2, GraphNode2);//list2.push_back(GraphNode2);
//			}
//		}
//
//		// Sets influence levels
//		for(const auto &GraphNode : influenceList)
//		{
//			// If node has not been influenced
//			// *this helps the influence move forward
//			if(GraphNode->GetInfluence() == 0.0f)
//			{
//				// Get influence of next node to half of parent node
//				GraphNode->SetInfluence( thisNode->GetInfluence() * 0.95f);///2 );
//			}
//		}
//
//		//give thisNode an address from the last round of nodes
//		thisNode = influenceList.at(0);
//
//		// Set new Influence List and start over
//		influenceList = list2;
//		list2.clear();
//
//		// If all nodes have been influenced leave
//		if(AreAllNodesInfluenced())
//			return;
//	}
//}

//void GraphMap::SetInfluence(int nodeIdToInfluence, 
//								float nearInfl, float nearInflIncrRate, 
//								float peak, float farInfl, float farDissipation)
//{
//	GraphNode *thisNode, *mainNode = GetNodeById(nodeIdToInfluence);
//	//GraphicsM->GetSphere(9999)->SetPosition(mainNode->GetPosition());
//	//GraphicsM->GetSphere(9999)->SetScale(1.5f, 1.5f, 1.5f);
//
//	mainNode->SetInfluence(nearInfl);
//	thisNode = mainNode;
//	float currentInfluence = nearInfl;
//	bool hitPeak = false;
//
//	// Nodes to be influenced
//	std::vector<GraphNode*> influenceList = AList->GetAdjNodes(thisNode);
//	std::vector<GraphNode*> list2, list3;
//
//	while(true)
//	{
//		// Grab all Adjacent nodes with no Influence
//		for(const auto &GraphNode1 : influenceList)
//		{
//			for(const auto &GraphNode2 : AList->GetAdjNodes(GraphNode1))
//			{
//				// Only grab is influence is 0
//				if(GraphNode2->GetInfluence() == 0.0)
//					PreventDuplicate(&list2, GraphNode2);//list2.push_back(GraphNode2);
//			}
//		}
//
//		// Sets influence levels
//		for(const auto &GraphNode : influenceList)
//		{
//			// If node has not been influenced
//			// *this helps the influence move forward
//			if(GraphNode->GetInfluence() == 0.0f)
//			{
//				// Get influence of next node to half of parent node
//				//GraphNode->SetInfluence( thisNode->GetInfluence() * 0.95f);///2 );
//				GraphNode->SetInfluence( currentInfluence );
//			}
//		}
//
//
//				if(!hitPeak)
//				{
//					if(currentInfluence > peak)
//					{
//						hitPeak = true;
//						currentInfluence = peak;
//						//GraphNode->SetInfluence( currentInfluence );
//					}
//					else
//					{
//						//GraphNode->SetInfluence( currentInfluence );
//						currentInfluence *= nearInflIncrRate + 1.0f;
//					}
//				}
//				else
//				{
//					currentInfluence *= farDissipation;
//					//currentInfluence = peak;
//					//GraphNode->SetInfluence( currentInfluence );
//				}
//
//		//give thisNode an address from the last round of nodes
//		thisNode = influenceList.at(0);
//
//		// Set new Influence List and start over
//		influenceList = list2;
//		list2.clear();
//
//		// If all nodes have been influenced leave
//		if(AreAllNodesInfluenced())
//			return;
//	}
//}

bool GraphMap::AreAllNodesInfluenced()
{
	for(const auto &GraphNode : m_vGraphNodes)
	{
		if(GraphNode->GetInfluence() == 0.0f)
			return false;
	}
		return true;
}

void GraphMap::CreateFromGraph(VectGraphNodes nodeList)
{
	// Make an entire new copy of graph
	for(const auto &node : nodeList)
	{
		//m_vGraphNodes.push_back(new GraphNode(node->GetID(), node->GetPosition()));
		m_vGraphNodes.push_back(new GraphNode(*node));
	}
}

GraphNode* GraphMap::GetNodeById(int id)
{
	for(const auto &node : m_vGraphNodes)
	{
		if(node->GetId() == id)
			return node;
	}

	// If not found return NULL
	return NULL;
}

VectGraphNodes	GraphMap::GetPeaks()
{
	return VectGraphNodes();
}

void GraphMap::SetMapToZero()
{
	VectGraphNodes::iterator i = m_vGraphNodes.begin();
	for(; i != m_vGraphNodes.end(); i++)
	{
		(*i)->SetInfluence(0.0f);
	}
}

void GraphMap::CreateGraphicObjects()
{
	VectGraphNodes::iterator i = m_vGraphNodes.begin();
	for(; i != m_vGraphNodes.end(); i++)
	{
		(*i)->CreateGraphicObject();
	}
}

void GraphMap::Update(float dt)
{
	for(const auto &GraphNode : m_vGraphNodes)
	{
		GraphNode->Update();
	}
}

GraphMap GraphMap::operator+=(GraphMap rhs)
{
	VectGraphNodes rhsNodeList = rhs.GetAllNodes();

	// Create two iterators
	std::vector<GraphNode*>::iterator i = m_vGraphNodes.begin(), j = rhsNodeList.begin();
	// Increment them at the same rate
	for(; i != m_vGraphNodes.end(); i++, j++)
	{
		// Add influnece to this map
		(*i)->SetInfluence((*j)->GetInfluence() + (*i)->GetInfluence());
	}
	return *this;
}

GraphMap GraphMap::operator-=(GraphMap rhs)
{
	VectGraphNodes rhsNodeList = rhs.GetAllNodes();

	// Create two iterators
	std::vector<GraphNode*>::iterator i = m_vGraphNodes.begin(), j = rhsNodeList.begin();
	// Increment them at the same rate
	for(; i != m_vGraphNodes.end(); i++, j++)
	{
		// Add influnece to this map
		(*i)->SetInfluence((*j)->GetInfluence() - (*i)->GetInfluence());
	}
	return *this;
}
