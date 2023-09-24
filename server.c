#include "server.h"
#include <stdio.h>
#include <stdlib.h>

struct Server serverConstructor(
	int domain,
	int service,
	int protocol, 
	u_long interface, 
	int port, 
	int backlog, 
	void(*launch)(struct Server *server)
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
	
	printf("cod server.socket: %i\n", server.socket);

	if(server.socket < 0)
	{
		perror("Socket err:!");	
		exit(1);
	}

	int bindStatus = bind(server.socket, (struct sockaddr *) &server.address, sizeof(server.address)); 
	printf("cod bind status: %i\n", bindStatus);
	
	if(bindStatus < 0)
	{
		perror("Failed to bind socket...\n");
		exit(1);
	}	

	int listenStatus = listen(server.socket, server.backlog);
	printf("cod listen status: %i\n", listenStatus);

	if(listenStatus < 0) 
	{
		perror("Failed to start listening!");
		exit(1);
	};

	return server;
}
