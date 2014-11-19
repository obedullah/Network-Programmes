#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	int i,j,m;
	char key[100],text[100],encrypt[100];
	printf("enter the text : ");
	gets(text);
	printf("enter the key of same length as text : ");
	gets(key);
	if(strlen(text)!=strlen(key))
	{
		printf("length of text and key is not same\n");
		exit(1);
	}
	m=0;
	for(i=0;i<strlen(key);i++)
	{
		encrypt[m++]=(key[i]+text[i]-194)%26+97;
	}
	encrypt[m]='\0';
	printf("the encrypted key is :\n\n%s\n",encrypt);
	return 0;
}
