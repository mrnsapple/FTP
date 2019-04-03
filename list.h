/*
** EPITECH PROJECT, 2019
** list
** File description:
** bu to
*/
#define PORT 8080

#ifndef LIST_H_
	#define LIST_H_

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <sys/types.h>
#include <sys/wait.h>




typedef struct			list
{
    int sock;
	int port;

    struct sockaddr_in adr;
  	int		ads;
	int new_sock;
    fd_set active_fd_set;
    fd_set read_fd_set;
    char ***reply_codes; 
    int **reply_codes_num;

}   list_t;

int	select_encap(list_t *l);
list_t	*set_reply_codes(list_t *l);
int	fork_stuff(list_t *l);
int set_socket(int port);
void	child_stuff(list_t *l);

#endif
