#pragma once

#include "data.hpp"
#include <enet/enet.h>
#include <spdlog/spdlog.h>

namespace Packet {
  static void Handler(ENetPacket *packet) {
    Data data(packet);
    spdlog::info("Received {} packet from server", data.Name());
    switch (data.Type) {
      case NET_MESSAGE_HELLO:
        break;
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
}
