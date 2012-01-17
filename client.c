#include <stdlib.h>

#include <event2/bufferevent.h>
#include <event2/buffer.h>

#include "client.h"

struct client *client_clients_tail;

int client_client_count;

struct client *
client_new_client(void)
{
    struct client * c = calloc(1, sizeof(struct client));
    
    if (client_clients_tail) {
        c->prev = client_clients_tail;
        client_clients_tail->next = c;
    }
    c->next = NULL;
    client_clients_tail = c;
    
    client_client_count++;
    
    return c;
}

void
client_free_client(struct client *c)
{
    if (c->next != NULL) {
        c->next->prev = c->prev;
    } else {
        client_clients_tail = c->prev;
    }

    if (c->prev != NULL) {
        c->prev->next = c->next;
    }
    //Free the socket bufferinfo, automatically disconnects.
    if (c->buf_event) {
        bufferevent_free(c->buf_event);
    }
    
    client_client_count--;
    
    free(c);
}

void
client_free_all_clients(void)
{
    struct client *temp = client_clients_tail;
    
    while(temp) {
        temp = client_clients_tail->prev;
        
        //Free the socket bufferinfo, automatically disconnects.
        if (client_clients_tail->buf_event) {
            bufferevent_free(client_clients_tail->buf_event);
        }
        
        free(client_clients_tail);
        
        client_clients_tail = temp;
        
        client_client_count--;
    }
}
