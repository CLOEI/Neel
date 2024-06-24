#include "data.hpp"
#include <spdlog/spdlog.h>
#include <string>

using namespace Packet;

Data::Data(ENetPacket* packet) {
  if (packet->dataLength < 5) {
    spdlog::error("Packet is too small");
    return;
  }

  Type = *(ePacketType*)packet->data;
}

std::string Data::Name() {
  switch (Type) {
    case NET_MESSAGE_HELLO:
      return "NET_MESSAGE_HELLO";
    case NET_MESSAGE_GENERIC:
      return "NET_MESSAGE_GENERIC";
    case NET_MESSAGE_GAME_MESSAGE:
      return "NET_MESSAGE_GAME_MESSAGE";
    case NET_MESSAGE_GAME_TANK:
      return "NET_MESSAGE_GAME_TANK";
    case NET_MESSAGE_PACKET_FIVE:
      return "NET_MESSAGE_PACKET_FIVE";
    case NET_MESSAGE_PACKET_SIX:
      return "NET_MESSAGE_PACKET_SIX";
    default:
      return "UNKNOWN PACKET TYPE";
      break;
  }
}
