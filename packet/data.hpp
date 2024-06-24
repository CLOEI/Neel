#pragma once

#include <stdint.h>
#include <enet/enet.h>
#include <string>

enum ePacketType : int32_t {
  NET_MESSAGE_HELLO = 1,
  NET_MESSAGE_GENERIC,
  NET_MESSAGE_GAME_MESSAGE,
  NET_MESSAGE_GAME_TANK,
  NET_MESSAGE_PACKET_FIVE,
  NET_MESSAGE_PACKET_SIX,
};

namespace Packet {
  class Data {
    public:
      Data(ENetPacket* packet);
      std::string Name();
    public:
      ePacketType Type;
  };
}
