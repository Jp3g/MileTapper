#include <utils/event/Handler.hpp>
#include <utils/event/VEmitter.hpp>
#include <algorithm>

namespace utils
{
    namespace event
    {
        
        Handler::Handler() : _defaultCallback(nullptr)
        {
        }

        Handler::Handler(const std::function<void(const VEvent& event)>& defaultCallback) : _defaultCallback(defaultCallback)
        {
        }

        Handler::~Handler()
        {
            _callbacks.clear();
            for(VEmitter* emitter :  _emitters)
                emitter->_unregister(this);
        }

        void Handler::connect(VEmitter& emitter)
        {
            emitter._register(this);
            _emitters.emplace_back(&emitter);
        }

        void Handler::disconnect(VEmitter& emitter)
        {
            auto it = std::find(_emitters.begin(),_emitters.end(),&emitter);
            if(it != _emitters.end())
            {
                emitter._unregister(this);
                _emitters.erase(it);
            }
        }

        
        ////////////////////// PRIVATE ///////////////
        
        Handler::VFunction::VFunction()
        {
        }

        Handler::VFunction::~VFunction()
        {
        }

        void Handler::_unregister(const VEmitter* emitter)
        {
            _emitters.remove(const_cast<VEmitter*>(emitter));

            auto it = _callbacksByEmitter.find(const_cast<VEmitter*>(emitter));
            if(it != _callbacksByEmitter.end())
                _callbacksByEmitter.erase(it);

        }
    }
}
