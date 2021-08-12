#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    int p[2]; 
    pipe(p);
    char buf[1024] = {"\0"};
    char* params[100];
    int index = 0;
    int k;
    for(int i=1; i< argc;i++){
	 params[index++] = argv[i];
//	 printf("%d: %s\n", index-1, params[index-1]); 
	}
     while((k = read(0, buf, 1024)) > 0 ) {
//	printf("data ava\n");
	char tmp[1024] = {"\0"};
	params[index] = tmp; 
       for(int i=0; i< strlen(buf); i++) {
         if(buf[i] == '\n') {
		if (fork() ==0) {
		   exec(argv[1], params);      
		}
		wait(0);
         }
	 else {
	  tmp[i] = buf[i];
	 }
//	 printf("buf %d: %c\n",i,  buf[i]);
       }
     }
    exit(0);
}
