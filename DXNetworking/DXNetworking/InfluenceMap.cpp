#include "InfluenceMap.h"
#include "HelperFunctions.h"

InfluenceMap::InfluenceMap(GraphMap* cloneThis)
{
	std::vector<GraphNode*> nodeList = cloneThis->GetAllNodes();
	int size =0 , ct=0;
	//GraphNode* node;

	VectGraphNodes::iterator i = nodeList.begin();
	for(; i != nodeList.end(); ++i)
	{
		m_mGraphNodes.insert(std::pair<int, GraphNode>(ct, **i));
		m_vGraphNodes.push_back( &m_mGraphNodes.find((*i)->GetId())->second );
		++ct;
	}
}

InfluenceMap::~InfluenceMap()
{
}

bool PreventDuplicate(std::vector<int>* graph, int addThis)
{
	// Search for node already in graph
	std::vector<int>::iterator i = graph->begin();
	for(; i != graph->end(); ++i)
	{
		if ( (*i) == addThis)
			return false;
	}

	// If node was not found add and return true
	graph->push_back(addThis);
	return true;
}

void InfluenceMap::SetMapToZero()
{
	i = m_vGraphNodes.begin();
	for(; i != m_vGraphNodes.end(); ++i)
	{
		(*i)->SetInfluence(0.0f);
	}
}

void InfluenceMap::SetInfluence(int nodeIdToInfluence, float influence)
{
	static GraphNode* node;// = this->GetNodeById(nodeIdToInfluence);
	static float highestValue;
	static float infl;// = 0.0f;
	static bool neg;// = !(influence > 0);
	static float distSq;// = 0.0f;

	highestValue = 0.0f;
	distSq = 0.0f;
	node = this->GetNodeById(nodeIdToInfluence);
	node->SetInfluence(influence);
	neg = !(influence > 0);

	this->GetNodeById(nodeIdToInfluence)->SetInfluence(influence);

	i = m_vGraphNodes.begin();
	for(; i != m_vGraphNodes.end(); ++i)
	{
		distSq = MeasureDistance(node->GetPosition(), (*i)->GetPosition());
		if (distSq == 0)
		{
			infl = influence;
		}
		else
		{
			//infl = ((influence*influence) / distSq);//*100;
			//infl =  distSq / ((influence*influence));//*100;
			infl = (influence*influence) / distSq;// MeasureDistance(node->GetPosition(), (*i)->GetPosition());
		}

		if(neg)
			(*i)->SetInfluence(-(infl));
		else
		{
			(*i)->SetInfluence(infl);
			if(infl > highestValue)
			{
				highestValue = infl;
				m_nHighestValueNode = (*i);
			}
		}
	}
}

//void InfluenceMap::SetInfluence(int nodeIdToInfluence, float influence)
//{
//	GraphNode *thisNode, *mainNode = GetNodeById(nodeIdToInfluence);
//	mainNode->SetInfluence(influence);
//	thisNode = mainNode;
//
//	// Nodes to be influenced
//	std::vector<int> influenceList = AList->GetAdjNodesById(thisNode->GetId());
//	//std::vector<GraphNode*> list2, list3;
//	std::vector<int> list2;
//
//	while(true)
//	{
//		// Grab all Adjacent nodes with no Influence
//		for(const auto &id1 : influenceList)
//		{
//			for(const auto &graphNode2 : AList->GetAdjNodesById(id1))//GetAdjNodesById(id1))
//			{
//				// Only grab is influence is 0
//				if(this->GetNodeById(id1)->GetInfluence() == 0.0)
//					PreventDuplicate(&list2, graphNode2);//this->GetNodeById(graphNode2));//list2.push_back(GraphNode2);
//			}
//		}
//
//		// Sets influence levels
//		for(const auto &GraphNode : influenceList)
//		{
//			// If node has not been influenced
//			// *this helps the influence move forward
//			if(GetNodeById(GraphNode)->GetInfluence() == 0.0f)
//			{
//				// Get influence of next node to half of parent node
//				GetNodeById(GraphNode)->SetInfluence( thisNode->GetInfluence() * 0.8f);///2 );
//			}
//		}
//
//		if (list2.size() == 0)
//			return;
//
//		//give thisNode an address from the last round of nodes
//		thisNode = GetNodeById(influenceList.at(0));
//
//		// Set new Influence List and start over
//		influenceList = list2;
//		list2.clear();
//	}
//}

void InfluenceMap::CreateGraphicObjects()
{
	i = m_vGraphNodes.begin();
	for(; i != m_vGraphNodes.end(); ++i)
	{
		(*i)->CreateGraphicObject();
	}
}

void InfluenceMap::Update(float dt)
{
	i = m_vGraphNodes.begin();
	for(; i != m_vGraphNodes.end(); ++i)
	{
		(*i)->Update();
	}
}



//void InfluenceMap::SetInfluence(int nodeIdToInfluence, 
//								float nearInfl, float nearInflIncrRate, 
//								float peak, float farInfl, float farDissipation)
//{
//	GraphNode *thisNode, *mainNode = GetNodeById(nodeIdToInfluence);
//	GraphicsM->GetSphere(9999)->SetPosition(mainNode->GetPosition());
//	GraphicsM->GetSphere(9999)->SetScale(1.5f, 1.5f, 1.5f);
//
//	mainNode->SetInfluence(nearInfl);
//	thisNode = mainNode;
//	float currentInfluence = nearInfl;
//	bool hitPeak = false;
//
//	// Nodes to be influenced
//	std::vector<int> influenceList = AList->GetAdjNodes(thisNode);
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

