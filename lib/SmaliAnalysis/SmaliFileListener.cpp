//===- SmaliFileListener.cpp - ART-GUI Analysis engine ----------*- cpp -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "SmaliFileListener.h"

#include "SmaliAnalysis/SmaliFile.h"
#include "LiteralTools.h"

SmaliFileListener::SmaliFileListener(SmaliFile *filedata) {
    m_smali = filedata;
}

void SmaliFileListener::enterMethod(SmaliParser::MethodContext *ctx) {
    auto method = new SmaliMethod;

    method->m_startline = ctx->METHOD_DIRECTIVE()->getSymbol()->getLine();
    method->m_endline = ctx->END_METHOD_DIRECTIVE()->getSymbol()->getLine();

    method->m_accessflag = method->getAccessFlag(
            QString::fromStdString(ctx->access_list()->getText()));
    method->m_name = QString::fromStdString(ctx->member_name()->getText());
    {
        auto proto = ctx->method_prototype();
        auto param = proto->param_list();
        for(auto &paramctx: param->nonvoid_type_descriptor()) {
            method->m_params.push_back(QString::fromStdString(paramctx->getText()));
        }
        method->m_ret = QString::fromStdString(proto->type_descriptor()->getText());
    }

    if(method->m_accessflag && ACC_STATIC) {
        method->m_paramRegisterCount = method->m_params.size();
    } else {
        // P0 is used for this pointer
        method->m_paramRegisterCount = method->m_params.size() + 1;
    }

    auto statectx = ctx->statements_and_directives();
    if(statectx->hasRegistersDirective) {
        auto registerctx = statectx->registers_directive(0);
        if(registerctx->isRegister) {
            method->m_localRegisterCount =
                    LiteralTools::parseInt(registerctx->regCount2->getText())
                    - method->m_paramRegisterCount;
        } else {
            method->m_localRegisterCount =
                    LiteralTools::parseInt(registerctx->regCount2->getText());
        }
    }

//    auto orderctx = statectx->ordered_method_item();
    // TODO get method item codeIdx


    m_smali->m_methods.push_back(method);
}

void SmaliFileListener::exitMethod(SmaliParser::MethodContext *ctx) {

}

void SmaliFileListener::enterField(SmaliParser::FieldContext *ctx) {
    auto field = new SmaliField;
    field->m_line = ctx->FIELD_DIRECTIVE()->getSymbol()->getLine();

    field->m_name = QString::fromStdString(ctx->member_name()->getText());
    field->m_accessflag = field->getAccessFlag(
            QString::fromStdString(ctx->access_list()->getText()));
    field->m_class = QString::fromStdString(ctx->nonvoid_type_descriptor()->getText());

    // TODO parse annotation data if existed?

    m_smali->m_fields.push_back(field);
}

void SmaliFileListener::exitField(SmaliParser::FieldContext *ctx) {

}

void SmaliFileListener::enterSmali_file(SmaliParser::Smali_fileContext *ctx) {
}

void SmaliFileListener::exitSmali_file(SmaliParser::Smali_fileContext *ctx) {
    m_smali->m_isValid = ctx->isValid;
}


