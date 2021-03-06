#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 
#include <gtk/gtk.h>

void closeApp ( GtkWidget *window, gpointer data)
{
	gtk_main_quit();
}

int main(int argc, char *argv[])
{
	int sockfd,result,len;
	struct sockaddr_in address;
	
	int i,j;
	GtkWidget *window;
	GtkWidget *hbox;
	GtkWidget *vbox;
	GtkWidget *ok_button;
	
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	address.sin_family=AF_INET;
	address.sin_addr.s_addr=inet_addr("127.0.0.1");
	address.sin_port=htons(9734);
	len=sizeof(address);
	result=connect(sockfd,(struct sockaddr *)&address,len);
	if(result==-1)
	{
		perror("error in connecting\n");
	}
	
	while(1)
	{
		gtk_init(&argc, &argv);
		window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
		gtk_window_set_title(GTK_WINDOW(window), "TICTACTOE CLIENT");
		gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
		gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);
		g_signal_connect ( GTK_OBJECT (window), "destroy",GTK_SIGNAL_FUNC ( closeApp), NULL);
		
		vbox = gtk_vbox_new ( TRUE, 0);
		
		for(i=0;i<3;i++)
		{
			hbox = gtk_hbox_new ( FALSE, 0);
			for(j=0;j<3;j++)
			{
				ok_button = gtk_button_new_with_label("---");
				gtk_box_pack_start(GTK_BOX(hbox), ok_button, TRUE, TRUE, 0);
			}
			gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, TRUE, 0);
		}
		gtk_container_add(GTK_CONTAINER(window), vbox);
		gtk_widget_show_all(window);
		gtk_main ();
	}

	
	return 0;
}
