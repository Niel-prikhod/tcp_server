#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
// #include <netinet/in.h>
#include <netinet/tcp.h>
#include <err.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define LISTEN_BACKLOG 50

int main(void) {
	int tcp_socket, peer_socket;
	struct sockaddr_in my_addr, peer_addr;
	socklen_t	peer_addr_len;

	tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (tcp_socket < 0)
		err(EXIT_FAILURE, "socket: ");
	memset(&my_addr, 0, sizeof(my_addr));
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(8080);
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(tcp_socket, (struct sockaddr *)&my_addr, sizeof(my_addr)) == -1)
		err(EXIT_FAILURE, "bind: ");
	puts("binded; listening...");
	if (listen(tcp_socket, LISTEN_BACKLOG) == -1)
		err(EXIT_FAILURE, "listen: ");
	peer_addr_len = sizeof(peer_addr);
	peer_socket = accept(tcp_socket, (struct sockaddr *)&peer_addr, &peer_addr_len);
	if (peer_socket == -1)
		err(EXIT_FAILURE, "accept: ");
	else 
		printf("Connected with client on address %d, using port %d\n", \
			ntohl(peer_addr.sin_addr.s_addr), ntohs(peer_addr.sin_port));
	if (close(tcp_socket) == -1)
		err(EXIT_FAILURE, "close: ");
	while(1)
	{
	}
	return 0;
}
