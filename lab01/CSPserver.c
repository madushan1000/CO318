#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

void ctu(char *s);

int main(){
	int sockfd,n,sen,i;
	struct sockaddr_in servaddr, cliaddr;
	socklen_t len;
	char mesg[1000];
	
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(32000);
	bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	
	len = sizeof(cliaddr);
	
	n = recvfrom(sockfd, mesg, 1000, 0, (struct sockaddr *)&cliaddr, &len);
	sendto( sockfd, "ack", 3, 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
	sen = atoi(mesg);
	for( i = 0; i < sen; i++){
		n = recvfrom(sockfd, mesg, 1000, 0, (struct sockaddr *)&cliaddr, &len);
		mesg[n] = '\0';
		printf("Received: %s\n",mesg);
		ctu(mesg);
		sendto( sockfd, mesg, n, 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
	}
	return 0; 
}

void ctu(char *s){
	while(*s != '\0'){
		*s = toupper((unsigned char)*s);
		s++;
		}
}
