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
#include <memory>
#include "SmaliParser.hpp"
#include "SmaliAst/SmaliClass.h"
#include "SmaliLexer.h"

//#define DEBUG

namespace Analysis {
    class Interpreter
    {
    public:
        Interpreter();
        ~Interpreter ();
        /**
         * Run parser. Results are stored inside.
         * \returns 0 on success, 1 on failure
         */
        int parse();
        void analysis();
        /**
         * Switch scanner input stream. Default is standard input (std::cin).
         * It will also reset AST.
         */
        void switchInputStream (std::istream *is,SmaliClass *pClass);
        StringPool* stringPool();
        /**
         * print AST message
         */
        void print();
        friend class SmaliLexer;
        friend class SmaliParser;

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
        // scan and anslysis method ops,
        void analysisMethod(SmaliMethod* method);

    private:
        std::shared_ptr<SmaliLexer> mLexer;
        std::shared_ptr<SmaliParser> mParser;

        SmaliClass* mClass;
        SmaliMethod* mCurMethod;
        StringPool* mStringPool;

    private:
        long long int parseLongInt(std::string s);
    };
}



#endif //PROJECT_INTERPRETER_H
