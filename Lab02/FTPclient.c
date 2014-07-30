
/* Sample TCP client */

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char**argv)
{
	int sockfd,n,k=1000;
	struct sockaddr_in servaddr;
	char banner[] = "request";
	char buffer[1000];
	
	if (argc != 2)
	{
		printf("usage:  ./%s <IP address>\n",argv[0]);
		return -1;
	}
	/* socket to connect */
	sockfd=socket(AF_INET,SOCK_STREAM,0);

	/* IP address information of the server to connect to */ 
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr=inet_addr(argv[1]);
	servaddr.sin_port=htons(32000);
	
	connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	
	sendto(sockfd,banner,strlen(banner),0, (struct sockaddr *)&servaddr,sizeof(servaddr));
	
	n=recvfrom(sockfd,buffer,10000,0,NULL,NULL);
	buffer[n]=0;
	
	while(k == 1000){
		k=recvfrom(sockfd,buffer,1000,0,NULL,NULL);
		//printf("%d %d", size, k);
		//printf("%s",buffer);
		memset(buffer, 0, sizeof(buffer));
		//size+=k;
	}
	
	return 0;
}
