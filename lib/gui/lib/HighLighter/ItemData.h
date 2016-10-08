//===- ItemData.h - ART-GUI HighLighter-------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//
//
//
//
//===----------------------------------------------------------------------===//


#ifndef PROJECT_ITEMDATA_H
#define PROJECT_ITEMDATA_H

#include <QString>
#include <QColor>
#include <QTextCharFormat>

class ItemData {

public:
    ItemData();

    void setStyle(const QString &style);
    const QString &style() const;

    void setColor(const QString &color);
    const QColor &color() const;

    void setSelectionColor(const QString &color);
    const QColor &selectionColor() const;

    void setItalic(const QString &italic);
    bool isItalic() const;
    bool isItalicSpecified() const;

    void setBold(const QString &bold);
    bool isBold() const;
    bool isBoldSpecified() const;

    void setUnderlined(const QString &underlined);
    bool isUnderlined() const;
    bool isUnderlinedSpecified() const;

    void setStrikeOut(const QString &strike);
    bool isStrikeOut() const;
    bool isStrikeOutSpecified() const;

    bool isCustomized() const;

    bool makeFormat();
    const QTextCharFormat& getFormat() const;
private:
    bool m_italic;
    bool m_italicSpecified;
    bool m_bold;
    bool m_boldSpecified;
    bool m_underlined;
    bool m_underlinedSpecified;
    bool m_strikedOut;
    bool m_strikeOutSpecified;
    bool m_isCustomized;
    QString m_style;
    QColor m_color;
    QColor m_selectionColor;

    QTextCharFormat format;
};



#endif //PROJECT_ITEMDATA_H
