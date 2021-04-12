/**
 * @copyright Copyright (C) 2021  Conor Begley
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#include "RemoteNotifyReceive.h"

#include <exception>

namespace RemoteNotify {
int err_msg(int num, std::string msg) {
  if (num < 0) {
    std::cerr << "Error with " << msg << "\n"
              << "Error Code:" << errno << "\n";
    exit(1);
  }
  return 0;
}

std::string GetStringFromCommand(std::string cmd) {
  std::string data;
  FILE *stream;
  const int MaxBuffer = 256;
  char buffer[MaxBuffer];
  cmd.append(" 2>&1");

  stream = popen(cmd.c_str(), "r");

  if (stream) {
    while (!feof(stream))
      if (fgets(buffer, MaxBuffer, stream) != NULL) data.append(buffer);
    pclose(stream);
  }
  return data;
}

Receive::Receive(int port, bool check_env, std::string title,
                 std::string image) {
  // Setup notify send command
  if (check_env == true) {
    char *env = getenv("XDG_CURRENT_DESKTOP");
    if (env != NULL) {
      if (std::strcmp(env, "ubuntu:GNOME") == 0) {
        this->command = "notify-send -u critical ";
      }
    }
  }
  this->title = title;
  this->command =
      this->command + this->space + this->quote + this->title + this->quote;
  this->image = image;

  // Setup socket
  this->receive_fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (this->receive_fd == 0) {
    err_msg(-1, "socket_creation");
  }
  this->address.sin_family = AF_INET;
  this->address.sin_addr.s_addr = htons(INADDR_ANY);
  this->address.sin_port = htons(port);
  int opt = 1;
  int setup =
      setsockopt(this->receive_fd, SOL_SOCKET,
                 SO_REUSEADDR | SO_REUSEPORT | SO_BROADCAST, &opt, sizeof(opt));
  if (setup) {
    err_msg(-1, "socket_creation");
  }
  int binding = bind(this->receive_fd, (struct sockaddr *)&(this->address),
                     sizeof(this->address));
  err_msg(binding, "socket_bind");
}  // namespace RemoteNotify
Receive::~Receive() {
  shutdown(this->receive_fd, SHUT_RDWR);
  close(this->receive_fd);
}

void Receive::run() {
  std::cout.flush();
  std::memset(this->buffer, 0, sizeof(this->buffer));
  std::memset(&this->Broadcast_address, 0, sizeof(Broadcast_address));
  int read_value =
      recvfrom(this->receive_fd, this->buffer, 1024, MSG_DONTWAIT,
               (struct sockaddr *)&this->Broadcast_address,
               reinterpret_cast<socklen_t *>(&this->Broadcast_len));
  if (read_value > 0) {
    this->buffer[read_value] = '\0';
    std::string out = this->command + this->space + this->quote + this->buffer +
                      this->quote + this->space + this->middle + this->space +
                      this->image;
    system(out.c_str());
  }
}
};  // namespace RemoteNotify
