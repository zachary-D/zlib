#pragma once

#ifdef _WIN32

//#include <iostream>

#include <WinSock2.h>
#include <WS2tcpip.h>
//#include <stdlib.h>

#include "zlib/varConv.h"

namespace zlib
{
	namespace network
	{
		//Initialize WsaData & check for errors
		void initWinSock();

		enum sockError
		{
			notOpened,				//The socket was never opened
			open,					//The socket is operating normally
			addressError,
			socketCreationError,
			connectionError,
			bindError,
			listenError,
			acceptFailed,
			sendError,
			receiveError,
			shutdownError,
			badType,				//The socket type specified to the constructor was invalid
			terminated,				//The connection was terminated
			closed,					//The socket was closed
		};

		enum t_sockType
		{
			client,
			server,
		};

		//Virtual class containing the base code to open and operate a socket
		class socketBase
		{
		private:
			unsigned buffer_length = 512;

			bool isUsable;	//True when the socket is able to send data.  False when close() has been called
			sockError state;
			int errorDetails;

		protected:
			SOCKET ConnectSocket = INVALID_SOCKET;

		public:
			socketBase();

			virtual ~socketBase() = 0;

		protected:
			void initializeSocket(string address, unsigned port, t_sockType type);

		protected:
			void error(sockError errorState);

			void error(sockError errorState, int details);

		public:

			bool usable() { return isUsable; }

			unsigned getBufferSize() { return buffer_length; }

			std::pair<sockError, int> getDetails() { return {state, errorDetails}; }

			//Sets the size of the send/receive buffers.  Must be > 0, if not no action will be taken
			void setBufferSize(unsigned length);

			//TODO - make specific versions of this for each child-class?
			//Send data through the socket
			void transmit(std::string data);

			//TODO - make specific versions of this for each child-class?
			//Receive data through the socket
			string receive();

			void close();
		};

		class socketServer : public socketBase
		{
			//Todo: merge ConnectScoket with ClientSocket, or make it so ClientSocket is scalable, and is potentially its own object?
			SOCKET ClientSocket;

		public:
			socketServer();
			socketServer(unsigned localPort);

			void transmit(string data);
			
			string receive();
			void close();

			~socketServer() override  { close(); }
		};

		class socketClient : public socketBase
		{

		public:
			socketClient();
			socketClient(string remoteAddress, unsigned remotePort);

			~socketClient() override { close(); }
		};
	}
}
#endif