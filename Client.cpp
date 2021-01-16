#include "Client.hpp"



template <>
auto client (const char* msg, const char* ipaddress, const int& port) -> const char* {
      addrinfo info, *res;
      info.ai_family = AF_UNSPEC;
      info.ai_socktype = SOCK_STREAM;
      info.ai_flags = AI_PASSIVE;
      info.ai_protocol = IPPROTO_TCP;
      
      getaddrinfo(ipaddress, to_string(port).c_str(), &info, &res);
      
      int sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
      
      connect(sock, res->ai_addr, res->ai_addrlen);
      
      freeaddrinfo(res);
      
      //            const char* toClient = "hejsan från klienten";
      
      send(sock, msg, strlen(msg) + 1, 0);
      
      char buf[4096];
      
      read (sock , buf, 4096);
      
      
      close (sock);
      
      
      return buf;
}

template <>
auto client (const char* msg, const char* ipaddress, const int& port) -> std::string {
      return std::string (client<const char*, const char*>(msg, ipaddress, port));
}

template <>
auto client (const char* msg, const char* ipaddress, const int& port) -> nlohmann::json {
      return nlohmann::json (nlohmann::json::parse(client<std::string, const char*>(msg, ipaddress, port)));
}


auto te (const string& msg, const char* ipaddress, const int& port) -> const char* {
      addrinfo info, *res;
      info.ai_family = AF_UNSPEC;
      info.ai_socktype = SOCK_STREAM;
      info.ai_flags = AI_PASSIVE;
      info.ai_protocol = IPPROTO_TCP;
      
      getaddrinfo(ipaddress, to_string(port).c_str(), &info, &res);
      
      int sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
      
      connect(sock, res->ai_addr, res->ai_addrlen);
      
      freeaddrinfo(res);
      
      //            const char* toClient = "hejsan från klienten";
      
      send(sock, &msg, msg.size() + 1, 0);
      
      char buf[4096];
      
      read (sock , buf, 4096);
      
      
      close (sock);
      
      
      return buf;
}
