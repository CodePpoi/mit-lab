#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char*
fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  memmove(buf, p, strlen(p) + 1);
  return buf;
}

void
find(char *path, char* findName)
{
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if((fd = open(path, 0)) < 0){
    fprintf(2, "find: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    fprintf(2, "find: cannot stat %s\n", path);
    close(fd);
    return;
  }

  switch(st.type){
  case T_FILE:
    if(strcmp(fmtname(path), findName) == 0) 
      printf("%s\n", path);
//    else
  //    printf("path:%s %d, findName:%s %d\n", fmtname(path),strlen(fmtname(path)), findName, strlen(findName));
    break;

  case T_DIR:
//	printf("is dir\n");
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf("find: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';//p is used to add path after buf, buf is a absolute path
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum == 0) {
        //printf("de inum 0 \n");
	continue;
	}
      memmove(p, de.name, DIRSIZ);//memmove, move de.name info to p,where de.name is char name[255], which indicate the file name
      p[strlen(de.name)] = 0;
    // printf("dir: %s %s %d %d %d\n", buf, p, st.type, st.ino, st.size);
	if(strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0) {
		//printf("is in if\n");
		continue;
	}
	find(buf, findName);
    }
    break;
  }
  close(fd);
}

int
main(int argc, char *argv[])
{

  if(argc < 2){
    //find(".")
	printf("error argc num");
    exit(0);
  }
    find(argv[1], argv[2]);
  exit(0);
}
