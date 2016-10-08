//===- ItemData.h - ART-GUI HighLighter-------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//


#include "ItemData.h"
#include "HighLighterUtil.h"



ItemData::ItemData() :
        m_italic(false),
        m_italicSpecified(false),
        m_bold(false),
        m_boldSpecified(false),
        m_underlined(false),
        m_underlinedSpecified(false),
        m_strikedOut(false),
        m_strikeOutSpecified(false),
        m_isCustomized(false)
{}

void ItemData::setStyle(const QString &style)
{ m_style = style; }

const QString &ItemData::style() const
{ return m_style; }

void ItemData::setColor(const QString &color)
{
    if (!color.isEmpty()) {
        m_color.setNamedColor(color);
        m_isCustomized = true;
    }
}

const QColor &ItemData::color() const
{ return m_color; }

void ItemData::setSelectionColor(const QString &color)
{
    if (!color.isEmpty()) {
        m_selectionColor.setNamedColor(color);
        m_isCustomized = true;
    }
}

const QColor &ItemData::selectionColor() const
{ return m_selectionColor; }

void ItemData::setItalic(const QString &italic)
{
    if (!italic.isEmpty()) {
        m_italic = toBool(italic);
        m_italicSpecified = true;
        m_isCustomized = true;
    }
}

bool ItemData::isItalic() const
{ return m_italic; }

bool ItemData::isItalicSpecified() const
{ return m_italicSpecified; }

void ItemData::setBold(const QString &bold)
{
    if (!bold.isEmpty()) {
        m_bold = toBool(bold);
        m_boldSpecified = true;
        m_isCustomized = true;
    }
}

bool ItemData::isBold() const
{ return m_bold; }

bool ItemData::isBoldSpecified() const
{ return m_boldSpecified; }

void ItemData::setUnderlined(const QString &underlined)
{
    if (!underlined.isEmpty()) {
        m_underlined = toBool(underlined);
        m_underlinedSpecified = true;
        m_isCustomized = true;
    }
}

bool ItemData::isUnderlined() const
{ return m_underlined; }

bool ItemData::isUnderlinedSpecified() const
{ return m_underlinedSpecified; }

void ItemData::setStrikeOut(const QString &strike)
{
    if (!strike.isEmpty()) {
        m_strikedOut = toBool(strike);
        m_strikeOutSpecified = true;
        m_isCustomized = true;
    }
}

bool ItemData::isStrikeOut() const
{ return m_strikedOut; }

bool ItemData::isStrikeOutSpecified() const
{ return m_strikeOutSpecified; }

bool ItemData::isCustomized() const
{ return m_isCustomized; }

const QTextCharFormat &ItemData::getFormat() const {
    return format;
}

bool ItemData::makeFormat() {

    format.setForeground(QBrush(m_color));

    format.setFontItalic(m_italic);
    format.setFontUnderline(m_underlined);
    format.setFontStrikeOut(m_strikedOut);
    return true;
}
