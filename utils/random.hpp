#pragma once

#include <cstddef>
#include <string>

namespace Utils {
  class Random {
    public:
      static std::string HEX(size_t length) {
        std::string chars = "0123456789ABCDEF";
        std::string res;
        for (size_t i = 0; i < length; i++) {
          res += chars[rand() % chars.size()];
        }
        return res;
      }
      
      static std::string MAC() {
        std::string res;
        for (size_t i = 0; i < 6; i++) {
          res += HEX(2);
          if (i < 5) {
            res += ":";
          }
        }
        return res;
      }
  };
}