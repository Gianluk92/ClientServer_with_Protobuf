#include "test.hh"
#include <iostream>
#include <string>
#include "test.pb.h"



myproto server::sum(myproto a, myproto b){
    myproto c;
    c.set_a(a.a()+b.a());
    c.set_b(a.b()+b.b());
    c.set_c(a.c()+b.c());
    return c;
}

int server::prod(int a, int b){
    return a * b;
}

int main(int argc, char** argv) {
    
    server* Server;
    
    if(argc > 1)
        Server = new server(argv[1]);
    else 
        Server =new server(); 

	Server->server_init();    

    while (1) 
    {     
        Server->server_accept(Server->getDescriptor());
        Server->request_handler();
        std::cout<<"End Server"<<std::endl;
        Server->accept_close(Server->getSessionDescriptor());
    }

    Server->server_close();

    return 0;
}

