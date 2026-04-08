# Network Programming Basics

A simple TCP client-server project to learn network programming fundamentals.

## Overview

This project demonstrates basic socket programming in C with:
- **TCP Server**: Listens on port 8080, accepts connections, and prints messages from clients
- **TCP Client**: Connects to the server and sends a message

## Building

```bash
make
```

## Running

1. Start the server:
   ```bash
   ./tcp_server
   ```

2. In another terminal, run the client:
   ```bash
   ./tcp_client
   ```

## Key Concepts

- `socket()` - Creates a TCP socket
- `bind()` - Binds server to port 8080
- `listen()` - Enables incoming connections
- `accept()` - Accepts a client connection
- `connect()` - Client connects to server
- `send()`/`recv()` - Data exchange

## Clean up

```bash
make clean
```
