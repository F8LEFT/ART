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

void Interpreter::switchInputStream (std::istream *is,SmaliClass *pClass)
{
    mLexer.switch_streams (is,nullptr);
    mClass = pClass;
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
    std::string codeStr = code->toString ();
    std::string tStr = trim(mLexer.text ());
    std::cout << tStr << std::endl;
    assert (codeStr == tStr);       // for debug only
    mCurMethod->mInsList.push_back (code);
}

void Interpreter::endMethod ()
{
    mCurMethod = nullptr;
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