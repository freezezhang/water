#include <cstring>

#include <iostream>
#include <string>
using namespace std;

#include "net/socket.h"
#include "net/reactor.h"
#include "net/epoll.h"
#include "net/connector.h"
#include "net/handler.h"
#include "time/time_value.h"
#include "net/protocol_types.h"
#include "net/socket_address.h"
#include <signal.h>

using namespace Water;

class ClientHandler : public Handler {
public:
	ClientHandler(int fd, Reactor* reactor) :
		Handler(fd, reactor) {
	}

	int HandleOpen() {
		printf("Client::HandleOpen(%d)...\n", fd());
		socket_.SetSocket(fd());

		reactor()->RegisterHandler(this, kEventInput);
		return 0;
	}

	int HandleInput(int fd) {
		// printf("Client::HandleInput(%d)...\n", fd);
		char buf[kBufferSize];
		int recv_size = socket_.Recv(buf, kBufferSize);
		if (recv_size == 0)
		{
			return -1;
		}
		printf("%s", buf);
		return 0;
	}

	int HandleOutput(int fd) {
		printf("Client:HandleOutput(%d)...\n", fd);
		return 0;
	}

	int HandleTimeout() {
		printf("Client:HandleTimeout()...\n");
		return 0;
	}

	int HandleClose() {
		printf("Server::HandleClose(%d)...\n", fd());
		reactor()->RemoveHandler(this);
		delete this;
        exit(0);
		return 0;
	}
private:
    Socket<IPV4_TCP> socket_;
};

int main() {
    signal(SIGPIPE, SIG_IGN);

	Reactor reactor(new EPoll());
	Connector<IPV4_TCP, ClientHandler> connector(&reactor);
	if (connector.Connect("0.0.0.0", 1111) != -1) {
		reactor.StartEventLoop();
	}
	return 0;
}

