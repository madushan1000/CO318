/* Sample TCP server */

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>

#define FILENAME "serverfile.txt"

int main(int argc, char**argv)
{
	int listenfd,connfd,n;
	struct sockaddr_in servaddr,cliaddr;
	socklen_t clilen;
	//char* banner = "Hello TCP client! This is TCP server";
	char buffer[1000];
	
	/* one socket is dedicated to listening */
	listenfd=socket(AF_INET,SOCK_STREAM,0);
	perror("");
	/* initialize a sockaddr_in struct with our own address information for binding the socket */
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(32000);

	/* binding */
	bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	perror("");
	listen(listenfd,0);
	perror("");
	clilen=sizeof(cliaddr);

	/* accept the client with a different socket.  */
	
	connfd = accept(listenfd,(struct sockaddr *)&cliaddr,&clilen); // the uninitialized cliaddr variable is filled in with the
	perror("");
	n = recvfrom(connfd,buffer,1000,0,(struct sockaddr *)&cliaddr,&clilen);// information of the client by recvfrom function
	perror("");
	buffer[n] = 0;
	printf("%s %d", buffer,strncmp(buffer, "request",7));
	if(0==strncmp(buffer, "request",7)){
		FILE *fd;
		int sz=1000,size;
		
		fd = fopen(FILENAME,"r");
		fseek(fd, 0L, SEEK_END);
		size = ftell(fd);
		rewind(fd);
		memset(buffer, 0, sizeof(buffer));
		sprintf(buffer, "%d", size);
		
		sendto(connfd,buffer,strlen(buffer),0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
		
		while(sz==1000){
			
			sz=fread(buffer, 1, 1000, fd);
			sendto(connfd,buffer,strlen(buffer),0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
			//printf("%s",buffer);
			memset(buffer, 0, sizeof(buffer));
		
		}
		
		fclose(fd);
	}
	return 0;
}
