//===- SmaliField.cpp - ART-LEX ---------------------------------*- c++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "SmaliField.h"
#include <iostream>
#include <utils/formater.hpp>

using namespace std;
using namespace Analysis;

void SmaliField::setName (std::string name)
{
    mName = (*mStringPool)[name];
}

std::string SmaliField::name ()
{
    return (*mStringPool)[mName];
}

void SmaliField::setFlag (int flag)
{
    mFlag = flag;
}

int SmaliField::flag ()
{
    return mFlag;
}

void SmaliField::setType (std::string type)
{
    mType = (*mStringPool)[type];
}

std::string SmaliField::type ()
{
    return (*mStringPool)[mType];
}

void SmaliField::setParent (SmaliClass *parent)
{
    mParent = parent;
}

SmaliClass *SmaliField::parent ()
{
    return mParent;
}

bool SmaliField::operator== (SmaliField &f)
{
    if (f.name () == (*mStringPool)[mName]) {
        return true;
    }
    return false;
}

void SmaliField::clear ()
{
    mParent = nullptr;
    mType = -1;
    mName = -1;
    mFlag = 0;

}

void SmaliField::setStringPool (StringPool *sp)
{
    mStringPool = sp;
}

StringPool *SmaliField::stringPool ()
{
    return mStringPool;
}

void SmaliField::printAst (std::vector<std::string> &v)
{
    v.push_back (".field "+formater::getAccessFlagField (mFlag)+" "+(*mStringPool)[mName]+":"+(*mStringPool)[mType]);
}












