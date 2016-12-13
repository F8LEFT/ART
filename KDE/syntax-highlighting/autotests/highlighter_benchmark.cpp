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

#include "test-config.h"

#include <abstracthighlighter.h>
#include <definition.h>
#include <repository.h>
#include <state.h>

#include <QObject>
#include <QtTest/qtest.h>

using namespace KSyntaxHighlighting;

class NullHighlighter : public AbstractHighlighter
{
public:
    void highlightFile(const QString &inFileName)
    {
        QFile f(inFileName);
        if (!f.open(QFile::ReadOnly)) {
            qWarning() << "Failed to open input file" << inFileName << ":" << f.errorString();
            return;
        }

        QTextStream in(&f);
        State state;
        while (!in.atEnd())
            state = highlightLine(in.readLine(), state);
    }

protected:
    void applyFormat(int, int, const Format&) Q_DECL_OVERRIDE {}
};

class HighlighterBenchmark : public QObject
{
    Q_OBJECT
public:
    explicit HighlighterBenchmark(QObject *parent = Q_NULLPTR) : QObject(parent), m_repo(Q_NULLPTR) {}

private:
    Repository *m_repo;

private Q_SLOTS:
    void initTestCase()
    {
        m_repo = new Repository;
    }

    void cleanupTestCase()
    {
        delete m_repo;
        m_repo = Q_NULLPTR;
    }

    void benchmarkHighlight_data()
    {
        QTest::addColumn<QString>("inFile");
        QTest::addColumn<QString>("syntax");

        QTest::newRow("mimedb") << QStringLiteral(":/qt-project.org/qmime/freedesktop.org.xml") << QStringLiteral("XML");
    }

    void benchmarkHighlight()
    {
        QFETCH(QString, inFile);
        QFETCH(QString, syntax);
        QVERIFY(m_repo);

        NullHighlighter highlighter;
        auto def = m_repo->definitionForFileName(inFile);
        if (!syntax.isEmpty())
            def = m_repo->definitionForName(syntax);
        QVERIFY(def.isValid());
        highlighter.setDefinition(def);
        QBENCHMARK {
            highlighter.highlightFile(inFile);
        }
    }

};

QTEST_GUILESS_MAIN(HighlighterBenchmark)

#include "highlighter_benchmark.moc"

