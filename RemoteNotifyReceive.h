/**
 * @file RemoteNotifyReceive.h
 * @brief For listening and receiving notifications from
 * `Notify::Broadcast`
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

#ifndef REMOTENOTIFYRECEIVE_H_
#define REMOTENOTIFYRECEIVE_H_

#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <string>

namespace RemoteNotify {
/**
 * @brief Error handler for socket connections
 *
 * @param num The result of socket function
 * @param msg Message to be printed also default error message
 */
int err_msg(int num, std::string msg);

/**
 * @brief Return result from system command as a string
 * @param cmd The system command
 */
std::string GetStringFromCommand(std::string cmd);

/**
 * @brief A `Notify::NotifyReceive` for listening and receiving notifications
 * from `Notify::NotifyBroadcast`
 *
 */
class Receive {
 private:
  int receive_fd;              ///< Receive socket file descriptor
  struct sockaddr_in address,  ///<  Receive address
      Broadcast_address;  ///<  Specific address details for received messages
  int addr_len = sizeof(address);  ///<  Length of address structure
  int Broadcast_len =
      sizeof(Broadcast_address);  ///<  Length of Broadcast address structure
  std::string command = "notify-send -t 0";  ///< Notify-send command
                                             ///< and flags
  std::string title;                         ///< Title of Notify Send message
  std::string image;                         ///< Absolute path of image
  std::string middle = "--icon";
  char quote = '"';
  char space = ' ';

 public:
  char buffer[1024];  ///< Returned result from broadcasted message
  /**
   * @brief Constructor for `Notify::NotifyReceive`
   *
   * @param port Port number to listen on (default is 121121)
   * @param ignore Boolean to ignore location where Notify::NotifyReceive is
   * running
   * @param check_env If `true` will check current desktop environment and
   * change notify-send command if needed
   */
  explicit Receive(int port = 121121, bool check_env = true,
                   std::string title = "Remote Notify Send Receive",
                   std::string image = "");
  ~Receive();

  /**
   * @brief Sets the `Notify::NotifyReceive` to start listening
   */
  void run();
};
}  // namespace RemoteNotify
#endif  // SRC_NOTIFICATIONS_Receive_H_
