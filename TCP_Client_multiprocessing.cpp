#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<iostream>
#include<unistd.h>
#include<arpa/inet.h>
#include<string>
#include<strings.h>
#define MYPORT 51000
#define CLIENTS 5
void send_message(int sockfd){
    std::string s="yangwei";
    write(sockfd,&s,sizeof(s));
}
int main(){
    sockaddr_in servaddr;
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(MYPORT);
    servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    std::cout<<inet_ntoa(servaddr.sin_addr)<<" "<<servaddr.sin_port<<std::endl;
    //std::cout<<inet_ntoa(servaddr.sin_addr)<<std::endl;
    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    std::cout<<sockfd<<std::endl;
    int x=connect(sockfd,(sockaddr*)&servaddr,sizeof(servaddr));
    std::cout<<inet_ntoa(servaddr.sin_addr)<<" "<<servaddr.sin_port<<std::endl;
    sockaddr_in s;
    socklen_t s_len=sizeof(s);
    getpeername(sockfd,(sockaddr*)&s,&s_len);
    std::cout<<inet_ntoa(s.sin_addr)<<" "<<s.sin_port<<std::endl;
    send_message(sockfd);
    close(sockfd);
    return 0;
}