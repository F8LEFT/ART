//===- Debugger.cpp - ART-DEBUGGER ------------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "Debugger/Debugger.h"

#include "DebugSocket.h"
Debugger::Debugger(QObject *parent)
    : QObject(parent)
{
    // adb shell pidof f8left.cm2
}

