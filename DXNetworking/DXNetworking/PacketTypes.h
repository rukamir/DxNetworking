//#pragma once
//

#pragma once

#include <D3dx9math.h>

#define CLIENT_JOIN_SERVER			0x0001
#define CLIENT_JOIN_GAME			0x0002
#define CLIENT_MOVE_EVENT			0x0004
#define CLIENT_FIRE_EVENT			0x0008
#define CLIENT_QUIT_GAME			0x0010
#define CLIENT_QUIT_SERVER			0x0020
#define SERVER_SYNC_LOBBY			0x0040
#define SERVER_CLIENT_JOIN_GAME		0x0080
#define SERVER_SYNC_GAME			0x0100
#define SERVER_MOVE_EVENT			0x0200
#define SERVER_FIRE_EVENT			0x0400
#define SERVER_GAME_OVER			0x0800
#define SERVER_CLIENT_QUIT_GAME		0x1000


struct Packet {
	Packet(){}
	Packet(short iD, float xVal, float yVal){
		id=iD; x=xVal; y=yVal;
	}
	short id;
	float x, y;
};


#ifndef PACKETS_H
#define PACKETS_H

struct PlayerData
{
	short playerID;
	int health;
	float positionX;
	float positionY;
	float rotation;
	char moveFlags;
};

struct ClientPacket_JoinServer // ID #1
{
	short packetID;
	short clientID;
	char clientName[28];
};

struct ClientPacket_JoinGame // ID #2
{
	short packetID;
	short clientID;
	short gameID;
};

struct ClientPacket_MoveEvent // ID #3
{	
	short packetID;
	short clientID;
	char moveflags;
};

struct ClientPacket_FireEvent // ID #4
{
	short playerID;
	short clientID;
};

struct ClientPacket_QuitGame // ID #5
{
	short packetID;
	short clientID;
	short gameID;
};

struct ClientPacket_QuitServer // ID #6
{
	short packetID;
	short clientID;
	short gameID;
};

struct ServerPacket_SyncLobby // ID #7
{
	short packetID;
	short clientID;
	char playersInGame[4]; //4 games total - 8 players in each game - bit encoded
	char playersInLobby[4]; // number of players in the lobby - bit encoded
};

struct ServerPacket_ClientJoinGame // ID #8
{
	short packetID;
	short clientID;
	short gameID;
};

struct ServerPacket_SyncGame // ID #9
{
	short packetID;
	PlayerData data[8];
};

struct ServerPacket_MoveEvent // ID #10
{
	short packetID;
	short clientID;
	char moveflags;
};

struct ServerPacket_FireEvent // ID #11
{
	short packetID;
	PlayerData data;
};

struct ServerPacket_GameOver // ID #12
{
	short packetID;
	short winnerID;
	char winnerName[28];
};

struct ServerPacket_ClientQuitGame // ID #13
{
	short packetID;
	short clientID;
	short gameID;
};

// Function to output packets
//void PacketOutput(void *acReadBuffer){
//	short id;
//	memcpy( &id, acReadBuffer, sizeof(short));
//	printf("Packet Id: %i\n", id);
//	switch (id)
//	{
//	case 1:
//		printf("Joined server Packet received!\nClient Id: %i\nClient Name: %s\n\n",
//			((ClientPacket_JoinServer*)acReadBuffer)->clientID,
//			((ClientPacket_JoinServer*)acReadBuffer)->clientName);
//		break;
//	case 2:
//		printf("Joined game Packet received!\nClient Id: %i\nGame Id: %i\n\n",
//			((ClientPacket_JoinGame*)acReadBuffer)->clientID,
//			((ClientPacket_JoinGame*)acReadBuffer)->gameID);
//		break;
//	case 3:
//		printf("Move Packet received!\nClient Id: %i\nMove Flag: %i\n\n",
//			((ClientPacket_MoveEvent*)acReadBuffer)->clientID,
//			((ClientPacket_MoveEvent*)acReadBuffer)->moveflags);
//		break;
//	case 4:
//		printf("Fire Packet received!\nClient Id: %i\nPlayer Id: %i\n\n",
//			((ClientPacket_FireEvent*)acReadBuffer)->clientID,
//			((ClientPacket_FireEvent*)acReadBuffer)->playerID);
//		break;
//	case 5:
//		printf("Quit Game Packet received!\nClient Id: %i\nQuit Game Id: %i\n\n",
//			((ClientPacket_QuitGame*)acReadBuffer)->clientID,
//			((ClientPacket_QuitGame*)acReadBuffer)->gameID);
//		break;
//	case 6:
//		printf("Quit server Packet received!\nClient Id: %i\nQuit Game Id: %i\n\n",
//			((ClientPacket_QuitGame*)acReadBuffer)->clientID,
//			((ClientPacket_QuitGame*)acReadBuffer)->gameID);
//		break;
//	case 7:
//		printf("Sync Lobby Pack!!\nClient Id: %i\n\n",
//			((ServerPacket_SyncLobby*)acReadBuffer)->clientID);
//		break;
//	case 8:
//		printf("Client Joined Server!!\nClient %i joined game %i\n\n",
//			((ServerPacket_ClientJoinGame*)acReadBuffer)->clientID,
//			((ServerPacket_ClientJoinGame*)acReadBuffer)->gameID);
//		break;
//	case 9:
//		printf("Sync Game Packet!!\n\n");
//		break;
//	case 10:
//		printf("Server Move Event!!\nPlayer %i moved with %i flags\n\n",
//			((ServerPacket_MoveEvent*)acReadBuffer)->clientID,
//			((ServerPacket_MoveEvent*)acReadBuffer)->moveflags);
//		break;
//	case 11:
//		printf("Server Fire!!\n\n");
//		break;
//	case 12:
//		printf("Server Game Over!!\nPlayer: %s %i Wins!\n\n",
//			((ServerPacket_GameOver*)acReadBuffer)->winnerName,
//			((ServerPacket_GameOver*)acReadBuffer)->winnerID);
//		break;
//	case 13:
//		printf("Someone Quit!!\nPlayer %i quit game %i\n\n",
//			((ServerPacket_ClientQuitGame*)acReadBuffer)->clientID,
//			((ServerPacket_ClientQuitGame*)acReadBuffer)->gameID);
//		break;
//	default:
//		printf("Not valid data packet!!!!!!!!!!!!");
//		break;
//	}
//}

#endif