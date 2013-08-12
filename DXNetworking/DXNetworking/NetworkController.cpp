#include "NetworkController.h"
#include "ThreadController.h"


NetworkController::NetworkController(void)
{
	m_sClientId					=	5;
	m_sCurGameId				=	4;
	memcpy( m_sClientName, "Jimmy", 6);//				=	"Jimmy";
	m_sClientName[sizeof(m_sClientName - 1)] = '\0';
	m_Client = new NetClient();
	m_Client->SetServIP("192.168.1.101");
	m_Client->Initialize();
	m_Client->Connect();

	ThrdCon->CreateNewThread(NetClient::listen_loop, ((void*)m_Client), false);

	//void* myP = new Packet(1, 5, 5);
	//Packet* myPack;
	//memcpy( myP, myPack, sizeof(Packet));



	//byte myByte[2] = (byte)myP << 8;


	//short val = (val << 8) + myByte[1];
	//val = (val << 8) + myByte[0];
}

NetworkController::~NetworkController(void)
{
	m_Client->Shutdown();
	delete m_Client;
}

void NetworkController::JoinServer(){
	static void* ptr = NULL;
	ptr = new ClientPacket_JoinServer();

	((ClientPacket_JoinServer*)ptr)->clientID	=	m_sClientId;
	memcpy( ((ClientPacket_JoinServer*)ptr)->clientName, m_sClientName, 28);
	((ClientPacket_JoinServer*)ptr)->packetID	=	CLIENT_JOIN_SERVER;//1;

	m_Client->SetBuffer(ptr);
	m_Client->SendBuffer();

	delete ptr;
}

void NetworkController::JoinGame(short GameId){
	static void* ptr = NULL;
	ptr = new ClientPacket_JoinGame();

	((ClientPacket_JoinGame*)ptr)->clientID		=	m_sClientId;
	((ClientPacket_JoinGame*)ptr)->gameID		=	GameId;
	((ClientPacket_JoinGame*)ptr)->packetID		=	CLIENT_JOIN_GAME;//2;

	m_Client->SetBuffer(ptr);
	m_Client->SendBuffer();

	delete ptr;
}

void NetworkController::SendPlayerFire(short playerId){
	static void* ptr = NULL;
	ptr = new ClientPacket_FireEvent();

	((ClientPacket_FireEvent*)ptr)->clientID		=	m_sClientId;
	((ClientPacket_FireEvent*)ptr)->playerID		=	playerId;
	//((ClientPacket_FireEvent*)ptr)->packetID		=	3;

	m_Client->SetBuffer(ptr);
	m_Client->SendBuffer();

	delete ptr;
}

void NetworkController::SendPlayerMove(char moveFlags){
	static void* ptr = NULL;
	ptr = new ClientPacket_MoveEvent();

	((ClientPacket_MoveEvent*)ptr)->clientID	=	m_sClientId;
	((ClientPacket_MoveEvent*)ptr)->packetID	=	CLIENT_MOVE_EVENT;//3;
	((ClientPacket_MoveEvent*)ptr)->moveflags	=	moveFlags;

	m_Client->SetBuffer(ptr);
	m_Client->SendBuffer();

	delete ptr;
	ptr = NULL;
}

void NetworkController::QuiteGame(){
	static void* ptr = NULL;
	ptr = new ClientPacket_MoveEvent();

	((ClientPacket_QuitGame*)ptr)->clientID		=	m_sClientId;
	((ClientPacket_QuitGame*)ptr)->gameID		=	m_sCurGameId;
	((ClientPacket_QuitGame*)ptr)->packetID		=	CLIENT_QUIT_GAME;//5;

	m_Client->SetBuffer(ptr);
	m_Client->SendBuffer();

	delete ptr;
	ptr = NULL;
}

void NetworkController::QuiteServer(){
	static void* ptr = NULL;
	ptr = new ClientPacket_QuitServer();

	((ClientPacket_QuitServer*)ptr)->clientID	=	m_sClientId;
	((ClientPacket_QuitServer*)ptr)->gameID		=	m_sCurGameId;
	((ClientPacket_QuitServer*)ptr)->packetID	=	CLIENT_QUIT_SERVER;//6;

	m_Client->SetBuffer(ptr);
	m_Client->SendBuffer();

	delete ptr;
	ptr = NULL;
}


