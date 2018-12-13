#include <string>
#include <iostream>

#ifdef _WIN32
//Behind another #if to prevent conflicts with windows.h
#ifndef _WINDOWS_
#include <WinSock2.h>
#include <WS2tcpip.h>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")
#endif

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
#include "var.h"

namespace zlib
{
	namespace network
	{
		void startup()
		{
#ifdef _WIN32
			WSADATA wsaData;

			int initResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

			if(initResult != 0)
			{
				throw socketWSAException("Unable to initialize WinSock2");
			}
#endif
		}
		
		void cleanup()
		{
#ifdef _WIN32
			WSACleanup();
#endif
		}

		
		socketBase::socketBase()
		{
			error(notOpened, true);
		}

		socketBase::~socketBase() 
		{
			closeSocket();
		}

		void socketBase::initializeSocket(std::string address,
			unsigned port,
			t_sockType type
#ifdef __linux__
			, int clientLocalPort	//The port the client should connect from (linux, client side only).  If -1, it will default to a random port 25000->30,000
#endif
		)
		{
			if(type != client && type != server) throw badType;

#ifdef __linux__
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
					error(addressError);
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
					error(bindError, true);
					freeaddrinfo(result);
					closesocket(ConnectSocket);
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
			//cout << "outbound:" << data << endl;
			//For once, this is the same on Windows and Linux
			int err = send(ConnectSocket, data.c_str(), data.length() + 1, 0);

			//But of course this isn't
#ifdef _WIN32
			if(err == SOCKET_ERROR)
			{
				error(sendError, true);
				closesocket(ConnectSocket);
				throw sendError;
			}
#elif __linux__
			if(err < 0) error(sendError);
#endif
		}

		string socketBase::receive()
		{
			if (vBuff.size() != 0)
			{
				string ret = vBuff[0];
				vBuff.erase(vBuff.begin());
				//cout << "Inbound:" << ret << endl;
				return ret;
			}
			int err = recv(ConnectSocket, recvbuf, buffer_length, 0);

			if(err == 0) closeSocket();
			else if (err < 0)
			{
#ifdef _WIN32 
				error(receiveError, WSAGetLastError());
#elif __linux__
				error(receiveError);
#endif
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
				//cout << "Inbound:" << ret << endl;
				return ret;
			}
			else return ""; 

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
			if (err == SOCKET_ERROR)
			{
				error(shutdownError, true);
				closesocket(ConnectSocket);
				//throw shutdownError;
				//We just assume that the socket was already shutdown, and leave it at that.
				return;
			}
			//Make sure we can't call closesocket() twice if the 'throw' is somehow missed/blocked/other oddness
			else
			{
				closesocket(ConnectSocket);
			}
#endif
			error(closed);
		}

		string socketBase::getErrorName(sockError e)
		{
			switch(e)
			{
			case notOpened:
				return "notOpened";
			case open:
				return "open";
			case addressError:
				return "addressError";
			case socketCreationError:
				return "socketCreationError";
			case connectionError:
				return "connectionError";
			case bindError:
				return "bindError";
			case listenError:
				return "listenError";
			case acceptFailed:
				return "acceptFailed";
			case sendError:
				return "sendError";
			case receiveError:
				return "receiveError";
			case shutdownError:
				return "shutdownError";
			case badType:
				return "badType";
			case terminated:
				return "terminated"; 
			case closed:
				return "closed";
			default:
				return "sockError \"" + conv::toString(e) + "\" does not have a plaintext equivalent set!";
			}
		}



		socketServer::socketServer()
		{
			error(notOpened, true);
		}

		socketServer::socketServer(OS_socket_base socket)
		{
			ConnectSocket = socket;

#ifdef _WIN32
			if (ConnectSocket == INVALID_SOCKET) throw socketServerException("Socket passed is invalid!");
#elif __linux__
			if (ConnectSocket < 0) throw socketServerException("Socket passes is invalid!");
#endif
		}

		/*void socketServer::transmit(string data)
		{
			//cout << "outbound:" << data << endl;
			int errSend = send(ClientSocket, data.c_str(), data.length() + 1, 0);

#ifdef _WIN32
			if(errSend == SOCKET_ERROR)
			{
				error(sendError, WSAGetLastError());
				closesocket(ClientSocket);
				return;
			}
#elif __linux__
			if(errSend < 0) error(sendError);
#endif
		}

		//Todo: work on SocketServer so it doesn't create another socket, and can use socketBase::receive()
		string socketServer::receive()
		{	
			if (vBuff.size() != 0)
			{
				string ret = vBuff[0];
				vBuff.erase(vBuff.begin());
				//cout << "inbound:" << ret << endl;
				return ret;
			}

			int err = recv(ClientSocket, recvbuf, getBufferSize(), 0);
			
			if(err == 0)
			{
#ifdef _WIN32
				int errCode = WSAGetLastError();
				closeSocket();
				error(terminated, errCode);	//Override the 'closed' error set in close()
#elif __linux__
				error(terminated);
#endif
			}
			else if(err < 0)
			{
#ifdef __linux__
				error(receiveError);
#elif _WIN32
				error(receiveError, WSAGetLastError(), true);
				closesocket(ClientSocket);
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
				//cout << "Inbound:" << ret << endl;
				return ret;
			}
			else return "";
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
				return;
			}

			closesocket(ClientSocket);
#endif
			error(closed);
		}*/


		socketDoorbell::socketDoorbell()
		{
			error(notOpened, true);
		}

		socketDoorbell::socketDoorbell(unsigned localPort)
		{
			initializeSocket("", localPort, server);
			if (!usable()) throw (socketException("unknown creation exception"));
		}

		socketServer socketDoorbell::getNextConnection()
		{
			OS_socket_base newSock;

			//Start listening
#ifdef _WIN32
			if (listen(ConnectSocket, SOMAXCONN) == SOCKET_ERROR)
			{
				error(listenError, WSAGetLastError(), true);
				closesocket(ConnectSocket);
				throw socketDoorbellException("Listen failed!");
			}

			newSock = INVALID_SOCKET;

			newSock = accept(ConnectSocket, NULL, NULL);
			if (newSock == INVALID_SOCKET)
			{
				//TODO: More checking - see if the socket is still usable or not after an accept failure
				throw socketDoorbellException("New connection accept failed");
			}
#elif __linux__
			listen(ConnectSocket, 0);

			newSock = accept(ConnectSocket, (struct sockaddr *) NULL, NULL);

			if (newSock < 0) throw socketDoorbellException("New connection accept failed");
#endif
			return socketServer(newSock);
		}


		socketClient::socketClient()
		{
			error(notOpened, true);
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