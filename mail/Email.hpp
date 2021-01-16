#pragma once
#include <curl/curl.h>

#define FROM    "philip.sve@hotmail.com"
#define TO      "philipius96@gmail.com"
#define CC      "philip.sve@hotmail.com"

static const char *payload_text[] = {
      "Date: Mon, 29 Nov 2010 21:54:29 +1100\r\n",
      "To: " TO "\r\n",
      "From: " FROM " (Example User)\r\n",
      "Cc: " CC " (Another example User)\r\n",
      "Message-ID: <dcd7cb36-11db-487a-9f3a-e652a9458efd@"
      "rfcpedant.example.org>\r\n",
      "Subject: SMTP TLS example message\r\n",
      "\r\n", /* empty line to divide headers from body, see RFC5322 */
      "The body of the message starts here.\r\n",
      "\r\n",
      "It could be a lot of lines, could be MIME encoded, whatever.\r\n",
      "Check RFC5322.\r\n",
      NULL
};

struct upload_status {
      int lines_read;
};

static size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp)
{
      struct upload_status *upload_ctx = (struct upload_status *)userp;
      const char *data;
      
      if((size == 0) || (nmemb == 0) || ((size*nmemb) < 1)) {
            return 0;
      }
      
      data = payload_text[upload_ctx->lines_read];
      
      if(data) {
            size_t len = strlen(data);
            memcpy(ptr, data, len);
            upload_ctx->lines_read++;
            
            return len;
      }
      
      return 0;
}

void send2();


void sendEmail();







#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;


class Email
{
public:
      Email (const char* address, int port)
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
