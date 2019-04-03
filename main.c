/*
** EPITECH PROJECT, 2019
** 203hotline_2018
** File description:
** main
*/
// Server side C/C++ program to demonstrate Socket programming 

#include "list.h"

char *reply_codes[] = { 
	"120 Service ready in nnn minutes.",
	"125 Data connection already open; transfer starting.",
  "150 File status okay; about to open data connection.",
	"200 Command okay.",
  "214 Help message.On how to use the server or the meaning of a particular non-standard command.  This reply is useful only to the human user.",
  "220 Service ready for new user.",
  "221 Service closing control connection. Logged out if appropriate.",
	"226 Closing data connection. Requested file action successful (for example, file transfer or file abort).",
  "227 Entering Passive Mode (h1,h2,h3,h4,p1,p2).",
  "230 User logged in, proceed.",
	"250 Requested file action okay, completed.",
	"257 \"PATHNAME\" created.",
	"331 User name okay, need password.",
	"332 Need account for login.",
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

void	get_client_request(list_t *l)
{

}

void	child_stuff(list_t *l)
{
	char *hello = (char *)"220";
	int	connection = 1;

	while(connection == 1) {
		FD_ZERO (&(l->active_fd_set));
		FD_SET (l->sock, &(l->active_fd_set));
		connection = select_encap(l);
		if (connection > 0)
			get_client_request(l);
		else
			connection = 0;
			
	}	
	send(l->new_sock, hello, strlen(hello), 0);		
}

int	fork_stuff(list_t *l)
{
	pid_t pid = fork();
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
	}
	return 0;
}

int	select_encap(list_t *l)
{
	l->read_fd_set = l->active_fd_set;

	return (select (l->new_sock, &(l->read_fd_set), NULL, NULL, NULL) < 0);
}

int	loop(list_t *l)
{
	l->ads = sizeof(l->adr);
	printf("INFO : Server started on port %d.\n", l->port);

	for (int i = 0; i == 0; i = 0) {
		l->new_sock = accept(l->sock, (struct sockaddr*)&(l->adr), (socklen_t*)(&(l->ads)));
		printf("the child loop:%d\n", l->new_sock);
		if (l->new_sock > 0)
			fork_stuff(l);
	} 
	close(l->sock);
	return 0;	
}

int main(int ac, char **av)
{
	list_t *list = malloc(sizeof(list_t));

	for (int i = 0; reply_codes[i] != NULL; i++)
		printf("%s\n", reply_codes[i]);
	if (ac == 2 && av != NULL && list != NULL) {
		list->port = atoi(av[1]);
		list->sock = set_socket(list->port);
		return (loop(list));
	}
	return 84;
}
/*
int main(int argc, char const *argv[]) 
{ 
	int server_fd, new_socket, valread; 
	struct sockaddr_in address; 
	int opt = 1; 
	int addrlen = sizeof(address); 
	char buffer[1024] = {0}; 
	char *hello = "Hello from server"; 
	
	// Creating socket file descriptor 
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
	{ 
		perror("socket failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	// Forcefully attaching socket to the port 8080 
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
												&opt, sizeof(opt))) 
	{ 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	} 
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons( PORT ); 
	
	// Forcefully attaching socket to the port 8080 
	if (bind(server_fd, (struct sockaddr *)&address, 
								sizeof(address))<0) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	if (listen(server_fd, 3) < 0) 
	{ 
		perror("listen"); 
		exit(EXIT_FAILURE); 
	} 
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
					(socklen_t*)&addrlen))<0) 
	{ 
		perror("accept"); 
		exit(EXIT_FAILURE); 
	} 
	valread = read( new_socket , buffer, 1024); 
	printf("%s\n",buffer ); 
	send(new_socket , hello , strlen(hello) , 0 ); 
	printf("Hello message sent\n"); 
	return 0; 
} 
*/