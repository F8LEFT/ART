//===- JdwpHandler.h - ART-DEBUGGER ------------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// JdwpHandler is used to handle jdwp request.
//
//===----------------------------------------------------------------------===//


#ifndef PROJECT_JDWPHANDLER_H
#define PROJECT_JDWPHANDLER_H

#include "JdwpReader.h"
/* JDWP Command
 * cmd  cmdset  name
 *
 * VirtualMachine command set (1)
 * 1    1       VirtualMachine.Version
 * 1    2       VirtualMachine.ClassesBySignature
 * 1    3       VirtualMachine.AllClasses
 * 1    4       VirtualMachine.AllThreads
 * 1    5       VirtualMachine.TopLevelThreadGroups
 * 1    6       VirtualMachine.Dispose
 * 1    7       VirtualMachine.IDSizes
 * 1    8       VirtualMachine.Suspend
 * 1    9       VirtualMachine.Resume
 * 1    10      VirtualMachine.Exit
 * 1    11      VirtualMachine.CreateString
 * 1    12      VirtualMachine.Capabilities
 * 1    13      VirtualMachine.ClassPaths
 * 1    14      VirtualMachine.DisposeObjects
 * 1    15      VirtualMachine.HoldEvents
 * 1    16      VirtualMachine.ReleaseEvents
 * 1    17      VirtualMachine.CapabilitiesNew
 * 1    18      VirtualMachine.RedefineClasses
 * 1    19      VirtualMachine.SetDefaultStratum
 * 1    20      VirtualMachine.AllClassesWithGeneric
 * 1    21      VirtualMachine.InstanceCounts
 *
 * ReferenceType command set (2)
 * 2    1       ReferenceType.Signature
 * 2    2       ReferenceType.ClassLoader
 * 2    3       ReferenceType.Modifiers
 * 2    4       ReferenceType.Fields
 * 2    5       ReferenceType.Methods
 * 2    6       ReferenceType.GetValues
 * 2    7       ReferenceType.SourceFile
 * 2    8       ReferenceType.NestedTypes
 * 2    9       ReferenceType.Status
 * 2    10      ReferenceType.Interfaces
 * 2    11      ReferenceType.ClassObject
 * 2    12      ReferenceType.SourceDebugExtension
 * 2    13      ReferenceType.SignatureWithGeneric
 * 2    14      ReferenceType.FieldsWithGeneric
 * 2    15      ReferenceType.MethodsWithGeneric
 * 2    16      ReferenceType.Instances
 * 2    17      ReferenceType.ClassFileVersion
 * 2    18      ReferenceType.ConstantPool
 *
 * ClassType command set (3)
 * 3    1       ClassType.Superclass
 * 3    2       ClassType.SetValues
 * 3    3       ClassType.InvokeMethod
 * 3    4       ClassType.NewInstance
 *
 * ArrayType command set (4)
 * 4    1       ArrayType.NewInstance
 *
 * InterfaceType command set (5)
 *
 * Method command set (6)
 * 6    1       Method.LineTable
 * 6    2       Method.VariableTable
 * 6    3       Method.Bytecodes
 * 6    4       Method.IsObsolete
 * 6    5       Method.VariableTableWithGeneric
 *
 * Field command set (8)
 *
 * ObjectReference command set (9)
 * 9    1       ObjectReference.ReferenceType
 * 9    2       ObjectReference.GetValues
 * 9    3       ObjectReference.SetValues
 * 9    4       ObjectReference.UNUSED
 * 9    5       ObjectReference.MonitorInfo
 * 9    6       ObjectReference.InvokeMethod
 * 9    7       ObjectReference.DisableCollection
 * 9    8       ObjectReference.EnableCollection
 * 9    9       ObjectReference.IsCollected
 * 9    10      ObjectReference.ReferringObjects
 *
 * StringReference command set (10)
 * 10   1       StringReference.Value
 *
 * ThreadReference command set (11)
 * 11   1       ThreadReference.Name
 * 11   2       ThreadReference.Suspend
 * 11   3       ThreadReference.Resume
 * 11   4       ThreadReference.Status
 * 11   5       ThreadReference.ThreadGroup
 * 11   6       ThreadReference.Frames
 * 11   7       ThreadReference.FrameCount
 * 11   8       ThreadReference.OwnedMonitors
 * 11   9       ThreadReference.CurrentContendedMonitor
 * 11   10      ThreadReference.Stop
 * 11   11      ThreadReference.Interrupt
 * 11   12      ThreadReference.SuspendCount
 * 11   13      ThreadReference.OwnedMonitorsStackDepthInfo
 * 11   14      ThreadReference.ForceEarlyReturn
 *
 * ThreadGroupReference command set (12)
 * 12   1       ThreadGroupReference.Name
 * 12   2       ThreadGroupReference.Parent
 * 12   3       ThreadGroupReference.Children
 *
 * ArrayReference command set (13)
 * 13   1       ArrayReference.Length
 * 13   2       ArrayReference.GetValues
 * 13   3       ArrayReference.SetValues
 *
 * ClassLoaderReference command set (14)
 * 14   1       ClassLoaderReference.VisibleClasses
 *
 * EventRequest command set (15)
 * 15   1       EventRequest.Set
 * 15   2       EventRequest.Clear
 * 15   3       EventRequest.ClearAllBreakpoints
 *
 * StackFrame command set (16)
 * 16   1       StackFrame.GetValues
 * 16   2       StackFrame.SetValues
 * 16   3       StackFrame.ThisObject
 * 16   4       StackFrame.PopFrames
 *
 * ClassObjectReference command set (17)
 * 17   1       ClassObjectReference.ReflectedType
 *
 * Event command set (64)
 * 64   100     Event.Composite
 *
 * 199  1       DDM.Chunk
 * */

#include "JdwpReader.h"
#include "jdwp.h"
#include <vector>

namespace JDWP {
    namespace VirtualMachine {
        static uint8_t set_ = 1;

        struct Version : public JdwpReader {
            Version(const uint8_t* bytes, uint32_t available);

            std::string version;
            uint32_t major;
            uint32_t minor;
            std::string javaVersion;
            std::string javaVmName;

            static std::string buildReq(int id = 0);
            const static uint8_t cmd = 1;
        };

        struct ClassesBySignature : public JdwpReader {
            ClassesBySignature(const uint8_t* bytes, uint32_t available);

            uint32_t mSize;
            std::vector<ClassInfo> mInfos;

            static std::string buildReq(const std::string &classDescriptor,
                                        int id = 0);
            const static uint8_t cmd = 2;
        };

        struct AllClasses : public JdwpReader {
            AllClasses(const uint8_t* bytes, uint32_t available);

            uint32_t mSize;
            std::vector<ClassInfo> mInfos;

            static std::string buildReq(int id = 0);
            const static uint8_t cmd = 3;
        };
    }

    bool Write1(std::string &s, uint8_t v);
    bool Write2(std::string &s, uint16_t v);
    bool Write4(std::string &s, uint32_t v);
    bool Write8(std::string &s, uint64_t v);
    bool WriteString(std::string &s, const std::string &l);
    std::string BuildReq(int id, int cmdset, int cmd, const std::string &extra);
}


#endif //PROJECT_JDWPHANDLER_H
