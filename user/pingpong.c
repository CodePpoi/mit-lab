#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
	int p[2]; 
	int q[2];
    pipe(p);
    pipe(q);
    if(fork() == 0) {
	   write(q[1], "received pong\n", 16 );
	    char buf[1024] = {"\0"};
	    read(p[0], buf, 16);
	    printf("%d: %s",getpid(),buf);
	   close(p[0]);
	   close(p[1]);
	exit(0);
    } else {
	   write(p[1], "received ping\n", 16 );
	    char buf[1024] = {"\0"};
	    read(q[0], buf, 16);
	    printf("%d: %s",getpid(),buf);
	   close(q[0]);
	   close(q[1]);
	exit(0);
    }

    exit(0);
}
