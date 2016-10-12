//===- SmaliMethod.h - ART-LEX ---------------------------------*- c++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// SmaliMethod store Method message
//
//===----------------------------------------------------------------------===//


#ifndef SMALIPARSER_SMALIMETHOD_H
#define SMALIPARSER_SMALIMETHOD_H
#include <string>
#include <vector>
#include <list>
#include <utils/StringPool.hpp>
#include "Ops/OpCode.h"

namespace Analysis {
    class SmaliClass;

    class SmaliMethod
    {
    public:
        void setStringPool (StringPool *sp);
        StringPool* stringPool();

        void setName (std::string &name);
        std::string name();
        void setFlag (int flag);
        int flag();
        void setType (std::string &type);
        std::string type();
        void setParent (SmaliClass *parent);
        SmaliClass* parent();

        void setArgs(std::vector<std::string> &args);
        void setArgs(std::vector<int> &args);
        std::vector<std::string> args();
        bool argsEqual(std::vector<std::string> &args);
        bool argsEqual(std::vector<int> &args);
//        bool operator==(SmaliMethod &f);

        void setRegSize(int regsize);
        int regSize ();

        std::list<OpCode*>  mInsList;

        void clear ();

        void printAst (std::vector<std::string> &v);
    private:
        StringPool* mStringPool = nullptr;

        int mName;
        int mType;
        std::vector<int> mArgs;
        int mFlag = 0;
        SmaliClass* mParent;

        // method define
        int mRegSize = 0;

        // extra message
    };
}


#endif //SMALIPARSER_SMALIMETHOD_H
