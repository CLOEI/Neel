#include "data.hpp"
#include "enet/enet.h"
#include <iostream>
#include <memory>
#include <ostream>
#include <spdlog/spdlog.h>
#include <string>

using namespace Packet;

Data::Data(ENetPacket* packet) {
  if (packet->dataLength < 5) {
        return;
  }

  Type = *(ePacketType*)packet->data;

  if (Type != ePacketType::NET_MESSAGE_GAME_MESSAGE) {
      TextPkt = std::make_unique<std::string>(packet->data + sizeof(ePacketType), packet->data + packet->dataLength - 1);
  } else {
      TankPacket* tank = (TankPacket*)packet->data;
      std::cout << "Tank type " << (int)tank->Type << std::endl;
  };
}

Data::~Data() {
  TextPkt.release();
  Type = ePacketType::NET_MESSAGE_UNKNOWN;
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
    case NET_MESSAGE_GAME_EVENT:
      return "NET_MESSAGE_GAME_EVENT";
    default:
      return "UNKNOWN PACKET TYPE";
      break;
  }
}

ENetPacket* Data::Create(ePacketType type, std::string data) {
  ENetPacket* pkt = enet_packet_create(nullptr, sizeof(ePacketType) + data.length() + 1, ENET_PACKET_FLAG_RELIABLE);
  *(ePacketType*)pkt->data = ePacketType::NET_MESSAGE_GENERIC;
  memcpy(pkt->data + sizeof(ePacketType), data.c_str(), data.length());
  return pkt;
}
