#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <server.h>

int main()
{
	int domain = AF_INET;
	int socketTypeService = SOCK_STREAM;
	int protocol = 0; // Deixo para o sistema escolher o protocol com base no domain e tipo de socket, aparentemente ira ser o protocol TCP/IP
	u_long ipaddress = INADDR_ANY;// especifica que o sistema irá disponibiizar todos os ips associados a está maquina.
	int port = 9999;
	int conectionsQueueMaxSize = 10;

	printf("Starting server at http://127.0.0.1:%i\n", port);
	
	struct Server server = serverConstructor(domain, socketTypeService, protocol, ipaddress, port, conectionsQueueMaxSize);
	
	launch(&server);
	
	return 0;
}
