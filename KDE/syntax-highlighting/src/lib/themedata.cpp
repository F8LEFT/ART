/*
    Copyright (C) 2016 Volker Krause <vkrause@kde.org>
    Copyright (C) 2016 Dominik Haumann <dhaumann@kde.org>

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

#include "themedata_p.h"
#include "ksyntaxhighlighting_logging.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QMetaEnum>

#include <QVariantMap>

#include <QDebug>

using namespace KSyntaxHighlighting;

ThemeData* ThemeData::get(const Theme &theme)
{
    return theme.m_data.data();
}

ThemeData::ThemeData()
    : m_revision(0)
    , m_readOnly(true)
{
    memset(m_editorColors, 0, sizeof(m_editorColors));
}

/**
 * Convert QJsonValue @p val into a color, if possible. Valid colors are only
 * in hex format: #rrggbb. On error, returns 0x00000000.
 */
static inline QRgb readColor(const QJsonValue &val)
{
    const QRgb unsetColor = 0;
    if (!val.isString()) {
        return unsetColor;
    }
    const QString str = val.toString();
    if (str.isEmpty() || str[0] != QLatin1Char('#')) {
        return unsetColor;
    }
    const QColor color(str);
    return color.isValid() ? color.rgb() : unsetColor;
}

static inline TextStyleData readThemeData(const QJsonObject &obj)
{
    TextStyleData td;

    td.textColor = readColor(obj.value(QLatin1String("text-color")));
    td.backgroundColor = readColor(obj.value(QLatin1String("background-color")));
    td.selectedTextColor = readColor(obj.value(QLatin1String("selected-text-color")));
    td.selectedBackgroundColor = readColor(obj.value(QLatin1String("selected-background-color")));

    auto val = obj.value(QLatin1String("bold"));
    if (val.isBool()) {
        td.bold = val.toBool();
        td.hasBold = true;
    }
    val = obj.value(QLatin1String("italic"));
    if (val.isBool()) {
        td.italic = val.toBool();
        td.hasItalic = true;
    }
    val = obj.value(QLatin1String("underline"));
    if (val.isBool()) {
        td.underline = val.toBool();
        td.hasUnderline = true;
    }
    val = obj.value(QLatin1String("strike-through"));
    if (val.isBool()) {
        td.strikeThrough = val.toBool();
        td.hasStrikeThrough = true;
    }

    return td;
}

bool ThemeData::load(const QString &filePath)
{
    QFile loadFile(filePath);
    if (!loadFile.open(QIODevice::ReadOnly)) {
        return false;
    }
    m_filePath = filePath;

    const QByteArray jsonData = loadFile.readAll();
    return loadFromJson(jsonData);
}


