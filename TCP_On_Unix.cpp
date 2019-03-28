//
// Created by yangwei on 3/28/19.
//
#include "Radar_Data.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <strings.h>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#define MYPORT 5100
using namespace std;
namespace Unix_TCP {
    class Server {
    public:
        Server():
        socketfd(0)
        {
            my_addr.sin_family=AF_INET;
            my_addr.sin_addr.s_addr=INADDR_ANY;
            my_addr.sin_port=htons(MYPORT);
            bzero(&(my_addr.sin_zero), sizeof(my_addr.sin_zero));
            if((socketfd=socket(AF_INET,SOCK_STREAM,0))==-1){
                perror("socket");exit(1);
            }
            if(bind(socketfd,(sockaddr*)(&my_addr), sizeof(my_addr))==-1)
            {perror("bind");exit(1);}
            if(listen(socketfd,5)==-1){
                perror("listen");exit(1);
            }
        }
        void accept_connection(){
            addr_in_length= sizeof(their_addr);
            if ((new_fd = accept(socketfd, (sockaddr *) (&their_addr), (socklen_t *)(&addr_in_length))) == -1) {
                perror("accept");exit(1);
            }
            while(true) {
                    if(recv(new_fd,buff, sizeof(buff),0)==-1){
                        perror("recv");i++;continue;
                    }
                    cout<<"connection from: "<<inet_ntoa(their_addr.sin_addr)<<"his port is "<<ntohs(their_addr.sin_port)<<endl;
                    memcpy(&a,buff, sizeof(buff));
                    if(a.targetcount>=1&&a.header==0x55AA){
                        for(int i=0;i<a.targetcount;i++){
                            std::cout<<"x:"<<a.targets[i].x<<" y:"<<a.targets[i].y<<" distance:"<<a.targets[i].distance<<" angle:"<<a.targets[i].angle<<std::endl;
                        }
                    }
                    bzero(buff, sizeof(buff));
                    bzero(&a, sizeof(a));
                    i++;
                }

        }
    ~Server(){
            close(new_fd);
        }
    private:
    sockaddr_in my_addr;
    sockaddr_in their_addr;
    char buff[100];
    radar_data a;
    int socketfd;
    int addr_in_length;
    int new_fd;
    int i=0;
    };
}
int main(){
    Unix_TCP::Server s;
    s.accept_connection();
    return 0;
}