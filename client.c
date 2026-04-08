#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <err.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>

#define CLIENT_ADDRESS "127.0.0.1"
#define BUFFER_SIZE 15

int main(void) {
	int ret_connect, clientfd;
	struct sockaddr_in	client_addr;
	socklen_t	client_addr_len;
	char buf[BUFFER_SIZE];

	clientfd = socket(AF_INET, SOCK_STREAM, 0);
	if (clientfd == -1)
		err(EXIT_FAILURE, "socket");
	client_addr_len = sizeof(client_addr);
	memset(&client_addr, 0, client_addr_len);
	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(8080);
	if (inet_pton(AF_INET, CLIENT_ADDRESS, &client_addr.sin_addr) == -1)
		err(EXIT_FAILURE, "inet_pton");
	ret_connect = connect(clientfd, (struct sockaddr *)&client_addr, client_addr_len);
	if (ret_connect == -1)
		err(EXIT_FAILURE, "connect");
	puts("connected!");
	inet_ntop(AF_INET, &client_addr.sin_addr, buf, BUFFER_SIZE);
	dprintf(clientfd, "first message from client\nAddres: %s\n", buf);
	return 0;
}
