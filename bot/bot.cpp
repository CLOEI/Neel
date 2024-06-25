#include <spdlog/spdlog.h>
#include <string>
#include "bot.hpp"
#include "../utils/random.hpp"
#include "../utils/hash.hpp"
#include "../packet/handler.hpp"

using namespace Utils;
using namespace std;

Bot::Bot(shared_ptr<spdlog::logger> logger, string ID, string password) {
  this->logger = logger;
  loginData.ID = ID;
  loginData.Password = password;
  if (password.empty()) {}
  Spoof();
  Start();
}

void Bot::Start() {
  isRunning = true;
  Run(logger);
  connect_thread = std::move(std::thread(&Bot::Event, this));
  bot_thread = std::move(thread(&Bot::Thread, this));
}

void Bot::Event() {
  ENetEvent event;
  Packet::Handler packet(logger, this);
  while (isRunning) {
    while (enet_host_service(client, &event, 100) > 0) {
      switch (event.type) {
        case ENET_EVENT_TYPE_CONNECT:
          logger->info("Connected to server");
          break;
        case ENET_EVENT_TYPE_RECEIVE:
          packet.Handle(event.packet);
          break;
        case ENET_EVENT_TYPE_DISCONNECT:
          logger->info("Disconnected from server, reconnecting...");
          HTTP();
          break;
        case ENET_EVENT_TYPE_NONE:
          break;
      }
    }
  }
}

void Bot::Thread() {
  while (isRunning) {
    // TBA
  }
}

void Bot::Spoof() {
  loginData.Mac = Random::MAC();
  loginData.Wk = Random::HEX(32);
  loginData.Rid = Random::HEX(32);
  loginData.Hash = to_string(Hash::HashString(fmt::format("{}RT", loginData.Mac).c_str(), 0));
  loginData.Hash2 = to_string(Hash::HashString(fmt::format("{}RT", Random::HEX(16)).c_str(), 0));
  logger->info("Spoofed data: Mac: {}, Wk: {}, Rid: {}, Hash: {}, Hash2: {}", loginData.Mac, loginData.Wk, loginData.Rid, loginData.Hash, loginData.Hash2);
}