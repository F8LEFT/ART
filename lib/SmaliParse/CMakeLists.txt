SET(TARGET_NAME SmaliParse)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions -Wno-undef -Wno-overloaded-virtual")

if(NOT ANTLR_JAR_LOCATION)
    message(FATAL_ERROR "Missing antlr4.jar location. You can specify it's path using: -DANTLR_JAR_LOCATION=<path>")
endif()

if(NOT ANTLR_RUNTIME_HEADER)
    message(FATAL_ERROR "Missing antlr4 runtime header location. You can specify it's path using: -DANTLR_RUNTIME_HEADER=<path>")
endif()

if(NOT ANTLR_RUNTIME_LIBRARY)
    message(FATAL_ERROR "Missing antlr4 runtime header location. You can specify it's path using: -DANTLR_RUNTIME_LIBRARY=<path>")
endif()

# build Antlr source file
file(GLOB smali-GENERATED_SRC "generated/*")

foreach(src_file ${smali-GENERATED_SRC})
    set_source_files_properties(
            ${src_file}
            PROPERTIES
            GENERATED TRUE
    )
endforeach()

add_custom_target(GenerateParser
        COMMAND
        ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_SOURCE_DIR}/generated/
        COMMAND
        java -jar ${ANTLR_JAR_LOCATION} -Werror -Dlanguage=Cpp -o generated/ SmaliLexer.g4 SmaliParser.g4
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        DEPENDS SmaliLexer.g4 SmaliParser.g4
        )

#FILE(GLOB_RECURSE ART_HEADER ${ART_INCLUDE_DIR}/${TARGET_NAME}/*.h Ops/*.h)

set(SmaliParse_src InvalidToken.cpp LiteralTools.cpp ${smali-GENERATED_SRC})

ADD_LIBRARY(SmaliParse STATIC ${SmaliParse_src})
add_dependencies(SmaliParse GenerateParser)
TARGET_LINK_LIBRARIES(SmaliParse utils ${ANTLR_RUNTIME_LIBRARY}/libantlr4-runtime.a)
TARGET_INCLUDE_DIRECTORIES(SmaliParse PUBLIC
        ${ANTLR_RUNTIME_HEADER}
        generated)

add_executable(SmaliParse_Test main.cpp)
target_link_libraries(SmaliParse_Test SmaliParse)

