#include "MapCreator.h"
#include "HelperFunctions.h"

MapCreator::MapCreator()
{
	aID			=	0;
	bID			=	0;
}
MapCreator::~MapCreator()
{
	delete tempClone;
	delete mainOrigMap;
	// Delete maps
	std::vector<std::string>::iterator i = m_sMapNameList.begin();
	for(; i != m_sMapNameList.end(); ++i)
		delete m_mMapList.find(*i)->second;
}

void MapCreator::CreateMap(std::string mapName)
{
	// If map created register maps name
	if(m_mMapList.insert(std::make_pair(mapName, new InfluenceMap( (mainOrigMap) ))).second)
		m_sMapNameList.push_back(mapName);
}

GraphMap* MapCreator::CreateNxNMap(std::string mapName, int* startOfIds, int size, float density)
{
	GraphMap* tempMap = new GraphMap();
	//float x=-5.0f+10, y=5.0f+10, z=0.0f+10;
	float x=-density+10, y=density+10, z=0.0f;

	GraphNode *A;//, *B;
	UINT mapSize = size;
	UINT startID = (UINT)*startOfIds;

	for(UINT i=0; i<mapSize; ++i)
	{
		for(UINT j=0; j<mapSize; ++j)
		{
			A = tempMap->CreateGraphNode(*startOfIds, D3DXVECTOR3(x+(density*j), y, z));
			(*startOfIds)++;
		}
		y -= density;
	}

	tempMap->SetUpAdjList();

	// Connect horizontal edges
	aID = startID, bID = startID+1;
	for(UINT i=0; i<mapSize; ++i)
	{
		aID = (i*mapSize)+startID; bID = ((i*mapSize)+1)+startID;
		for(UINT j=0; j<mapSize-1; j++)
		{
			tempMap->ConnectGraphNodes(aID, bID, true);
			aID+=1; bID+=1;
		}
	}

	// Connect vertical edges
	aID = startID, bID = startID+mapSize;
	for(UINT i=0; i<mapSize-1; ++i)
	{
		aID = (i*mapSize)+startID; bID = (mapSize+(i*mapSize))+startID;
		for(UINT j=0; j<mapSize; ++j)
		{
			tempMap->ConnectGraphNodes(aID, bID, true);
			aID+=1; bID+=1;
		}
	}

	// Add map and map names to proper vectors
	if(m_mMapList.insert(std::make_pair(mapName, new InfluenceMap(tempMap))).second)
		m_sMapNameList.push_back(mapName);

	if(mapName == "main")
	{
		mainOrigMap = tempMap;
		// Model clone after main map
		tempClone = new InfluenceMap(mainOrigMap);
	}

	return tempMap;
}

void MapCreator::CreateInfluence(std::string mapName, int id, 
								 D3DXVECTOR3* pos, float influence, float* health)
{
	// Set influence properties
	MapCreator::Influence infl;
	infl.id					=	id;
	infl.influenceValue		=	influence;
	infl.mapName			=	mapName;
	infl.pos				=	pos;
	infl.health				=	health;
	
	// Register influence
	m_iInfluenceList.push_back(infl);
}

void MapCreator::AddInfluenceToMap(std::string mapName, D3DXVECTOR3 pos, float influence)
{
	static int nodeId;

	closestNode = FindClosestGraphNode(pos);
	nodeId = closestNode->GetId();
	// Add influence to tempMap
	tempClone->SetInfluence(nodeId, influence);
	// Add tempMap to desired map
	m_mMapList.find(mapName)->second->AddMap(tempClone);
}

//InfluenceMap* MapCreator::GetSelectedMap(DWORD mapTypeFlags)
//{
//	// Check flags and add maps accordingly
//	if ((ALLY & mapTypeFlags) == ALLY)
//	{
//		tempClone->AddMap(m_mMapList.find("ally")->second);
//	}
//
//	if ((ENEMY & mapTypeFlags) == ENEMY)
//	{
//		tempClone->AddMap(m_mMapList.find("enemy")->second);
//	}
//
//	if ((HEALTH & mapTypeFlags) == HEALTH)
//	{
//		tempClone->AddMap(m_mMapList.find("health")->second);
//	}
//
//	if ((WEAPON & mapTypeFlags) == WEAPON)
//	{
//		tempClone->AddMap(m_mMapList.find("weapon")->second);
//	}
//
//	if ((INFLUENCE & mapTypeFlags) == INFLUENCE)
//	{
//		tempClone->AddMap(m_mMapList.find("ally")->second)
//				 ->SubtractMap(m_mMapList.find("enemy")->second);
//	}
//
//	if ((TENSION & mapTypeFlags) == TENSION)
//	{
//		tempClone->AddMap(m_mMapList.find("ally")->second)
//				 ->AddMap(m_mMapList.find("enemy")->second);
//	}
//
//	if ((VULNERABILITY & mapTypeFlags) == VULNERABILITY)
//	{
//		//tempClone->AddMap(m_mMapList.find("weapon")->second);
//	}
//
//	return tempClone;
//}

