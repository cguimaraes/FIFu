/** Brief: Plugin Protocol Interface
 *  Copyright (C) 2016  Carlos Guimaraes <cguimaraes@av.it.pt>
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
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PLUGIN_PROTOCOL__HPP_
#define PLUGIN_PROTOCOL__HPP_

#include "metamessage.hpp"
#include "concurrent-blocking-queue.hpp"

#include <atomic>
#include <map>
#include <string>


class PluginProtocol
{
private:
  ConcurrentBlockingQueue<MetaMessage*>& _send_to_core;

protected:
  std::atomic<bool> isRunning;
  ConcurrentBlockingQueue<MetaMessage*> _msg_to_send;

public:
  PluginProtocol(ConcurrentBlockingQueue<MetaMessage*>& queue)
    : _send_to_core(queue),
      isRunning(false)
  { };

  virtual ~PluginProtocol()
  { };

  virtual void start() = 0;
  virtual void stop() = 0;

  virtual std::string getProtocol() = 0;
  virtual std::string installMapping(std::string uri) = 0;

  void receivedMessage(MetaMessage* msg)
  {
    _send_to_core.push(msg);
  }

  void sendMessage(MetaMessage* msg)
  {
    _msg_to_send.push(msg);
  }
};

#endif /* PLUGIN_PROTOCOL__HPP_ */

