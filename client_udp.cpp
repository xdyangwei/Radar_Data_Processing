#include"radar.h"
#include<boost/asio.hpp>
#include<iostream>
#include<thread>
#include<chrono>
using namespace boost::asio;
using namespace std;
class client_udp{
using socket_type=ip::udp::socket;
using socket_ptr=shared_ptr<socket_type>;
using endpoint_type=ip::udp::endpoint;
public:
client_udp():
endpoint(ip::address::from_string("127.0.0.1"),5100),
sp(new socket_type(io))
{
        (*sp).open(ip::udp::v4());
        start();
}
void run(){
    io.run();
}
private:
io_context io;
socket_ptr sp;
endpoint_type endpoint;
char buff[100];
char buff2[100];
radar_data a;
void start(){    
    memcpy(buff,&a,sizeof(a));
    (*sp).send_to(buffer(buff),endpoint);
    cout<<"send successfully"<<endl;
    (*sp).receive_from(buffer(buff2),endpoint);
    cout<<buff2<<endl;
    this_thread::sleep_for(std::chrono::microseconds(100));
    start();
}
};
int main(){
client_udp c;
c.run();
}