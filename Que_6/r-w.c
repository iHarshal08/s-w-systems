#include<unistd.h>
int main(){
    char buffer[1024];
    ssize_t bytesRead;
    bytesRead = read(0, buffer, sizeof(buffer)-1);
    if(bytesRead>0){
        buffer[bytesRead]='\0';
        write(1, buffer, bytesRead);
    }
    return 0;
}