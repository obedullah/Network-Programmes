#include<stdio.h>
#include<string.h>
int main()
{
	char decrypted[20][20],encrypted[100],key[20],okey[20],ch;
	int index[20],i,j,k=0,row,temp;
	printf("enter encrypted key :\n");
	gets(encrypted);
	printf("enter key :\n");
	gets(key);
	for(i=0;i<strlen(key);i++)
	{
		index[i]=i;
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
				temp=index[i];
				index[i]=index[j];
				index[j]=temp;
			}
		}
	}
	row=strlen(encrypted)/strlen(key);
	for(i=0;i<strlen(key);i++)
	{
		for(j=0;j<row;j++)
		{
			decrypted[j][index[i]]=encrypted[k++];
		}
	}
	k=0;
	for(i=0;i<row;i++)
	{
		for(j=0;j<strlen(key);j++)
		{
			if(decrypted[i][j]=='-')
			{
				encrypted[k++]=' ';
			}
			else
			{
				encrypted[k++]=decrypted[i][j];
			}
		}
	}
	encrypted[k]='\0';
	printf("\nthe decrypted text is :\n");
	puts(encrypted);
	return 0;
}
