#include "handler.hpp"
#include <cstdint>
#include <enet/enet.h>
#include <iostream>
#include <spdlog/spdlog.h>
#include <string>
#include "../utils/textparse.hpp"
#include "data.hpp"
#include <memory>

using namespace Packet;

Handler::Handler(std::shared_ptr<spdlog::logger> logger, Bot *bot) {
  this->logger = logger;
  this->bot = bot;
}

void Handler::Handle(ENetPacket* packet) {
  Data data(packet);
  logger->info("Received {} packet from server", data.Name());
  switch (data.Type) {
    case NET_MESSAGE_HELLO: {
      Utils::TextParse login(fmt::format("mac|{}", bot->loginData.Mac));

      login.add("requestedName", bot->loginData.RequestedName);
      login.add("hash2", bot->loginData.Hash2);
      login.add("hash", bot->loginData.Hash);
      login.add("country", bot->loginData.Country);
      login.add("wk", bot->loginData.Wk);
      login.add("rid", bot->loginData.Rid);
      login.add("game_version", bot->loginData.GameVersion);
      login.add("protocol", bot->loginData.GameProtocol);
      login.add("GDPR", bot->loginData.GDPR);
      login.add("player_age", bot->loginData.PlayerAge);
      login.add("total_playtime", bot->loginData.TotalPlaytime);
      login.add("category", bot->loginData.Category);
      login.add("fhash", bot->loginData.Fhash);
      login.add("lmode", bot->loginData.Lmode);
      login.add("zf", bot->loginData.Zf);
      login.add("deviceVersion", bot->loginData.DeviceVersion);
      login.add("platformID", bot->loginData.PlatformID);
      login.add("klv", bot->loginData.klv);

      if (!bot->loginData.tankIDName.empty()) {
        login.add("tankIDName", bot->loginData.tankIDName);
        login.add("tankIDPass", bot->loginData.tankIDPass);
      }
      
      logger->info("Sending login packet to server");
      bot->SendPacket(Data::Create(NET_MESSAGE_GENERIC, login.Text));
      break;
    }
    case NET_MESSAGE_GENERIC:
      break;
    case NET_MESSAGE_GAME_MESSAGE: {
      // logger->info("Tank type {}", (int)data.TankPkt->Header.Type);

      break;  
    }
    case NET_MESSAGE_GAME_TANK:
      break;
    case NET_MESSAGE_PACKET_FIVE:
      break;
    case NET_MESSAGE_GAME_EVENT: {
      packet->data[packet->dataLength - 1] = '\0';
      logger->info("{}", (char*)(packet->data + sizeof(uint32_t)));
      break;
    }
    default:
      break;
  }
  enet_packet_destroy(packet);
}