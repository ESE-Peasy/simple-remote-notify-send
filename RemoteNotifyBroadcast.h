/**
 * @file RemoteNotifyBroadcast.h
 * @brief Broadcast for sending notifications to `RemoteNotify:Receive`
 *
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

#ifndef REMOTENOTIFYBROADCAST_H_
#define REMOTENOTIFYBROADCAST_H_
#include <string>

#include "RemoteNotify.h"

namespace RemoteNotify {
/**
 * @brief A Broadcast to send messages to `RemoteNotify::Receive`
 *
 */
class Broadcast {
 private:
  int broadcast_fd;            ///< Socket which the Broadcast is bound to
  struct sockaddr_in address;  ///< Broadcast address structure
  char* target_ip;             ///< Broadcast IP address

 public:
  /**
   * @brief Constructor for `RemoteNotify::Broadcast`
   *
   * @param port Port number to listen on (default is 121121)
   * @param ip Broadcast address (default is 255.255.255.255)
   */
  explicit Broadcast(int port = 121121,
                     char* ip = const_cast<char*>("255.255.255.255"));
  ~Broadcast();

  /**
   * @brief Broadcasts message to ip
   * @param msg The message to be sent
   */
  void sendMessage(std::string msg);
};
}  // namespace RemoteNotify
#endif  // REMOTENOTIFYBROADCAST_H_
