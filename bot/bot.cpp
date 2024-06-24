#include "bot.hpp"
#include "../utils/random.hpp"

Bot::Bot() {}

void Bot::Spoof() {
  loginData.Mac = Utils::Random::MAC();
  loginData.Wk = Utils::Random::HEX(32);
  loginData.Rid = Utils::Random::HEX(32);
}