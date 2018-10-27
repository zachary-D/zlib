#include <string>
#include <iostream>

#ifdef _WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#elif __linux__
#include<stdlib.h>
#include<time.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<strings.h>
#include<unistd.h>
#include<netinet/in.h>
#else
#error "Platform not supported!"
#endif

#include "network.h"
#include "varConv.h"

namespace zlib
{
	namespace network
	{
#ifdef _WIN32
		WSADATA wsaData;

		void initWinSock()
		{
			static bool isInitialized;

			//if(isInitialized != true)
			{
				int initResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

				if(initResult != 0)
				{
					throw "Unable to initialize WinSock2";
				}
				isInitialized = true;
			}
		}
#endif
		
		socketBase::socketBase()
		{
			error(notOpened);
		}

		socketBase::~socketBase() 
		{
			closeSocket();
		}

		void socketBase::pBuff()
		{/*
			for (unsigned i = 0; i < getBufferSize(); i++)
			{
				std::cout << '<' << i << '>';
				if (recvbuf[i] == '\000') cout << "\\000";
				else cout << recvbuf[i];
			}
			std::cout << endl;
			for (unsigned i = 0; i < vBuff.size(); i++)
			{
				cout << i << '>' << vBuff[i] << endl;
			}*/
		}

		void socketBase::initializeSocket(
			std::string address,
			unsigned port,
			t_sockType type
#ifdef __linux__
			, int clientLocalPort	//The port the client should connect from (linux, client side only).  If -1, it will default to a random port 25000->30,000
#endif
		)
		{
			if(type != client && type != server) throw badType;

#ifdef _WIN32
			initWinSock();
#elif __linux__
			//If this is -1, we need to assign it a random port (within 25000 and 30000)
			if(clientLocalPort == -1)
			{
				srand(time(NULL));
				clientLocalPort = rand() % 5000 + 25001;
			}
#endif

			//Swap "localhost" for the actual loopback IP we want to connect to that
			//Add auto-lowercase for localhost back again later
			if(address == "localhost") address = "127.0.0.1";
			//if(conv::toLowercase(address, false) == "localhost") address = "127.0.0.1";

#ifdef _WIN32
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
					error(addressError, false);
					WSACleanup();
					throw addressError;
				}
			}

			//Create our socket to connect
			{
				ptr = result;

				ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

				if(ConnectSocket == INVALID_SOCKET)
				{
					error(socketCreationError, false);
					freeaddrinfo(result);
					WSACleanup();
					throw socketCreationError;
				}
			}
#elif __linux__
			//Create the socket
			{
				ConnectSocket = socket(PF_INET, SOCK_STREAM, 0);

				if(ConnectSocket < 0) error(socketCreationError);
			}
#endif

			//Connect to a server
			if(type == client)
			{
#ifdef _WIN32
				int err = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);

				if(err == SOCKET_ERROR)
				{
					closesocket(ConnectSocket);
					ConnectSocket = INVALID_SOCKET;
				}

				freeaddrinfo(result);

				if(ConnectSocket == INVALID_SOCKET)
				{
					error(connectionError, false);
					closesocket(ConnectSocket);
					WSACleanup();
					throw connectionError;
				}
#elif __linux__
				struct sockaddr_in serv_addr;

				//Get server address and port
				{
					struct hostent * target;

					target = gethostbyname(address.c_str());

					if(target == NULL) error(addressError);

					bzero((char*)& serv_addr, sizeof(serv_addr));
					serv_addr.sin_family = AF_INET;
					bcopy(
						target->h_addr,
						(char*)& serv_addr.sin_addr.s_addr,
						target->h_length
					);
					serv_addr.sin_port = htons(port);
				}

