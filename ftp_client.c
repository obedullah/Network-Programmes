#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main(int argc , char *argv[])
{
	int sock,i;
	struct sockaddr_in server;
	char name[200] , buffer[40],fname[50];
	FILE *fp;
	sock = socket(AF_INET , SOCK_STREAM , 0);
	if (sock == -1)
	{
		printf("Could not create socket");
	}
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons( 8889 );

	if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		perror("connect failed. Error");
		return 1;
	}
	if(argc==2)
	{
		strcpy(name, argv[1]);
	}
	else
	{
		printf("Enter file name : ");
		scanf("%s" , name);
	}
		
	i=strlen(name);
	while(i-- && name[i]!='/');
	if(i == 0){
	    memcpy(fname, &name[-1], strlen(name) );
	}
	else
	    memcpy(fname, &name[i+1], strlen(name)-1 ); //To avoid enter at the end of file
	write(sock, fname, 50);
	printf("%s",fname);
	fp=fopen(name,"r");		
	while(!feof(fp))
	{
		bzero(buffer,40);
		fread(buffer,39,1,fp);
		//puts(buffer);
		if( send(sock , buffer , 39 , 0) < 0)
		{
			puts("Send failed");
			return 1;
		}
	}
	
	printf("file transfer complete\n");
	close(sock);
	return 0;
}
