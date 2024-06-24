#include "connect/connect.hpp"

int main() {
  Connect connection("ID", "password");
  connection.Run();
  return 0;
}
