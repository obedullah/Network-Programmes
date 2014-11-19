#include<stdio.h>
#include<string.h>    //strlen
#include<stdlib.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include<pthread.h> //for threading , link with lpthread

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



//the thread function
void *connection_handler(void *);
 
int main(int argc , char *argv[])
{
    int socket_desc , client_sock , c , *new_sock;
    struct sockaddr_in server , client;
     
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
     
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(5000);
     
    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");
     
    //Listen
    listen(socket_desc , 3);
     
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
     
     
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
    while( (client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
    {
        puts("Connection accepted");
         
        pthread_t sniffer_thread;
        new_sock = malloc(1);
        *new_sock = client_sock;
         
        if( pthread_create( &sniffer_thread , NULL ,  connection_handler , (void*) new_sock) < 0)
        {
            perror("could not create thread");
            return 1;
        }
         
        //Now join the thread , so that we dont terminate before the thread
        //pthread_join( sniffer_thread , NULL);
        puts("Handler assigned");
    }
     
    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }
     
    return 0;
}
 
/*
 * This will handle connection for each client
 * */
void *connection_handler(void *socket_desc)
{
 
    int sock = *(int*)socket_desc;
    int read_size,flag=0;
    
   strcpy(ptr.name,"server");
   
   while(1)
   {	
   	bzero(ptr.name,10);
   	bzero(ptr.buffer,256);
   	
   	read(sock ,&ptr ,sizeof(ptr));
   	decrypt();
   /*	
   	bzero(ptr.name,10);
   	bzero(ptr.buffer,256);
   	
   	strcpy(ptr.buffer,"your message has been received");
   	strcpy(ptr.name,"server");
   	encrypt();
   	write(sock ,&ptr ,sizeof(ptr));
   	
   	strcpy(ptr.buffer,msg);
   	strcpy(ptr.name,tempname);
   	
    	write(sock ,&ptr ,sizeof(ptr));*/
    }
     
    return 0;
}
