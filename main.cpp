#include "enet/enet.h"
#include <cstring>
#include <iostream>
#include <sstream>
#include <map>
#include <cpr/cpr.h>
#include <stdint.h>
#include <string>

using namespace std;

map<string, string> mappedData;

void parseServerData(string& data) {
  stringstream ss(data);
  vector <string> tokens;
  string token;

  while(getline(ss, token, '\n')) {
    tokens.push_back(token);
  }

  for(const string& token: tokens) {
    size_t delimiter = token.find("|");
    if (delimiter != string::npos) {
      string key = token.substr(0, delimiter);
      string value = token.substr(delimiter + 1);
      mappedData[key] = value;
    }
  }
}

void connectENET() {
  cout << "Connecting to " + mappedData["server"] + " on port " + mappedData["port"] << endl;
  ENetHost* client = enet_host_create(nullptr, 1, 2, 0, 0);
  if (client == nullptr) {
    cout << "ENet failed to create client" << endl;
  }
  client->usingNewPacket = true;
  enet_host_compress_with_range_coder(client);
  client->checksum = enet_crc32;

  ENetAddress address;
  enet_address_set_host_ip(&address, mappedData["server"].c_str());
  address.port = stoi(mappedData["port"]);

  ENetPeer *peer = enet_host_connect(client, &address, 2, 0);
  ENetEvent event;

  while (true) {
    while (enet_host_service(client, &event, 100) > 0) {
      switch (event.type) {
        case ENET_EVENT_TYPE_CONNECT:
          cout << "Connected to server" << endl;
          break;
        case ENET_EVENT_TYPE_RECEIVE:
          cout << "Received data from server" << endl;
          break;
        case ENET_EVENT_TYPE_DISCONNECT:
          cout << "Disconnected from server" << endl;
          break;
        case ENET_EVENT_TYPE_NONE:
          break;
      }
    }
  }
}

void connectHTTP() {
  cout << "Getting data from server..." << endl;
  cpr::Response r = cpr::Post(cpr::Url("https://www.growtopia1.com/growtopia/server_data.php"), cpr::Header{{"Content-Type", "application/x-www-form-urlencoded"},{"User-Agent", "UbiServices_SDK_2022.Release.9_PC64_ansi_static"}}, cpr::Payload{});
  parseServerData(r.text);
  cout << "Server data parsed" << endl;
  if (mappedData.find("maint") != mappedData.end()) {
    cout << "Server is under maintenance" << endl;
  }
  if (enet_initialize() < 0) {
    cout << "ENet failed to initialize" << endl;
  }
  connectENET();
}

int main() {
  connectHTTP();
  return 0;
}
