#include "test.hh"
#include <iostream>
#include <string>
#include <stdio.h>
#include "test.pb.h"

int main(int argc, char** argv) {
      
  client* Client;

  if(argc > 2)
    if(atoi(argv[2])>65565){
      std::cout<<"numero di porta non valida\n";
      exit(1);
    }
    else
      Client = new client(argv[1],argv[2]);
  else
    Client = new client();

  myproto prt,ptr,r;
  
  prt.set_a(6);
  prt.clear_b();
  prt.set_b(1);
  prt.set_c(3);
  ptr.set_a(1);
  ptr.set_b(2);
  ptr.set_c(3);

  Client->client_init();    

  Client->client_connect(Client->getDescriptor());

  r = Client->sum(prt,ptr);
  std::cout<<r.a()<<std::endl;
  std::cout<<r.b()<<std::endl;
  std::cout<<r.c()<<std::endl;
  
  //std::cout<<"Somma:"<<<<std::endl;
  std::cout<<"Prodotto:"<<Client->prod(0,2)<<std::endl;

  std::cout<<"End client\n";    
  Client->client_close();

  return 0;
}