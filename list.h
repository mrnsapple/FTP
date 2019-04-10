/*
** EPITECH PROJECT, 2019
** list
** File description:
** bu to
*/
#define PORT 8080

#ifndef LIST_H_
	#define LIST_H_
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
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

#define LEN_OPTIONS 15
#define MAX_CLIENTS 30

typedef struct  read
{
    char buff[2000];
    char **buff_array;
    int buff_array_size;

} read_t;

typedef struct			list
{
    int sock;
	int port;
    struct sockaddr_in adr;
  	int		ads;
    fd_set read_fd_set;
    struct sockaddr_in addr;
    int counter;
    read_t  *read;
    void (*options[LEN_OPTIONS])(struct list*);

    int client_socket[MAX_CLIENTS];
    int current_socket;
}   list_t;

int	select_encap(list_t *l);
list_t	*set_reply_codes(list_t *l);
int accept_client(int i, list_t *l);
int interact_with_client(int i, list_t *l);

void	set_socket(list_t *l);
void	child_stuff(list_t *l);
int        read_stuff(list_t *l);
void    set_options(list_t *l);
void    try_options(list_t *l);
int    len_array(char **av);
char **my_str_to_wordtab(char *str, char x);
void	send_specific_code(list_t *l, int specific_code);
void	fork_stuff(int i, list_t *l);
void    initialize_clients(list_t *l);
void    add_client_to_sockket(list_t *l);
void	add_new_socket(list_t *l, int new_socket);

#endif
