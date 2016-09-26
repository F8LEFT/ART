//===- CmdMsgUtil.cpp - ART-GUI utilpart ------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#include "utils/CmdMsgUtil.h"

CmdMsg::CmdMsg (QObject *parent): QObject (parent)
{
}

CmdMsg::~CmdMsg ()
{

}

CmdMsg *CmdMsg::instance ()
{
    static CmdMsg* mPtr = nullptr;
    if(mPtr == nullptr) {
        mPtr = new CmdMsg;
    }
    return mPtr;
}


