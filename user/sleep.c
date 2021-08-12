#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) 
{
if (argc != 2) 
{
	fprintf(2, "error input\n");
	exit(1);
}
int sec = atoi(argv[1]);
sleep(sec);
exit(0);
}
