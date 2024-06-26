#include "manager.hpp"
#include "bot.hpp"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"
#include <memory>
#include <string>

using namespace std;

Manager::Manager() {
  // Init item database
}

shared_ptr<Bot> Manager::Add(string ID, string password) {
  auto logger = spdlog::stdout_color_mt(ID);
  logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%^%l%$] %v");
  logger->info("Adding bot: {}", ID);
  bots.insert_or_assign(ID, make_shared<Bot>(logger, ID, password));
  return Get(ID);
}

shared_ptr<Bot> Manager::Get(string ID) {
  auto it = bots.find(ID);
  if (it != bots.end()) {
    return it->second;
  } else {
    return nullptr;
  }
}

void Manager::Remove(string ID) {
  spdlog::info("Removing bot: {}", ID);
  bots.erase(ID);
}