bool ThemeData::loadFromJson(const QByteArray &jsonData)
{
    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        qCWarning(Log) << "Failed to parse theme file" << m_filePath << ":" << parseError.errorString();
        return false;
    }

    QJsonObject obj = jsonDoc.object();

    // read metadata
    const QJsonObject metadata = obj.value(QLatin1String("metadata")).toObject();
    m_name = metadata.value(QLatin1String("name")).toString();
    m_revision = metadata.value(QLatin1String("revision")).toInt();
    m_author = metadata.value(QLatin1String("author")).toString();
    m_license = metadata.value(QLatin1String("license")).toString();
    m_readOnly = metadata.value(QLatin1String("read-only")).toBool();

    // read text styles
    static const auto idx = Theme::staticMetaObject.indexOfEnumerator("TextStyle");
    Q_ASSERT(idx >= 0);
    const auto metaEnum = Theme::staticMetaObject.enumerator(idx);
    const QJsonObject textStyles = obj.value(QLatin1String("text-styles")).toObject();
    for (int i = 0; i < metaEnum.keyCount(); ++i) {
        Q_ASSERT(i == metaEnum.value(i));
        m_textStyles[i] = readThemeData(textStyles.value(QLatin1String(metaEnum.key(i))).toObject());
    }

    // read editor area colors
    const QJsonObject editorColors = obj.value(QLatin1String("editor-colors")).toObject();
    m_editorColors[Theme::BackgroundColor] = readColor(editorColors.value(QLatin1String("background-color")));
    m_editorColors[Theme::TextSelection] = readColor(editorColors.value(QLatin1String("selection")));
    m_editorColors[Theme::CurrentLine] = readColor(editorColors.value(QLatin1String("current-line")));
    m_editorColors[Theme::SearchHighlight] = readColor(editorColors.value(QLatin1String("search-highlight")));
    m_editorColors[Theme::ReplaceHighlight] = readColor(editorColors.value(QLatin1String("replace-highlight")));
    m_editorColors[Theme::BracketMatching] = readColor(editorColors.value(QLatin1String("bracket-matching")));
    m_editorColors[Theme::TabMarker] = readColor(editorColors.value(QLatin1String("tab-marker")));
    m_editorColors[Theme::SpellChecking] = readColor(editorColors.value(QLatin1String("spell-checking")));
    m_editorColors[Theme::IndentationLine] = readColor(editorColors.value(QLatin1String("indentation-line")));
    m_editorColors[Theme::IconBorder] = readColor(editorColors.value(QLatin1String("icon-border")));
    m_editorColors[Theme::CodeFolding] = readColor(editorColors.value(QLatin1String("code-folding")));
    m_editorColors[Theme::LineNumbers] = readColor(editorColors.value(QLatin1String("line-numbers")));
    m_editorColors[Theme::CurrentLineNumber] = readColor(editorColors.value(QLatin1String("current-line-number")));
    m_editorColors[Theme::WordWrapMarker] = readColor(editorColors.value(QLatin1String("word-wrap-marker")));
    m_editorColors[Theme::ModifiedLines] = readColor(editorColors.value(QLatin1String("modified-lines")));
    m_editorColors[Theme::SavedLines] = readColor(editorColors.value(QLatin1String("saved-lines")));
    m_editorColors[Theme::Separator] = readColor(editorColors.value(QLatin1String("separator")));
    m_editorColors[Theme::MarkBookmark] = readColor(editorColors.value(QLatin1String("mark-bookmark")));
    m_editorColors[Theme::MarkBreakpointActive] = readColor(editorColors.value(QLatin1String("mark-breakpoint-active")));
    m_editorColors[Theme::MarkBreakpointReached] = readColor(editorColors.value(QLatin1String("mark-breakpoint-reached")));
    m_editorColors[Theme::MarkBreakpointDisabled] = readColor(editorColors.value(QLatin1String("mark-breakpoint-disabled")));
    m_editorColors[Theme::MarkExecution] = readColor(editorColors.value(QLatin1String("mark-execution")));
    m_editorColors[Theme::MarkWarning] = readColor(editorColors.value(QLatin1String("mark-warning")));
    m_editorColors[Theme::MarkError] = readColor(editorColors.value(QLatin1String("mark-error")));
    m_editorColors[Theme::TemplateBackground] = readColor(editorColors.value(QLatin1String("template-background")));
    m_editorColors[Theme::TemplatePlaceholder] = readColor(editorColors.value(QLatin1String("template-placeholder")));
    m_editorColors[Theme::TemplateFocusedPlaceholder] = readColor(editorColors.value(QLatin1String("template-focused-placeholder")));
    m_editorColors[Theme::TemplateReadOnlyPlaceholder] = readColor(editorColors.value(QLatin1String("template-read-only-placeholder")));

    // read per-definition style overrides
    const auto customStyles = obj.value(QLatin1String("custom-styles")).toObject();
    for (auto it = customStyles.begin(); it != customStyles.end(); ++it) {
        const auto obj = it.value().toObject();
        QHash<QString, TextStyleData> overrideStyle;
        for (auto it2 = obj.begin(); it2 != obj.end(); ++it2)
            overrideStyle.insert(it2.key(), readThemeData(it2.value().toObject()));
        m_textStyleOverrides.insert(it.key(), overrideStyle);
    }

    return true;
}

