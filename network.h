#pragma once

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
			int initResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

			if(initResult != 0)
			{
				std::cout << "An error was encountered!  Code: " << initResult << std::endl;
				std::cin.get();	//pause
				exit(1);
			}
		}

		struct socket_out
		{
		private:
			bool isUsable;	//True when the socket is able to send data.  False when close() has been called

			enum sockError
			{
				open,
				addressError,
				socketCreationError,
				connectionError,
				sendError,
				closed,
				shutdownError,
			} state;

		public:

			socket_out()
			{
				error(closed);
			}

			socket_out(std::string address, unsigned port)
			{
				//Create 3 addrinfo structs, just rolled into one 'line'
				struct addrinfo * result = NULL,
					*ptr = NULL,
					hints;

				ZeroMemory(&hints, sizeof(hints));

				hints.ai_family = AF_UNSPEC;		//Internet address family = unspecified ("What?")
				hints.ai_socktype = SOCK_STREAM;	//Socket type = stream
				hints.ai_protocol = IPPROTO_TCP;	//Protocol = TCP

													//Get server address and port
				{
					int fnResult = getaddrinfo(address.c_str(), conv::toString(port).c_str(), &hints, &result);

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
				isUsable = true;
			}

		private:
			void error(sockError errorState)
			{
				state = errorState;
				isUsable = false;
			}

			void error(sockError errorState, int details)
			{

			}

		public:

			void transmit(std::string data)
			{
				int err = send(ConnectSocket, data.c_str(), (int)strlen(data.c_str()), 0);

				if(err == SOCKET_ERROR)
				{
					error(sendError);
					closesocket(ConnectSocket);
					WSACleanup();
					return;
				}
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
					std::cin.get();	//pause
					exit(1);
				}
			}

			~socket_out()
			{
				close();
			}
		};

		struct socket_in
		{

		};



		//Send data
		//Prereq: you must be connected to a server (use comnect() )
		void sendData(std::string data)
		{
			


		}
	}
}