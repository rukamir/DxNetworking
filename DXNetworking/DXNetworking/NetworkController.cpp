#include "NetworkController.h"
#include "ThreadController.h"


NetworkController::NetworkController(void)
{
	m_sClientId					=	5;
	m_sCurGameId				=	0;
	memcpy( m_sClientName, "Jimmy", 6);//				=	"Jimmy";
	m_sClientName[sizeof(m_sClientName - 1)] = '\0';
	m_Client = new NetClient();
	//m_Client->SetServIP("192.168.1.101");
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
	((ClientPacket_JoinServer*)ptr)->packetID	=	0;

	m_Client->SetBuffer(ptr);
	m_Client->SendBuffer();

	delete ptr;
}

void NetworkController::JoinGame(char GameId){
	static void* ptr = NULL;
	ptr = new ClientPacket_JoinGame();

	((ClientPacket_JoinGame*)ptr)->clientID		=	m_sClientId;
	((ClientPacket_JoinGame*)ptr)->gameID		=	GameId;
	((ClientPacket_JoinGame*)ptr)->packetID		=	1;

	m_Client->SetBuffer(ptr);
	m_Client->SendBuffer();

	delete ptr;
}

void NetworkController::SendPlayerFire(char playerId){
	static void* ptr = NULL;
	ptr = new ClientPacket_FireEvent();

	((ClientPacket_FireEvent*)ptr)->clientID		=	m_sClientId;
	((ClientPacket_FireEvent*)ptr)->targetID		=	playerId;
	((ClientPacket_FireEvent*)ptr)->packetID		=	3;

	m_Client->SetBuffer(ptr);
	m_Client->SendBuffer();

	delete ptr;
}

void NetworkController::SendPlayerMove(char moveFlags){
	static void* ptr = NULL;
	ptr = new ClientPacket_MoveEvent();

	((ClientPacket_MoveEvent*)ptr)->clientID	=	m_sClientId;
	((ClientPacket_MoveEvent*)ptr)->packetID	=	2;
	//((ClientPacket_MoveEvent*)ptr)->moveflags	=	moveFlags;

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
	((ClientPacket_QuitGame*)ptr)->packetID		=	4;

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
	((ClientPacket_QuitServer*)ptr)->packetID	=	5;

	m_Client->SetBuffer(ptr);
	m_Client->SendBuffer();

	delete ptr;
	ptr = NULL;
}


void NetworkController::Update(float dt)
{
	static void*  ptr = NULL;
	static float counter = 0;
	//static char g1, g2, g3, g4;

	// every two seconds
	if (counter > 2.0f){
		ptr = m_Client->GetReceiveBuff();
		if (ptr){
			//GetEntityById(0)->SetPosition(D3DXVECTOR3(packet->x, 0.0f, packet->y));
			//void;
			//void* myP = (void*)(new Packet(1, 5, 5));
			//Packet myPack;
			char packId;
			memcpy( &packId, ptr, sizeof(char));
			//int id = packId >> 4;
			int id = packId;

			// Switch to determine server packets received
			switch (id)
			{
			case 6:
				g1 = (0xf000 & ((ServerPacket_SyncLobby*)ptr)->playersInGame) >> 12;
				g2 = (0xf00 & ((ServerPacket_SyncLobby*)ptr)->playersInGame) >> 8;
				g3 = (0xf0 & ((ServerPacket_SyncLobby*)ptr)->playersInGame) >> 4;
				g4 = (0xf & ((ServerPacket_SyncLobby*)ptr)->playersInGame);
				lobby = (((ServerPacket_SyncLobby*)ptr)->playersInLobby);
				break;
			case 7:
				m_sCurGameId	=	((ServerPacket_ClientJoinGame*)ptr)->gameID;
				break;
			case 8:
				((ServerPacket_SyncGame*)ptr);
				break;
			case 9:
				((ServerPacket_MoveEvent*)ptr);
				break;
			case 10:
				((ServerPacket_FireEvent*)ptr);
				break;
			case 11:
				((ServerPacket_GameOver*)ptr);
				break;
			case 12:
				((ServerPacket_ClientQuitGame*)ptr);
				break;
			default:
				break;
			}
			//delete ptr;
			ptr = NULL;
		}
		counter = 0.0f;
	} else{
		counter += dt;
	}

}

void NetworkController::Server_SyncLobby(){
	static void *ptr = NULL;
	ptr = new ServerPacket_SyncLobby();

	((ServerPacket_SyncLobby*)ptr)->packetID	=	6;
	((ServerPacket_SyncLobby*)ptr)->clientID	=	m_sClientId;
	((ServerPacket_SyncLobby*)ptr)->playersInLobby = 0x10;
	((ServerPacket_SyncLobby*)ptr)->playersInGame  = 0X00ff;

	m_Client->SetBuffer(ptr);
	m_Client->SendBuffer();

	delete ptr;
	ptr = NULL;
}

