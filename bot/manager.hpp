#pragma once

#include "bot.hpp"
#include <map>
#include <memory>
#include <string>

class Manager {
  public:
    std::shared_ptr<Bot> Add(std::string ID, std::string password = "");
    std::shared_ptr<Bot> Get(std::string ID);
    void Remove(std::string ID);
  public:
    std::map<std::string, std::unique_ptr<Bot>> bots;
};