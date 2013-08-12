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
	short							m_sClientId;
	char							m_sClientName[28];
	std::map<short, Entity*>		m_mEntMap;

	short							m_sCurGameId;
public:
	NetworkController(void);
	~NetworkController(void);

	void JoinServer();
	void JoinGame(short GameId);
	void SendPlayerFire(short playerId);
	void QuiteGame();
	void QuiteServer();
	void SendPlayerMove(char moveFlags);

	void TestServerPackets();

	void Update(float dt);

};

