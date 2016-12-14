//===- FileTextStyleConfig.h - ART-GUI Config ------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
//
// Set Theme TextStyle config.
//
//===----------------------------------------------------------------------===//

#ifndef FILESCHEMECONFIG_H
#define FILESCHEMECONFIG_H


#include "EditorTab/TextEditor.h"
#include "ColorItem.h"


#include <Repository>


#include <QWidget>
#include <QColor>
#include <QtGui/QSyntaxHighlighter>
#include <QMap>
#include <QtWidgets/QListWidgetItem>
#include  <QFont>
#include <QStyleOptionButton>
#include <QPushButton>
#include <QtWidgets/QCheckBox>
#include <QVBoxLayout>



class FileTextStyleConfig : public QWidget
{
    Q_OBJECT

public:
    explicit FileTextStyleConfig (QWidget *parent);
    ~FileTextStyleConfig();

    void setTheme(KSyntaxHighlighting::Theme theme);

signals:
    void formatUpdate();

private:

    QListWidget* m_colorList;

    KSyntaxHighlighting::Theme m_theme;

    ColorItem* m_foreground;
    ColorItem* m_background;
    QCheckBox* m_bold;
    QCheckBox* m_italic;
    QCheckBox* m_underline;
    QCheckBox* m_strikThrough;
};



#endif // FILESCHEMECONFIG_H
