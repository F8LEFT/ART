//===- SmaliClass.h - ART-LEX -----------------------------------*- c++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// SmaliClass store class message
//
//===----------------------------------------------------------------------===//


#ifndef SMALIPARSER_SMALICLASS_H
#define SMALIPARSER_SMALICLASS_H

#include <string>
#include <map>
#include <list>
#include <vector>
#include "SmaliField.h"
#include "SmaliMethod.h"
#include <utils/StringPool.hpp>

namespace Analysis {
    class SmaliField;
    class SmaliMethod;

    class SmaliClass
    {
    public:
        ~SmaliClass ();
        void setStringPool (StringPool *sp);
        StringPool* stringPool();

        void setClassType (std::string &classType);
        std::string classType();
        void setFlag(int flag);
        int flag();
        void setSource (std::string &source);
        std::string source();
        void setSuper(std::string &super);
        std::string super();

        SmaliMethod* addMethod (std::string &name,std::vector<std::string> &args);
        SmaliMethod* getMethod (std::string &name,std::vector<std::string> &args);
        bool delMethod(std::string &name,std::vector<std::string> &args);

        SmaliField* getField (std::string &name);
        SmaliField* addField (std::string &name);
        bool delField (std::string &name);

        // for test
        void printAst (std::vector<std::string> &v);

    public:
        std::list<SmaliField*> fields;
        std::list<SmaliMethod*> methods;
    private:
        StringPool *mStringPool = nullptr;

        int mClassType;
        int mSource = -1;
        int mSuper;
        int mFlag = 0;


    };
}

#endif //SMALIPARSER_SMALICLASS_H
