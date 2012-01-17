#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdbool.h>
#include <string.h>

//Fork, umask, etc
#include <unistd.h>
#include <sys/stat.h>
//Signals
#include <signal.h>
//Open, etc
#include <sys/stat.h>
#include <fcntl.h>
//Socket, etc
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//Errors
#include <errno.h>

#include <event2/event.h>
#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>

#include "client.h"
#include "game.h"
#include "packet.h"

#define RUNNING_DIR "/user/local/bin"
#define LOCK_FILE "tank-serv.lock"

#define DEFAULT_PORT 3033

//Game map.
struct game_map map;

static void
readcb(struct bufferevent *bev, void *ctx)
{
    struct client * c = ctx;
    struct evbuffer *input = bufferevent_get_input(bev);
    enum tank_packet_type packet_id;
    //struct client * temp_client;
    
    //int i, n, item_count, failed;
    
    //Peak at packet_id.
    evbuffer_copyout(input, (void *) &packet_id,
                     sizeof(enum tank_packet_type));
    
    switch (packet_id) {
            /*
        case LOBBY_PING:
            n = bufferevent_read(bev, &empty_packet, sizeof(empty_packet));
            if (n != sizeof(empty_packet)) {
                syslog(LOG_WARNING, "[%s] Got PING packet with "
                       "bad size (%d).", inet_ntoa(c->address.sin_addr), n);    
                client_free_client(c);
            }
            break;
        case LOBBY_REGISTER:
            n = bufferevent_read(bev, &register_packet,
                                 sizeof(register_packet));
            if (n == sizeof(register_packet)) {
                if (!c->info) {
                    c->info = malloc(sizeof(struct server_info));
                    
                    c->info->server_port = register_packet.server_port;
                    memcpy(c->info->server_name, register_packet.server_name,
                           LOBBY_STR_LEN);
                    //Just in case.
                    c->info->server_name[LOBBY_STR_LEN - 1] = '\0';
                }
            } else {
                syslog(LOG_WARNING, "[%s] Got REGISTER packet with "
                       "bad size (%d).", inet_ntoa(c->address.sin_addr), n);       
                client_free_client(c);
            }
            break;
            */
        default:
            printf("[%s] Got unknown packet (%d)!",
                   inet_ntoa(c->address.sin_addr), packet_id);
            //Just drop the connection.
            client_free_client(c);
            break;
    }
}

static void
eventcb(struct bufferevent *bev, short events, void *ctx)
{
    struct client *c = ctx;
    int err;
    
    //Print error.
    if (events & BEV_EVENT_ERROR) {
        err = EVUTIL_SOCKET_ERROR();
        printf("[%s] Bufferevent error %d: %s.",
               inet_ntoa(c->address.sin_addr),
               err, evutil_socket_error_to_string(err));
    }
    //Client closed connection.
    if (events & BEV_EVENT_EOF) {
        printf("[%s] Client closed connection.",
               inet_ntoa(c->address.sin_addr));
    }
    //Client timed out.
    if (events & BEV_EVENT_TIMEOUT) {
        printf("[%s] Client timed out.",
               inet_ntoa(c->address.sin_addr));
    }
    
    //In case of error, end of connection or timeout, disconnect and free the
    //client.
    if (events & (BEV_EVENT_EOF | BEV_EVENT_ERROR | BEV_EVENT_TIMEOUT)) {
        client_free_client(c);
    }
}

static void
accept_conn_cb(struct evconnlistener *listener,
    evutil_socket_t fd, struct sockaddr *address, int socklen,
    void *ctx)
{
    struct sockaddr_in * addr = (struct sockaddr_in *) address;
    //int failed = 0;
    
    //We got a connection.
    printf("[%s] New connection received.",
          inet_ntoa(addr->sin_addr));
          
    struct client *c = client_new_client();
    
    /* We got a new connection! Set up a bufferevent for it. */
    c->evloop = evconnlistener_get_base(listener);
    c->buf_event = bufferevent_socket_new(
            c->evloop, fd, BEV_OPT_CLOSE_ON_FREE);
            
    //Init player.
    player_init(&(c->player_data), &(map));
    
    memcpy(&(c->address), address, sizeof(struct sockaddr));
    
    ///Set callbacks.
    bufferevent_setcb(c->buf_event, readcb, NULL,
                    eventcb, (void *) c);
    //Enable both reading and writing.
    bufferevent_enable(c->buf_event, EV_READ|EV_WRITE);
    
    //Send MAP_INFO packet.
    /*
    failed = bufferevent_write(c->buf_event, (const void *) &info_packet,
                        sizeof(info_packet));
    if(failed) {
        printf("[%s] Failed to send INFO packet.",
               inet_ntoa(c->address.sin_addr));
    }
    */
}

