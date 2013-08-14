#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H

#include <vector>

#include "Entity.h"
#include "3DObj.h"
#include "SpriteManager.h"
#include  "MenuObj.h"

class NetworkController;

#define WMI WorldManager::Instance()

class WorldManager
{
private:
	std::vector<Entity*>		m_vEntities;
	Entity*						ent;
	unsigned short				m_sMenuId;

public:
	NetworkController			*m_NetControl;
	SpriteManager				*m_SpriteMan;
	//Obj3D						*myObj;
	MenuObj						*myMenu;
	WorldManager();
	~WorldManager();

	Entity*		GetEntityById(int id);

	Entity*		CreateBall();
	Entity*		CreateTiger();

	// General Menu Controls
	bool IsOverMenuButton(LPCSTR buttonTitle);
	SpriteElements* GetMenuElemByTitle(LPCSTR buttonTitle);

	// Server Menu
	// Menu ID: 1
	void CreateServerMenu();
	// Menu ID: 2
	void CreateGameLobbyMenu();

	// Network Controls
	void JoinGame(short gameId);
	void QuitGame();
	void Server_SendPackets(int packId);
	void RemoveMenu();

private:
	int m_iNVID;								// next valid ID

public:
	int GetNVID();								// get next valid ID
	void Update(float dt);
	void Render();
	void ResetWorldManager();

	static WorldManager* Instance();\
};

#endif	// end WORLDMANAGER_H