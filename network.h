#pragma once

#ifdef _WIN32

#include <iostream>

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdlib.h>

#include "zlib/varConv.h"

namespace zlib
{
	namespace network
	{
		const unsigned buffer_length = 512;

		WSADATA wsaData;

		SOCKET ConnectSocket = INVALID_SOCKET;


		//Initialize WsaData & check for errors
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

		enum sockError
		{
			open,
			addressError,
			socketCreationError,
			connectionError,
			bindError,
			sendError,
			receiveError,
			closed,
			shutdownError,
			badType,			//The socket type specified to the constructor was invalid
		};

		enum t_sockType
		{
			client,
			server,
		};

		class zSocket
		{
		private:
			bool isUsable;	//True when the socket is able to send data.  False when close() has been called
			
			unsigned buffer_size = 512;

			sockError state;
			int errorDetails;

			t_sockType sockType;
			

		public:

			zSocket()
			{
				error(closed);
			}

		private:
			zSocket(std::string address, unsigned port, t_sockType type)
			{
				if(type != client && type != server) throw badType;

				sockType = type;

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

		public:
			static zSocket createClient(string address, unsigned remotePort)
			{
				return zSocket(address, remotePort, client);
			}

			static zSocket createServer(unsigned localPort)
			{
				return zSocket(NULL, localPort, server);
			}

		private:
			void error(sockError errorState)
			{
				state = errorState;
				isUsable = false;
			}

			void error(sockError errorState, int details)
			{
				state = errorState;
				isUsable = false;
				errorDetails = details;
			}

		public:

			bool usable()
			{
				return isUsable;
			}

			std::pair<sockError, int> getDetails()
			{
				return {state, errorDetails};
			}

			//Sets the size of the send/receive buffers.  Must be > 0, if not no action will be taken
			void setBufferSize(unsigned length)
			{
				if(length <= 0) return;
				buffer_size = length;
			}

			//Send data through the socket
			void transmit(std::string data)
			{
				const char * dat = data.c_str();

				int err = send(ConnectSocket, dat, (int)strlen(dat), 0);

				if(err == SOCKET_ERROR)
				{
					error(sendError);
					closesocket(ConnectSocket);
					WSACleanup();
					return;
				}
			}

			//Receive data through the socket
			string receive()
			{
				char * buffer = new char[buffer_length];

				int err = recv(ConnectSocket, buffer, buffer_length, 0);

				if(err == 0) close();
				else error(receiveError, WSAGetLastError());

				return string(buffer);
			}

			void close()
			{
				if(!isUsable) return;
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

			~zSocket()
			{
				close();
			}
		};



		//Send data
		//Prereq: you must be connected to a server (use comnect() )
		void sendData(std::string data)
		{
			


		}
	}
}
#endif