#pragma once

#include "bot.hpp"
#include <memory>
#include <string>
#include <unordered_map>
#include "../itemdat/itemdat.hpp"


class Manager {
  public:
    Manager();
    std::shared_ptr<Bot> Add(std::string ID, std::string password = "");
    std::shared_ptr<Bot> Get(std::string ID);
    void Remove(std::string ID);
  public:
    std::unordered_map<std::string, std::shared_ptr<Bot>> bots;
    std::shared_ptr<Itemdat> items_data;
};