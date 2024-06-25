#pragma once

#include "logindata.hpp"
#include <enet/enet.h>
#include <memory>
#include "../connect/connect.hpp"
#include "spdlog/logger.h"

class Bot: public Connect {
  public:
    Bot(std::shared_ptr<spdlog::logger> logger, string ID, string password = "");
    void Start();
    void Event();
    void Thread();
    void Spoof();
    void SendPacket(ENetPacket* packet);
  public:
    std::shared_ptr<spdlog::logger> logger;
    LoginData loginData;
    std::thread bot_thread;
};