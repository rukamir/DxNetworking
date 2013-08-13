#pragma once

#include <D3dx9math.h>
#include <stdio.h>

//#define CLIENT_JOIN_SERVER			0x0001
//#define CLIENT_JOIN_GAME			0x0002
//#define CLIENT_MOVE_EVENT			0x0004
//#define CLIENT_FIRE_EVENT			0x0008
//#define CLIENT_QUIT_GAME			0x0010
//#define CLIENT_QUIT_SERVER			0x0020
//#define SERVER_SYNC_LOBBY			0x0040
//#define SERVER_CLIENT_JOIN_GAME		0x0080
//#define SERVER_SYNC_GAME			0x0100
//#define SERVER_MOVE_EVENT			0x0200
//#define SERVER_FIRE_EVENT			0x0400
//#define SERVER_GAME_OVER			0x0800
//#define SERVER_CLIENT_QUIT_GAME		0x1000

////////////////////////////////////////////////
///
///	WARNING:
///	packetID first 4 bits will be 0-15 and determine the packet type based on the IDs below
///	On MOVE EVENT the last 4 bits will be encoded for the movement flags
///	
///	_ _ _ _ | _ _ _ _
///	^ v < > | _ I D _
///
////////////////////////////////////////////////

struct PlayerData
{
	char clientID;
	char health;
	char moveFlags;
	//extra byte here
	float positionX;
	float positionY;
	float rotation;
};

struct ClientPacket_JoinServer // ID #0
{
	char packetID;
	char clientID;
	char clientName[30];
};

struct ClientPacket_JoinGame // ID #1
{
	char packetID;
	char clientID;
	char gameID;
};

struct ClientPacket_MoveEvent // ID #2
{	
	char packetID;
	char clientID;
};

struct ClientPacket_FireEvent // ID #3
{
	char packetID;
	char clientID;
	char targetID; // if 0 no target
};

struct ClientPacket_QuitGame // ID #4
{
	char packetID;
	char clientID;
	char gameID;
};

struct ClientPacket_QuitServer // ID #5
{
	char packetID;
	char clientID;
	char gameID;
};

struct ServerPacket_SyncLobby // ID #6
{
	char packetID;
	char clientID;		//Gives the client it's ID
	short playersInGame; //first 4 bits is first game, second is second game, etc. BIT_ENCODED
	char playersInLobby; //number of players connected in the lobby. MAX 255
};

struct ServerPacket_ClientJoinGame // ID #7
{
	char packetID;
	char clientID;
	char gameID;
};

struct ServerPacket_SyncGame // ID #8
{
	char packetID;
	PlayerData data[8];
};

struct ServerPacket_MoveEvent // ID #9
{
	char packetID;
	char clientID;
};

struct ServerPacket_FireEvent // ID #10
{
	char packetID;
	char clientID;
	char targetID; // if 0 no target
};

struct ServerPacket_GameOver // ID #11
{
	char packetID;
	char winnerID;
	char winnerName[30];
};

struct ServerPacket_ClientQuitGame // ID #12
{
	char packetID;
	char clientID;
	char gameID;
};

// Function to output packets
//void PacketOutput(void *acReadBuffer){
//	short id;
//	memcpy( &id, acReadBuffer, sizeof(short));
//	printf("Packet Id: %i\n", id);
//	switch (id)
//	{
//	case 0:
//		printf("Joined server Packet received!\nClient Id: %i\nClient Name: %s\n\n",
//			((ClientPacket_JoinServer*)acReadBuffer)->clientID,
//			((ClientPacket_JoinServer*)acReadBuffer)->clientName);
//		break;
//	case 1:
//		printf("Joined game Packet received!\nClient Id: %i\nGame Id: %i\n\n",
//			((ClientPacket_JoinGame*)acReadBuffer)->clientID,
//			((ClientPacket_JoinGame*)acReadBuffer)->gameID);
//		break;
//	case 2:
//		printf("Move Packet received!\nClient Id: %i\n\n",
//			((ClientPacket_MoveEvent*)acReadBuffer)->clientID);
//		break;
//	case 3:
//		printf("Fire Packet received!\nClient Id: %i\nPlayer Id: %i\n\n",
//			((ClientPacket_FireEvent*)acReadBuffer)->clientID,
//			((ClientPacket_FireEvent*)acReadBuffer)->targetID);
//		break;
//	case 4:
//		printf("Quit Game Packet received!\nClient Id: %i\nQuit Game Id: %i\n\n",
//			((ClientPacket_QuitGame*)acReadBuffer)->clientID,
//			((ClientPacket_QuitGame*)acReadBuffer)->gameID);
//		break;
//	case 5:
//		printf("Quit server Packet received!\nClient Id: %i\nQuit Game Id: %i\n\n",
//			((ClientPacket_QuitServer*)acReadBuffer)->clientID,
//			((ClientPacket_QuitServer*)acReadBuffer)->gameID);
//		break;
//	case 6:
//		printf("Sync Lobby Pack!!\nClient Id: %i\n\n",
//			((ServerPacket_SyncLobby*)acReadBuffer)->clientID);
//		break;
//	case 7:
//		printf("Client Joined Server!!\nClient %i joined game %i\n\n",
//			((ServerPacket_ClientJoinGame*)acReadBuffer)->clientID,
//			((ServerPacket_ClientJoinGame*)acReadBuffer)->gameID);
//		break;
//	case 8:
//		printf("Sync Game Packet!!\n\n");
//		break;
//	case 9:
//		printf("Server Move Event!!\nPlayer %i moved\n\n",
//			((ServerPacket_MoveEvent*)acReadBuffer)->clientID);
//		break;
//	case 10:
//		printf("Server Fire!!\n\n");
//		break;
//	case 11:
//		printf("Server Game Over!!\nPlayer: %s %i Wins!\n\n",
//			((ServerPacket_GameOver*)acReadBuffer)->winnerName,
//			((ServerPacket_GameOver*)acReadBuffer)->winnerID);
//		break;
//	case 12:
//		printf("Someone Quit!!\nPlayer %i quit game %i\n\n",
//			((ServerPacket_ClientQuitGame*)acReadBuffer)->clientID,
//			((ServerPacket_ClientQuitGame*)acReadBuffer)->gameID);
//		break;
//	default:
//		printf("Not valid data packet!!!!!!!!!!!!");
//		break;
//	}
//}