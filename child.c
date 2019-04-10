/*
** EPITECH PROJECT, 2019
** child
** File description:
** by oriol
*/

#include "list.h"

const int reply_codes_num[] = {120, 125, 150, 200, 214, 220, 221, 226, 227,
                          230, 250, 257, 331, 333, -1};
const char    *reply_codes[] = { 
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
    NULL
};

int read_from_client (int filedes)
{
    char    buffer[MAXMSG];
    int nbytes;

    nbytes = read (filedes, buffer, MAXMSG);
    if (nbytes < 0) {
      perror ("read");
      exit (EXIT_FAILURE);
    }
    else if (nbytes == 0)
        return -1;
    else {
        fprintf (stderr, "Server: got message: `%s'\n", buffer);
        return 0;
    }
}

void    set_socket(list_t *l)
{
    if ((l->sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("setsockopt"); 
        exit(EXIT_FAILURE);   
    }
    l->addr.sin_family = AF_INET;
    l->addr.sin_addr.s_addr = INADDR_ANY;
    l->addr.sin_port = htons(l->port);
    if (bind(l->sock, (struct sockaddr *)&(l->addr), sizeof(l->addr)) == -1)
        perror("setsockopt_bind"); 
    if (listen(l->sock, MAX_CLIENTS) == -1)
        perror("setsockopt_listen"); 
}

void    send_specific_code(list_t   *l, int   specific_code)
{
    printf("sending code:%d\n", specific_code);
    for (int i = 0; reply_codes_num[i] != -1 ; i++)
        if (reply_codes_num[i] == specific_code)
            write(l->current_socket, reply_codes[i], strlen(reply_codes[i]));
}

void    child_stuff(list_t *l)	
{	
    send_specific_code(l, 220);
    for (l->counter = 0; l->counter >= 0; l->counter++) {
        read_stuff(l);
        try_options(l);
    }
}

int accept_client(int   i, list_t *l)
{
    if (i == l->sock) {
        printf("beforeaccept");
        l->current_socket = accept(l->sock, (struct sockaddr*)&(l->adr),
                                   (socklen_t*)(&(l->ads)));
        if (l->current_socket < 0) {
            perror ("accept");
            return (84);
        }
        add_new_socket(l, l->current_socket);
        send_specific_code(l, 220);
    }
    return (0);
}

int interact_with_client(int i, list_t *l)
{
    int sd;
    
    printf("\nafterinteract\n");
    for (i = 0; i < MAX_CLIENTS; i++) {
        if (FD_ISSET(sd , &l->read_fd_set)) {
            printf("client is not socket\n");
            sd = l->client_socket[i];		
            l->current_socket = l->client_socket[i];
            if (read_stuff(l) > 0)
                try_options(l);
        }
    }
    printf("afterclient\n");
    return (0);
}

/*
void	fork_stuff(int i, list_t *l)
{
	pid_t child_pid;
	//int	status = 0;
	//int	waitoptions = 0;

	printf("\nNEW CLIENT\n");
	child_pid = fork();
	if (child_pid == -1) {
		perror("error fork\n");
		exit(84);
	}
	if (child_pid == 0)
		inside_stuff(i, l);
	//if (child_pid > 0)
	//	child_pid = waitpid(child_pid, &status, waitoptions);
}*/
