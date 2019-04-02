#include"radar.h"
#include<vector>
#include<iostream>
#include<boost/asio.hpp>
#include<cstring>
#include<chrono>
#include<thread>
using namespace std;
using namespace boost::asio;
int main(){
    io_context io;
    //ip::tcp::endpoint port(ip::address::from_string("127.0.0.1"),5100);
    ip::tcp::resolver r(io);
    ip::tcp::resolver::query q("localhost","5100");
    auto it=r.resolve(q);
    decltype(it) end;
    boost::system::error_code ec=error::host_not_found;
    target_info info;
    radar_data a;
    for(auto xx:a.targets)
    xx=info;
    ip::tcp::socket sock(io);
    for(;ec&&it!=end;it++){
        sock.close();
      sock.connect(*it,ec);  
    }
    //sock.connect(port);
    cout<<sock.remote_endpoint().address()<<endl;
    int i=0;
    while(i<=10){
    //sock.send(buffer("hello,i am client"));
    char buff[72];
    char buff2[30];
    cout<<sizeof(a)<<endl;
    memcpy(buff,&a,sizeof(a));
    //ip::tcp::acceptor aa;
    sock.send(buffer(buff));
    this_thread::sleep_for(std::chrono::microseconds(100));
    io.run();
    i++;
    }
    return 0;
}