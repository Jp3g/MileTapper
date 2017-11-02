set(INCROOT ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME})
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/${PROJECT_NAME})

set(FILES_SRC "")
set(FILES_HEADER "")

add_subdirectory(event)
add_subdirectory(functional)
add_subdirectory(log)

list(APPEND FILES_SRC
    ${SRCROOT}/plot.cpp
    ${SRCROOT}/string.cpp
    ${SRCROOT}/sys.cpp
    ${SRCROOT}/thread.cpp
    ${SRCROOT}/memory.cpp
)

list(APPEND FILES_HEADER
    ${INCROOT}/event.hpp
    ${INCROOT}/functional.hpp
    ${INCROOT}/hash.hpp
    ${INCROOT}/log.hpp
    ${INCROOT}/json.hpp

    ${INCROOT}/maths.hpp
    ${INCROOT}/maths.tpl
    ${INCROOT}/plot.hpp
    ${INCROOT}/plot.tpl
    ${INCROOT}/string.hpp
    ${INCROOT}/string.tpl
    ${INCROOT}/sys.hpp
    ${INCROOT}/sys.tpl
    ${INCROOT}/thread.hpp
    ${INCROOT}/thread.tpl
    ${INCROOT}/memory.hpp
    ${INCROOT}/memory.tpl
)


build_library(${PROJECT_NAME}
    SOURCES ${FILES_SRC} ${FILES_HEADER}
    TYPE SHARED
    EXTERNAL_LIBS ${LIBS}
)

deploy(
    FILES ${INCROOT}
    DESTINATION include

)

if(UTILS_BUILD_JSON)
    add_subdirectory(json)
endif()
