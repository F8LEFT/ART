/* This file is part of the KDE libraries
 *  Copyright (C) 2003-2005 Hamish Rodda <rodda@kde.org>
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public License
 *  along with this library; see the file COPYING.LIB.  If not, write to
 *  the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA 02110-1301, USA.
 */

#ifndef KTEXTEDITOR_ATTRIBUTE_H
#define KTEXTEDITOR_ATTRIBUTE_H

#include <QTextFormat>

#include <QSharedData>
#include <QExplicitlySharedDataPointer>


class QAction;

namespace KTextEditor
{

/**
 * The following lists all valid default styles that are used for the syntax
 * highlighting files in the itemData's defStyleNum attribute.
 * Not all default styles are used by a syntax highlighting file.
 */
enum DefaultStyle {
    //
    // normal text
    //
    /** Default for normal text and source code. */
    dsNormal = 0,
    /** Used for language keywords. */
    dsKeyword,
    /** Used for function definitions and function calls. */
    dsFunction,
    /** Used for variables, if applicable. */
    dsVariable,
    /** Used for control flow highlighting, e.g., if, then, else, return, continue. */
    dsControlFlow,
    /** Used for operators such as +, -, *, / and :: etc. */
    dsOperator,
    /** Used for built-in language classes and functions. */
    dsBuiltIn,
    /** Used for extensions, such as Qt or boost. */
    dsExtension,
    /** Used for preprocessor statements. */
    dsPreprocessor,
    /** Used for attributes of a function, e.g. \@override in Java. */
    dsAttribute,

    //
    // Strings & Characters
    //
    /** Used for a single character. */
    dsChar,
    /** Used for an escaped character. */
    dsSpecialChar,
    /** Used for strings. */
    dsString,
    /** Used for verbatim strings such as HERE docs. */
    dsVerbatimString,
    /** Used for special strings such as regular expressions or LaTeX math mode. */
    dsSpecialString,
    /** Used for includes, imports and modules. */
    dsImport,

    //
    // Number, Types & Constants
    //
    /** Used for data types such as int, char, float etc. */
    dsDataType,
    /** Used for decimal values. */
    dsDecVal,
    /** Used for numbers with base other than 10. */
    dsBaseN,
    /** Used for floating point numbers. */
    dsFloat,
    /** Used for language constants. */
    dsConstant,

    //
    // Comments & Documentation
    //
    /** Used for normal comments. */
    dsComment,
    /** Used for comments that reflect API documentation. */
    dsDocumentation,
    /** Used for annotations in comments, e.g. \@param in Doxygen or JavaDoc. */
    dsAnnotation,
    /** Used to refer to variables in a comment, e.g. after \@param in Doxygen or JavaDoc. */
    dsCommentVar,
    /** Used for region markers, typically defined by BEGIN/END. */
    dsRegionMarker,
    /** Used for information, e.g. the keyword \@note in Doxygen. */
    dsInformation,
    /** Used for warnings, e.g. the keyword \@warning in Doxygen. */
    dsWarning,
    /** Used for comment specials TODO and WARNING in comments. */
    dsAlert,

    //
    // Misc
    //
    /** Used for attributes that do not match any of the other default styles. */
    dsOthers,
    /** Used to indicate wrong syntax. */
    dsError

    //
    // WARNING: Whenever you add a default style to this list,
    //          make sure to adapt KateHlManager::defaultStyleCount()
    //
};

/**
 * \brief A class which provides customized text decorations.
 *
 * The Attribute class extends QTextCharFormat, the class which Qt
 * uses internally to provide formatting information to characters
 * in a text document.
 *
 * In addition to its inherited properties, it provides support for:
 * \li several customized text formatting properties
 * \li dynamic highlighting of associated ranges of text
 * \li binding of actions with associated ranges of text (note: not currently implemented)
 *
 * Implementations are not required to support all properties.
 * In particular, several properties are not supported for dynamic
 * highlighting (notably: font() and fontBold()).
 *
 * Unfortunately, as QTextFormat's setProperty() is not virtual,
 * changes that are made to this attribute cannot automatically be
 * redrawn.  Once you have finished changing properties, you should
 * call changed() to force redrawing of affected ranges of text.
 *
 * \sa MovingInterface
 *
 * \author Hamish Rodda \<rodda@kde.org\>
 */
class Attribute : public QTextCharFormat, public QSharedData
{
public:
    /**
     * Shared data pointer for Attribute
     */
    typedef QExplicitlySharedDataPointer<Attribute> Ptr;

    /**
     * Default constructor.
     * The resulting Attribute has no properties set to begin with.
     */
    Attribute();
    
    /**
     * Construct attribute with given name & default style properties.
     * @param name attribute name
     * @param style attribute default style
     */
    Attribute(const QString &name, DefaultStyle style);

    /**
     * Copy constructor.
     */
    Attribute(const Attribute &a);

    Attribute(const QTextCharFormat& format);
    /**
     * Virtual destructor.
     */
    virtual ~Attribute();

    //BEGIN custom properties

    /**
     * \name Custom properties
     *
     * The following functions provide custom properties which can be set for
     * rendering by editor implementations.
     * \{
     */
    
    /**
     * Attribute name
     * 
     * \return attribute name
     */
    QString name() const;
    
    /**
     * Set attribute name
     * 
     * \param name new attribute name
     */
    void setName(const QString &name);

    /**
     * Default style of this attribute
     * 
     * \return default style
     */
    DefaultStyle defaultStyle() const;
    
    /**
     * Set default style of this attribute
     * 
     * \param style new default style
     */
    void setDefaultStyle(DefaultStyle style);

