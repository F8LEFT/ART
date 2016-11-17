/* This file is part of the KDE libraries
   Copyright (C) 2001,2002 Joseph Wenninger <jowenn@kde.org>
   Copyright (C) 2001 Christoph Cullmann <cullmann@kde.org>
   Copyright (C) 1999 Jochen Wilhelmy <digisnap@cs.tu-berlin.de>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef __KATE_SYNTAXMANAGER_H__
#define __KATE_SYNTAXMANAGER_H__

#include "kateextendedattribute.h"
#include "katesyntaxdocument.h"


#include <QVector>
#include <QList>
#include <QHash>
#include <QMap>

#include <QObject>
#include <QStringList>
#include <QPointer>
#include <QDate>
#include <QLinkedList>

class KateHighlighting;

/**
 * Information about each syntax hl Mode. This is documented in Kate's
 * <a href="http://docs.kde.org/stable/en/kdebase/kate/katehighlight-xml-format.html">user guide</a>
 * and repeated briefly here.
 */
class KateSyntaxModeListItem
{
public:
    QString name;           ///< Name of the mode (eg. Asm6502)
    QString nameTranslated; ///< i18n of same, for display purposes
    QString section;        ///< Submenu section (eg. Assembly)
    QString mimetype;       ///< Mimetypes this mode applies to
    QString extension;      ///< Semicolon-separated list of file extensions
    QString identifier;
    QString version;
    QString priority;       /**< Priority (mapped to an integer?) for conflict-
                                 resolution when the same file extension has
                                 multiple highlihgting definitions. */
    QString style;          ///< Default styles provided by the highlighter
    QString author;         ///< Author's name
    QString license;        ///< License; for example: "LGPL"
    QString indenter;       ///< Indenter to use for this highlighting
    bool hidden;            ///< Hides the mode from Kate's menus
};

/**
 * List of the KateSyntaxModeListItems holding all the syntax mode list items
 */
typedef QList<KateSyntaxModeListItem *> KateSyntaxModeList;

class KateHlManager : public QObject
{
    Q_OBJECT

public:
    KateHlManager();
    ~KateHlManager();

    static KateHlManager *self();

    KateSyntaxDocument *syntaxDocument()
    {
        return &syntax;
    }


    KateHighlighting *getHl(int n);
    int nameFind(const QString &name);

    QString identifierForName(const QString &);
    /**
     * Returns the mode name for a given identifier, as e.g.
     * returned by KateHighlighting::hlKeyForAttrib().
     */
    QString nameForIdentifier(const QString &);

    void getDefaults(const QString &schema, KateAttributeList &);
    void setDefaults(const QString &schema, KateAttributeList &);

    int highlights();
    QString hlName(int n);
    QString hlNameTranslated(int n);
    QString hlSection(int n);
    bool hlHidden(int n);

    void incDynamicCtxs()
    {
        ++dynamicCtxsCount;
    }
    int countDynamicCtxs()
    {
        return dynamicCtxsCount;
    }
    void setForceNoDCReset(bool b)
    {
        forceNoDCReset = b;
    }

    // be carefull: all documents hl should be invalidated after having successfully called this method!
    bool resetDynamicCtxs();
    
    void reload();

Q_SIGNALS:
    void changed();

//
// methodes to get the default style count + names
//
public:
    /**
     * Return the number of default styles.
     */
    static int defaultStyleCount();

    /**
     * Return the name of default style @p n. If @p translateNames is @e true,
     * the default style name is translated.
     */
    static QString defaultStyleName(int n, bool translateNames = false);

    /**
     * Return the index for the default style @p name.
     * @param name @e untranslated default style
     * @see KTextEditor::DefaultStyles)
     */
    static int defaultStyleNameToIndex(const QString &name);

    /**
     * Get the mode list
     * @return mode list
     */
    const KateSyntaxModeList &modeList()
    {
        return myModeList;
    }

private:
    friend class KateHighlighting;

    /**
     * Generate the list of hl modes, store them in myModeList
     */
    void setupModeList();

    /**
     * List of mode items
     */
    KateSyntaxModeList myModeList;

    // This list owns objects it holds, thus they should be deleted when the object is removed
    QList<KateHighlighting *> hlList;
    // This hash does not own the objects it holds, thus they should not be deleted
    QHash<QString, KateHighlighting *> hlDict;

    QStringList commonSuffixes;

    KateSyntaxDocument syntax;

    int dynamicCtxsCount;
    QTime lastCtxsReset;
    bool forceNoDCReset;
};

#endif

