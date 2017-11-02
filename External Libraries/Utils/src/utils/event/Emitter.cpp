#include <utils/event/Emitter.hpp>

namespace utils
{
namespace event
{
    Bus::Bus()
    {
    }

    Bus::~Bus()
    {
    }

    bool Bus::_checkFamily(unsigned int)const
    {
        return true;
    }
}
}
