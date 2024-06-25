#include "handler.hpp"
#include <enet/enet.h>
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

      login.add("requestedName", "BraveDuck");
      login.add("hash2", bot->loginData.Hash2);
      login.add("hash", bot->loginData.Hash);
      login.add("country", bot->loginData.Country);
      login.add("wk", bot->loginData.Wk);
      login.add("rid", bot->loginData.Rid);
      login.add("game_version", bot->loginData.GameVersion);
      login.add("protocol", bot->loginData.GameProtocol);
      login.add("GDPR", "1");
      login.add("player_age", "25");
      login.add("total_playtime", "0");
      login.add("category", "_-5100");
      login.add("fhash", "-716928004");
      login.add("lmode", "0");
      login.add("zf", "493085170");
      login.add("deviceVersion", "0");
      login.add("platformID", "0,1,1");
      login.add("klv", bot->loginData.klv);
      
      logger->info("Sending login packet to server");
      bot->SendPacket(Data::Create(NET_MESSAGE_GENERIC, login.Text));
      break;
    }
    case NET_MESSAGE_GENERIC:
      break;
    case NET_MESSAGE_GAME_MESSAGE:
      break;
    case NET_MESSAGE_GAME_TANK:
      break;
    case NET_MESSAGE_PACKET_FIVE:
      break;
    case NET_MESSAGE_PACKET_SIX:
      break;
    default:
      break;
  }
  enet_packet_destroy(packet);
}