static void
accept_error_cb(struct evconnlistener *listener, void *ctx)
{
    struct event_base *base = evconnlistener_get_base(listener);
    
    int err = EVUTIL_SOCKET_ERROR();
    printf("Got an error %d (%s) on the listener."
           "Shutting down.", err, evutil_socket_error_to_string(err));

    event_base_loopexit(base, NULL);
}

static void
sigterm_cb(evutil_socket_t fd, short events, void *ptr)
{
    struct event_base *base = (struct event_base *) ptr;
    
    printf("Got SIGTERM. Shutting down!\n");
    //client_free_all_clients();
    event_base_loopexit(base, NULL);
}

static void
daemonize()
{
    int i,lfp;
    char str[10];
    //Alreadt daemon?
	if(getppid() == 1) {
	    return;
	}
	//Fork.
	i=fork();
	if (i<0) exit(1);
	if (i>0) exit(0);

	//Get new process group.
	setsid();
	//Close all descriptors.
	for (i=getdtablesize(); i >= 0; --i) {
	     close(i);
     }
    //Standard I/O. 
	i=open("/dev/null", O_RDWR);
	dup(i);
	dup(i);
	//Set file permissions.
	umask(027);
	//Change CWD.
	chdir(RUNNING_DIR);
	//Open lock file.
	lfp = open(LOCK_FILE, O_RDWR | O_CREAT, 0640);
	if (lfp < 0) {
	    //Can't open lock file.
	    exit(1);
	}
	if (lockf(lfp, F_TLOCK, 0) < 0) {
	    //Can't lock file.
	    exit(0);
    } 
    //Get pid.
	sprintf(str, "%d\n", getpid());
	//Write it.
	write(lfp, str, strlen(str));
	//Signals.
	signal(SIGCHLD, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGHUP, SIG_IGN);
	//Handle is from libevent.
	signal(SIGTERM, SIG_IGN);
}

int
main(int argc, char **argv)
{
    char ch;
    bool port = DEFAULT_PORT;
    bool daemon = false;
    
    struct event_base *base;
    struct evconnlistener *listener;
    struct sockaddr_in sin;
    struct event *term_event;
    
    while ((ch = getopt(argc, argv, "dp:")) != -1) {
        switch (ch) {
            case 'd':
                daemon = true;
                break;
            case 'p':
                port = optarg;
                break;
        }
    }
    
    if (port == 0) {
        port = DEFAULT_PORT;
    }
    
    if (daemon) {
        daemonize();
    }
    
    //Make default event base.
    base = event_base_new();
    if (!base) {
        printf("Can't create event base.\n");
        return 1;
    }
    
    //Prepare listening address.
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = htonl(0);
    sin.sin_port = htons(port);
    
    //Try to bind to the socket.
    listener = evconnlistener_new_bind(base, accept_conn_cb, NULL,
        LEV_OPT_CLOSE_ON_FREE|LEV_OPT_REUSEABLE, -1,
        (struct sockaddr*)&sin, sizeof(sin));
    if (!listener) {
        printf("Failed to create listening socket.\n");
        return 1;
    }
    
    //Set the error callback.
    evconnlistener_set_error_cb(listener, accept_error_cb);
    
    //Set up SIGTERM handler.
    term_event = evsignal_new(base, SIGTERM, sigterm_cb, (void *) base);
    event_add(term_event, NULL);
    
    printf("Load map.\n");
    map_init(&map, "");
    
    printf("Starting main event loop.\n");
    
    //Start the event loop.	
    event_base_dispatch(base);
    
    printf("Shutting down.\n");
    
    //Free event base.
    event_base_free(base);
    
    //Free term_event event.
    event_free(term_event);
    
    //Free listener (also closes the socket).	
    free(listener);
    
    return (EXIT_SUCCESS);
}
