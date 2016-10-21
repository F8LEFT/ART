//===- jdwp.h - ART-DEBUGGER ------------------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// jdwp.h contain some defination for jdwp msg
//
//===----------------------------------------------------------------------===//

#ifndef PROJECT_JDWP_H
#define PROJECT_JDWP_H

namespace JDWP {

/*
 * Fundamental types.
 *
 * ObjectId and RefTypeId must be the same size.
 */
    typedef uint32_t FieldId;     /* static or instance field */
    typedef uint32_t MethodId;    /* any kind of method, including constructors */
    typedef uint64_t ObjectId;    /* any object (threadID, stringID, arrayID, etc) */
    typedef uint64_t RefTypeId;   /* like ObjectID, but unique for Class objects */
    typedef uint64_t FrameId;     /* short-lived stack frame ID */

    struct ClassInfo {
        u1	       mRefTypeTag;	    // Kind of following reference type.
        RefTypeId  mTypeId;         // Loaded reference type
        std::string mDescriptor;    // The JNI signature of the loaded reference type.
        std::string mGenericSignature;  // The generic signature of the loaded reference type.
        u4	       mStatus;	        // The current class status.
    };
}
#endif //PROJECT_JDWP_H
