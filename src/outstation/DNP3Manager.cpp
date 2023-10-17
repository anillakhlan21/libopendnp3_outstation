
#include "opendnp3/DNP3Manager.h"

#include "../include/DNP3ManagerImpl.h"

#include <utility>

namespace opendnp3
{

DNP3Manager::DNP3Manager(uint32_t concurrencyHint,
                         std::shared_ptr<ILogHandler> handler,
                         std::function<void(uint32_t)> onThreadStart,
                         std::function<void(uint32_t)> onThreadExit)
    : impl(std::make_unique<DNP3ManagerImpl>(concurrencyHint, handler, onThreadStart, onThreadExit))
{
}

DNP3Manager::~DNP3Manager() = default;

void DNP3Manager::Shutdown()
{
    impl->Shutdown();
}

std::shared_ptr<IChannel> DNP3Manager::AddTCPClient(const std::string& id,
                                                    const LogLevels& levels,
                                                    const ChannelRetry& retry,
                                                    const std::vector<IPEndpoint>& hosts,
                                                    const std::string& local,
                                                    std::shared_ptr<IChannelListener> listener)
{
    return this->impl->AddTCPClient(id, levels, retry, hosts, local, std::move(listener));
}

std::shared_ptr<IChannel> DNP3Manager::AddTCPServer(const std::string& id,
                                                    const LogLevels& levels,
                                                    ServerAcceptMode mode,
                                                    const IPEndpoint& endpoint,
                                                    std::shared_ptr<IChannelListener> listener)
{
    return this->impl->AddTCPServer(id, levels, mode, endpoint, std::move(listener));
}


std::shared_ptr<IListener> DNP3Manager::CreateListener(std::string loggerid,
                                                       const LogLevels& loglevel,
                                                       const IPEndpoint& endpoint,
                                                       const std::shared_ptr<IListenCallbacks>& callbacks)
{
    return impl->CreateListener(std::move(loggerid), loglevel, endpoint, callbacks);
}

std::shared_ptr<IListener> DNP3Manager::CreateListener(std::string loggerid,
                                                       const LogLevels& loglevel,
                                                       const IPEndpoint& endpoint,
                                                       const TLSConfig& config,
                                                       const std::shared_ptr<IListenCallbacks>& callbacks)
{
    return impl->CreateListener(std::move(loggerid), loglevel, endpoint, config, callbacks);
}

} // namespace opendnp3
