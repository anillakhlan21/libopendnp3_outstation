
#ifndef OPENDNP3_RESOURCEMANAGER_H
#define OPENDNP3_RESOURCEMANAGER_H

#include "IResourceManager.h"

#include <memory>
#include <mutex>
#include <set>

namespace opendnp3
{

class ResourceManager final : public IResourceManager
{

public:
    static std::shared_ptr<ResourceManager> Create()
    {
        return std::make_shared<ResourceManager>();
    }

    void Detach(const std::shared_ptr<IResource>& resource) final;

    void Shutdown();

    template<class R, class T> std::shared_ptr<R> Bind(const T& create)
    {
        std::lock_guard<std::mutex> lock(this->mutex);

        if (this->is_shutting_down)
        {
            return nullptr;
        }
        else
        {
            auto item = create();
            if (item)
            {
                this->resources.insert(item);
            }
            return item;
        }
    }

private:
    std::mutex mutex;
    bool is_shutting_down = false;
    std::set<std::shared_ptr<IResource>> resources;
};

} // namespace opendnp3

#endif