void NetworkController::Update(float dt)
{
	static void*  ptr = NULL;
	static float counter = 0;

	// every two seconds
	if (counter > 2.0f){
		ptr = m_Client->GetReceiveBuff();
		if (ptr){
			//GetEntityById(0)->SetPosition(D3DXVECTOR3(packet->x, 0.0f, packet->y));
			//void;
	//void* myP = (void*)(new Packet(1, 5, 5));
	//Packet myPack;
	short id;
	memcpy( &id, ptr, sizeof(short));

	// Switch to determine server packets received
	switch (id)
	{
	case 7:
		((ServerPacket_SyncLobby*)ptr);
		break;
	case 8:
		m_sCurGameId	=	((ServerPacket_ClientJoinGame*)ptr)->gameID;
		break;
	case 9:
		((ServerPacket_SyncGame*)ptr);
		break;
	case 10:
		((ServerPacket_MoveEvent*)ptr);
		break;
	case 11:
		((ServerPacket_FireEvent*)ptr);
		break;
	case 12:
		((ServerPacket_GameOver*)ptr);
		break;
	case 13:
		((ServerPacket_ClientQuitGame*)ptr);
		break;
	default:
		break;
	}


			delete ptr;
			ptr = NULL;
		}
		counter = 0.0f;
	} else{
		counter += dt;
	}

}

void NetworkController::TestServerPackets(){
	//static unsigned char *c = new unsigned char();
	static void* ptr = NULL;
	ptr = new ServerPacket_SyncLobby();

	((ServerPacket_SyncLobby*)ptr)->packetID	=	SERVER_SYNC_LOBBY;//7;
	((ServerPacket_SyncLobby*)ptr)->clientID	=	m_sClientId;

	////memset(c, 0, 4);
	//*c = 0x1; ++c;
	//*c = 0x2; ++c;
	//*c = 0x4; ++c;
	//*c = 0x8;
	//((ServerPacket_SyncLobby*)ptr)->playersInGame[0]	= ONE;
	//((ServerPacket_SyncLobby*)ptr)->playersInGame[1]	= THREE;
	//((ServerPacket_SyncLobby*)ptr)->playersInGame[2]	= SEVEN;
	//((ServerPacket_SyncLobby*)ptr)->playersInGame[3]	= THREE;

	//((ServerPacket_SyncLobby*)ptr)->playersInLobby[0]	= SEVEN;
	//((ServerPacket_SyncLobby*)ptr)->playersInLobby[1]	= FIVE;
	//((ServerPacket_SyncLobby*)ptr)->playersInLobby[2]	= ONE;
	//((ServerPacket_SyncLobby*)ptr)->playersInLobby[3]	= FIVE;

	m_Client->SetBuffer(ptr);
	m_Client->SendBuffer();

	delete ptr;
	ptr = NULL;

	ptr = new ServerPacket_ClientJoinGame();

	((ServerPacket_ClientJoinGame*)ptr)->packetID	=	SERVER_CLIENT_JOIN_GAME;//8;
	((ServerPacket_ClientJoinGame*)ptr)->clientID	=	m_sClientId;
	((ServerPacket_ClientJoinGame*)ptr)->gameID		=	m_sCurGameId;

	m_Client->SetBuffer(ptr);
	m_Client->SendBuffer();

	delete ptr;
	ptr = NULL;

	ptr = new ServerPacket_SyncGame();

	((ServerPacket_SyncGame*)ptr)->packetID	=	SERVER_SYNC_GAME;//9;
	((ServerPacket_SyncGame*)ptr)->data;//	=	m_sClientId;

	m_Client->SetBuffer(ptr);
	m_Client->SendBuffer();

	delete ptr;
	ptr = NULL;

	ptr = new ServerPacket_MoveEvent();

	((ServerPacket_MoveEvent*)ptr)->packetID	=	SERVER_MOVE_EVENT;
	((ServerPacket_MoveEvent*)ptr)->clientID	=	m_sClientId;
	((ServerPacket_MoveEvent*)ptr)->moveflags	=	SERVER_MOVE_EVENT;//8;

	m_Client->SetBuffer(ptr);
	m_Client->SendBuffer();

	delete ptr;
	ptr = NULL;

	ptr = new ServerPacket_FireEvent();

	((ServerPacket_FireEvent*)ptr)->packetID	=	SERVER_FIRE_EVENT;//=	11;
	((ServerPacket_FireEvent*)ptr)->data;//	=	m_sClientId;

	m_Client->SetBuffer(ptr);
	m_Client->SendBuffer();

	delete ptr;
	ptr = NULL;

	ptr = new ServerPacket_GameOver();

	((ServerPacket_GameOver*)ptr)->packetID	=	SERVER_GAME_OVER;
	((ServerPacket_GameOver*)ptr)->winnerID;//	=	m_sClientId;
	((ServerPacket_GameOver*)ptr)->winnerName;//	=	m_sClientId;

	m_Client->SetBuffer(ptr);
	m_Client->SendBuffer();

	delete ptr;
	ptr = NULL;

	ptr = new ServerPacket_ClientQuitGame();

	((ServerPacket_ClientQuitGame*)ptr)->packetID	=	SERVER_CLIENT_QUIT_GAME;
	((ServerPacket_ClientQuitGame*)ptr)->clientID	=	m_sClientId;
	((ServerPacket_ClientQuitGame*)ptr)->gameID		=	m_sCurGameId;

	m_Client->SetBuffer(ptr);
	m_Client->SendBuffer();

	delete ptr;
	ptr = NULL;
}