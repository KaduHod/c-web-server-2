#include <request.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

struct Request requestConstructor(int clientSocket) {
	char route;
	char httpMethod;
	char body;
	char requestBuffer[30000];
	struct Request request;
	
	int readRequestStatus = getRequestInfo(clientSocket, requestBuffer);

	printf("Request: %s\n", requestBuffer);
/*
	int count = 0;

	char * line = strtok(requestBuffer, "\n");

	struct Request request;

	while(line != NULL) 
	{
		if(count == 0)
		{
			setHttpMethodAndRouteFromBuffer(&request, line);
		}
		line = strtok(NULL, "\n");
		count++;
	}
*/
	return request;
}


void setHttpMethodAndRouteFromBuffer(struct Request * request, char * line)
{
	char metodo[64]; // Tamanho máximo para o método HTTP (ajuste conforme necessário)
    	char rota[256]; // Tamanho máximo para a rota (ajuste conforme necessário)
    	char versao[64]; // Tamanho máximo para a versão HTTP (ajuste conforme necessário)

    // Use sscanf para analisar a linha de solicitação HTTP
    	if (sscanf(line, "%s %s %s", metodo, rota, versao) != 3) {
        // A linha de solicitação não está no formato esperado
        	printf("Erro ao analisar a linha de solicitação HTTP\n");
        	return;
    	}
}

int getRequestInfo(int clientSocket, char* buffer)
{
	memset(buffer, 0, sizeof(buffer));
	int bytesLidos = read(clientSocket, buffer, sizeof(buffer) -1);

	if(bytesLidos < 0)
	{
		perror("Erro lendo o requet: ");
		close(clientSocket);
		return -1;
	}

	if(bytesLidos == 0)
	{
		printf("Cliente fechou a conexão");
		close(clientSocket);
		return -1;
	}

	return 0;
}

