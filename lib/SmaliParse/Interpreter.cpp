//===- Interpreter.h - ART-LEX ----------------------------------*- c++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "Interpreter.h"
using namespace Analysis;

std::string trim (const std::string &si);

Interpreter::Interpreter()
    : mParser(mLexer, *this)
{

}

int Interpreter::parse ()
{
    return mParser.parse ();
}

void Interpreter::analysis ()
{
    for(auto it = mClass->methods.begin (), itEnd = mClass->methods.end ();
            it != itEnd; it++) {
        analysisMethod ((*it));
    }
}

void Interpreter::switchInputStream (std::istream *is,SmaliClass *pClass)
{
    mLexer.switch_streams (is,nullptr);
    mClass = pClass;
    mStringPool = pClass->stringPool ();
}

void Interpreter::print ()
{
    std::vector<std::string> vTree;
    mClass->printAst (vTree);
    for (auto &s: vTree) {
        std::cout << s << std::endl;
    }
}

void Interpreter::setClassDefine (int flag,std::string &type)
{
    assert (mClass != nullptr);
    mClass->setClassType (type);
    mClass->setFlag (flag);
}

void Interpreter::setSuperDefine (std::string &super)
{
    mClass->setSuper (super);
}

void Interpreter::setSourceDefine (std::string &source)
{
    mClass->setSource (source);
}

void Interpreter::addField (std::string &name,int flag,std::string &type)
{
    auto f = mClass->addField (name);
    f->setFlag (flag);
    f->setType (type);
}

void Interpreter::addMethod (std::string &name,int flag,std::string &type,std::vector<std::string> &args)
{
    mCurMethod = mClass->addMethod (name,args);
    mCurMethod->setFlag (flag);
    mCurMethod->setType (type);
}

void Interpreter::setCurMethodRegSize (int size)
{
    mCurMethod->setRegSize (size);
}

void Interpreter::addOpcode (OpCode *code)
{
#ifdef DEBUG
    std::string tStr = trim(mLexer.text ());
    std::cout << tStr << std::endl;
    std::string codeStr = code->toString ();
    assert (codeStr == tStr);
#endif
    mCurMethod->mInsList.push_back (code);
}

void Interpreter::endMethod ()
{
    mCurMethod = nullptr;
}

StringPool *Interpreter::stringPool (){ return mStringPool;}

void Interpreter::analysisMethod (SmaliMethod *method)
{
    for(auto it = method->mInsList.begin (), itEnd = method->mInsList.end ();
            it != itEnd; it++) {
        if((*it)->op == OP_PACKED_SWITCHDATABEG) {
            auto packedbeg = (Op_PACKED_SWITCHDATA_BEG*)(*it);
            auto packedtable = new Op_PACKED_SWITCHDATA(OP_PACKED_SWITCHDATA,
                                        packedbeg->mStringPool, packedbeg->md);
            bool succ = false;
            packedbeg->deleteThis ();
            it = method->mInsList.erase (it);
            while(it != itEnd) {
                if((*it)->op == OP_JMPLABEL) {
                    packedtable->addLabels (((Op_JmpLabel*)(*it))->jmpLabel);
                    (*it)->deleteThis ();
                    it = method->mInsList.erase (it);
                } else if((*it)->op == OP_PACKED_SWITCHDATAEND) {
                    (*it)->deleteThis ();
                    it = method->mInsList.erase (it);
                    succ = true;
                    break;
                } else {
                    // error, just skip
                    break;
                }
            }
            if(succ) {
                method->mInsList.insert (it, packedtable);
            } else {
                packedtable->deleteThis ();
            }
        }


    }
}

std::string trim (const std::string &si)
{
    std::string s = si;
    if (s.empty())
    {
        return s;
    }
    s.erase(0,s.find_first_not_of(" "));
    s.erase(s.find_last_not_of(" ") + 1);
    return s;
}