GraphNode* InfluenceMap::GetNodeById(int id)
{
	return &m_mGraphNodes.find(id)->second;
}

GraphNode*	InfluenceMap::GetLargestInflunece()
{
	//return m_nHighestValueNode;
	static float highest, influenceValue;
	static GraphNode* node;
	static D3DXVECTOR3 pos;
	highest = 0.0f;
	influenceValue = 0.0f;

	i = m_vGraphNodes.begin();
	for(; i != m_vGraphNodes.end(); ++i)
	{
		influenceValue = (*i)->GetInfluence();
		if(highest < influenceValue)
		{
			highest = influenceValue;
			node = (*i);
			//pos = (*i)->GetPosition();
		}
	}
	return node;
}

void replaceLowest(std::vector<GraphNode*>* list, GraphNode* node)
{
	std::vector<GraphNode*>::iterator tempIt = list->begin();
	GraphNode* lowest = list->at(0);
	int counter = 0;


	for(; tempIt != list->end(); ++tempIt)
	{
		//get lowest out of current list
		if( (*tempIt)->GetInfluence() < lowest->GetInfluence() || !lowest)
		{
			lowest = *tempIt;
			counter++;

			//list[counter];
		}
	}

	if(node->GetInfluence() > lowest->GetInfluence())
	{
		lowest = node;
		(*list).at(counter) = node;
	}
}

std::vector<GraphNode*> getHighestOf(std::vector<GraphNode*>* list, int listCap)
{
	int itemsInList = 0;
	std::vector<GraphNode*> tempVect;
	std::vector<GraphNode*>::iterator tempIt = list->begin();
	std::vector<GraphNode*>::iterator tempIt2;

	for(; tempIt != list->end(); ++tempIt)
	{
		if(tempVect.size() < listCap)
		{
			tempVect.push_back(*tempIt);
		}
		else
		{
			replaceLowest(&tempVect, *tempIt);
		}
	}

	return tempVect;
}

std::vector<GraphNode*>	InfluenceMap::GetListOfLargest(const int numOfNodes)
{

	//unsigned int count = 0;
	//float highest[5], influenceValue;
	//static vector<GraphNode*> nodeList;
	//static D3DXVECTOR3 pos;
	//highest[0] = 0.0f;
	//influenceValue = 0.0f;
	//bool vectFull = false;

	//i = m_vGraphNodes.begin();
	//for(; i != m_vGraphNodes.end(); ++i)
	//{
	//	influenceValue = (*i)->GetInfluence();
	//	 add to list
	//	for (int it=0; it < numOfNodes; it++)
	//	{
	//		if(!vectFull)
	//		{
	//			if(highest[it] < influenceValue)
	//			{
	//				highest[it] = influenceValue;
	//				nodeList.push_back(*i);
	//				count++;
	//				if(count == numOfNodes)
	//					vectFull = true;
	//			}
	//		}
	//		else // if vect is full
	//		{
	//			if(highest[it] < influenceValue)
	//			{
	//				highest[it] = influenceValue;
	//				nodeList.push_back(*i);
	//				count++;
	//				if(count == numOfNodes)
	//					vectFull = true;
	//			}
	//		}
	//	}
	//}

	//i = m_vGraphNodes.begin();
	//for(; i != m_vGraphNodes.end(); ++i)
	//{
	//	influenceValue = (*i)->GetInfluence();
	//	for (int it=0; it < numOfNodes; it++)
	//	{
	//		if(highest[it] < influenceValue)
	//		{
	//			highest[count] = influenceValue;
	//			nodeList.push_back(*i);
	//			count++;
	//			//pos = (*i)->GetPosition();
	//		}
	//	}
	//}
	return getHighestOf(&this->m_vGraphNodes, 3);
}

InfluenceMap* InfluenceMap::AddMap(InfluenceMap* addThis)
{
	addList = addThis->GetAllNodes();

	// Create two iterators
	i = m_vGraphNodes.begin();
	j = addList.begin();
	// Increment them at the same rate
	for(; i != m_vGraphNodes.end(); ++i, ++j)
	{
		// Add influnece to this map
		m_mGraphNodes.find((*i)->GetId())->second.SetInfluence( (*j)->GetInfluence() + (*i)->GetInfluence() );
	}

	return this;
}

InfluenceMap* InfluenceMap::SubtractMap(InfluenceMap* addThis)
{
	addList = addThis->GetAllNodes();

	// Create two iterators
	i = m_vGraphNodes.begin();
	j = addList.begin();
	// Increment them at the same rate
	for(; i != m_vGraphNodes.end(); ++i, ++j)
	{
		// Add influnece to this map
		m_mGraphNodes.find((*i)->GetId())->second.SetInfluence( (*i)->GetInfluence() - (*j)->GetInfluence() );
	}

	return this;
}

InfluenceMap* InfluenceMap::MultiplyMap(InfluenceMap* addThis)
{
	addList = addThis->GetAllNodes();

	// Create two iterators
	i = m_vGraphNodes.begin();
	j = addList.begin();
	// Increment them at the same rate
	for(; i != m_vGraphNodes.end(); ++i, ++j)
	{
		// Add influnece to this map
		m_mGraphNodes.find((*i)->GetId())->second.SetInfluence( (*i)->GetInfluence() * (*j)->GetInfluence() );
	}

	return this;
}

bool InfluenceMap::AreAllNodesInfluenced()
{
	i = m_vGraphNodes.begin();
	for(; i != m_vGraphNodes.end(); i++)
	{
		if((*i)->GetInfluence() == 0.0f)
			return false;
	}
	return true;
}
