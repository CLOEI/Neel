#pragma once

#include "logindata.hpp"
#include <enet/enet.h>
#include <memory>
#include "spdlog/logger.h"
#include "../connect/connect.hpp"
#include "../itemdat/itemdat.hpp"

class Bot: public Connect {
  public:
    Bot(std::shared_ptr<spdlog::logger> logger, shared_ptr<Itemdat> items_data, string ID, string password = "");
    void Start();
    void Event();
    void Thread();
    void Spoof();
    void SendPacket(ENetPacket* packet);
  public:
    std::shared_ptr<spdlog::logger> logger;
    shared_ptr<Itemdat> items_data;
    LoginData loginData;
    std::thread bot_thread;
};