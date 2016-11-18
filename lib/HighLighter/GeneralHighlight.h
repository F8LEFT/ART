//===- GeneralHighlight.h - ART-GUI HighLighter-----------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
//
// GeneralHighlight read highlight defination from xml
//
//===----------------------------------------------------------------------===//


#ifndef PROJECT_GENERALHIGHLIGHT_H
#define PROJECT_GENERALHIGHLIGHT_H

#include <KateHighlight/katehighlight.h>
#include <KateHighlight/katesyntaxmanager.h>

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QHash>
#include <QList>
#include <HighLighter/HighLightConfig.h>

class GeneralHighlight : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    GeneralHighlight(QTextDocument *parent, QString fileName,
                    HighLightConfig* config);

protected:
    void highlightBlock(const QString &text) Q_DECL_OVERRIDE;

private slots:
    void hlAttrUpdate();
private:
    KateHighlighting* mHl;
    KateAttributeList mAttrlist;

    HighLightConfig* mConfig;
};

class GeneralHlTextData: public QTextBlockUserData
{
public:
    GeneralHlTextData(QTextBlock& b);
    ~GeneralHlTextData();

    Kate::TextLineData* mTextData;
};

#endif //PROJECT_GENERALHIGHLIGHT_H
