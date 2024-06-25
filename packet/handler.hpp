#pragma once

#include "data.hpp"
#include <enet/enet.h>
#include <memory>
#include <spdlog/spdlog.h>
#include "../bot/bot.hpp"
#include "spdlog/logger.h"

namespace Packet {
  class Handler {
    public:
      Handler(std::shared_ptr<spdlog::logger> logger, Bot *bot);
      void Handle(ENetPacket* packet);
    public:
      std::shared_ptr<spdlog::logger> logger;
      Bot *bot;
  };
}
