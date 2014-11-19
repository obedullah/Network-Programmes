#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	char text[100],key[20],ch,encrypted[20][20];
	int index[20],temp,i,j,k,row,len,text_len,key_len;
	char decrypted[20][20],okey[20];
	
	printf("enter the text :\n");
	gets(text);
	printf("enter the key :\n");
	gets(key);
	text_len=strlen(text);
	key_len=strlen(key);
	len=text_len%key_len;
	for(i=0;i<strlen(text);i++)
	{
		if(text[i]==' ')
		{
			text[i]='-';
		}
	}
	len=text_len+(key_len-len);
	for(i=text_len;i<len;i++)
	{
		text[i]='-';
	}
	text[len]='\0';
	for(i=0;i<strlen(key);i++)
	{
		index[i]=i;
	}
	row=strlen(text)/strlen(key);
	k=0;
	for(i=0;i<row;i++)
	{
		for(j=0;j<strlen(key);j++)
		{
			encrypted[i][j]=text[k++];
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
				temp=index[i];
				index[i]=index[j];
				index[j]=temp;
			}
		}
	}
	k=0;
	for(i=0;i<strlen(key);i++)
	{
		for(j=0;j<row;j++)
		{
			text[k++]=encrypted[j][index[i]];
		}
	}
	text[k]='\0';
	printf("the encrypted key :\n%s\n",text);
	row=strlen(text)/strlen(key);
	k=0;
	for(i=0;i<strlen(key);i++)
	{
		for(j=0;j<row;j++)
		{
			decrypted[j][index[i]]=text[k++];
		}
	}
	k=0;
	for(i=0;i<row;i++)
	{
		for(j=0;j<strlen(key);j++)
		{
			if(decrypted[i][j]=='-')
			{
				text[k++]=' ';
			}
			else
			{
				text[k++]=decrypted[i][j];
			}
		}
	}
	text[k]='\0';
	printf("\nthe decrypted text is :\n");
	puts(text);
	return 0;
}
