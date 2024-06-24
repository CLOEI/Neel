#include "manager.hpp"
#include "bot.hpp"
#include <memory>
#include <string>

using namespace std;

shared_ptr<Bot> Manager::Add(string ID, string password) {}

shared_ptr<Bot> Manager::Get(string ID) {}

void Manager::Remove(string ID) {
  bots.erase(ID);
}