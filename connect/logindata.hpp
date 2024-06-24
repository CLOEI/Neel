#pragma once

#include <string>

using namespace std;

struct LoginData {
  string ID;
  string Password;
  string GameVersion = "4.59";
  string GameProtocol = "208";
  string Meta;
  string Mac;
  string Wk;
  string Hash;
  string Rid;  
};