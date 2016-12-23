SET(TARGET_NAME SmaliParse)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

if(NOT ANTLR_JAR_LOCATION)
    message(FATAL_ERROR "Missing antlr4.jar location. You can specify it's path using: -DANTLR_JAR_LOCATION=<path>")
endif()

if(NOT ANTLR_RUNTIME_HEADER)
    message(FATAL_ERROR "Missing antlr4 runtime header location. You can specify it's path using: -DANTLR_RUNTIME_HEADER=<path>")
endif()

if(NOT ANTLR_RUNTIME_LIBRARY)
    message(FATAL_ERROR "Missing antlr4 runtime header location. You can specify it's path using: -DANTLR_RUNTIME_LIBRARY=<path>")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-type-limits")

# build Antlr source file
set(smali-GENERATED_SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/SmaliLexer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/SmaliParser.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/SmaliParserBaseListener.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/SmaliParserListener.cpp
        )

foreach(src_file ${smali-GENERATED_SRC})
    set_source_files_properties(
            ${src_file}
            PROPERTIES
            GENERATED TRUE
    )
endforeach()



if((${CMAKE_CURRENT_SOURCE_DIR}/SmaliLexer.g4 IS_NEWER_THAN ${CMAKE_CURRENT_SOURCE_DIR}/generated/SmaliLexer.cpp)
        OR
    (${CMAKE_CURRENT_SOURCE_DIR}/SmaliParser.g4 IS_NEWER_THAN ${CMAKE_CURRENT_SOURCE_DIR}/generated/SmaliParser.cpp))
    message("ANTLR4 parser not exist, generating...")
    set(GENRATEANTLR ON)
    add_custom_target(GenerateParser
            COMMAND
            ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_SOURCE_DIR}/generated/
            COMMAND
            java -jar ${ANTLR_JAR_LOCATION} -Werror -Dlanguage=Cpp -o generated/ SmaliLexer.g4 SmaliParser.g4
            WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
            DEPENDS SmaliLexer.g4 SmaliParser.g4
            )
endif()


set(SmaliParse_src InvalidToken.cpp LiteralTools.cpp SmaliFile.cpp ${smali-GENERATED_SRC})

ADD_LIBRARY(SmaliParse STATIC ${SmaliParse_src})
if(GENRATEANTLR)
    add_dependencies(SmaliParse GenerateParser)
endif()
TARGET_LINK_LIBRARIES(SmaliParse utils ${ANTLR_RUNTIME_LIBRARY})
TARGET_INCLUDE_DIRECTORIES(SmaliParse PUBLIC
        .
        ${ANTLR_RUNTIME_HEADER}
        generated)

add_executable(SmaliParse_Test main.cpp)
target_link_libraries(SmaliParse_Test SmaliParse)

