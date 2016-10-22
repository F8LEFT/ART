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

#include <cstring>
#include "utils/Defs.h"

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
        uint8_t    mRefTypeTag;	    // Kind of following reference type.
        RefTypeId  mTypeId;         // Loaded reference type
        std::string mDescriptor;    // The JNI signature of the loaded reference type.
        std::string mGenericSignature;  // The generic signature of the loaded reference type.
        uint32_t   mStatus;	        // The current class status.
    };

    struct MethodInfo {
        MethodId	 mMethodId;
        std::string	 mName;
        std::string	 mSignature;
        std::string	 mGenericSignature;
        uint32_t	 mFlags;
    };

    struct FieldInfo {
        FieldId	     mFieldId;
        std::string	 mName;
        std::string	 mDescriptor;
        std::string	 mGenericSignature;
        uint32_t	 mFlags;
    };


    enum JdwpTag {
        JT_ARRAY                 = '[',
        JT_BYTE                  = 'B',
        JT_CHAR                  = 'C',
        JT_OBJECT                = 'L',
        JT_FLOAT                 = 'F',
        JT_DOUBLE                = 'D',
        JT_INT                   = 'I',
        JT_LONG                  = 'J',
        JT_SHORT                 = 'S',
        JT_VOID                  = 'V',
        JT_BOOLEAN               = 'Z',
        JT_STRING                = 's',
        JT_THREAD                = 't',
        JT_THREAD_GROUP          = 'g',
        JT_CLASS_LOADER          = 'l',
        JT_CLASS_OBJECT          = 'c',
    };

    struct JValue_Private {
        union {
            unsigned char b;
            int16_t c;
            float f;
            double d;
            int32_t i;
            int64_t j;
            int16_t s;
            void* v;    // void v
            bool z;
        };
        JdwpTag tag;
    public:
        JValue_Private(unsigned char v) {
            b = v; tag = JT_BYTE;
        }
        JValue_Private(char v) {
            c = v; tag = JT_CHAR;
        }
        JValue_Private(float v) {
            f = v; tag = JT_FLOAT;
        }
        JValue_Private(double v) {
            d = v; tag = JT_DOUBLE;
        }
        JValue_Private(int32_t v) {
            i = v; tag = JT_INT;
        }
        JValue_Private(int64_t v) {
            j = v; tag = JT_LONG;
        }
        JValue_Private(int16_t v) {
            s = v; tag = JT_SHORT;
        }
        JValue_Private(bool v) {
            b = v; tag = JT_BOOLEAN;
        }
        JValue_Private() {
            tag = JT_VOID;
        }
        JValue_Private(JDWP::JdwpTag tag, const void* p) {
            switch (tag) {
                case JDWP::JT_BOOLEAN:
                case JDWP::JT_BYTE:
                    memcpy(v, p, 1);
                    break;
                case JDWP::JT_CHAR:
                case JDWP::JT_SHORT:
                    memcpy(v, p, 2);
                    break;
                case JDWP::JT_INT:
                case JDWP::JT_FLOAT:
                    memcpy (v, p, 4);
                    break;
                case JDWP::JT_DOUBLE:
                case JDWP::JT_LONG:
                    memcpy (v, p, 8);
                    break;
                case JDWP::JT_VOID:
                default:
                    break;
            }
        }
    };

    bool IsPrimitiveTag(JDWP::JdwpTag tag) {
        switch (tag) {
            case JDWP::JT_BOOLEAN:
            case JDWP::JT_BYTE:
            case JDWP::JT_CHAR:
            case JDWP::JT_FLOAT:
            case JDWP::JT_DOUBLE:
            case JDWP::JT_INT:
            case JDWP::JT_LONG:
            case JDWP::JT_SHORT:
            case JDWP::JT_VOID:
                return true;
            default:
                return false;
        }
    }

}
#endif //PROJECT_JDWP_H