void MapCreator::ModifyRegInfluence(int id, float influneceValue)
{
	infIt = m_iInfluenceList.begin();
	for(; infIt != m_iInfluenceList.end(); ++infIt)
	{
		if( (*infIt).id == id )
		{
			(*infIt).influenceValue = influneceValue;
			return;
		}
	}
}

GraphNode* MapCreator::GetHighestInfluence(std::string searchMapName)
{
	return m_mMapList.find(searchMapName)->second->GetLargestInflunece();
}

void MapCreator::Update(float dt)
{
	// Reset maps for new influence claculations
	stringIt = m_sMapNameList.begin();
	for(; stringIt != m_sMapNameList.end(); ++stringIt)
	{
		m_mMapList.find(*stringIt)->second->SetMapToZero();
	}
	tempClone->SetMapToZero();

	// Update all registered influences
	infIt = m_iInfluenceList.begin();
	for(; infIt != m_iInfluenceList.end(); ++infIt)
	{
		AddInfluenceToMap(infIt->mapName, *infIt->pos, infIt->influenceValue);
	}

	//(GetSelectedMap(INFLUENCE));
	tempClone->GetListOfLargest(3);
	tempClone->Update(dt);
}

void MapCreator::CreateGraphicsFor(std::string mapName)
{
	if(mapName == "temp")
		tempClone->CreateGraphicObjects();
	else
		m_mMapList.find(mapName)->second->CreateGraphicObjects();
}

GraphNode* MapCreator::FindClosestGraphNode(D3DXVECTOR3 pos)
{
	std::vector<GraphNode*> mainNodeList = mainOrigMap->GetAllNodes();
	std::vector<GraphNode*>::iterator i = mainNodeList.begin();
	float testDistance, shortestDistance = 999999;
	GraphNode*	closestNode = 0;

	for(; i != mainNodeList.end(); ++i)
	{
		testDistance = MeasureDistance((*i)->GetPosition(), pos);
		if(shortestDistance > testDistance)
		{
			closestNode = (*i);
			shortestDistance = testDistance;
		}
	}

	return closestNode;
}

void MapCreator::CreateDynamicNode(int id, D3DXVECTOR3 pos, std::string mapName, float influence)
{
	// Set influence properties
	MapCreator::Influence infl;
	infl.id					=	id;
	infl.influenceValue		=	influence;
	infl.mapName			=	mapName;
	infl.pos				=	new D3DXVECTOR3(pos);
	
	// Register influence
	m_iInfluenceList.push_back(infl);
}

//void MapCreator::CreateClone(GraphMap* makeClone, GraphMap* cloneThis)
//{
//	//std::vector<GraphNode*> graph1;// = makeClone->GetAllNodes();
//	std::vector<GraphNode*> graph2 = cloneThis->GetAllNodes();
//
//	if(!makeClone)
//		makeClone = new GraphMap();
//
//	std::vector<GraphNode*>::iterator i = graph2.begin();
//	for(; i != graph2.end(); i++)
//	{
//		makeClone->CreateGraphNode( (*i)->GetId(), (*i)->GetPosition());
//	}
//
//}

//GraphMap* MapCreator::CreateClone(GraphMap* cloneThis)
//{
//	//std::vector<GraphNode*> graph1;// = makeClone->GetAllNodes();
//	GraphMap* makeClone = new GraphMap();
//	std::vector<GraphNode*> graph2 = cloneThis->GetAllNodes();
//
//	std::vector<GraphNode*>::iterator i = graph2.begin();
//	for(; i != graph2.end(); i++)
//	{
//		makeClone->CreateGraphNode( (*i)->GetId(), (*i)->GetPosition());
//	}
//
//	return makeClone;
//}

