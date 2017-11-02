set(INCROOT ${INCROOT}/json)
set(SRCROOT ${SRCROOT}/json)


set(BisonOutputSrc ${SRCROOT}/Parser.cpp)
set(BisonOutputInc ${INCROOT}/Parser.hpp)
set(BisonOutputExtra ${INCROOT}/stack.hh)
set(FlexOutputSrc ${SRCROOT}/Lexer.cpp)

if(UTILS_BUILD_PARSER)
    FIND_PACKAGE(BISON REQUIRED)
    IF(BISON_FOUND)
        ADD_CUSTOM_COMMAND(
            OUTPUT ${BisonOutputSrc} ${BisonOutputInc} ${BisonOutputExtra}
            COMMAND ${BISON_EXECUTABLE} --output=${BisonOutputSrc} --defines=${BisonOutputInc} ${SRCROOT}/Parser.yy
            COMMAND sed -i "s/\"Parser.hpp\"/<utils\\/json\\/Parser.hpp>/g" ${BisonOutputSrc}
            COMMAND mv ${SRCROOT}/stack.hh ${INCROOT}/stack.hh

            COMMENT "Generating Parser file from with bison"
            VERBATIM
        )

        ADD_CUSTOM_COMMAND(
            OUTPUT ${INCROOT}/stack.hh
            COMMENT "Move Generated files"
       )
        

    else()
        message( SEND_ERROR "Bison is required" )
    ENDIF()

    FIND_PACKAGE(FLEX REQUIRED)
    IF(FLEX_FOUND)
        ADD_CUSTOM_COMMAND(
            OUTPUT ${FlexOutputSrc}
            COMMAND ${FLEX_EXECUTABLE} --outfile=${FlexOutputSrc} ${SRCROOT}/Lexer.lex
            COMMENT "Generating lexer file with flex"
            VERBATIM
        )
    else()
        message( SEND_ERROR "Flex is required" )
    ENDIF()

endif()

#ROOT files
set(FILES_SRC
    ${SRCROOT}/Array.cpp
    ${SRCROOT}/Driver.cpp
    ${SRCROOT}/Object.cpp
    ${SRCROOT}/Scanner.cpp
    ${SRCROOT}/Value.cpp
    ${BisonOutputSrc}
    ${FlexOutputSrc}
)
set(FILES_HEADER
    ${INCROOT}/Array.hpp
    ${INCROOT}/Driver.hpp
    ${INCROOT}/FlexLexer.hpp
    ${INCROOT}/Object.hpp
    ${INCROOT}/Scanner.hpp
    ${INCROOT}/Value.hpp
    ${BisonOutputInc}
    ${BisonOutputExtra}
)

build_library("${PROJECT_NAME}-json"
    SOURCES ${FILES_SRC} ${FILES_HEADER}
    TYPE SHARED
    DEPENDS ${PROJECT_NAME}
)

