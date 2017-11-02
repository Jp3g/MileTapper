set(INCROOT ${INCROOT}/event)
set(SRCROOT ${SRCROOT}/event)

list(APPEND FILES_SRC
    ${SRCROOT}/Emitter.cpp
    ${SRCROOT}/Handler.cpp
    ${SRCROOT}/VEmitter.cpp
    ${SRCROOT}/VEvent.cpp
)
set(FILES_SRC "${FILES_SRC}" PARENT_SCOPE)

list(APPEND FILES_HEADER
    ${INCROOT}/Emitter.hpp
    ${INCROOT}/Emitter.tpl
    ${INCROOT}/Event.hpp
    ${INCROOT}/Event.tpl
    ${INCROOT}/Handler.hpp
    ${INCROOT}/Handler.tpl
    ${INCROOT}/VEmitter.hpp
    ${INCROOT}/VEmitter.tpl
    ${INCROOT}/VEvent.hpp

)
set(FILES_HEADER "${FILES_HEADER}" PARENT_SCOPE)

