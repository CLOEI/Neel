#include "connect.hpp"
#include <enet/enet.h>
#include <spdlog/spdlog.h>
#include <cpr/cpr.h>
#include <string>
#include <thread>
#include "../packet/handler.hpp"

void Connect::Thread(std::shared_ptr<spdlog::logger> logger) {
  this->logger = logger;
  isRunning = true;
  HTTP();
  t = std::move(std::thread(&Connect::Event, this));
}

void Connect::HTTP() {
  logger->info("Getting data from server...");
  cpr::Response r = cpr::Post(cpr::Url("https://www.growtopia1.com/growtopia/server_data.php"), cpr::Header{{"Content-Type", "application/x-www-form-urlencoded"},{"User-Agent", "UbiServices_SDK_2022.Release.9_PC64_ansi_static"}}, cpr::Payload{});
  ParseServerData(r.text);
  if (ServerData.find("maint") != ServerData.end()) {
    logger->error("Server is under maintenance");
    return;
  }
  ENet();
}

void Connect::ENet() {
  if (enet_initialize() < 0) {
    logger->error("ENet failed to initialize");
    return;
  }
  logger->info("Connecting to {} on port {}", ServerData["server"], ServerData["port"]);
  client = enet_host_create(nullptr, 1, 2, 0, 0);
  if (client == nullptr) {
    spdlog::error("ENet failed to create client");
    return;
  }
  client->usingNewPacket = true;
  enet_host_compress_with_range_coder(client);
  client->checksum = enet_crc32;

  ENetAddress address;
  if (enet_address_set_host_ip(&address, ServerData["server"].c_str()) != 0) {
    logger->error("ENet failed to set host IP, retrying...");
    HTTP();
    return;
  }
  address.port = stoi(ServerData["port"]);
  ENetPeer *peer = enet_host_connect(client, &address, 2, 0);
}

void Connect::Event() {
  ENetEvent event;
  while (isRunning) {
    while (enet_host_service(client, &event, 100) > 0) {
      switch (event.type) {
        case ENET_EVENT_TYPE_CONNECT:
          logger->info("Connected to server");
          break;
        case ENET_EVENT_TYPE_RECEIVE:
          Packet::Handler(event.packet);
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

void Connect::ParseServerData(std::string& data) {
  std::string key;
  std::string value;
  bool isKey = true;
  for (char& c : data) {
    if (c == '\n') {
      ServerData[key] = value;
      key.clear();
      value.clear();
      isKey = true;
    } else if (c == '|') {
      isKey = false;
    } else {
      if (isKey) {
        key += c;
      } else {
        value += c;
      }
    }
  }
}