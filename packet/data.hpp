#pragma once

#include <cstdint>
#include <memory>
#include <stdint.h>
#include <enet/enet.h>
#include <string>

enum ePacketType : int32_t {
  NET_MESSAGE_UNKNOWN,
  NET_MESSAGE_HELLO,
  NET_MESSAGE_GENERIC,
  NET_MESSAGE_GAME_MESSAGE,
  NET_MESSAGE_GAME_TANK,
  NET_MESSAGE_PACKET_FIVE,
  NET_MESSAGE_GAME_EVENT,
};

enum eTankPacketType : uint8_t {
  NET_TANK_UNKNOWN = 0,
  NET_TANK_VARIANT = 1,
  NET_TANK_SET_TILE = 3,
  NET_TANK_WORLD = 4,
  NET_TANK_UPDATE_TILE = 5,
  NET_TANK_UPDATE = 16,
};

struct TankPacket {
  eTankPacketType Type;
  uint8_t idk;
  uint8_t idk2;
  uint8_t idk3;
  uint32_t NetID;
  uint8_t idk4;
  uint32_t offset;
  uint32_t idk5;
  uint32_t Main;
  float XPosition;
  float YPosition;
  float XVelocity;
  float YVelocity;
  float idk6;
  uint32_t TileX;
  uint32_t TileY;
  uint32_t ExtendedDataLength;
};

namespace Packet {
  class Data {
    public:
      Data(ENetPacket* packet);
      ~Data();
      std::string Name();
      static ENetPacket* Create(ePacketType type, std::string data); 
    public:
      ePacketType Type;
      std::unique_ptr<std::string> TextPkt;
  };
}
