//
// Created by yangwei on 3/27/19.
//
#include "Radar_Data.h"
#include <cstring>
#include <memory>
#include <boost/asio.hpp>
using namespace boost::asio;
namespace Sync {
    class Server{
    public:
        typedef ip::tcp::socket socket_type;
        typedef ip::tcp::endpoint end_type;
        typedef ip::tcp::acceptor acceptor_type;
        typedef std::shared_ptr<socket_type> socket_ptr;
    Server():acceptor(io,end_type(ip::tcp::v4(),5100)){
            start();
    }
    void start(){
        socket_ptr sock(new socket_type(io));
        acceptor.accept(*sock);
        read(sock);
        start();
    }
    void read(socket_ptr sock){
        (*sock).receive(buffer(buff));
        memmove(&a,buff, sizeof(buff));
        //memset(buff,0, sizeof(buff));
        if(a.targetcount>=1&&a.header==0x55AA){
            for(int i=0;i<=a.targetcount-1;i++){
                std::cout<<"x:"<<a.targets[i].x<<" y:"<<a.targets[i].y<<" distance:"<<a.targets[i].distance<<" angle:"<<a.targets[i].angle<<std::endl;
            }
            std::cout<<std::endl;
        }
        read(sock);
    }
    void run(){
        io.run();
    }
    private:
        io_context io;
        acceptor_type acceptor;
        char buff[100];
        radar_data a;
    };
}
using namespace Sync;
int main(){
    try{
    Server s;
    s.run();
    }catch(std::exception& e){
        std::cout<<e.what()<<std::endl;
    }
    return 0;
}