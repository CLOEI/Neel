#pragma once

#include <cstddef>
#include <string>

namespace Utils {
  class Random {
    public:
      static std::string HEX(size_t length);
      static std::string MAC();
  };
}