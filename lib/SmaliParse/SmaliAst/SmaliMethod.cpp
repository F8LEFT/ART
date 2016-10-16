//===- SmaliMethod.cpp - ART-LEX --------------------------------*- c++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//


#include <iostream>
#include <utils/formater.hpp>
#include "SmaliMethod.h"
using namespace Analysis;
using namespace std;

SmaliMethod::~SmaliMethod ()
{
    for(auto it = mInsList.begin (), itEnd = mInsList.end ();
            it != itEnd; it++ ) {
        (*it)->deleteThis ();
    }
}


void SmaliMethod::setName (std::string &name)
{
    mName = (*mStringPool)[name];
}

std::string SmaliMethod::name ()
{
    return (*mStringPool)[mName];
}

void SmaliMethod::setFlag (int flag)
{
    mFlag = flag;
}

int SmaliMethod::flag ()
{
    return mFlag;
}

void SmaliMethod::setType (std::string &type)
{
    mType = (*mStringPool)[type];
}

std::string SmaliMethod::type ()
{
    return (*mStringPool)[mType];
}

void SmaliMethod::setParent (SmaliClass *parent)
{
    mParent = parent;
}

SmaliClass *SmaliMethod::parent ()
{
    return mParent;
}

void SmaliMethod::setArgs (std::vector<std::string> &args)
{
    mArgs.clear ();
    for (auto &s: args)
    {
        mArgs.push_back ((*mStringPool)[s]);
    }
}

std::vector<std::string> SmaliMethod::args ()
{
    std::vector<std::string> sArgs;
    for (auto i : mArgs)
    {
        sArgs.push_back ((*mStringPool)[i]);
    }
    return move(sArgs);
}

bool SmaliMethod::argsEqual (std::vector<std::string> &args)
{
    std::vector<int> iArgs;
    for (auto &s: args)
    {
        iArgs.push_back ((*mStringPool)[s]);
    }
    return mArgs == iArgs;
}

void SmaliMethod::clear ()
{
    mName = -1;
    mType = -1;
    mArgs.clear ();
    mFlag = 0;
    mParent = nullptr;
}

void SmaliMethod::setRegSize (int regsize)
{
    mRegSize = regsize;
}

int SmaliMethod::regSize ()
{
    return mRegSize;
}

void SmaliMethod::setStringPool (StringPool *sp)
{
    mStringPool = sp;
}

StringPool *SmaliMethod::stringPool ()
{
    return mStringPool;
}

void SmaliMethod::setArgs (std::vector<int> &args)
{
    mArgs = args;
}

bool SmaliMethod::argsEqual (std::vector<int> &args)
{
    return mArgs == args;
}

void SmaliMethod::printAst (std::vector<std::string> &v)
{
    std::string s;
    s = ".method " + formater::getAccessFlagMethod (mFlag)+" "+(*mStringPool)[mName];
    s += "(";
    for (auto arg: mArgs) {
        s += (*mStringPool)[arg];
    }
    s += ")";
    s += (*mStringPool)[mType];
    v.push_back (s);
    v.push_back (".registers " + formater::int2decStr (mRegSize));
    for (auto op:mInsList) {
        v.push_back (op->toString ());
    }
}

