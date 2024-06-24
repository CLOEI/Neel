#include "random.hpp"
#include <string>

using namespace Utils;
using namespace std;

string Random::HEX(size_t length) {
  string chars = "0123456789ABCDEF";
  string res;

  for (size_t i = 0; i < length; i++) {
    res += chars[rand() % chars.size()];
  }
  return res;
}

string Random::MAC() {
  string res;

  for (size_t i = 0; i < 6; i++) {
    res += HEX(2);
    if (i < 5) {
      res += ":";
    }
  }

  return res;
}