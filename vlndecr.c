#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	int i,j,m=0;
	char key[100],encrypt[100],decrypt[100];
	printf("enter the encrypted encrypt : ");
	gets(encrypt);
	printf("enter the key of same length as encrypt : ");
	gets(key);
	if(strlen(encrypt)!=strlen(key))
	{
		printf("length of encrypt and key is not same\n");
		exit(1);
	}
	for(i=0;i<strlen(key);i++)
	{
		decrypt[m]=(encrypt[i]-key[i]);
		if(decrypt[m] < 0)
		{
			decrypt[m]+=26;
		}
		decrypt[m]+=97;
		m++;
	}
	decrypt[m]='\0';
	printf("the decrypted key is :\n\n%s\n",decrypt);
	return 0;
}