void NetworkController::Server_JoinGame(){
	static void *ptr = NULL;
	ptr = new ServerPacket_ClientJoinGame();

	((ServerPacket_ClientJoinGame*)ptr)->packetID	=	7;
	((ServerPacket_ClientJoinGame*)ptr)->clientID	=	m_sClientId;
	((ServerPacket_ClientJoinGame*)ptr)->gameID		=	m_sCurGameId;

	m_Client->SetBuffer(ptr);
	m_Client->SendBuffer();

	delete ptr;
}

void NetworkController::Server_SyncGame(){
	void *ptr = NULL;

	ptr = new ServerPacket_SyncGame();

	((ServerPacket_SyncGame*)ptr)->packetID	=	8;
	for(int i=0; i < 8; i++){
		((ServerPacket_SyncGame*)ptr)->data[i].clientID		= i;
		((ServerPacket_SyncGame*)ptr)->data[i].health		= 0x1;
		((ServerPacket_SyncGame*)ptr)->data[i].moveFlags	= 0xf;
		((ServerPacket_SyncGame*)ptr)->data[i].positionX	= 5.0f;
		((ServerPacket_SyncGame*)ptr)->data[i].positionY	= 5.0f;
		((ServerPacket_SyncGame*)ptr)->data[i].rotation		= 0.0f;
	}

	m_Client->SetBuffer(ptr);
	m_Client->SendBuffer();

	delete ptr;
	ptr = NULL;
}

void NetworkController::TestServerPackets(){
	static void* ptr = NULL;
	ptr = new ServerPacket_SyncLobby();

	((ServerPacket_SyncLobby*)ptr)->packetID	=	6;
	((ServerPacket_SyncLobby*)ptr)->clientID	=	m_sClientId;

	m_Client->SetBuffer(ptr);
	m_Client->SendBuffer();

	delete ptr;
	ptr = NULL;

	ptr = new ServerPacket_ClientJoinGame();

	((ServerPacket_ClientJoinGame*)ptr)->packetID	=	7;
	((ServerPacket_ClientJoinGame*)ptr)->clientID	=	m_sClientId;
	((ServerPacket_ClientJoinGame*)ptr)->gameID		=	m_sCurGameId;

	m_Client->SetBuffer(ptr);
	m_Client->SendBuffer();

	delete ptr;
	ptr = NULL;

	ptr = new ServerPacket_SyncGame();

	((ServerPacket_SyncGame*)ptr)->packetID	=	8;
	for(int i=0; i < 8; i++){
		((ServerPacket_SyncGame*)ptr)->data[0].clientID		= i;
		((ServerPacket_SyncGame*)ptr)->data[0].health		= 0x1;
		((ServerPacket_SyncGame*)ptr)->data[0].moveFlags	= 0xf;
		((ServerPacket_SyncGame*)ptr)->data[0].positionX	= 5.0f;
		((ServerPacket_SyncGame*)ptr)->data[0].positionY	= 5.0f;
		((ServerPacket_SyncGame*)ptr)->data[0].rotation		= 0.0f;
	}

	m_Client->SetBuffer(ptr);
	m_Client->SendBuffer();

	delete ptr;
	ptr = NULL;

	ptr = new ServerPacket_MoveEvent();

	((ServerPacket_MoveEvent*)ptr)->packetID	=	9;
	((ServerPacket_MoveEvent*)ptr)->clientID	=	m_sClientId;

	m_Client->SetBuffer(ptr);
	m_Client->SendBuffer();

	delete ptr;
	ptr = NULL;

	ptr = new ServerPacket_FireEvent();

	((ServerPacket_FireEvent*)ptr)->packetID	=	10;
	((ServerPacket_FireEvent*)ptr)->clientID	=	m_sClientId;
	((ServerPacket_FireEvent*)ptr)->targetID	=	1;

	m_Client->SetBuffer(ptr);
	m_Client->SendBuffer();

	delete ptr;
	ptr = NULL;

	ptr = new ServerPacket_GameOver();

	((ServerPacket_GameOver*)ptr)->packetID		=	11;
	((ServerPacket_GameOver*)ptr)->winnerID		=	m_sClientId;
	//((ServerPacket_GameOver*)ptr)->winnerName	=	"I Win";

	m_Client->SetBuffer(ptr);
	m_Client->SendBuffer();

	delete ptr;
	ptr = NULL;

	ptr = new ServerPacket_ClientQuitGame();

	((ServerPacket_ClientQuitGame*)ptr)->packetID	=	12;
	((ServerPacket_ClientQuitGame*)ptr)->clientID	=	m_sClientId;
	((ServerPacket_ClientQuitGame*)ptr)->gameID		=	m_sCurGameId;

	m_Client->SetBuffer(ptr);
	m_Client->SendBuffer();

	delete ptr;
	ptr = NULL;
}