#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

struct buffer
{
	char buffer_text[100];
};
struct buffer *ptr;

int main()
{
	int sockfd;
	int len;
	struct sockaddr_in address;
	int result;
	char filename[10];
	FILE * fp;

	ptr = (struct buffer *)malloc(sizeof(struct buffer));

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("192.168.1.6");
	address.sin_port = htons(9734);
	len = sizeof(address);
	
	result = connect(sockfd, (struct sockaddr *)&address, len);
	if(result == -1)
	{
		perror("oops error occurred\n");
		fclose(fp);
		exit(1);
	}

	while(1) 
	{
		printf("enter file name you want to retrieve from server : ");
		scanf("%s",filename);
		write(sockfd,filename,100);
		fp=fopen(filename,"wb");
		while()
		read(sockfd,ptr->buffer_text,100);

		fwrite(ptr->buffer_text,100,1,fp);
		close(sockfd);
	}
}
