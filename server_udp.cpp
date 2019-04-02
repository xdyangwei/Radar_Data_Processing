//
// Created by yangwei on 4/2/19.
//
#include "Radar_Data.h"
#include <boost/asio.hpp>
#include <memory>
using namespace boost::asio;
using namespace std;

class Server_UDP{
    using socket_type=ip::udp::socket;
    using endpoint_type=ip::udp::endpoint;
    using socket_ptr=shared_ptr<socket_type>;
public:
    Server_UDP():
    sp(sp1)
    {
        start();
    }
    void run(){
        io.run();
    }
private:
    void start(){
        (*sp).receive_from(buffer(buff),endpoint);
        memcpy(&a,buff, sizeof(buff));
        bzero(buff, sizeof(buff));
        if(a.targetcount>=1&&a.header==0x55AA){
            for(int i=0;i<=a.targetcount-1;i++){
                std::cout<<"x:"<<a.targets[i].x<<" y:"<<a.targets[i].y<<" distance:"<<a.targets[i].distance<<" angle:"<<a.targets[i].angle<<std::endl;
            }
        }
        (*sp).send_to(buffer("i have received your message"),endpoint);
        cout<<endl;
        start();
    }
    int i;
    io_context io;
    endpoint_type endpoint;
    char buff[100];
    socket_type * sp1=new socket_type(io,endpoint_type(ip::udp::v4(),5100));
    socket_ptr sp;
    radar_data a;
};
int main(){
    Server_UDP s;
    s.run();

    return 0;
}

