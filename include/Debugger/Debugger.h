//===- Debugger.h - ART-DEBUGGER --------------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Debugger handle socket packet between host and client.
//
//===----------------------------------------------------------------------===//

#ifndef PROJECT_DEBUGGER_H
#define PROJECT_DEBUGGER_H

#include <QObject>
#include <QString>


class DebugSocket;

class Debugger: public QObject
{
    Q_OBJECT
    Debugger(QObject* parent = nullptr);

protected slots:

private:
    DebugSocket* mSocket;
};


#endif //PROJECT_DEBUGGER_H
