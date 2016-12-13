/* This file is part of the KDE libraries
   Copyright (C) 2007 Sebastian Pipping <webmaster@hartwork.org>
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

#include "wildcardmatcher_p.h"

using namespace KSyntaxHighlighting;

#include <QString>
#include <QChar>

static bool exactMatch(const QString &candidate, const QString &wildcard, int candidatePosFromRight,
                       int wildcardPosFromRight, bool caseSensitive = true)
{
    for (; wildcardPosFromRight >= 0; wildcardPosFromRight--) {
        const auto ch = wildcard.at(wildcardPosFromRight).unicode();
        switch (ch) {
        case L'*':
            if (candidatePosFromRight == -1) {
                break;
            }

            if (wildcardPosFromRight == 0) {
                return true;
            }

            // Eat all we can and go back as far as we have to
            for (int j = -1; j <= candidatePosFromRight; j++) {
                if (exactMatch(candidate, wildcard, j, wildcardPosFromRight - 1)) {
                    return true;
                }
            }
            return false;

        case L'?':
            if (candidatePosFromRight == -1) {
                return false;
            }

            candidatePosFromRight--;
            break;

        default:
            if (candidatePosFromRight == -1) {
                return false;
            }

            const auto candidateCh = candidate.at(candidatePosFromRight).unicode();
            const auto match = caseSensitive ? (candidateCh == ch) : (QChar::toLower(candidateCh) == QChar::toLower(ch));
            if (match) {
                candidatePosFromRight--;
            } else {
                return false;
            }
        }
    }
    return true;
}

bool WildcardMatcher::exactMatch(const QString &candidate, const QString &wildcard,
                                 bool caseSensitive)
{
    return exactMatch(candidate, wildcard, candidate.length() - 1, wildcard.length() - 1, caseSensitive);
}
