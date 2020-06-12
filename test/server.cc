#include <cstring>

#include <iostream>
#include <string>
using namespace std;

#include "net/socket.h"
#include "net/reactor.h"
#include "net/epoll.h"
#include "net/acceptor.h"
#include "net/handler.h"
#include "time/time_value.h"
#include "net/protocol_types.h"
#include "net/socket_address.h"

#include <signal.h>


using namespace Water;

class ServerHandler : public Handler {
public:
	ServerHandler(int fd, Reactor* reactor) :
		Handler(fd, reactor) {
	}

	int HandleOpen() {
		printf("Server::HandleOpen(%d)...\n", fd());
        socket_.SetSocket(fd());
        reactor()->RegisterHandler(this, kEventInput);
		TimeValue delay(5, 0);
		TimeValue rpeat(5, 0);
		reactor()->ScheduleTimer(this, delay, rpeat);
		return 0;
	}

	int HandleInput(int fd) {
		printf("Server::HandleInput(%d)...\n", fd);
		char buf[kBufferSize];
        int result = socket_.Recv(buf, kBufferSize);
        if (result == 0)
        {
            return -1;
        }
        buf[result] = 0;
		printf("%s", buf);
		return 0;
	}

	int HandleOutput(int fd) {
		printf("Server::HandleOutput(%d)...\n", fd);
		return 0;
	}

	int HandleTimeout() {
		// printf("Server::HandleTimeout()...\n");
		TimeValue now = TimeValue::Now();
		char buf[kBufferSize];
		size_t send_size = snprintf(buf, 
				kBufferSize, 
				"%s:%ld\r\n", 
				static_cast<DateTime>(now).TimeFormatString("%Y/%m/%d %H:%M:%S").c_str(),
                now.GetMicrosecond());
		socket_.Send(buf, send_size);
		return 0;
	}

	int HandleClose() {
		reactor()->RemoveHandler(this);
		delete this;
		printf("Server::HandleClose(%d)...\n", fd());
		return 0;
	}

private:
    Socket<IPV4_TCP> socket_;
};

int main() {
    signal(SIGPIPE, SIG_IGN);

	Reactor reactor(new EPoll());
	Acceptor<IPV4_TCP, ServerHandler> acceptor(&reactor);
	if (acceptor.Accept(1111) != -1) {
		reactor.StartEventLoop();
	}
	return 0;
}

