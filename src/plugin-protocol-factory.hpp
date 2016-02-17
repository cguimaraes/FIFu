/** Brief: Plugin Protocol Factory
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

#ifndef PLUGIN_PROTOCOL_FACTORY__HPP_
#define PLUGIN_PROTOCOL_FACTORY__HPP_

#include "plugin-protocol.hpp"

#include <dlfcn.h>
#include <boost/shared_ptr.hpp>
#include <boost/lockfree/queue.hpp>

class PluginProtocolFactory {
public:
  static boost::shared_ptr<PluginProtocol> createPlugin(std::string path, boost::lockfree::queue<MetaMessage*>& queue)
  {
    void* handle = dlopen(path.c_str(), RTLD_LAZY);

    PluginProtocol* (*create)(boost::lockfree::queue<MetaMessage*>&)
      = (PluginProtocol* (*)(boost::lockfree::queue<MetaMessage*>&)) dlsym(handle, "create_plugin_object");
    PluginProtocol* plugin = create(queue);

    return boost::shared_ptr<PluginProtocol>(plugin);
  }
};

#endif /* PLUGIN_PROTOCOL_FACTORY__HPP_ */

