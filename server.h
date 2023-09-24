#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <netinet/in.h>

struct Server 
{
	int domain;
	int service;
	int port;
	u_long interface;
	int protocol;
	int backlog;
	struct sockaddr_in address;
	int socket;
	void (*launch)(struct Server *server);
};

struct Server serverConstructor(
	int domain,
	int service,
	int protocol, 
	u_long interface, 
	int port, 
	int backlog, 
	void (*launch)(struct Server *server)
);
#endif
