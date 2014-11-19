#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
char decrypted[20][20],key[]={'o','b','e','d','\0'},ch,encrypted[20][20];
int indexing[20],i,j,k=0,row,temp,text_len,key_len,len;
char tempname[10],msg[100];
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
void decrypt()
{
	for(i=0;i<strlen(key);i++)
	{
		indexing[i]=i;
	}
	for(i=0;i<strlen(key);i++)
	{
		for(j=i+1;j<strlen(key);j++)
		{	
			if(key[i] > key[j])
			{
				ch=key[i];
				key[i]=key[j];
				key[j]=ch;
				temp=indexing[i];
				indexing[i]=indexing[j];
				indexing[j]=temp;
			}
		}
	}
	row=strlen(ptr.buffer)/strlen(key);
	for(i=0;i<strlen(key);i++)
	{
		for(j=0;j<row;j++)
		{
			decrypted[j][indexing[i]]=ptr.buffer[k++];
		}
	}
	k=0;
	for(i=0;i<row;i++)
	{
		for(j=0;j<strlen(key);j++)
		{
			if(decrypted[i][j]=='-')
			{
				ptr.buffer[k++]=' ';
			}
			else
			{
				ptr.buffer[k++]=decrypted[i][j];
			}
		}
	}
	ptr.buffer[k]='\0';
	printf("\nthe decrypted text is :\n");
	printf("Name : %s\n",ptr.name);
	printf("Message : %s\n",ptr.buffer);
	if(strcmp(ptr.buffer,"quit")==0)
	{
		exit(1);
	}
}

void encrypt()
{
	text_len=strlen(msg);
	key_len=strlen(key);
	len=text_len%key_len;
	for(i=0;i<strlen(msg);i++)
	{
		if(msg[i]==' ')
		{
			msg[i]='-';
		}
	}
	len=text_len+(key_len-len);
	for(i=text_len;i<len;i++)
	{
		msg[i]='-';
	}
	msg[len]='\0';
	for(i=0;i<strlen(key);i++)
	{
		indexing[i]=i;
	}
	row=strlen(msg)/strlen(key);
	k=0;
	for(i=0;i<row;i++)
	{
		for(j=0;j<strlen(key);j++)
		{
			encrypted[i][j]=msg[k++];
		}
	}
	for(i=0;i<strlen(key);i++)
	{	
		for(j=i+1;j<strlen(key);j++)
		{
			if(key[i] > key[j])
			{
				ch=key[i];
				key[i]=key[j];
				key[j]=ch;
				temp=indexing[i];
				indexing[i]=indexing[j];
				indexing[j]=temp;
			}
		}
	}
	k=0;
	for(i=0;i<strlen(key);i++)
	{
		for(j=0;j<row;j++)
		{
			msg[k++]=encrypted[j][indexing[i]];
		}
	}
	msg[k]='\0';
	printf("the encrypted message :\n%s\n",msg);
}

int main(int argc, char *argv[])
{
	int sockfd, portno, n, res;
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
	fgets(tempname,10,stdin);

	while(1)
	{	
		bzero(msg,100);
		printf("\nenter the message: ");
		fgets(msg,100,stdin);
		bzero(ptr.buffer,256);
		encrypt();
		strcpy(ptr.buffer,msg);
		strcpy(ptr.name,tempname);
		n = write(sockfd,&ptr,sizeof(ptr));
		if (n < 0) 
		{
			error("ERROR writing to socket");
		}
		/*n = read(sockfd,&ptr,sizeof(ptr));
		if (n < 0) 
		{
			error("ERROR writing to socket");
		}
		decrypt();*/
	}
	return 0;
}
