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
#include "Radar_Data.h"
#define SERV_PORT 51000
#define LISTENCLENTS 5
void data_process(int socketfd,int n){
    //size_t len= sizeof(s);
    radar_data a;
    bzero(&a, sizeof(a));
    char s[72];
    bzero(&s, sizeof(s));
    size_t n1;
        if((n1=recv(socketfd,&s, 72,0))>0){
            memcpy(&a,&s, sizeof(s));
            std::cout<<stoi(std::to_string(a.targetcount))<<std::endl;
            if(a.targetcount>=1&&a.header==0x55AA){
                for(int i=0;i<a.targetcount;i++){
                    std::cout<<"x:"<<a.targets[i].x<<" y:"<<a.targets[i].y<<" distance:"<<a.targets[i].distance<<" angle:"<<a.targets[i].angle<<std::endl;
                }
            }
            bzero(s, sizeof(s));
            bzero(&a, sizeof(a));
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
            std::cout<<"connection from: "<<inet_ntoa(cliaddr.sin_addr)<<" "<<cliaddr.sin_port<<std::endl;
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
