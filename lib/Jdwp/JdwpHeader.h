//===- Jdwpheader.h - ART-DEBUGGER ------------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// The file contains jdwp defination
//
//===----------------------------------------------------------------------===//

#ifndef PROJECT_JDWPHEADER_H
#define PROJECT_JDWPHEADER_H

namespace JDWP {


/*
* JDWP constants.
*/
#define kJDWPHeaderLen  11
#define kJDWPFlagReply  0x80

/* DDM support */
#define kJDWPDdmCmdSet  199     /* 0xc7, or 'G'+128 */
#define kJDWPDdmCmd     1

#define kInputBufferSize    (256*1024)
#define kMagicHandshakeLen  14      /* "JDWP-Handshake" */

//#pragma pack (1)
//    struct JdwpReqHeader {
//        u4  length;
//        u4  id;
//        u1  flag;
//        u1  cmdSet;
//        u1  cmd;
//        u1  extradata[0];
//    };
//#pragma pack ()

}

#endif //PROJECT_JDWPHEADER_H
