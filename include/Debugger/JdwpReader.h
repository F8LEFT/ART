//===- JdwpReader.h - ART-DEBUGGER ------------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// JdwpReader is used to read socket
//
//===----------------------------------------------------------------------===//


#ifndef PROJECT_JDWPREADER_H
#define PROJECT_JDWPREADER_H

#include <cstdint>
#include <cstddef>
#include <string>
#include "jdwp.h"

namespace JDWP {
    class JdwpReader {
    public:
        JdwpReader(const uint8_t* bytes, uint32_t available);

        uint8_t Read1();

        uint16_t Read2();

        uint32_t Read4();

        uint64_t Read8();

        uint64_t ReadValue(size_t width);

        uint32_t ReadFieldId() {return Read4 (); }
        uint32_t ReadMethodId() {return Read4 ();}
        uint64_t ReadObjectId() {return Read8 ();}
        uint64_t ReadRefTypeId() {return Read8 ();}
        uint64_t ReadFrameId() { return Read8();}
        uint64_t ReadThreadId() {return Read8 (); }
        JdwpLocation ReadJdwpLocation();


        std::string ReadString();

        // Returns the number of bytes remaining.
        size_t size() { return end_ - p_; }
        // Returns a pointer to the next byte.
        const uint8_t* data() { return p_; }

        void Skip(size_t count) { p_ += count; }

    protected:
        bool error = false;
        const uint8_t* p_;
        const uint8_t* end_;
    };

}
#endif //PROJECT_JDWPREADER_H
