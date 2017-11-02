#ifndef EVENT_EMITTER_HPP
#define EVENT_EMITTER_HPP

#include <utils/event/VEmitter.hpp>
#include <utils/event/Event.hpp>


namespace utils
{

namespace event
{
    /**
     * \brief This class will be able to deal with all Args events
     **/
    template<typename ... Args>
    class Emitter : public VEmitter
    {
        public:
            Emitter();

            /**
             * \brief automaticly unregister all the handlers
             */
            virtual ~Emitter();

        private:
            virtual bool _checkFamily(unsigned int family)const override;

    };

    /**
     * \brief This class is able to send any kind of event
     */
    class Bus : public VEmitter
    {
        public:
            Bus();

            /**
             * \brief automaticly unregister all the handlers
             */
            virtual ~Bus();

        private:
            virtual bool _checkFamily(unsigned int family)const override;

    };
}
}

#include <utils/event/Emitter.tpl>

#endif
