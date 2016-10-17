//===- SmaliClass.cpp - ART-LEX ---------------------------------*- c++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include <iostream>
#include "SmaliClass.h"
#include "SmaliMethod.h"
#include "SmaliField.h"
#include "utils/formater.hpp"
using namespace Analysis;
using namespace std;

void SmaliClass::setClassType (string &classType)
{
    mClassType = (*mStringPool)[classType];
}

string SmaliClass::classType ()
{
    return (*mStringPool)[mClassType];
}

void SmaliClass::setFlag (int flag)
{
    mFlag = flag;
}

int SmaliClass::flag ()
{
    return mFlag;
}

void SmaliClass::setSource (string &source)
{
    mSource = (*mStringPool)[source];
}

string SmaliClass::source ()
{
    return (*mStringPool)[mSource];
}

SmaliField *SmaliClass::addField (string &name)
{
    auto f = getField (name);
    if (f != nullptr) {
        f->clear ();
    } else {
        f = new SmaliField;
        fields.push_back (f);
    }
    f->setStringPool (mStringPool);
    f->setName (name);
    f->setParent(this);
    return f;
}

SmaliField *SmaliClass::getField (string &name)
{
    for(auto &f: fields) {
        if (f->name () ==  name) {
            return f;
        }
    }
    return nullptr;
}

bool SmaliClass::delField (string &name)
{
    auto f = getField (name);
    if (f != nullptr) {
        fields.remove (f);
        delete f;
        return true;
    }
    return false;
}

SmaliMethod *SmaliClass::addMethod (string &name,vector<string> &args)
{
    auto m = getMethod (name, args);
    if (m != nullptr) {
        m->clear ();
    } else {
        m = new SmaliMethod;
        methods.push_back (m);
    }
    m->setStringPool (mStringPool);
    m->setName (name);
    m->setArgs (args);
    m->setParent(this);
    return m;
}

SmaliMethod *SmaliClass::getMethod (string &name, vector<string> &args)
{
    for(auto &m: methods) {
        if (m->name () ==  name && m->argsEqual(args))  {
            return m;
        }
    }
    return nullptr;
}

bool SmaliClass::delMethod (std::string &name,std::vector<std::string> &args)
{
    auto m = getMethod (name, args);
    if (m != nullptr) {
        methods.remove (m);
        delete m;
        return true;
    }
    return false;
}

void SmaliClass::setSuper (std::string &super)
{
    mSuper = (*mStringPool)[super];
}

std::string SmaliClass::super ()
{
    return (*mStringPool)[mSuper];
}

SmaliClass::~SmaliClass ()
{
    for(auto &f : fields) {
        delete f;
    }
    for(auto &m : methods) {
        delete m;
    }
}

void SmaliClass::setStringPool (StringPool *sp)
{
    mStringPool = sp;
}

StringPool *SmaliClass::stringPool ()
{
    return mStringPool;
}

void SmaliClass::printAst (std::vector<std::string> &v)
{
    v.push_back (".class " + formater::getAccessFlagClass (mFlag) + " " + (*mStringPool)[mClassType]);
    v.push_back (std::string(".super ") + (*mStringPool)[mSuper]);
    if(mSource != -1) {
        v.push_back (std::string(".source \"") + (*mStringPool)[mSource]+"\"");
    }
    for (auto f: fields) {
        f->printAst (v);
    }
    for (auto m: methods) {
        m->printAst (v);
    }
}