QByteArray ThemeData::getThemeConfig()
{
    QVariantMap themeConfig;
    QVariantMap metadata;
    QVariantMap textStyles;
    QVariantMap editorColors;

    // set text styles
    metadata.insert(QLatin1String("name"), m_name);
    metadata.insert(QLatin1String("revision"), m_revision);
    metadata.insert(QLatin1String("author"), m_author);
    metadata.insert(QLatin1String("license"), m_license);
    metadata.insert(QLatin1String("read-only"), m_readOnly);

    // set text styles
    static const auto idx = Theme::staticMetaObject.indexOfEnumerator("TextStyle");
    Q_ASSERT(idx >= 0);
    const auto metaEnum = Theme::staticMetaObject.enumerator(idx);
    for (int i = 0; i < metaEnum.keyCount(); ++i) {
        Q_ASSERT(i == metaEnum.value(i));
        QVariantMap style;

        auto& td = m_textStyles[i];

        if(td.textColor != 0) {
            style.insert(QLatin1String("text-color"), QColor(td.textColor).name());
        }
        if(td.backgroundColor != 0) {
            style.insert(QLatin1String("background-color"), QColor(td.backgroundColor).name());
        }
        if(td.selectedTextColor != 0) {
            style.insert(QLatin1String("selected-text-color"), QColor(td.selectedTextColor).name());
        }
        if(td.selectedBackgroundColor != 0) {
            style.insert(QLatin1String("selected-background-color"), QColor(td.selectedBackgroundColor).name());
        }
        if(td.bold) {
            style.insert(QLatin1String("bold"), td.bold);
        }
        if(td.italic) {
            style.insert(QLatin1String("italic"), td.italic);

        }
        if(td.underline) {
            style.insert(QLatin1String("underline"), td.underline);
        }
        if(td.strikeThrough) {
            style.insert(QLatin1String("strike-through"), td.strikeThrough);
        }
        textStyles.insert(QLatin1String(metaEnum.key(i)), style);
    }

    editorColors.insert(QLatin1String("background-color"), QColor(m_editorColors[Theme::BackgroundColor]).name());
    editorColors.insert(QLatin1String("selection"), QColor(m_editorColors[Theme::TextSelection]).name());
    editorColors.insert(QLatin1String("current-line"), QColor(m_editorColors[Theme::CurrentLine]).name());
    editorColors.insert(QLatin1String("search-highlight"), QColor(m_editorColors[Theme::SearchHighlight]).name());
    editorColors.insert(QLatin1String("replace-highlight"), QColor(m_editorColors[Theme::ReplaceHighlight]).name());
    editorColors.insert(QLatin1String("bracket-matching"), QColor(m_editorColors[Theme::BracketMatching]).name());
    editorColors.insert(QLatin1String("tab-marker"), QColor(m_editorColors[Theme::TabMarker]).name());
    editorColors.insert(QLatin1String("spell-checking"), QColor(m_editorColors[Theme::SpellChecking]).name());
    editorColors.insert(QLatin1String("indentation-line"), QColor(m_editorColors[Theme::IndentationLine]).name());
    editorColors.insert(QLatin1String("icon-border"), QColor(m_editorColors[Theme::IconBorder]).name());
    editorColors.insert(QLatin1String("code-folding"), QColor(m_editorColors[Theme::CodeFolding]).name());
    editorColors.insert(QLatin1String("line-numbers"), QColor(m_editorColors[Theme::LineNumbers]).name());
    editorColors.insert(QLatin1String("current-line-number"), QColor(m_editorColors[Theme::CurrentLineNumber]).name());
    editorColors.insert(QLatin1String("word-wrap-marker"), QColor(m_editorColors[Theme::WordWrapMarker]).name());
    editorColors.insert(QLatin1String("modified-lines"), QColor(m_editorColors[Theme::ModifiedLines]).name());
    editorColors.insert(QLatin1String("saved-lines"), QColor(m_editorColors[Theme::SavedLines]).name());
    editorColors.insert(QLatin1String("separator"), QColor(m_editorColors[Theme::Separator]).name());
    editorColors.insert(QLatin1String("mark-bookmark"), QColor(m_editorColors[Theme::MarkBookmark]).name());
    editorColors.insert(QLatin1String("mark-breakpoint-active"), QColor(m_editorColors[Theme::MarkBreakpointActive]).name());
    editorColors.insert(QLatin1String("mark-breakpoint-reached"), QColor(m_editorColors[Theme::MarkBreakpointReached]).name());
    editorColors.insert(QLatin1String("mark-breakpoint-disabled"), QColor(m_editorColors[Theme::MarkBreakpointDisabled]).name());
    editorColors.insert(QLatin1String("mark-execution"), QColor(m_editorColors[Theme::MarkExecution]).name());
    editorColors.insert(QLatin1String("mark-warning"), QColor(m_editorColors[Theme::MarkWarning]).name());
    editorColors.insert(QLatin1String("mark-error"), QColor(m_editorColors[Theme::MarkError]).name());
    editorColors.insert(QLatin1String("template-background"), QColor(m_editorColors[Theme::TemplateBackground]).name());
    editorColors.insert(QLatin1String("template-placeholder"), QColor(m_editorColors[Theme::TemplatePlaceholder]).name());
    editorColors.insert(QLatin1String("template-focused-placeholder"), QColor(m_editorColors[Theme::TemplateFocusedPlaceholder]).name());
    editorColors.insert(QLatin1String("template-read-only-placeholder"), QColor(m_editorColors[Theme::TemplateReadOnlyPlaceholder]).name());

    themeConfig.insert(QLatin1String("metadata"), metadata);
    themeConfig.insert(QLatin1String("text-styles"), textStyles);
    themeConfig.insert(QLatin1String("editor-colors"), editorColors);

    QJsonDocument jsonDoc = QJsonDocument::fromVariant(themeConfig);
    if(jsonDoc.isNull()) {
        return QByteArray();
    }
    return jsonDoc.toJson();
}


