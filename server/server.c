#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include "request.h"

struct Server serverConstructor(
	int domain,
	int service,
	int protocol, 
	u_long interface, 
	int port, 
	int backlog 
){
	struct Server server;

	server.domain = domain;
	server.service = service;
	server.protocol = protocol;
	server.interface = interface; 
	server.port = port; 
	server.backlog = backlog; 
	server.address.sin_family = domain;
	server.address.sin_port = htons(port);
	server.address.sin_addr.s_addr = htonl(interface);
	server.socket = socket(domain, service, protocol);
	server.launch = launch;

	if(server.socket < 0)
	{
		perror("Socket err:!");	
		exit(1);
	}

	int bindStatus = bind(server.socket, (struct sockaddr *) &server.address, sizeof(server.address)); 
	
	if(bindStatus < 0)
	{
		perror("Failed to bind socket...\n");
		exit(1);
	}	

	int listenStatus = listen(server.socket, server.backlog);

	if(listenStatus < 0) 
	{
		perror("Failed to start listening!");
		exit(1);
	};

	return server;
}

void launch(struct Server * server) 
{
	char buffer[30000];
 	char *hello = "HTTP/1.1 200 OK\nDate: Mon, 27 Jul 2009 12:28:53 GMT\nServer: Apache/2.2.14(Win32)\nLast-Modified: Wed, 22 Jul 2009 19:15:56 GMT\nContent-type:text/html\nConnection: Closed\n\n<html><body><h1>Hello,World!</h1></body></html>";
	int addressLength = sizeof(server->address);
	int newSocket;
	while(1) {
		newSocket = accept(server->socket, (struct sockaddr *)&server->address, (socklen_t *)&addressLength);
		struct Request request = requestConstructor(newSocket);
		write(newSocket, hello, strlen(hello));
		close(newSocket); 
		close(server->socket);
		exit(0);
	}
}

