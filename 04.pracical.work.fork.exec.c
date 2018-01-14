#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
int main (){
int x=fork();
if (x==0){
printf("ps -ef\n\n");
char *args[]={"/bin/ps","-ef",NULL};
execvp('/bin/ps",args);
}
int y=fork();
if (y==0){
printf ("free -h \n\n");
char *args[]={"free","-h",NULL};
execvp("free",args);
}
return 0;
}
