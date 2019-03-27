#include<vector>
#include<iostream>
#include<boost/asio.hpp>
#include<cstring>
using namespace std;
using namespace boost::asio;
struct target_info{
int distance=10;
int16_t angle=30;
int y=6;
int x=8;
int16_t speed=100;
int8_t power=20;
};
struct radar_data
{
int16_t header=0x55AA;
int8_t address=0x12;
int16_t length=0x0204;
int8_t targetcount=0x3;
target_info targets[3];
int8_t sum=0x11;
};

int main(){
    io_context io;
    ip::tcp::endpoint port(ip::address::from_string("127.0.0.1"),5100);
    target_info info;
    radar_data a;
    for(auto xx:a.targets)
    xx=info;
    ip::tcp::socket sock(io);
    sock.connect(port);
    int i=0;
    while(true){
    //sock.send(buffer("hello,i am client"));
    char buff[72];
    char buff2[30];
    cout<<sizeof(a)<<endl;
    memcpy(buff,&a,sizeof(a));
    sock.async_send(buffer(buff),[&](const boost::system::error_code &ec,std::size_t size){
        memset(&buff,0,72);
        sock.receive(buffer(buff2));
        cout<<buff2<<endl;    
    });
    io.run();
    //i++;
    }
    return 0;
}