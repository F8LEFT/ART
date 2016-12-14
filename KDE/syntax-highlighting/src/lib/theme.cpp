/*
    Copyright (C) 2016 Volker Krause <vkrause@kde.org>

    This program is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This program is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "theme.h"
#include "themedata_p.h"

#include <QCoreApplication>

using namespace KSyntaxHighlighting;

Theme::Theme()
{
}

Theme::Theme(const Theme &copy)
{
    m_data = copy.m_data;
}

Theme::Theme(ThemeData* data)
    : m_data(data)
{
}

Theme::~Theme()
{
}

bool Theme::makeData()
{
    if(isValid())
        return false;
    m_data = new ThemeData;
    return true;
}

Theme &Theme::operator=(const Theme &other)
{
    m_data = other.m_data;
    return *this;
}

bool Theme::isValid() const
{
    return m_data.data();
}

QString Theme::name() const
{
    return m_data ? m_data->name() : QString();
}

void Theme::setName(const QString& n)
{
    if(m_data) {
        m_data->setName(n);
    }
}

QString Theme::translatedName() const
{
    return m_data ? QCoreApplication::instance()->translate("Theme", m_data->name().toUtf8().constData())
                  : QString();
}

bool Theme::isReadOnly() const
{
    return m_data ? m_data->isReadOnly() : false;
}

void Theme::setReadOnly(bool b)
{
    if(m_data) {
        m_data->setReadOnly(b);
    }
}

QString Theme::filePath() const
{
    return m_data ? m_data->filePath() : QString();
}

QRgb Theme::textColor(TextStyle style) const
{
    return m_data ? m_data->textColor(style) : 0;
}

void Theme::setTextColor(Theme::TextStyle style, QRgb rgb) const
{
    if(m_data) {
        m_data->setTextColor(style, rgb);
    }
}

QRgb Theme::selectedTextColor(TextStyle style) const
{
    return m_data ? m_data->selectedTextColor(style) : 0;
}

void Theme::setSelectedTextColor(Theme::TextStyle style, QRgb rgb) const
{
    if(m_data) {
        m_data->setSelectedTextColor(style, rgb);
    }
}

QRgb Theme::backgroundColor(TextStyle style) const
{
    return m_data ? m_data->backgroundColor(style) : 0;
}

void Theme::setBackgroundColor(Theme::TextStyle style, QRgb rgb) const
{
    if(m_data) {
        m_data->setBackgroundColor(style, rgb);
    }
}

QRgb Theme::selectedBackgroundColor(TextStyle style) const
{
    return m_data ? m_data->selectedBackgroundColor(style) : 0;
}

void Theme::setSelectedBackgroundColor(Theme::TextStyle style, QRgb rgb) const
{
    if(m_data) {
        m_data->setSelectedBackgroundColor(style, rgb);
    }
}

bool Theme::isBold(TextStyle style) const
{
    return m_data ? m_data->isBold(style) : false;
}

void Theme::setBold(Theme::TextStyle style, bool b) const
{
    if(m_data) {
        m_data->setBold(style, b);
    }
}

bool Theme::isItalic(TextStyle style) const
{
    return m_data ? m_data->isItalic(style) : false;
}

void Theme::setItalic(Theme::TextStyle style, bool b) const
{
    if(m_data) {
        m_data->setItalic(style, b);
    }
}

bool Theme::isUnderline(TextStyle style) const
{
    return m_data ? m_data->isUnderline(style) : false;
}

void Theme::setUnderline(Theme::TextStyle style, bool b) const
{
    if(m_data) {
        m_data->setUnderline(style, b);
    }
}

bool Theme::isStrikeThrough(TextStyle style) const
{
    return m_data ? m_data->isStrikeThrough(style) : false;
}

void Theme::setStrikeThrough(Theme::TextStyle style, bool b) const
{
    if(m_data) {
        m_data->setStrikeThrough(style, b);
    }
}

QRgb Theme::editorColor(EditorColorRole role) const
{
    return m_data ? m_data->editorColor(role) : 0;
}

void Theme::setEditorColor(Theme::EditorColorRole role, QRgb rgb) const
{
    if(m_data) {
        m_data->setEditorColor(role, rgb);
    }
}

QByteArray Theme::getThemeConfig() {
    return m_data ? m_data->getThemeConfig() : QByteArray("");
}

QString Theme::getTextStyleName(int n, bool translated) {
    static QStringList names;
    static QStringList translatedNames;

    if (names.isEmpty()) {
        names << QStringLiteral("Normal");
        names << QStringLiteral("Keyword");
        names << QStringLiteral("Function");
        names << QStringLiteral("Variable");
        names << QStringLiteral("Control Flow");
        names << QStringLiteral("Operator");
        names << QStringLiteral("Built-in");
        names << QStringLiteral("Extension");
        names << QStringLiteral("Preprocessor");
        names << QStringLiteral("Attribute");

        names << QStringLiteral("Character");
        names << QStringLiteral("Special Character");
        names << QStringLiteral("String");
        names << QStringLiteral("Verbatim String");
        names << QStringLiteral("Special String");
        names << QStringLiteral("Import");

        names << QStringLiteral("Data Type");
        names << QStringLiteral("Decimal/Value");
        names << QStringLiteral("Base-N Integer");
        names << QStringLiteral("Floating Point");
        names << QStringLiteral("Constant");

        names << QStringLiteral("Comment");
        names << QStringLiteral("Documentation");
        names << QStringLiteral("Annotation");
        names << QStringLiteral("Comment Variable");
        // this next one is for denoting the beginning/end of a user defined folding region
        names << QStringLiteral("Region Marker");
        names << QStringLiteral("Information");
        names << QStringLiteral("Warning");
        names << QStringLiteral("Alert");

        // this one is for marking invalid input
        names << QStringLiteral("Error");
        names << QStringLiteral("Others");


        translatedNames << QObject::tr("Normal");
        translatedNames << QObject::tr("Keyword");
        translatedNames << QObject::tr("Function");
        translatedNames << QObject::tr("Variable");
        translatedNames << QObject::tr("Control Flow");
        translatedNames << QObject::tr("Operator");
        translatedNames << QObject::tr("Built-in");
        translatedNames << QObject::tr("Extension");
        translatedNames << QObject::tr("Preprocessor");
        translatedNames << QObject::tr("Attribute");

        translatedNames << QObject::tr("Character");
        translatedNames << QObject::tr("Special Character");
        translatedNames << QObject::tr("String");
        translatedNames << QObject::tr("Verbatim String");
        translatedNames << QObject::tr("Special String");
        translatedNames << QObject::tr("Imports, Modules, Includes");

        translatedNames << QObject::tr("Data Type");
        translatedNames << QObject::tr("Decimal/Value");
        translatedNames << QObject::tr("Base-N Integer");
        translatedNames << QObject::tr("Floating Point");
        translatedNames << QObject::tr("Constant");

        translatedNames << QObject::tr("Comment");
        translatedNames << QObject::tr("Documentation");
        translatedNames << QObject::tr("Annotation");
        translatedNames << QObject::tr("Comment Variable");
        // this next one is for denoting the beginning/end of a user defined folding region
        translatedNames << QObject::tr("Region Marker");
        translatedNames << QObject::tr("Information");
        translatedNames << QObject::tr("Warning");
        translatedNames << QObject::tr("Alert");

        // this one is for marking invalid input
        translatedNames << QObject::tr("Error");
        translatedNames << QObject::tr("Others");

    }

    // sanity checks
    Q_ASSERT(n >= 0);
    Q_ASSERT(n < names.size());

    return translated ? translatedNames[n] : names[n];
}

QString Theme::getEditorColorRoleName(int n, bool translated) {
    static QStringList names;
    static QStringList translatedNames;

    if (names.isEmpty()) {
        names << QStringLiteral("BackgroundColor");
        names << QStringLiteral("TextSelection");
        names << QStringLiteral("CurrentLine");
        names << QStringLiteral("SearchHighlight");
        names << QStringLiteral("ReplaceHighlight");
        names << QStringLiteral("BracketMatching");
        names << QStringLiteral("TabMarker");
        names << QStringLiteral("SpellChecking");
        names << QStringLiteral("IndentationLine");
        names << QStringLiteral("IconBorder");
        names << QStringLiteral("CodeFolding");
        names << QStringLiteral("LineNumbers");
        names << QStringLiteral("CurrentLineNumber");
        names << QStringLiteral("WordWrapMarker");
        names << QStringLiteral("ModifiedLines");
        names << QStringLiteral("SavedLines");
        names << QStringLiteral("Separator");
        names << QStringLiteral("MarkBookmark");
        names << QStringLiteral("MarkBreakpointActive");
        names << QStringLiteral("MarkBreakpointReached");
        names << QStringLiteral("MarkBreakpointDisabled");
        names << QStringLiteral("MarkExecution");
        names << QStringLiteral("MarkWarning");
        names << QStringLiteral("MarkError");
        names << QStringLiteral("TemplateBackground");
        names << QStringLiteral("TemplatePlaceholder");
        names << QStringLiteral("TemplateFocusedPlaceholder");
        names << QStringLiteral("TemplateReadOnlyPlaceholder");


        translatedNames << QObject::tr("BackgroundColor");
        translatedNames << QObject::tr("TextSelection");
        translatedNames << QObject::tr("CurrentLine");
        translatedNames << QObject::tr("SearchHighlight");
        translatedNames << QObject::tr("ReplaceHighlight");
        translatedNames << QObject::tr("BracketMatching");
        translatedNames << QObject::tr("TabMarker");
        translatedNames << QObject::tr("SpellChecking");
        translatedNames << QObject::tr("IndentationLine");
        translatedNames << QObject::tr("IconBorder");
        translatedNames << QObject::tr("CodeFolding");
        translatedNames << QObject::tr("LineNumbers");
        translatedNames << QObject::tr("CurrentLineNumber");
        translatedNames << QObject::tr("WordWrapMarker");
        translatedNames << QObject::tr("ModifiedLines");
        translatedNames << QObject::tr("SavedLines");
        translatedNames << QObject::tr("Separator");
        translatedNames << QObject::tr("MarkBookmark");
        translatedNames << QObject::tr("MarkBreakpointActive");
        translatedNames << QObject::tr("MarkBreakpointReached");
        translatedNames << QObject::tr("MarkBreakpointDisabled");
        translatedNames << QObject::tr("MarkExecution");
        translatedNames << QObject::tr("MarkWarning");
        translatedNames << QObject::tr("MarkError");
        translatedNames << QObject::tr("TemplateBackground");
        translatedNames << QObject::tr("TemplatePlaceholder");
        translatedNames << QObject::tr("TemplateFocusedPlaceholder");
        translatedNames << QObject::tr("TemplateReadOnlyPlaceholder");
    }

    // sanity checks
    Q_ASSERT(n >= 0);
    Q_ASSERT(n < names.size());

    return translated ? translatedNames[n] : names[n];
}

bool Theme::loadFromJson(const QByteArray &jsonData) {
    if(m_data) {
        return m_data->loadFromJson(jsonData);
    }
    return false;
}