QString ThemeData::name() const
{
    return m_name;
}

void ThemeData::setName(const QString& n)
{
    m_name = n;
}

int ThemeData::revision() const
{
    return m_revision;
}

bool ThemeData::isReadOnly() const
{
    return m_readOnly;
}

void ThemeData::setReadOnly(bool b)
{
    m_readOnly = b;
}

QString ThemeData::filePath() const
{
    return m_filePath;
}

QRgb ThemeData::textColor(Theme::TextStyle style) const
{
    Q_ASSERT(static_cast<int>(style) >= 0 && static_cast<int>(style) <= static_cast<int>(Theme::Others));
    return m_textStyles[style].textColor;
}

void ThemeData::setTextColor(Theme::TextStyle style, QRgb rgb)
{
    Q_ASSERT(static_cast<int>(style) >= 0 && static_cast<int>(style) <= static_cast<int>(Theme::Others));
    m_textStyles[style].textColor = rgb;
}

QRgb ThemeData::selectedTextColor(Theme::TextStyle style) const
{
    Q_ASSERT(static_cast<int>(style) >= 0 && static_cast<int>(style) <= static_cast<int>(Theme::Others));
    return m_textStyles[style].selectedTextColor;
}

void ThemeData::setSelectedTextColor(Theme::TextStyle style, QRgb rgb)
{
    Q_ASSERT(static_cast<int>(style) >= 0 && static_cast<int>(style) <= static_cast<int>(Theme::Others));
    m_textStyles[style].selectedTextColor = rgb;
}

