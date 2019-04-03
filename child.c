/*
** EPITECH PROJECT, 2019
** child
** File description:
** by oriol
*/

#include "list.h"

#define MAXMSG  512

int
read_from_client (int filedes)
{
  char buffer[MAXMSG];
  int nbytes;

  nbytes = read (filedes, buffer, MAXMSG);
  if (nbytes < 0)
    {
      /* Read error. */
      perror ("read");
      exit (EXIT_FAILURE);
    }
  else if (nbytes == 0)
    /* End-of-file. */
    return -1;
  else
    {
      /* Data read. */
      fprintf (stderr, "Server: got message: `%s'\n", buffer);
      return 0;
    }
}



/////////
int reply_codes_num[] =  {120, 125, 150, 200, 214, 220, 221,226,227,230,250,257,331,333, -1};
char *reply_codes[] = { 
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

int set_socket(int port)
{
	int		sok;
  	struct sockaddr_in addr;

	if ((sok = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("setsockopt"); 
		exit(EXIT_FAILURE);   
	}
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(port);
	if (bind(sok, (struct sockaddr *)&addr, sizeof(addr)) == -1)
		perror("setsockopt"); 
	if (listen(sok, 5) == -1)
		perror("setsockopt"); 
	return (sok);
}

void    get_client_request(list_t *l)
{
    printf("inget_client\n");
	
}

void	child_stuff(list_t *l)	
{
	//char *hello = (char *)"220";
	int	connection = 1;
    printf("connection:%d, counter:%d\n", connection, l->counter);
    for (int i = 0; reply_codes_num[i] != -1 ; i++) {
        l->read_fd_set = l->active_fd_set;
		if ((l->counter == 0 && reply_codes_num[i] == 220) || (l->counter == 1 && reply_codes_num[i] == 331))
			send(l->new_sock, reply_codes[i], strlen(reply_codes[i]), 0);
	}
    read_stuff(l);
    //FD_ZERO (&(l->active_fd_set));
	//FD_SET (l->sock, &(l->active_fd_set));
	//send(l->new_sock, hello, strlen(hello), 0);
	/*while(connection == 1 && l->counter > 0) {
        printf("inside\n");
		
		connection = select_encap(l);
        printf("connection:%d\n", connection);
		if (connection > 0)
			get_client_request(l);
		else
			connection = 0;		
	}*/
}

int inside_stuff(int i, list_t *l)
{
    printf("begining, count:%d\n", l->counter);
    if (i == l->sock) {
        l->new_sock = accept(l->sock, (struct sockaddr*)&(l->adr), (socklen_t*)(&(l->ads)));
        printf("the child loop:%d\n", l->new_sock);
        if (l->new_sock < 0) {
            perror ("accept");
            exit (84);
        }
        child_stuff(l);
       // fprintf (stderr, "Server: connect from host %s, port %hd.\n",
        //             (l->adr.sin_addr),
         //           ntohs (l->adr.sin_port));
        FD_SET (l->new_sock, &l->active_fd_set);
    }
    else {
        /* Data arriving on an already-connected socket. */
        if (read_from_client (i) < 0) {
            close (i);
            FD_CLR (i, &l->active_fd_set);
            }
    }	
    return (0);
}

	/*pid_t pid = fork();
	int start;

	if (pid == 0) {
		printf("the child:%d\n", l->new_sock);
		child_stuff(l);
		exit (0);
	} //else if (pid > 0) //	close (new_sock);
	else if (pid < 0) {
		return 84;
	}
	else if (pid > 0) {
		waitpid(pid, &start, 0);
		close(l->new_sock);
	}*/
