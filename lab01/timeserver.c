#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(){
	int sockfd, n;
	struct sockaddr_in servaddr, cliaddr;
	socklen_t len;
	char mesg[1000], *msg;
	time_t rt;
	struct tm *ti;
	
	sockfd = socket( AF_INET, SOCK_DGRAM, 0);
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(32000);
	bind( sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	
	len = sizeof(cliaddr);
	n = recvfrom( sockfd, mesg, 1000, 0, (struct sockaddr *)&cliaddr, &len);
	mesg[n] = 0;
	printf("Recived: %s\n", mesg);
	while(1){
		time(&rt);
		ti = localtime( &rt);
		msg = asctime(ti);
		sendto( sockfd, msg, strlen(msg), 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
		sleep(1);
	}
	return 0;
}
