#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>

#include "NetClient.h"
#include "ThreadController.h"

NetClient::NetClient(){
    SOCKET ConnectSocket = INVALID_SOCKET;
    result = NULL;
    ptr = NULL;
    sendbuf = "this is a test";
    //recvbuf = char[DEFAULT_BUFLEN];
    recvbuflen = DEFAULT_BUFLEN;

	ThrdCon->MakeMutex("RecvBuffer");
}

NetClient::NetClient(int argc, char* argv[])
{
	
    SOCKET ConnectSocket = INVALID_SOCKET;
    result = NULL;
    ptr = NULL;
    sendbuf = "this is a test";
    //recvbuf = char[DEFAULT_BUFLEN];
    recvbuflen = DEFAULT_BUFLEN;

	// Sets ip to local host
	// re assign using SetServIP()
	serverIP = argv[1];

}

NetClient::~NetClient()
{
	closesocket(m_sClientSock);
    WSACleanup();
}

void NetClient::ValidateClient()
{
	//// Validate the parameters
 //   if (argc != 2) {
 //       printf("usage: %s server-name\n", argv[0]);
 //       return;
 //   }
}

void NetClient::Initialize(){
	// Initialize Winsock
    error = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (error != 0) {
        printf("WSAStartup failed with error: %d\n", error);
        return;
    }

	ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    //error = getaddrinfo(argv[1], DEFAULT_PORT, &hints, &result);
	//one below works
  // error = getaddrinfo("192.168.1.11", DEFAULT_PORT, &hints, &result);
   error = getaddrinfo(serverIP, DEFAULT_PORT, &hints, &result);
    if ( error != 0 ) {
        printf("getaddrinfo failed with error: %d\n", error);
		OutputDebugString("getaddrinfo failed with error: %d\n");
        WSACleanup();
        return;
    }
}

void NetClient::Initialize(int argc, char* argv[])
{
    if (argc != 2)
        printf("usage: %s server-name\n", argv[0]);

	// Initialize Winsock
    error = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (error != 0) {
        printf("WSAStartup failed with error: %d\n", error);
        return;
    }

	ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    //error = getaddrinfo(argv[1], DEFAULT_PORT, &hints, &result);
	//one below works
  // error = getaddrinfo("192.168.1.11", DEFAULT_PORT, &hints, &result);
   error = getaddrinfo(serverIP, DEFAULT_PORT, &hints, &result);
    if ( error != 0 ) {
        printf("getaddrinfo failed with error: %d\n", error);
		OutputDebugString("getaddrinfo failed with error");
        WSACleanup();
        return;
    }

}

void NetClient::Connect()
{
 // Attempt to connect to an address until one succeeds
    for(ptr=result; ptr != NULL ;ptr=ptr->ai_next) {

        // Create a SOCKET for connecting to server
        m_sClientSock = socket(ptr->ai_family, ptr->ai_socktype, 
            ptr->ai_protocol);
		OutputDebugString("Connected!");
//u_long iMode=1;
//ioctlsocket(m_sClientSock,FIONBIO,&iMode);

        if (m_sClientSock == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
			OutputDebugString("socket failed");
            WSACleanup();
            return;
        }

        // Connect to server.
        //error = connect( m_sClientSock, ptr->ai_addr, (int)ptr->ai_addrlen);
		error = connect( m_sClientSock, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (error == SOCKET_ERROR) {
			OutputDebugString("This didn't work");
            closesocket(m_sClientSock);
            m_sClientSock = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (m_sClientSock == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
		OutputDebugString("Unable to connect to server!");
        WSACleanup();
        return;
    }
}

void NetClient::SetBuffer(void* msg)
{
	sendbuf = msg;
}

void NetClient::SendBuffer()
{
	// Send an initial buffer
    error = send( m_sClientSock, (char*)sendbuf, sizeof(sendbuf), 0 );
    if (error == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(m_sClientSock);
        WSACleanup();
        return;
    }

    printf("Bytes Sent: %ld\n", error);
}

void NetClient::CheckIncoming()
{
	// Receive until the peer closes the connection
    do {
		//ThrdCon->MutexOpen("RecvBuffer");
        error = recv(m_sClientSock, recvbuf, recvbuflen, 0);
  		//ThrdCon->MutexRelease("RecvBuffer");
       if ( error > 0 )
		{
			OutputDebugString("Data Received!");
            printf("Bytes received: %d\n", error);
			printf((char*)recvbuf, error);
		}
        else if ( error == 0 )
            printf("Connection closed\n");
        else
            printf("recv failed with error: %d\n", WSAGetLastError());

   } while( error > 0 );
}

void NetClient::Shutdown()
{
	 // shutdown the connection since no more data will be sent
    error = shutdown(m_sClientSock, SD_SEND);
    if (error == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(m_sClientSock);
        WSACleanup();
        return;
    }
}

void* NetClient::GetReceiveBuff(){
	char* temp;
	//ThrdCon->MutexOpen("RecvBuffer");
	temp = recvbuf;
	//ThrdCon->MutexRelease("RecvBuffer");
	return (void*)temp;
}