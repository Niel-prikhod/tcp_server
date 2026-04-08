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
#define BUFFER_SIZE 15

static int print_from_client(int socket_fd) {
	char	buf[BUFFER_SIZE];
	int		read_num;

	read_num = 0;
	while(1) {
		read_num = recv(socket_fd, buf, BUFFER_SIZE, 0);
		if (read_num == -1) {
			close(socket_fd);
			perror("recv");
		}
		else if (read_num > 0)
			write(STDOUT_FILENO, buf, read_num);
	}
	return 0;
}


int main(void) {
	int					tcp_socket, peer_socket;
	struct sockaddr_in	my_addr, peer_addr;
	socklen_t			peer_addr_len;
	char				buf[BUFFER_SIZE];

	tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (tcp_socket < 0)
		err(EXIT_FAILURE, "socket");
	memset(&my_addr, 0, sizeof(my_addr));
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(8080);
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(tcp_socket, (struct sockaddr *)&my_addr, sizeof(my_addr)) == -1) {
		close(tcp_socket);
		err(EXIT_FAILURE, "bind");
	}
	puts("binded; listening...");
	if (listen(tcp_socket, LISTEN_BACKLOG) == -1) {
		close(tcp_socket);
		err(EXIT_FAILURE, "listen");
	}
	peer_addr_len = sizeof(peer_addr);
	peer_socket = accept(tcp_socket, (struct sockaddr *)&peer_addr, &peer_addr_len);
	if (peer_socket == -1) {
		close(tcp_socket);
		err(EXIT_FAILURE, "accept");
	}
	else 
	{
		inet_ntop(AF_INET, &peer_addr.sin_addr, buf, BUFFER_SIZE);
		printf("Connected with client on address %s, using port %d\n", \
			buf, ntohs(peer_addr.sin_port));
	}
	print_from_client(peer_socket);
	
	if (close(tcp_socket) == -1)
		err(EXIT_FAILURE, "close");

	return 0;
}
