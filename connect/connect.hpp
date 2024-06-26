#ifndef CONNECT_H
#define CONNECT_H

#include "spdlog/logger.h"
#include <enet/enet.h>
#include <map>
#include <memory>
#include <string>
#include <thread>

class Connect {
  public:
    void HTTP();
    void ENet();
    void Run(std::shared_ptr<spdlog::logger> logger);
  private:
    void ParseServerData(std::string& data);
  public:
    std::map<std::string, std::string> ServerData;
    std::shared_ptr<spdlog::logger> logger;
    std::thread connect_thread;
    bool isRunning;
    ENetHost* client;
    ENetPeer* peer;
};

#endif