    /**
     * Should spellchecking be skipped?
     * 
     * \return skip spellchecking?
     */
    bool skipSpellChecking() const;
    
    /**
     * Set if we should spellchecking be skipped?
     * 
     * @param skipspellchecking should spellchecking be skipped?
     */
    void setSkipSpellChecking(bool skipspellchecking);

    /**
     * Find out if the font weight is set to QFont::Bold.
     *
     * \return \c true if the font weight is exactly QFont::Bold, otherwise \c false
     *
     * \see QTextCharFormat::fontWeight()
     */
    bool fontBold() const;

    /**
     * Set the font weight to QFont::Bold.  If \a bold is \p false, the weight will be set to 0 (normal).
     *
     * \param bold whether the font weight should be bold or not.
     *
     * \see QTextCharFormat::setFontWeight()
     */
    void setFontBold(bool bold = true);

    /**
     * Get the brush used to draw an outline around text, if any.
     *
     * \return brush to be used to draw an outline, or Qt::NoBrush if no outline is set.
     */
    QBrush outline() const;

    /**
     * Set a brush to be used to draw an outline around text.
     *
     * Use \p clearProperty(Outline) to clear.
     *
     * \param brush brush to be used to draw an outline.
     */
    void setOutline(const QBrush &brush);

    /**
     * Get the brush used to draw text when it is selected, if any.
     *
     * \return brush to be used to draw selected text, or Qt::NoBrush if not set
     */
    QBrush selectedForeground() const;

    /**
     * Set a brush to be used to draw selected text.
     *
     * Use \p clearProperty(SelectedForeground) to clear.
     *
     * \param foreground brush to be used to draw selected text.
     */
    void setSelectedForeground(const QBrush &foreground);

    /**
     * Get the brush used to draw the background of selected text, if any.
     *
     * \return brush to be used to draw the background of selected text, or Qt::NoBrush if not set
     */
    QBrush selectedBackground() const;

    /**
     * Set a brush to be used to draw the background of selected text, if any.
     *
     * Use \p clearProperty(SelectedBackground) to clear.
     *
     * \param brush brush to be used to draw the background of selected text
     */
    void setSelectedBackground(const QBrush &brush);

    /**
     * Determine whether background color is drawn over whitespace. Defaults to true if not set.
     *
     * \return whether the background color should be drawn over whitespace
     */
    bool backgroundFillWhitespace() const;

    /**
     * Set whether background color is drawn over whitespace. Defaults to true if not set.
     *
     * Use \p clearProperty(BackgroundFillWhitespace) to clear.
     *
     * \param fillWhitespace whether the background should be drawn over whitespace.
     */
    void setBackgroundFillWhitespace(bool fillWhitespace);

    /**
     * Clear all set properties.
     */
    void clear();

    /**
     * Determine if any properties are set.
     *
     * \return \e true if any properties are set, otherwise \e false
     */
    bool hasAnyProperty() const;

    //END

    //BEGIN Dynamic highlighting

    /**
     * \name Dynamic highlighting
     *
     * The following functions allow for text to be highlighted dynamically based on
     * several events.
     * \{
     */

    /**
     * Several automatic activation mechanisms exist for associated attributes.
     * Using this you can conveniently have your ranges highlighted when either
     * the mouse or cursor enter the range.
     */
    enum ActivationType {
        /// Activate attribute on mouse in
        ActivateMouseIn = 0,
        /// Activate attribute on caret in
        ActivateCaretIn
    };

    /**
     * Return the attribute to use when the event referred to by \a type occurs.
     *
     * \param type the activation type for which to return the Attribute.
     *
     * \returns the attribute to be used for events specified by \a type, or null if none is set.
     */
    Attribute::Ptr dynamicAttribute(ActivationType type) const;

    /**
     * Set the attribute to use when the event referred to by \a type occurs.
     *
     * \note Nested dynamic attributes are ignored.
     *
     * \param type the activation type to set the attribute for
     * \param attribute the attribute to assign. As attribute is refcounted, ownership is not an issue.
     */
    void setDynamicAttribute(ActivationType type, Attribute::Ptr attribute);

    //!\}

    //END

    /**
     * Addition assignment operator.  Use this to merge another Attribute with this Attribute.
     * Where both attributes have a particular property set, the property in \a a will
     * be used.
     *
     * \param a attribute to merge into this attribute.
     */
    Attribute &operator+=(const Attribute &a);

    /**
     * Replacement assignment operator.  Use this to overwrite this Attribute with another Attribute.
     *
     * \param a attribute to assign to this attribute.
     */
    Attribute &operator=(const Attribute &a);

private:
    /**
     * Private d-pointer
     */
    class AttributePrivate *const d;
};

/**
 * @brief Attribute%s of a part of a line.
 *
 * An AttributeBlock represents an Attribute spanning the interval
 * [start, start + length) of a given line. An AttributeBlock is
 * obtained by calling KTextEditor::View::lineAttributes().
 *
 * \see KTextEditor::View::lineAttributes()
 */
class AttributeBlock
{
public:
    /**
     * Constructor of AttributeBlock.
     */
    AttributeBlock(int _start, int _length, const Attribute::Ptr &_attribute)
        : start(_start), length(_length), attribute(_attribute) {
    }

    /**
     * The column this attribute starts at.
     */
    int start;

    /**
     * The number of columns this attribute spans.
     */
    int length;

    /**
     * The attribute for the current range.
     */
    Attribute::Ptr attribute;
};

}

Q_DECLARE_TYPEINFO(KTextEditor::AttributeBlock, Q_MOVABLE_TYPE);

#endif
