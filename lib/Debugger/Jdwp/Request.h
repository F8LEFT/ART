//===- Request.h - ART-DEBUGGER ---------------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// The file defines jdwp Request for handling jdwp packet
//
//===----------------------------------------------------------------------===//

#ifndef PROJECT_REQUEST_H
#define PROJECT_REQUEST_H



#include "Jdwp/JdwpReader.h"
#include <QByteArray>

namespace JDWP {
    class Request: public JdwpReader
    {
    public:
        Request(const uint8_t* bytes, uint32_t available);

        // Return values from this JDWP packet's header.
        size_t GetLength() { return byte_count_; }
        uint32_t GetId() { return id_; }
        void SetId(uint32_t id) { id_ = id; }
        uint8_t GetCommandSet() { return command_set_; }
        uint8_t GetCommand() { return command_; }

        const uint8_t* GetExtra() const;
        size_t GetExtraLen() const;

        bool isValid() { return valid_; }
        bool isReply() { return reply; }

        static bool isValid(const uint8_t* bytes, uint32_t available);
    private:
        uint32_t byte_count_;

        uint32_t id_;
        uint8_t command_set_;
        uint8_t command_;

        bool reply;

        bool valid_;
        QByteArray extra;
    };
}

#endif //PROJECT_REQUEST_H
