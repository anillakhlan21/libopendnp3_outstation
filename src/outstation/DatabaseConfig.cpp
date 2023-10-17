#include "opendnp3/outstation/DatabaseConfig.h"

namespace opendnp3
{

template<class T> void initialize(std::map<uint16_t, T>& map, uint16_t count)
{
    for (uint16_t i = 0; i < count; ++i)
    {
        map[i] = {};
    }
}

DatabaseConfig::DatabaseConfig(uint16_t all_types)
{
    initialize(this->binary_input, all_types);
    initialize(this->double_binary, all_types);
    initialize(this->analog_input, all_types);
    initialize(this->counter, all_types);
    initialize(this->frozen_counter, all_types);
    initialize(this->binary_output_status, all_types);
    initialize(this->analog_output_status, all_types);
    initialize(this->time_and_interval, all_types);
    initialize(this->octet_string, all_types);
};

} // namespace opendnp3
