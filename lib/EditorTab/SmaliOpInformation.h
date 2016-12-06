//===- SmaliOpInformation.h - ART-GUI Editor Tab ---------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
//
// SmaliOpInfomation can show the information of the OpCodes.
//
//===----------------------------------------------------------------------===//


#ifndef ANDROIDREVERSETOOLKIT_SMALIOPINFORMATION_H
#define ANDROIDREVERSETOOLKIT_SMALIOPINFORMATION_H

#include <QLineEdit>
#include <QPlainTextEdit>

class SmaliOpInformation: public QLineEdit {
    Q_OBJECT
public:
    SmaliOpInformation(QPlainTextEdit* parent);

protected slots:
    void cursorChanged();

    static QString getOpInformation(int token);
private:
    QPlainTextEdit* m_edit;
};


#endif //ANDROIDREVERSETOOLKIT_SMALIOPINFORMATION_H
