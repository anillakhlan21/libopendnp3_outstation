

#ifndef OPENDNP3_DNP3MANAGERIMPL_H
#define OPENDNP3_DNP3MANAGERIMPL_H

#include "ResourceManager.h"

#include "opendnp3/channel/ChannelRetry.h"
#include "opendnp3/channel/IChannel.h"
#include "opendnp3/channel/IChannelListener.h"
#include "opendnp3/channel/IListener.h"
#include "opendnp3/channel/IPEndpoint.h"
#include "opendnp3/gen/ServerAcceptMode.h"
#include "opendnp3/logging/Logger.h"
#include "opendnp3/master/IListenCallbacks.h"
#include "opendnp3/util/Uncopyable.h"

#include <exe4cpp/asio/ThreadPool.h>

namespace opendnp3
{

class DNP3ManagerImpl : private Uncopyable
{

public:
    DNP3ManagerImpl(uint32_t concurrencyHint,
                    std::shared_ptr<opendnp3::ILogHandler> handler,
                    std::function<void(uint32_t)> onThreadStart,
                    std::function<void(uint32_t)> onThreadExit);

    ~DNP3ManagerImpl();

    void Shutdown();

    std::shared_ptr<IChannel> AddTCPClient(const std::string& id,
                                           const opendnp3::LogLevels& levels,
                                           const ChannelRetry& retry,
                                           const std::vector<IPEndpoint>& hosts,
                                           const std::string& local,
                                           std::shared_ptr<IChannelListener> listener);

    std::shared_ptr<IChannel> AddTCPServer(const std::string& id,
                                           const opendnp3::LogLevels& levels,
                                           ServerAcceptMode mode,
                                           const IPEndpoint& endpoint,
                                           std::shared_ptr<IChannelListener> listener);

    std::shared_ptr<IListener> CreateListener(std::string loggerid,
                                              const opendnp3::LogLevels& levels,
                                              const IPEndpoint& endpoint,
                                              const std::shared_ptr<IListenCallbacks>& callbacks);

    std::shared_ptr<IListener> CreateListener(std::string loggerid,
                                              const opendnp3::LogLevels& levels,
                                              const IPEndpoint& endpoint,
                                              const TLSConfig& config,
                                              const std::shared_ptr<IListenCallbacks>& callbacks);

private:
    Logger logger;
    const std::shared_ptr<asio::io_context> io;
    exe4cpp::ThreadPool threadpool;
    std::shared_ptr<ResourceManager> resources;
};

} // namespace opendnp3

#endif
