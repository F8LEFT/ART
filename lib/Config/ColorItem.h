//===- ColorItem.h - ART-GUI Config ----------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
//
// Print a button to set color config.
//
//===----------------------------------------------------------------------===//

#ifndef ANDROIDREVERSETOOLKIT_COLORITEM_H
#define ANDROIDREVERSETOOLKIT_COLORITEM_H

#include <QPushButton>
#include <QWidget>
#include <QVariant>


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

    void setData(QVariant v) {m_data = v;}
    QVariant data() {return m_data; }

    void setClearBtnEnable(bool b);
    bool isClearBtnEnable();
signals:
    void colorChanged(QRgb rgb, QVariant data);

private:
    QRgb m_rgb;
    ColorButton* m_colorBtn;
    QPushButton* m_clearBtn;

    QVariant m_data;
};


#endif //ANDROIDREVERSETOOLKIT_COLORITEM_H
