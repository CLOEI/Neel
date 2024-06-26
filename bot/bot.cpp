#include <memory>
#include <spdlog/spdlog.h>
#include <string>
#include "bot.hpp"
#include "../utils/random.hpp"
#include "../utils/hash.hpp"
#include "../utils/klv.hpp"
#include "../packet/handler.hpp"

using namespace Utils;
using namespace std;

Bot::Bot(shared_ptr<spdlog::logger> logger, shared_ptr<Itemdat> items_data, string ID, string password) {
  this->logger = logger;
  this->items_data = items_data;
  if (!password.empty()) {
    loginData.tankIDName = ID;
    loginData.tankIDPass = password;
  }
  loginData.RequestedName = ID;
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

void Bot::SendPacket(ENetPacket* packet) {
  enet_peer_send(peer, 0, packet);
}

void Bot::Spoof() {
  loginData.Mac = Random::MAC();
  loginData.Wk = Random::HEX(32);
  loginData.Rid = Random::HEX(32);
  loginData.Hash = to_string(Hash::HashString(fmt::format("{}RT", loginData.Mac).c_str(), 0));
  loginData.Hash2 = to_string(Hash::HashString(fmt::format("{}RT", Random::HEX(16)).c_str(), 0));
  loginData.klv = Utils::generate_klv(std::stoi(loginData.GameProtocol), loginData.GameVersion, loginData.Rid);
  logger->info("Spoofed data: Mac: {}, Wk: {}, Rid: {}, Hash: {}, Hash2: {}, KLV: {}", loginData.Mac, loginData.Wk, loginData.Rid, loginData.Hash, loginData.Hash2, loginData.klv);
}