				if(connect(ConnectSocket, (struct sockaddr*) & serv_addr, sizeof(serv_addr)) < 0)
				{
					error(connectionError);
					throw connectionError;
				}
#endif
			}
			else if(type == server)
			{
#ifdef _WIN32
				int err = bind(ConnectSocket, result->ai_addr, (int)result->ai_addrlen);

				if(err == SOCKET_ERROR)
				{
					error(bindError);
					freeaddrinfo(result);
					closesocket(ConnectSocket);
					WSACleanup();
					throw bindError;
				}

				freeaddrinfo(result);

#elif __linux__
				ConnectSocket = socket(AF_INET, SOCK_STREAM, 0);

				struct sockaddr_in servaddr;

				servaddr.sin_family = AF_INET;
				servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
				servaddr.sin_port = htons(port);

				bind(ConnectSocket, (struct sockaddr *) & servaddr, sizeof(servaddr));
#endif
			}
			isUsable = true;
		}

		void socketBase::error(sockError errorState, bool noExcept)
		{
			state = errorState;
			isUsable = false;
#ifdef __linux__ //On linux we only close the connect	ion in this one way/place
			close(ConnectSocket);
#endif
			if (!noExcept && errorState != closed && errorState != notOpened && errorState != open) throw errorState;
		}

		void socketBase::error(sockError errorState, int details, bool noExcept)
		{
			state = errorState;
			isUsable = false;
			errorDetails = details;
#ifdef __linux__ //On linux we only close the connection in this one way/place
			close(ConnectSocket);
#endif
			if (!noExcept && errorState != closed && errorState != notOpened && errorState != open) throw errorState;
		}

		void socketBase::setBufferSize(unsigned length)
		{
			if(length <= 0) return;
			buffer_length = length;
		}

		void socketBase::transmit(std::string data)
		{
			cout << "outbound:" << data << endl;
			//For once, this is the same on Windows and Linux
			int err = send(ConnectSocket, data.c_str(), data.length() + 1, 0);

			//But of course this isn't
#ifdef _WIN32
			if(err == SOCKET_ERROR)
			{
				error(sendError);
				closesocket(ConnectSocket);
				WSACleanup();
				return;
			}
#elif __linux__
			if(err < 0) error(sendError);
#endif
		}

		string socketBase::receive()
		{
			cout << "preBuff:";
			pBuff();
			if (vBuff.size() != 0)
			{
				string ret = vBuff[0];
				vBuff.erase(vBuff.begin());
				return ret;
			}
			int err = recv(ConnectSocket, recvbuf, buffer_length, 0);

			cout << "postBuff:";
			pBuff();

			if(err == 0) closeSocket();
			else if (err < 0)
			{
#ifdef _WIN32 
				error(receiveError, WSAGetLastError());
#elif __linux__
				error(receiveError);
#endif
				throw receiveError;
			}
			string msg = "";
			for (unsigned i = 0; i < getBufferSize(); i++)
			{
				//If we hit a terminator push the message to the string-buffer
				if (recvbuf[i] == '\000')
				{
					if (msg != "")//As long as it's not empty
					{
						vBuff.push_back(msg);
						msg = "";
					}
				}
				//Otherwise if it's any other character add it to the current message we're extracting
				else msg += recvbuf[i];

			}

			clearCharBuffer();

			if (vBuff.size() != 0)
			{
				string ret = vBuff[0];
				vBuff.erase(vBuff.begin());
				return ret;
			}
			else throw "No data received?";

		}

		void socketBase::clearCharBuffer()
		{
			for (unsigned i = 0; i < getBufferSize(); i++)
			{
				recvbuf[i] = '\000';
			}
		}

		void socketBase::closeSocket()
		{
			if(!usable()) return;
			int err = shutdown(ConnectSocket, 
#ifdef _WIN32
				SD_SEND
#elif __linux__
				SHUT_RDWR
#endif	
			);

#ifdef _WIN32
			if(err == SOCKET_ERROR)
			{
				error(shutdownError);
				closesocket(ConnectSocket);
				WSACleanup();
			}

			closesocket(ConnectSocket);
			WSACleanup();
#endif
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

			//Start listening
#ifdef _WIN32
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
#elif __linux__
			listen(ConnectSocket, 0);

			ClientSocket = accept(ConnectSocket, (struct sockaddr *) NULL, NULL);

			if(ClientSocket < 0) error(acceptFailed);
#endif
		}

		void socketServer::transmit(string data)
		{
			cout << "outbound:" << data << endl;
			int errSend = send(ClientSocket, data.c_str(), data.length() + 1, 0);

#ifdef _WIN32
			if(errSend == SOCKET_ERROR)
			{
				error(sendError, WSAGetLastError());
				closesocket(ClientSocket);
				WSACleanup();
				return;
			}
#elif __linux__
			if(errSend < 0) error(sendError);
#endif
		}

		//Todo: work on SocketServer so it doesn't create another socket, and can use socketBase::receive()
		string socketServer::receive()
		{
			cout << "preBuff:";
			pBuff();
			if (vBuff.size() != 0)
			{
				string ret = vBuff[0];
				vBuff.erase(vBuff.begin());
				return ret;
			}

			int err = recv(ClientSocket, recvbuf, getBufferSize(), 0);

			cout << "postBuff:";
			pBuff();

			if(err == 0)
			{
#ifdef _WIN32
				int errCode = WSAGetLastError();
				closeSocket();
				error(terminated, errCode);	//Override the 'closed' error set in close()
#elif __linux__
				error(terminated);
#endif
				return "";
			}
			else if(err < 0)
			{
#ifdef __linux__
				error(receiveError);
#elif _WIN32
				error(receiveError, WSAGetLastError());
				closesocket(ClientSocket);
				WSACleanup();
#endif
				throw receiveError;
			}

			string msg = "";
			for (unsigned i = 0; i < getBufferSize(); i++)
			{
				//If we hit a terminator push the message to the string-buffer
				if (recvbuf[i] == '\000')
				{
					if (msg != "")//As long as it's not empty
					{
						vBuff.push_back(msg);
						msg = "";
					}
				}
				//Otherwise if it's any other character add it to the current message we're extracting
				else msg += recvbuf[i];

			}

			clearCharBuffer();

			if (vBuff.size() != 0)
			{
				string ret = vBuff[0];
				vBuff.erase(vBuff.begin());
				return ret;
			}
			else throw "No data received?";
		}

		void socketServer::closeSocket()
		{
			if(!usable()) return;

			int err = shutdown(ClientSocket,
#ifdef _WIN32
				SD_SEND
#elif __linux__
				SHUT_RDWR
#endif	
			);

#ifdef _WIN32
			if(err == SOCKET_ERROR)
			{
				error(shutdownError, WSAGetLastError());
				closesocket(ClientSocket);
				WSACleanup();
				return;
			}

			closesocket(ClientSocket);
			WSACleanup();
#endif
			error(closed);
		}


		socketClient::socketClient()
		{
			error(notOpened);
		}

		socketClient::socketClient(string remoteAddress, unsigned remotePort
#ifdef  __linux__
		, int localPort
#endif
		)
		{
			initializeSocket(remoteAddress, remotePort, client
#ifdef __linux__
			, localPort
#endif
			);
		}
	}
}