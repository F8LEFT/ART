//===- StringPool.hpp - ART-utils -------------------------------*- c++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// The file defines a StringPool that can store string.
//
//===----------------------------------------------------------------------===//


#ifndef SMALIPARSER_STRINGPOOL_H
#define SMALIPARSER_STRINGPOOL_H

#include "trie.hpp"
#include <vector>
#include <map>
#include <string>

class StringPool {
public:
    int insert(const std::string &s) {
        auto it = mStrsMap.find (s);
        if(it != mStrsMap.end ()) {
            return it->second;
        }
        mStrsMap[s] = count;
        const std::string *b;
        it = mStrsMap.find (s);
        b = &it->first;
        strs.push_back ((*b).c_str ());
        return count++;
    }

    const char* operator[](int id) {
        if (id < count) {
            return strs[id];
        }
        return nullptr;
    }

    int operator[](const std::string &s) {
        return insert (s);
    }
protected:
    std::vector<const char*> strs;

    std::map<std::string, int> mStrsMap;
    int count = 0;
};
#endif //SMALIPARSER_STRINGPOOL_H
