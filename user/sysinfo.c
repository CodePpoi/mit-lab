#include "kernel/types.h"
#include "user/user.h"
#include "kernel/sysinfo.h"

int main(int argc, char *argv[])
{
if (argc != 1)
{
        fprintf(2, "error input\n");
        exit(1);
}
struct sysinfo info;
sysinfo(&info);
printf("%d %d", info.freemem, info.nproc);
exit(0);
}
        
