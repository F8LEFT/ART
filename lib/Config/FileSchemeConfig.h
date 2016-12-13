//===- FileSchemeConfig.h - ART-GUI Config ---------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
//
// Set Scheme Config
//
//===----------------------------------------------------------------------===//

#ifndef FILESCHEMECONFIG_H
#define FILESCHEMECONFIG_H


#include "EditorTab/TextEditor.h"

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

namespace Ui {
class FileSchemeConfig;
}

class ColorItem;

class FileSchemeConfig : public QWidget
{
    Q_OBJECT

public:
    explicit FileSchemeConfig (QWidget *parent,
                               const QString &themeName,const QString &sampleFile);
    ~FileSchemeConfig();

    void save();

protected slots:
//    void onColorListItemChange(QListWidgetItem* current, QListWidgetItem* prev);

//    void onSchemeComboboxChange(const QString &text);

//    void onFormatUpdate();

    void onSchemeCopyBtnClick();
    void onSchemeDeleteBtnClick();

private:
    void setupThemeGroup();
    void setupFontGroup();
    void setupColorGroup();

    void themeChanged(const QString& themeName);

protected slots:
    void fontUpdate();
private:
    Ui::FileSchemeConfig *ui;

    TextEditor* m_colorEditor;
    QListWidget* m_colorList;


    KSyntaxHighlighting::Repository m_repository;
    KSyntaxHighlighting::Theme m_theme;

    ColorItem* m_foreground;
    ColorItem* m_background;
    QCheckBox* m_bold;
    QCheckBox* m_italic;
    QCheckBox* m_underline;
    QCheckBox* m_strikThrough;


    QString m_sampleFile;

};

class ColorButton;

class ColorButton: public QPushButton {
    Q_OBJECT
public:
    ColorButton(QWidget* parent = Q_NULLPTR)
            :QPushButton(parent) {}
    void paintColor(QRgb rgb);
protected:
    void paintEvent(QPaintEvent* event);
private:
    QRgb m_rgb;
};

class ColorItem : public QWidget {
    Q_OBJECT
public:
    ColorItem(QWidget* parent = Q_NULLPTR, const QString& name = "");

    QRgb color() { return m_rgb; }
    void setColor(QRgb c);

signals:
    void colorChanged(QRgb rgb);

private:
    QRgb m_rgb;
    ColorButton* m_colorBtn;
    QPushButton* m_clearBtn;
};

#endif // FILESCHEMECONFIG_H
