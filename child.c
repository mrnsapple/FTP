/*
** EPITECH PROJECT, 2019
** child
** File description:
** by oriol
*/

#include "list.h"

const int   reply_codes_num[] = {120, 125, 150, 200, 214, 220, 221, 226, 227,
                          230, 250, 257, 331, 332, 530, 550, 500, 444, -1};

const char  *reply_codes[] = { 
    "120 Service ready in nnn minutes.\n",
    "125 Data connection already open; transfer starting.\n",
    "150 File status okay; about to open data connection.\n",
    "200 Command okay.\n",
    "214 Help message.On how to use the server or the meaning of a particular non-standard command.  This reply is useful only to the human user.\n",
    "220 Service ready for new user.\n",
    "221 Service closing control connection. Logged out if appropriate.\n",
    "226 Closing data connection. Requested file action successful (for example, file transfer or file abort).\n",
    "227 Entering Passive Mode (h1,h2,h3,h4,p1,p2).\n",
    "230 User logged in, proceed.\n",
    "250 Requested file action okay, completed.\n",
    "257 \"PATHNAME\" created.\n",
    "331 User name okay, need password.\n",
    "332 Need account for login.\n",
    "530 Not logged in.\n",
    "550 Requested action not taken. File unavailable (e.g., file not found, no access).\n",
    "500 Syntax error, command unrecognized and the requested action did not take place. This may include errors such as command line too long.\n",
    "xxx Error (RFC compliant)\n",
    NULL
};

void    set_socket(list_t *my_var)
{
    if ((my_var->sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("setsockopt"); 
        exit(EXIT_FAILURE);   
    }
    my_var->addr.sin_family = AF_INET;
    my_var->addr.sin_addr.s_addr = INADDR_ANY;
    my_var->addr.sin_port = htons(my_var->port);
    if (bind(my_var->sock, (struct sockaddr *)&(my_var->addr), sizeof(my_var->addr)) == -1)
        perror("setsockopt_bind"); 
    if (listen(my_var->sock, MAX_CLIENTS) == -1)
        perror("setsockopt_listen"); 
}

void    send_specific_code(int current_socket, int   specific_code)
{
    for (int i = 0; reply_codes_num[i] != -1 ; i++)
        if (reply_codes_num[i] == specific_code)
            write(current_socket, reply_codes[i], strlen(reply_codes[i]));
}

int child_loop(int  child_socket,
               void  (*options[LEN_OPTIONS])(int child_socket, read_t  *read), char *dir)
{
    read_t  *read;

    read = malloc(sizeof(read_t));
    read->dir = dir;
    read->is_autentificated = 0;
    read->is_anonimous = 0;

    send_specific_code(child_socket, 220);
    while (1)
        interact_with_client(child_socket, options, read);
    return (0);
}

int accept_client(int   i, list_t *my_var)
{
    pid_t pid;
    int child_socket;
    int ads;
    struct sockaddr_in adr;
    
    if (my_var != NULL && i == my_var->sock) {
        child_socket = accept(my_var->sock, (struct sockaddr*)&(adr),
                                   (socklen_t*)(&(ads)));
        if (child_socket < 0) {
            perror ("accept");
            return (84);
        }     
        pid = fork();
        if (pid < 0)
            exit(84);
        if (pid == 0 && child_loop(child_socket, my_var->options, my_var->path) == 84)
            exit(84);
    }
    return (0);
}

int interact_with_client(int child_socket,
                         void (*options[LEN_OPTIONS])(int child_socket, read_t  *read), read_t *read)
{   
    read = read_stuff(child_socket, read);
    if (read != NULL)
        try_options(child_socket, read, options);
    return (0);
}
