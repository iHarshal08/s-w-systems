#include<sys/stat.h>
#include<sys/types.h>
#include<stdio.h>
int main(){
    if(mkfifo("myfifo1",0777)==-1){
        printf("not created");
        return 1;
    }
    else{
        printf("created");
    }
return 0;
}