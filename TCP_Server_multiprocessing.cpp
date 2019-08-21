//
// Created by yangwei on 8/21/19.
//
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <strings.h>
#include <arpa/inet.h>
#include <cstring>
#include <strings.h>
#include <iostream>
#include <unistd.h>
#include <string>
#define SERV_PORT 51000
#define LISTENCLENTS 5
void data_process(int socketfd,int n){
    char s[7];
    size_t len= sizeof(s);
    size_t n1;
        if((n1=read(socketfd,&s, len))>0){
            std::cout<<s<<std::endl;
        }else if(n1<0&&errno==EINTR)
            ;
        else if(n1<0)
            std::cerr<<"read error"<<std::endl;
}


int main(){
    sockaddr_in cliaddr,servaddr;
    pid_t child_pid;
    auto listenfd=socket(AF_INET,SOCK_STREAM,0);
    if(listenfd==-1)
        exit(-1);
    else{
        servaddr.sin_family=AF_INET;
        servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
        servaddr.sin_port=htons(SERV_PORT);
        if(bind(listenfd, (sockaddr*)&servaddr, sizeof(servaddr))==-1){
            exit(1);
        }
        listen(listenfd,LISTENCLENTS);
        for(;;){
            socklen_t clilen= sizeof(cliaddr);
            //std::cout<<listenfd<<std::endl;
            auto connfd=accept(listenfd,(sockaddr*)&cliaddr, &clilen);
           std::cout<<connfd<<std::endl;
            std::cout<<inet_ntoa(cliaddr.sin_addr)<<" "<<cliaddr.sin_port<<std::endl;
            if(connfd<0){
                if(errno==EINTR)
                    continue;
                else
                    std::cerr<<"accept error"<<std::endl;
            }else{
                if(child_pid=fork()==0){
                    close(listenfd);
                    data_process(connfd,100);
                    exit(0);
                }
                close(connfd);
            }
        }
    }
}
