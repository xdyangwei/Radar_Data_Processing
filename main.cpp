#include <iostream>
#include <boost/asio.hpp>
#include <cstring>
using namespace boost::asio;
struct target_info{
int distance;
int16_t angle;
int y;
int x;
int16_t speed;
int8_t power;
};

struct radar_data
{
int16_t header;
int8_t address;
int16_t length;
int8_t targetcount;
target_info targets[30];
int8_t sum;
};

int main() {
    try {
        io_context io;
        ip::tcp::endpoint port(ip::tcp::v4(), 5100);
        ip::tcp::acceptor acceptor(io, port);
        char buff[1024];
        radar_data a;
        ip::tcp::socket sock(io);
        acceptor.accept(sock);
        int i=0;
        while (true) {
            //std::cout << "client:" << sock.remote_endpoint().address() <<" "<< sock.remote_endpoint().port()<<std::endl;
            sock.async_read_some(buffer(buff),[&](const boost::system::error_code &ec,std::size_t size){
                memcpy(&a,buff,72);
                sock.send(buffer("I have received your message!"));
                if(a.targetcount>=1&&a.header==0x55AA){
                    for(int i=0;i<=a.targetcount-1;i++){
                        std::cout<<"x:"<<a.targets[i].x<<" y:"<<a.targets[i].y<<" distance:"<<a.targets[i].distance<<" angle:"<<a.targets[i].angle<<std::endl;
                    }
                }

            });
            //memset(buff,0,72);
            //sock.send(buffer("I have received your message!"));
           /*sock.read_some(buffer(buff));
           std::cout<<buff<<std::endl;
           sock.send(buffer("hello,i am server"));*/
        }
    }catch (std::exception &e){
        std::cout<<e.what()<<std::endl;
    }
    return 0;
}