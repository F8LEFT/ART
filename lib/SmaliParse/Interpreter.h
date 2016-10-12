//===- Interpreter.h - ART-LEX ----------------------------------*- c++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// The file defines use lexer to parse smali file and generate ast.
//
//===----------------------------------------------------------------------===//


#ifndef PROJECT_INTERPRETER_H
#define PROJECT_INTERPRETER_H

#include <iostream>
#include "Parser.hpp"
#include "SmaliAst/SmaliClass.h"
#include "Lexer.h"

namespace Analysis {
    class Interpreter
    {
    public:
        Interpreter();

        /**
         * Run parser. Results are stored inside.
         * \returns 0 on success, 1 on failure
         */
        int parse();

        /**
         * Switch scanner input stream. Default is standard input (std::cin).
         * It will also reset AST.
         */
        void switchInputStream (std::istream *is,SmaliClass *pClass);
        /**
         * print AST message
         */
        void print();
        friend class Lexer;

    private:
        void setClassDefine(int flag,std::string& type);
        void setSuperDefine (std::string& super);
        void setSourceDefine(std::string& source);

        void addField(std::string& name, int flag, std::string& type);
        void addMethod(std::string& name, int flag, std::string& type,
                       std::vector<std::string> &args);
        void setCurMethodRegSize(int size);
        void addOpcode(OpCode* code);
        void endMethod();
    private:
        Lexer mLexer;

        SmaliClass* mClass;
        SmaliMethod* mCurMethod;

    private:
        // Parser
        bool consumeLine();
    };
}



#endif //PROJECT_INTERPRETER_H
