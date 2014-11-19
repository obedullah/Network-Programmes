#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<gtk/gtk.h>
#include <stdio.h>
#include <string.h>
GtkWidget *window;
void close_window(GtkWidget *window_new,gpointer data)
{
	gtk_main_quit();
}
void message_function(GtkWidget *button,gpointer data)
{
	const char *name = gtk_entry_get_text(GTK_ENTRY((GtkWidget *)data));
}
void button_clicked(GtkWidget *button,gpointer data)
{
	int sockfd;
	int len;
	char text[100];
	struct sockaddr_in address;
	int result;
	
	GtkWidget *user_label,*user_entry;
	GtkWidget *window_new,*hbox,*vbox;
	const char *name = gtk_entry_get_text(GTK_ENTRY((GtkWidget *)data));
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = htons(9734);
	len = sizeof(address);
	result = connect(sockfd, (struct sockaddr *)&address, len);
	if(result == -1)
	{
		perror("oops: client\n");
		exit(1);
	}
	write(sockfd,name,100);
	
	window_new=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window_new),"Welcome to Online Chat !");
	gtk_window_set_position(GTK_WINDOW(window_new),GTK_WIN_POS_MOUSE);
	gtk_window_set_default_size(GTK_WINDOW(window_new),500,300);
	user_label=gtk_label_new(name);
	user_entry=gtk_entry_new();
	g_signal_connect(GTK_OBJECT(window_new),"destroy",GTK_SIGNAL_FUNC(close_window),NULL);
	g_signal_connect(user_entry,"activate",GTK_SIGNAL_FUNC(message_function),user_entry);
	hbox=gtk_hbox_new(TRUE,5);
	vbox=gtk_vbox_new(FALSE,5);
	gtk_box_pack_start(GTK_BOX(hbox),user_label,TRUE,FALSE,5);
	gtk_box_pack_start(GTK_BOX(hbox),user_entry,TRUE,TRUE,5);
	gtk_box_pack_start(GTK_BOX(vbox),hbox,FALSE,FALSE,5);
	gtk_container_add(GTK_CONTAINER(window_new),vbox);
	gtk_widget_show_all(window_new);
	gtk_widget_destroy(window);
}

int main(int argc, char *argv[])
{
	GtkWidget *hbox,*vbox;
	GtkWidget *user_label,*user_entry;
	gtk_init(&argc,&argv);
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"Welcome to Online Chat !");
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_MOUSE);
	gtk_window_set_default_size(GTK_WINDOW(window),500,300);
	user_label=gtk_label_new("User Name : ");
	user_entry=gtk_entry_new();
	g_signal_connect(user_entry,"activate",GTK_SIGNAL_FUNC(button_clicked), user_entry);
	hbox=gtk_hbox_new(TRUE,5);
	vbox=gtk_vbox_new(FALSE,5);
	gtk_box_pack_start(GTK_BOX(hbox),user_label,TRUE,FALSE,5);
	gtk_box_pack_start(GTK_BOX(hbox),user_entry,TRUE,FALSE,5);
	gtk_box_pack_start(GTK_BOX(vbox),hbox,FALSE,FALSE,5);
	gtk_container_add(GTK_CONTAINER(window),vbox);
	gtk_widget_show_all(window);
	gtk_main();
	return 0;
} 
