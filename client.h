#include <inttypes.h>

#include <event2/event.h>

struct client {
	//Socket file descriptor.
	int fd;
	//Pointer to servers event loop.
	struct event_base *evloop;
	//Clients I/O event.
	struct bufferevent *buf_event;
	//Address.
	struct sockaddr_in address;
	//Linked list.
	struct client *prev, *next;
};

//Create a new client structure and add it to client list.
struct client * client_new_client(void);
//Free client.
void client_free_client(struct client *c);
//Free all clients.
void client_free_all_clients(void);

//Tail of clients list.
struct client *client_clients_tail;
