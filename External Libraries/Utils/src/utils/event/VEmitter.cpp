#include <utils/event/VEmitter.hpp>
#include <utils/event/VEvent.hpp>

namespace utils
{
    namespace event
    {
        
        VEmitter::VEmitter()
        {
        }

        VEmitter::~VEmitter()
        {
            for(Handler* h: _handlers)
            {
                h->_unregister(this);
            }
        }

        bool VEmitter::emit(const VEvent& event) const
        {
            return event._dispatch(*this);
        }

        void VEmitter::disconnect(Handler& handler)
        {
            handler.disconnect(*this);
        }


        ////////////////// PRIVATE //////////////

        void VEmitter::_register(const Handler* handler)
        {
            _handlers.emplace_back(const_cast<Handler*>(handler));
        }

        void VEmitter::_unregister(const Handler* handler)
        {
            _handlers.remove(const_cast<Handler*>(handler));
        }

    }
}
