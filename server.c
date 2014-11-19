#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
//#include <error.h>
#include <time.h>
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
int read_write=0,back=0;

struct node
{	
	char name[10];
	char buffer[256];
}ptr;

void error(char *msg)
{
	perror(msg);
	exit(1);
}
void *thread_write(void *arg) 
{
	int res, n;
	int *sock=(int *)arg;
	pthread_t a_thread;
	void *thread_result;
	
	while(1)
	{
		if(read_write==1)
		{
			read_write=0;
			n = write(*sock,&ptr,sizeof(ptr));
			if (n < 0)
			{
				error("ERROR writing to socket");
			}
			if(back==1)
			{
				pthread_exit("Thank you !");
				break;
			}
		}
	}
}

void *thread_read(void *arg) 
{
	int res, n;
	int *sock=(int *)arg;
	pthread_t a_thread;
	void *thread_result;
	
	bzero(ptr.name,10);
	bzero(ptr.buffer,256);
	res = pthread_create(&a_thread, NULL, thread_write, (void *)sock);
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
			n = read(*sock,&ptr,sizeof(ptr));
			if (n < 0) 
			{
				error("ERROR reading from socket");
			}
			printf("Name : %s\nMessage : %s\n",ptr.name,ptr.buffer);
			if(strcmp(ptr.buffer,"quit\n")==0)
			{
				back=1;
				res = pthread_join(a_thread, &thread_result);
				if(back==1)
				{
					pthread_exit("Thank you !");
					close(*sock);
					break;
				}
				close(*sock);
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
	int sockfd, newsockfd, portno, clilen, pid, n, i=0, res;	
	
	pthread_t a_thread;
	void *thread_result;
	
	struct sockaddr_in serv_addr;
	struct sockaddr_in cli_addr;
	
	if (argc < 2) 
	{
		fprintf(stderr,"ERROR, no port provided\n");
		exit(1);
	}
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
	{
		error("ERROR opening socket");
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
	{
		error("ERROR on binding");
	}
	listen(sockfd,5);
	printf("server waiting...\n");
	while (1) 
	{	
		clilen = sizeof(cli_addr);
		newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
		if (newsockfd < 0) 
		{
			error("ERROR on accept");
		}
		res = pthread_create(&a_thread, NULL, thread_read, (void *)&newsockfd);
		if(res!=0)
		{
			perror("Thread creation failed\n");
			exit(EXIT_FAILURE);
		}
		
		close(sockfd);
		
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
	return 0;
}
