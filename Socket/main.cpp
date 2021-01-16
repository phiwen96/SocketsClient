#include "cppSockets.hpp"
#include "Email.hpp"
#include "Client.hpp"
#include "Authenticator.hpp"
#include <Test.hpp>
using namespace nlohmann;

//#define concat(first, second) first second

#define IP "92.34.141.114"
#define PORT_get_accounts 54001
#define PORT_get_decks 54002
#define PORT_set_accounts 54003
#define PORT_set_decks 54004

#include <PhLib/PhLib.hpp>


template <typename... T>
ostream& operator<< (ostream& os, const tuple<T...>& t)
{
      apply([&os](auto&&... args){((os << args << endl), ...);}, t);
      return os;
}



template <typename... T>
const char* concat_spaces (T... rest) {
      size_t size = sizeof...(T);
      size += (strlen(rest) + ...);
      char* res = new char[size];
      ((strcat(res, rest), strcat(res, " ")), ...);
      return res;
}
template <typename... T>
const char* concat (T... rest) {
      size_t size = (strlen(rest) + ...);
      char* res = new char[size];
      ((strcat(res, rest)), ...);
      return res;
}

struct Deck
{
      Deck (const json& j) : m_decks (j["Decks"]), m_cards (j["Cards"])
      {
            
      }
      
private:
      json m_decks;
      json m_cards;
};





const char* callServer (const char* msg, const char* ip, const int& port) {
      const char* msg0 = "";
      while (strcmp(msg0, "") == 0) {
            msg0 = client<const char*, const char*>(msg, ip, port);
      }
      return msg0;
}



int main(int argc, char** argv){

      
      auto getDataWithUserID = [](int userID){
            const char* msg0 = "";
            while (strcmp(msg0, "") == 0) {
                  msg0 = client<const char*, const char*>(to_string(userID).c_str(), IP, PORT_get_decks);
            }
            return msg0;
      };
      
      auto getUserIDWithEmailAndPassword = [](const char* email, const char* password){
            string s = email;
            s += " ";
            s += password;
            const char* msg0 = "";
            while (strcmp(msg0, "") == 0) {
                  msg0 = client<const char*, const char*>(s.c_str(), IP, PORT_get_accounts);
            }
            return msg0;
      };
      
      auto setDataWithUserID = [](int userID, const char* method, const char* data) {
            return callServer(concat_spaces(to_string(userID).c_str(), method, data), IP, PORT_set_decks);
      };
      
//      cout << concat("hej", "kuk") << endl;

      
//      cout << getUserIDWithEmailAndPassword ("a", "a") << endl;
      
      
//      cout << getDataWithUserID (0) << endl;
//      cout << setDataWithUserID(0, "SET, )
      
      
      
      
      json j1 = R"({"Cards":[],"Decks":[{"title":"kuk","Cards":[],"Decks":[{"title":"fitta","Cards":[],"Decks":[]},{"title":"mechanics","Cards":[],"Decks":[]}]},{"title":"chemistry","Cards":[],"Decks":[]}]})"_json;
      const char* data = j1.dump().c_str();
      cout << j1.dump(4) << endl;
      
      setDataWithUserID(0, "SET", j1.dump().c_str());
      
      
      
      
//      cout << getDataWithUserID (0) << endl;
//      cout << j1.dump(4) << endl;
      
//      Test t(4);
//      cout << t.i << endl;
      

      

      
      return 0;
      

}
