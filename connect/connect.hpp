#ifndef CONNECT_H
#define CONNECT_H

#include <map>
#include <string>

class Connect {
  public:
    Connect(std::string ID, std::string password = "");
    void Run();
    void HTTP();
    void ENet();
  private:
    void ParseServerData(std::string& data);
  public:
    std::map<std::string, std::string> ServerData;
};

#endif