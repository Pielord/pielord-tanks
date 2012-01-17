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

#include <event2/event.h>
#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>

#include "packet.h"

#define RUNNING_DIR "/user/local/bin"
#define LOCK_FILE "tank-serv.lock"

static void daemonize()
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

int main(int argc, char **argv)
{
    char ch;
    bool daemon = false;
    
    while ((ch = getopt(argc, argv, "d:")) != -1) {
        switch (ch) {
            case 'd':
                daemon = true;
                break;
        }
    }
    
    if (daemon) {
        daemonize();
    }
    
    return (0);
}
