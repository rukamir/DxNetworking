#pragma once

#include <vector>
#include <map>

#include "NetClient.h"
#include "PacketTypes.h"
#include "Entity.h"

class NetworkController
{
private:
	Entity							*m_Owner;
	NetClient*						m_Client;
	char							m_sClientId;
	char							m_sClientName[30];
	char							g1, g2, g3, g4; // Holds players per game
	std::map<short, Entity*>		m_mEntMap;

	char							m_sCurGameId;
public:
	NetworkController(void);
	~NetworkController(void);

	void JoinServer();
	void JoinGame(char GameId);
	void SendPlayerFire(char playerId);
	void QuiteGame();
	void QuiteServer();
	void SendPlayerMove(char moveFlags);

	void TestServerPackets();

	void Update(float dt);

};

