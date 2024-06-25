#pragma once

#include <string>

namespace Utils {
  class TextParse {
    public:
      TextParse(std::string text) {
        Text = text;
      }
      void add(std::string key, std::string value) {
        Text += "\n" + key + "|" + value;
      }
    public:
      std::string Text;
  };
}