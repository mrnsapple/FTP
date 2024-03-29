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
    char *dir;
    int is_autentificated;
    int any_instruction_sent;
    int is_anonimous;
} read_t;

typedef struct  list
{
    int sock;
    int port;
    char    *path;
    fd_set read_fd_set;
    struct sockaddr_in addr;
    void (*options[LEN_OPTIONS])(int child_socket, read_t  *read);
    int current_socket;
}   list_t;

int select_encap(fd_set *read_fd_set);
list_t	*set_reply_codes(list_t *my_var);
int accept_client(int i, list_t *my_var);
int interact_with_client(int child_socket,
                         void (*options[LEN_OPTIONS])(int child_socket, read_t  *read), read_t *read);
read_t  *read_stuff(int child_socket, read_t *reader);

void	set_socket(list_t *my_var);
void    set_options(list_t *my_var);
int    try_options(int child_socket, read_t  *read,
                   void (*options[LEN_OPTIONS])(int child_socket, read_t  *read));
int    len_array(char **av);
char **my_str_to_wordtab(char *str, char x);
void    send_specific_code(int current_socket, int   specific_code);
void	fork_stuff(int i, list_t *my_var);
char *get_parent_dir(char *dir);
#endif
