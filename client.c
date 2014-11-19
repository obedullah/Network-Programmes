#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
int read_write=0,back=0;

struct node
{
	char name[10];
	char buffer[256];
}ptr;
void error(char *msg)
{
	perror(msg);
	exit(0);
}

void *thread_read(void *arg)
{
	int n,res;
	int *sockfd=(int *)arg;
	while(1)
	{
		if(read_write==1)
		{
			read_write=0;
			bzero(ptr.name,10);
			bzero(ptr.buffer,256);
			n = read(*sockfd,&ptr,sizeof(ptr));
			if (n < 0) 
			{
				error("ERROR reading from socket");
			}
			printf("Name : %s\nMessage : %s\n",ptr.name,ptr.buffer);
			if(strcmp(ptr.buffer,"quit\n")==0)
			{
				back=1;
				printf("\nbye bye !\n");
				pthread_exit("Thank you !");
				break;
			}
		}
		else
		{
			sleep(1);
		}
	}
}

int main(int argc, char *argv[])
{
	int sockfd, portno, n, res;
	char temp[10];
	struct sockaddr_in serv_addr;
	struct hostent *server;
	pthread_t a_thread;
	void *thread_result;
	
	if (argc < 3) 
	{
		fprintf(stderr,"usage %s hostname port\n", argv[0]);
		exit(0);
	}
	portno = atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
	{
		error("ERROR opening socket");
	}
	server = gethostbyname(argv[1]);
	if (server == NULL) 
	{
		fprintf(stderr,"ERROR, no such host\n");
		exit(0);
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portno);
	if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
	{
		error("ERROR connecting");
	}
	printf("enter your user name : ");
	fgets(temp,10,stdin);
	
	res = pthread_create(&a_thread, NULL, thread_read, (void *)&sockfd);
	if(res!=0)
	{
		perror("Thread creation failed\n");
		exit(EXIT_FAILURE);
	}
	while(1)
	{	
		if(read_write==0)
		{
			read_write=1;
			printf("\nenter the message: ");
			bzero(ptr.buffer,256);
			fgets(ptr.buffer,256,stdin);
		
			strcpy(ptr.name,temp);
			
			n = write(sockfd,&ptr,sizeof(ptr));
			if (n < 0) 
			{
				error("ERROR writing to socket");
			}
			if(back==1)
			{
				res = pthread_join(a_thread, &thread_result);
				if (res != 0) 
				{
					perror("Thread join failed\n");
					exit(EXIT_FAILURE);
				}
			}
		}
		else
		{
			sleep(1);
		}
	}
	return 0;
}
