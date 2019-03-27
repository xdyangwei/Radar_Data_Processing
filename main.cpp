#include <iostream>
#include <boost/asio.hpp>
#include <cstring>
#include <memory>
#include <vector>
#include "Radar_Data.h"
using namespace boost::asio;
class Server{
    using end_type=ip::tcp::endpoint;
    using acceptor_type=ip::tcp::acceptor;
    using socket_type=ip::tcp::socket;
    using socket_ptr=std::shared_ptr<socket_type>;
    using buff=char[100];
public:
    Server():acceptor(io,end_type(ip::tcp::v4(),5100))
    {
        start();
    }
    void start(){
        /*std::cout<<i<<std::endl;
        i++;*/
        socket_ptr sock(new socket_type(io));
        acceptor.async_accept(*sock,[this,sock](const boost::system::error_code& ec){
            (*sock).async_read_some(buffer(buff1),[this,sock](const boost::system::error_code& ec,std::size_t size){
                read_handler(sock,ec,size);
            }
            );
            start();
        });
    }
    void read_handler(socket_ptr sock,const boost::system::error_code& ec,std::size_t size){
        std::cout<< sizeof(buff1)<<std::endl;
        /*for(auto xx:buff1)
            std::cout<<xx<<std::endl;*/
        memmove(&a,buff1, sizeof(buff1));
        //memset(buff1,0, sizeof(buff1));
        //(*sock).send(buffer("I have received your message!"));
        memset(buff1,0, sizeof(buff1));
        //std::cout<<std::hex<<a.header<<std::endl;
        std::cout<<std::to_string(a.address)<<std::endl;
        if(a.targetcount>=1&&a.header==0x55AA){
            for(int i=0;i<=a.targetcount-1;i++){
                std::cout<<"x:"<<a.targets[i].x<<" y:"<<a.targets[i].y<<" distance:"<<a.targets[i].distance<<" angle:"<<a.targets[i].angle<<std::endl;
            }
        }
        (*sock).async_read_some(buffer(buff1),std::bind(&Server::read_handler,this,sock,ec,size));
    }
    void run(){
        io.run();
    }
private:
    io_context io;
    acceptor_type acceptor;
    buff buff1;
    radar_data a;
    //int i=0;
};

int main() {
    try {
       Server s;
       s.run();
    }catch (std::exception &e){
        std::cout<<e.what()<<std::endl;
    }
    return 0;
}