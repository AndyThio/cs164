#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
 
int main(int argc, char* argv[])
{
	
	int sockfd = 0,n = 0;
	char recvBuff[1024];
	char sendBuff[1024];
	struct sockaddr_in serv_addr;

	memset(recvBuff, '0' ,sizeof(recvBuff));
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0)
	{
		printf("\n Error : Could not create socket \n");
		return 1;
	}
	printf("Please Enter Message: ");
	fgets(sendBuff, 1023, stdin);
 	printf("Before gethost");

	struct hostent *hen;
hen = gethostbyname("server.andy.cs164");
	
	if(hen == NULL){
		fprintf(stdout, "host not found");
		}
	
	printf("After gethost");

	bcopy((char *)hen->h_addr, (char *)&serv_addr.sin_addr.s_addr, hen->h_length);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(5000);


	if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
	{
		printf("\n Error : Connect Failed \n");
		return 1;
	}
	if(write(sockfd, sendBuff,1023) < 0 ){
		perror("Error in sending message");
	}

	while((n = read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0)
	{
		recvBuff[n] = 0;
		if(fputs(recvBuff, stdout) == EOF)
		{
			printf("\n Error : Fputs error");
		}
		printf("\n");
	}

	if( n < 0)
	{
		printf("\n Read Error \n");
	}


	return 0;
}
