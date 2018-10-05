#ifdef _WIN32

#include <string>

#include <WinSock2.h>
#include <WS2tcpip.h>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#include "network.h"

namespace zlib
{
	namespace network
	{
		WSADATA wsaData;

		void initWinSock()
		{
			static bool isInitialized;

			if(isInitialized != true)
			{
				int initResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

				if(initResult != 0)
				{
					throw "Unable to initialize WinSock2";
				}
				isInitialized = true;
			}
		}
		
		socketBase::socketBase()
		{
			error(notOpened);
		}

		socketBase::~socketBase() 
		{
			close();
		}

		void socketBase::initializeSocket(std::string address, unsigned port, t_sockType type)
		{
			if(type != client && type != server) throw badType;

			initWinSock();

			//Swap "localhost" for the actual loopback IP we want to connect to that
			//Add auto-lowercase conversion here later (so LOCALHOST and LocalHost work, etc.)
			if(address == "localhost") address = "127.0.0.1";

			//Create 3 addrinfo structs, just rolled into one 'line'
			struct addrinfo * result = NULL,
				*ptr = NULL,
				hints;

			ZeroMemory(&hints, sizeof(hints));

			if(type == client)
			{
				hints.ai_family = AF_UNSPEC;
			}
			else if(type == server)
			{
				hints.ai_family = AF_INET;
				hints.ai_flags = AI_PASSIVE;
			}

			hints.ai_socktype = SOCK_STREAM;	//Socket type = stream
			hints.ai_protocol = IPPROTO_TCP;	//Protocol = TCP

												//Get server address and port
			{
				int fnResult;

				if(type == client) fnResult = getaddrinfo(address.c_str(), conv::toString(port).c_str(), &hints, &result);
				else if(type == server) fnResult = getaddrinfo(NULL, conv::toString(port).c_str(), &hints, &result);
				else throw badType;

				if(fnResult != 0)
				{
					error(addressError);
					WSACleanup();
					return;
				}
			}

			//Create our socket to connect
			{
				ptr = result;

				ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

				if(ConnectSocket == INVALID_SOCKET)
				{
					error(socketCreationError);
					freeaddrinfo(result);
					WSACleanup();
					return;
				}
			}


			//Connect to a server
			if(type == client)
			{
				int err = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);

				if(err == SOCKET_ERROR)
				{
					closesocket(ConnectSocket);
					ConnectSocket = INVALID_SOCKET;
				}

				freeaddrinfo(result);

				if(ConnectSocket == INVALID_SOCKET)
				{
					error(connectionError);
					closesocket(ConnectSocket);
					WSACleanup();
					return;
				}

			}
			else if(type == server)
			{
				int err = bind(ConnectSocket, result->ai_addr, (int)result->ai_addrlen);

				if(err == SOCKET_ERROR)
				{
					error(bindError);
					freeaddrinfo(result);
					closesocket(ConnectSocket);
					WSACleanup();
					return;
				}

				freeaddrinfo(result);
			}
			isUsable = true;
		}

		void socketBase::error(sockError errorState)
		{
			state = errorState;
			isUsable = false;
		}

		void socketBase::error(sockError errorState, int details)
		{
			state = errorState;
			isUsable = false;
			errorDetails = details;
		}

		void socketBase::setBufferSize(unsigned length)
		{
			if(length <= 0) return;
			buffer_length = length;
		}

		void socketBase::transmit(std::string data)
		{
			int err = send(ConnectSocket, data.c_str(), data.length() + 1, 0);

			if(err == SOCKET_ERROR)
			{
				error(sendError);
				closesocket(ConnectSocket);
				WSACleanup();
				return;
			}
		}

		string socketBase::receive()
		{
			char * buffer = new char[getBufferSize()];

			int err = recv(ConnectSocket, buffer, buffer_length, 0);

			if(err == 0) close();
			else error(receiveError, WSAGetLastError());

			return string(buffer);
		}

		void socketBase::close()
		{
			if(!usable()) return;
			int err = shutdown(ConnectSocket, SD_SEND);

			if(err == SOCKET_ERROR)
			{
				error(shutdownError);
				closesocket(ConnectSocket);
				WSACleanup();
			}

			closesocket(ConnectSocket);
			WSACleanup();
			error(closed);
		}



		socketServer::socketServer()
		{
			error(notOpened);
		}

		socketServer::socketServer(unsigned localPort)
		{
			initializeSocket("", localPort, server);
			if(!usable()) return;

			//Start listneing
			if(listen(ConnectSocket, SOMAXCONN) == SOCKET_ERROR)
			{
				error(listenError, WSAGetLastError());
				closesocket(ConnectSocket);
				WSACleanup();
				return;
			}

			ClientSocket = INVALID_SOCKET;

			ClientSocket = accept(ConnectSocket, NULL, NULL);
			if(ClientSocket == INVALID_SOCKET)
			{

				error(acceptFailed, WSAGetLastError());
				closesocket(ConnectSocket);
				WSACleanup();
				return;
			}
		}

		void socketServer::transmit(string data)
		{
			int errSend = send(ClientSocket, data.c_str(), data.length() + 1, 0);

			if(errSend == SOCKET_ERROR)
			{
				error(sendError, WSAGetLastError());
				closesocket(ClientSocket);
				WSACleanup();
				return;
			}
		}

		//Todo: work on SocketServer so it doesn't create another socket, and can use socketBase::receive()
		string socketServer::receive()
		{
			char * recvbuf = new char[getBufferSize()];
			int err = recv(ClientSocket, recvbuf, getBufferSize(), 0);

			if(err == 0)
			{
				int errCode = WSAGetLastError();
				close();
				error(terminated, errCode);	//Override the 'closed' error set in close()
				return "";
			}
			else if(err < 0)
			{
				error(receiveError, WSAGetLastError());
				closesocket(ClientSocket);
				WSACleanup();
				return "";
			}

			return string(recvbuf);
		}

		void socketServer::close()
		{
			if(!usable()) return;

			int err = shutdown(ClientSocket, SD_SEND);
			if(err == SOCKET_ERROR)
			{
				error(shutdownError, WSAGetLastError());
				closesocket(ClientSocket);
				WSACleanup();
				return;
			}

			closesocket(ClientSocket);
			WSACleanup();

			error(closed);
		}


		socketClient::socketClient()
		{
			error(notOpened);
		}

		socketClient::socketClient(string remoteAddress, unsigned remotePort)
		{
			initializeSocket(remoteAddress, remotePort, client);
		}
	}
}

#endif