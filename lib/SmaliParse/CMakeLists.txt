SET(TARGET_NAME SmaliParse)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions")


set(SRC_FILE SmaliLexer.cpp SmaliParser.cpp Interpreter.cpp)

FILE(GLOB_RECURSE ART_HEADER ${ART_INCLUDE_DIR}/${TARGET_NAME}/*.h Ops/*.h)
aux_source_directory(SmaliAst SMALIAST_SRC)
INCLUDE_DIRECTORIES(.)

ADD_EXECUTABLE(SmaliParse_Test main.cpp ${SRC_FILE} ${ART_HEADER} ${SMALIAST_SRC})
TARGET_LINK_LIBRARIES(SmaliParse_Test utils)

ADD_LIBRARY(SmaliParse STATIC ${SRC_FILE} ${ART_HEADER} ${SMALIAST_SRC})
TARGET_LINK_LIBRARIES(SmaliParse utils)
TARGET_INCLUDE_DIRECTORIES(SmaliParse PUBLIC .)
