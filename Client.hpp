#pragma once
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


template <typename Message, typename To>
auto client (Message msg, const char* ipaddress, const int& port) -> To {
      throw std::runtime_error("not defined!");
}


auto te (const string& msg, const char* ipaddress, const int& port) -> const char*;
