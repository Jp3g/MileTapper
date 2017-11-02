set(INCROOT ${INCROOT}/functional)
set(SRCROOT ${SRCROOT}/functional)

list(APPEND FILES_SRC
    ${SRCROOT}/functional.cpp
)
set(FILES_SRC "${FILES_SRC}" PARENT_SCOPE)

list(APPEND FILES_HEADER
    ${INCROOT}/functional.hpp
    ${INCROOT}/functional.tpl
)
set(FILES_HEADER "${FILES_HEADER}" PARENT_SCOPE)

