#pragma once
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;


class cppSockets
{
public:
      cppSockets (const char* address, int port)
      {
            auto one = [&]{
                  addrinfo hints
                  {
                        .ai_family = AF_UNSPEC, // or AF_INET, AF_INET6
                        .ai_socktype = SOCK_STREAM,
                        .ai_flags = AI_PASSIVE // fill in my IP for me
                  };

                  addrinfo* servinfo;
                  
                  
                  
                  getaddrinfo(address, to_string(port).c_str(), &hints, &servinfo);
                  
                  int sock = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
                  
                  connect(sock, servinfo->ai_addr, servinfo->ai_addrlen);
                  
                  char buf[100];
                  
                  size_t numbytes = recv(sock, buf, 99, 0);
                  
                  buf[numbytes] = '\0';
                  
                  cout << buf << endl;
                  
                  
                  
                  freeaddrinfo(servinfo);
            };
            auto two = [&]{
                  addrinfo info, *res;
                  info.ai_family = AF_UNSPEC;
                  info.ai_socktype = SOCK_STREAM;
                  info.ai_flags = AI_PASSIVE;
                  info.ai_protocol = IPPROTO_TCP;
                  
                  getaddrinfo(address, to_string(port).c_str(), &info, &res);
                  
                  int sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
                  
                  connect(sock, res->ai_addr, res->ai_addrlen);
                  
                  freeaddrinfo(res);
                  
                  const char* msg = "hejsan från klienten";
                  
                  send(sock, msg, 99, 0);
                  
                  char buf[100];
                  
                  int numbytes = recv(sock, buf, 99, 0);
                  
                  cout << buf << endl;
                  
                  close (sock);
                  
                  
   
            };
            two();
      }
};
