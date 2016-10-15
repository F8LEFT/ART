//===- SmaliField.h - ART-LEX -----------------------------------*- c++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// SmaliField store Field message
//
//===----------------------------------------------------------------------===//


#ifndef SMALIPARSER_SMALIFIELD_H
#define SMALIPARSER_SMALIFIELD_H

#include <string>
#include <utils/StringPool.hpp>


namespace Analysis {
    class SmaliClass;

    class SmaliField
    {
    public:
        void setStringPool (StringPool *sp);
        StringPool* stringPool();

        void setName (std::string name);
        std::string name();
        void setFlag (int flag);
        int flag();
        void setType (std::string type);
        std::string type();
        void setParent (SmaliClass *parent);
        SmaliClass* parent();

        void clear();
        bool operator==(SmaliField &f);

        void printAst (std::vector<std::string> &v);
    private:
        StringPool* mStringPool = nullptr;

        int mName;
        int mType;
        int mFlag = 0;
        SmaliClass* mParent;

        // extra
    };
}

#endif //SMALIPARSER_SMALIFIELD_H
