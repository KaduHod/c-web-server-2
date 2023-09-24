#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <server.h>

int main()
{
	int dominio = AF_INET;
	int socketTypeService = SOCK_STREAM;
	int protocolo = 0; // Deixo para o sistema escolher o protocolo com base no dominio e tipo de socket, aparentemente ira ser o protocolo TCP/IP
	u_long ipaddress = INADDR_ANY;// especifica que o sistema irá disponibiizar todos os ips associados a está maquina.
	int port = 9998;
	int tamanhoDeFilaDeConexoes = 10;

	printf("Starting server at http://127.0.0.1:%i\n", port);
	printf("Interface: %lu\n", ipaddress);
	
	struct Server server = serverConstructor(dominio, socketTypeService, protocolo, ipaddress, port, tamanhoDeFilaDeConexoes);
	
	launch(&server);
	
	return 0;
}
