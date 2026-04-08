CLIENT_NAME = tcp_client
SERVER_NAME = tcp_server

CLIENT_SRC = client.c
SERVER_SRC = server.c

CFLAGS = -Wall -Wextra -Werror

all: compile_server compile_client

compile_server: 
	$(CC) $(CFLAGS) $(SERVER_SRC) -o $(SERVER_NAME)

compile_client: 
	$(CC) $(CFLAGS) $(CLIENT_SRC) -o $(CLIENT_NAME)

clean:
	rm $(CLIENT_NAME) $(SERVER_NAME) || true

re: clean all

.PHONY: compile_server compile_client clean

