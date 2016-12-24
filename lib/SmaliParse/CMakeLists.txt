SET(TARGET_NAME SmaliParse)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-type-limits")
add_subdirectory(antlr4.6)

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
            java -jar antlr4.6/antlr-4.6-complete.jar -Werror -Dlanguage=Cpp -o generated/ SmaliLexer.g4 SmaliParser.g4
            WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
            DEPENDS SmaliLexer.g4 SmaliParser.g4
            )
endif()


set(SmaliParse_src InvalidToken.cpp LiteralTools.cpp SmaliFile.cpp ${smali-GENERATED_SRC})

ADD_LIBRARY(SmaliParse STATIC ${SmaliParse_src})
if(GENRATEANTLR)
    add_dependencies(SmaliParse GenerateParser)
endif()
TARGET_LINK_LIBRARIES(SmaliParse utils antlr4_static)
TARGET_INCLUDE_DIRECTORIES(SmaliParse PUBLIC
        .
        antlr4.6/runtime/src
        generated)

add_executable(SmaliParse_Test main.cpp)
target_link_libraries(SmaliParse_Test SmaliParse)