QRgb ThemeData::backgroundColor(Theme::TextStyle style) const
{
    Q_ASSERT(static_cast<int>(style) >= 0 && static_cast<int>(style) <= static_cast<int>(Theme::Others));
    return m_textStyles[style].backgroundColor;
}

void ThemeData::setBackgroundColor(Theme::TextStyle style, QRgb rgb)
{
    Q_ASSERT(static_cast<int>(style) >= 0 && static_cast<int>(style) <= static_cast<int>(Theme::Others));
    m_textStyles[style].backgroundColor = rgb;
}

QRgb ThemeData::selectedBackgroundColor(Theme::TextStyle style) const
{
    Q_ASSERT(static_cast<int>(style) >= 0 && static_cast<int>(style) <= static_cast<int>(Theme::Others));
    return m_textStyles[style].selectedBackgroundColor;
}

void ThemeData::setSelectedBackgroundColor(Theme::TextStyle style, QRgb rgb)
{
    Q_ASSERT(static_cast<int>(style) >= 0 && static_cast<int>(style) <= static_cast<int>(Theme::Others));
    m_textStyles[style].selectedBackgroundColor = rgb;
}

bool ThemeData::isBold(Theme::TextStyle style) const
{
    Q_ASSERT(static_cast<int>(style) >= 0 && static_cast<int>(style) <= static_cast<int>(Theme::Others));
    return m_textStyles[style].bold;
}

void ThemeData::setBold(Theme::TextStyle style, bool b)
{
    Q_ASSERT(static_cast<int>(style) >= 0 && static_cast<int>(style) <= static_cast<int>(Theme::Others));
    m_textStyles[style].bold = b;
}

bool ThemeData::isItalic(Theme::TextStyle style) const
{
    Q_ASSERT(static_cast<int>(style) >= 0 && static_cast<int>(style) <= static_cast<int>(Theme::Others));
    return m_textStyles[style].italic;
}

void ThemeData::setItalic(Theme::TextStyle style, bool b)
{
    Q_ASSERT(static_cast<int>(style) >= 0 && static_cast<int>(style) <= static_cast<int>(Theme::Others));
    m_textStyles[style].italic = b;
}

bool ThemeData::isUnderline(Theme::TextStyle style) const
{
    Q_ASSERT(static_cast<int>(style) >= 0 && static_cast<int>(style) <= static_cast<int>(Theme::Others));
    return m_textStyles[style].underline;
}

void ThemeData::setUnderline(Theme::TextStyle style, bool b)
{
    Q_ASSERT(static_cast<int>(style) >= 0 && static_cast<int>(style) <= static_cast<int>(Theme::Others));
    m_textStyles[style].underline = b;
}

bool ThemeData::isStrikeThrough(Theme::TextStyle style) const
{
    Q_ASSERT(static_cast<int>(style) >= 0 && static_cast<int>(style) <= static_cast<int>(Theme::Others));
    return m_textStyles[style].strikeThrough;
}

void ThemeData::setStrikeThrough(Theme::TextStyle style, bool b)
{
    Q_ASSERT(static_cast<int>(style) >= 0 && static_cast<int>(style) <= static_cast<int>(Theme::Others));
    m_textStyles[style].strikeThrough = b;
}

QRgb ThemeData::editorColor(Theme::EditorColorRole role) const
{
    Q_ASSERT(static_cast<int>(role) >= 0 && static_cast<int>(role) <= static_cast<int>(Theme::TemplateReadOnlyPlaceholder));
    return m_editorColors[role];
}

void ThemeData::setEditorColor(Theme::EditorColorRole role, QRgb rgb)
{
    Q_ASSERT(static_cast<int>(role) >= 0 && static_cast<int>(role) <= static_cast<int>(Theme::TemplateReadOnlyPlaceholder));
    m_editorColors[role] = rgb;
}

TextStyleData ThemeData::textStyleOverride(const QString& definitionName, const QString& attributeName) const
{
    return m_textStyleOverrides.value(definitionName).value(attributeName);
}
