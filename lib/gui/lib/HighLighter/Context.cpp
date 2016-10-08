//===- Context.cpp - ART-GUI HighLighter------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//


#include "Context.h"

#include "HighlightDefinition.h"

void Context::setRegion(const QString &begin) {
    m_Region = begin;
}

const QString &Context::region() {
    return m_Region;
}

void Context::setType(Context::CtxType ctx) {
    m_type = ctx;
}

Context::CtxType Context::type() {
    return m_type;
}

void Context::setName(const QString &name) {
        m_name = name;
}

const QString &Context::name() {
    return m_name;
}

const QRegExp & Context::getRegExpr(HighlightDefinition *define) {
    if (pattern.isEmpty()) {
        switch (m_type) {
            case Keyword:{
                auto keyList = define->keywordList(m_name)->keyword();
                bool begin = m_Region == "BeginRegion";
                QString patStr;
                int iCount = keyList.size();
                for(auto &keyword: keyList) {
                    if(begin) {
                        patStr.append("^(?:\\s*)" + keyword + "\\b");
                    } else {
                        patStr.append("\\b" + keyword + "\\b");
                    }
                    if (--iCount)
                        patStr.append('|');
                }
                pattern.setPattern(patStr);
            }
                break;
            case RegExpr: {
                pattern.setPattern(m_name);
            }
                break;
        }
    }
    return pattern;
}

void Context::setAttribute(const QString &attr) {
    m_attribute = attr;
}

const QString &Context::attribute() {
    return m_attribute;
}








