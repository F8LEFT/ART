//===- BreakPointManager.cpp - ART-GUI BreakPoint -------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#include "BreakPoint/BreakPointManager.h"
#include "BreakPointDelegate.h"

#include <utils/ScriptEngine.h>
#include <utils/CmdMsgUtil.h>

#include <QPixmap>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QToolTip>
#include <QDebug>


//BreakPointManager::BreakPointManager(QObject *parent)
//    :QObject(parent)
//{
//    ScriptEngine* script = ScriptEngine::instance();
//
//    connect(script, SIGNAL(projectOpened(QStringList)), this, SLOT(onProjectOpened(QStringList)));
//    connect(script, SIGNAL(projectClosed(QStringList)), this, SLOT(onProjectClosed()));
//}
//
//void BreakPointManager::onProjectOpened (QStringList args)
//{
//
//}
//
//void BreakPointManager::onProjectClosed()
//{
//    for(auto it = mBookMap.begin(), itEnd = mBookMap.end(); it != itEnd; it++) {
//        for(auto fileMap = it.value ().begin (), fileMapEnd = it.value ().end ();
//                fileMap != fileMapEnd; fileMap++) {
//            delBreakPoint(fileMap.value());
//        }
//        it->clear ();
//    }
//    mBookMap.clear();
//}

BreakPointManager::BreakPointManager() :
        m_breakpointIcon(QPixmap(":/images/breakpoint.png")),
        m_selectionModel(new QItemSelectionModel(this, this))
{
//    connect(ICore::instance(), &ICore::contextChanged,
//            this, &BreakPointManager::updateActionStatus);

//    connect(SessionManager::instance(), &SessionManager::sessionLoaded,
//            this, &BreakPointManager::loadBreakpoints);

    updateActionStatus();
}

BreakPointManager::~BreakPointManager()
{
    DirectoryFileBreakpointsMap::iterator it, end;
    end = m_breakpointsMap.end();
    for (it = m_breakpointsMap.begin(); it != end; ++it) {
        FileNameBreakpointsMap *bookmarks = it.value();
        qDeleteAll(*bookmarks);
        delete bookmarks;
    }
}

QItemSelectionModel *BreakPointManager::selectionModel() const
{
    return m_selectionModel;
}

bool BreakPointManager::hasBreakpointInPosition(const QString &fileName, int lineNumber)
{
    return findBreakpoint(fileName, lineNumber);
}

QModelIndex BreakPointManager::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid())
        return QModelIndex();
    else
        return createIndex(row, column);
}

QModelIndex BreakPointManager::parent(const QModelIndex &) const
{
    return QModelIndex();
}

int BreakPointManager::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    else
        return m_breakpointsList.count();
}

//int BreakPointManager::columnCount(const QModelIndex &parent) const
//{
//    if (parent.isValid())
//        return 0;
//    return 3;
//}

QVariant BreakPointManager::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.column() !=0 || index.row() < 0 || index.row() >= m_breakpointsList.count())
        return QVariant();

    BreakPoint *bookMark = m_breakpointsList.at(index.row());
    if(role == Qt::DisplayRole)
        return QVariant::fromValue<BreakPoint*>(bookMark);
    if (role == BreakPointManager::Filename)
        return bookMark->fileName();
    if (role == BreakPointManager::LineNumber)
        return bookMark->lineNumber();
    if (role == BreakPointManager::Directory)
        return QFileInfo(bookMark->fileName()).path();
    if (role == BreakPointManager::LineText)
        return bookMark->lineText();
    if (role == BreakPointManager::Note)
        return bookMark->note();
    if (role == Qt::ToolTipRole)
        return QDir::toNativeSeparators(bookMark->fileName());
    return QVariant();
}

Qt::ItemFlags BreakPointManager::flags(const QModelIndex &index) const
{
    if (!index.isValid() || index.column() !=0 || index.row() < 0 || index.row() >= m_breakpointsList.count())
        return Qt::NoItemFlags;
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled;
}

void BreakPointManager::toggleBreakpoint(const QString &fileName, int lineNumber)
{
    if (lineNumber <= 0 || fileName.isEmpty())
        return;

    // Remove any existing breakpoint on this line
    if (BreakPoint *mark = findBreakpoint(fileName, lineNumber)) {
        // TODO check if the breakpoint is really on the same markable Interface
        deleteBreakpoint(mark);
        return;
    }

    // Add a new breakpoint if no breakpoint existed on this line
    BreakPoint *mark = new BreakPoint(lineNumber, this);
    mark->updateFileName(fileName);
    addBreakpoint(mark);
}

void BreakPointManager::updateBreakpoint(BreakPoint *breakpoint)
{
    const int idx = m_breakpointsList.indexOf(breakpoint);
    if (idx == -1)
        return;

    dataChanged(index(idx, 0, QModelIndex()), index(idx, 2, QModelIndex()));
    saveBreakpoints();
}

void BreakPointManager::updateBreakpointFileName(BreakPoint *breakpoint, const QString &oldFileName)
{
    if (oldFileName == breakpoint->fileName())
        return;

    if (removeBreakpointFromMap(breakpoint, oldFileName))
        addBreakpointToMap(breakpoint);

    updateBreakpoint(breakpoint);
}

void BreakPointManager::removeAllBreakpoints()
{
    if (m_breakpointsList.isEmpty())
        return;
    beginRemoveRows(QModelIndex(), 0, m_breakpointsList.size() - 1);

    DirectoryFileBreakpointsMap::const_iterator it, end;
    end = m_breakpointsMap.constEnd();
    for (it = m_breakpointsMap.constBegin(); it != end; ++it) {
        FileNameBreakpointsMap *files = it.value();
        FileNameBreakpointsMap::const_iterator jt, jend;
        jend = files->constEnd();
        for (jt = files->constBegin(); jt != jend; ++jt) {
            delete jt.value();
        }
        files->clear();
        delete files;
    }
    m_breakpointsMap.clear();
    m_breakpointsList.clear();
    endRemoveRows();
}

bool BreakPointManager::removeBreakpointFromMap(BreakPoint *breakpoint, const QString &fileName)
{
    bool found = false;
    const QFileInfo fi(fileName.isEmpty() ? breakpoint->fileName() : fileName);
    if (FileNameBreakpointsMap *files = m_breakpointsMap.value(fi.path())) {
        FileNameBreakpointsMap::iterator i = files->begin();
        while (i != files->end()) {
            if (i.value() == breakpoint) {
                files->erase(i);
                found = true;
                break;
            }
            ++i;
        }
        if (files->count() <= 0) {
            m_breakpointsMap.remove(fi.path());
            delete files;
        }
    }
    return found;
}

void BreakPointManager::deleteBreakpoint(BreakPoint *breakpoint)
{
    int idx = m_breakpointsList.indexOf(breakpoint);
    beginRemoveRows(QModelIndex(), idx, idx);

    removeBreakpointFromMap(breakpoint);
    updateBreakPoint(breakpoint, false);

    delete breakpoint;

    m_breakpointsList.removeAt(idx);
    endRemoveRows();

    if (selectionModel()->currentIndex().isValid())
        selectionModel()->setCurrentIndex(selectionModel()->currentIndex(), QItemSelectionModel::Select | QItemSelectionModel::Clear);

    updateActionStatus();
    saveBreakpoints();
}

BreakPoint *BreakPointManager::bookmarkForIndex(const QModelIndex &index) const
{
    if (!index.isValid() || index.row() >= m_breakpointsList.size())
        return 0;
    return m_breakpointsList.at(index.row());
}

bool BreakPointManager::gotoBreakpoint(BreakPoint *breakpoint)
{
    QStringList args;
    args<< breakpoint->fileName()
        << QString::number(breakpoint->lineNumber());
    cmdexec("OpenFile", args, CmdMsg::script, true, false);
    return true;
}

//void BreakPointManager::nextInDocument()
//{
//    documentPrevNext(true);
//}
//
//void BreakPointManager::prevInDocument()
//{
//    documentPrevNext(false);
//}
//
//void BreakPointManager::documentPrevNext(bool next)
//{
//    IEditor *editor = EditorManager::currentEditor();
//    const int editorLine = editor->currentLine();
//    if (editorLine <= 0)
//        return;
//
//    const QFileInfo fi = editor->document()->filePath().toFileInfo();
//    if (!m_bookmarksMap.contains(fi.path()))
//        return;
//
//    int firstLine = -1;
//    int lastLine = -1;
//    int prevLine = -1;
//    int nextLine = -1;
//    const QList<BreakPoint *> marks = m_bookmarksMap.value(fi.path())->values(fi.fileName());
//    for (int i = 0; i < marks.count(); ++i) {
//        int markLine = marks.at(i)->lineNumber();
//        if (firstLine == -1 || firstLine > markLine)
//            firstLine = markLine;
//        if (lastLine < markLine)
//            lastLine = markLine;
//        if (markLine < editorLine && prevLine < markLine)
//            prevLine = markLine;
//        if (markLine > editorLine &&
//            (nextLine == -1 || nextLine > markLine))
//            nextLine = markLine;
//    }
//
//    EditorManager::addCurrentPositionToNavigationHistory();
//    if (next) {
//        if (nextLine == -1)
//            editor->gotoLine(firstLine);
//        else
//            editor->gotoLine(nextLine);
//    } else {
//        if (prevLine == -1)
//            editor->gotoLine(lastLine);
//        else
//            editor->gotoLine(prevLine);
//    }
//}

void BreakPointManager::next()
{
    QModelIndex current = selectionModel()->currentIndex();
    if (!current.isValid())
        return;
    int row = current.row();
    ++row;
    while (true) {
        if (row == m_breakpointsList.size())
            row = 0;

        BreakPoint *bk = m_breakpointsList.at(row);
        if (gotoBreakpoint(bk)) {
            QModelIndex newIndex = current.sibling(row, current.column());
            selectionModel()->setCurrentIndex(newIndex, QItemSelectionModel::Select | QItemSelectionModel::Clear);
            return;
        }
        deleteBreakpoint(bk);
        if (m_breakpointsList.isEmpty()) // No bookmarks anymore ...
            return;
    }
}

void BreakPointManager::prev()
{
    QModelIndex current = selectionModel()->currentIndex();
    if (!current.isValid())
        return;

    int row = current.row();
    while (true) {
        if (row == 0)
            row = m_breakpointsList.size();
        --row;
        BreakPoint *bk = m_breakpointsList.at(row);
        if (gotoBreakpoint(bk)) {
            QModelIndex newIndex = current.sibling(row, current.column());
            selectionModel()->setCurrentIndex(newIndex, QItemSelectionModel::Select | QItemSelectionModel::Clear);
            return;
        }
        deleteBreakpoint(bk);
        if (m_breakpointsList.isEmpty())
            return;
    }
}

BreakPointManager::State BreakPointManager::state() const
{
//    if (m_bookmarksMap.empty())
        return NoBreakPoints;

//    IEditor *editor = EditorManager::currentEditor();
//    if (!editor)
//        return HasBreakPoints;
//
//    const QFileInfo fi = editor->document()->filePath().toFileInfo();
//
//    const DirectoryFileBreakpointsMap::const_iterator dit = m_bookmarksMap.constFind(fi.path());
//    if (dit == m_bookmarksMap.constEnd())
//        return HasBreakPoints;
//
//    return HasBreakpointsInDocument;
}

void BreakPointManager::updateActionStatus()
{
//    IEditor *editor = EditorManager::currentEditor();
//    const bool enableToggle = editor && !editor->document()->isTemporary();
    bool enableToggle = true;
    updateActions(enableToggle, state());
}

void BreakPointManager::moveUp()
{
    QModelIndex current = selectionModel()->currentIndex();
    int row = current.row();
    if (row == 0)
        row = m_breakpointsList.size();
    --row;

    // swap current.row() and row

    BreakPoint *b = m_breakpointsList.at(row);
    m_breakpointsList[row] = m_breakpointsList.at(current.row());
    m_breakpointsList[current.row()] = b;

    QModelIndex topLeft = current.sibling(row, 0);
    QModelIndex bottomRight = current.sibling(current.row(), 2);
    dataChanged(topLeft, bottomRight);
    selectionModel()->setCurrentIndex(current.sibling(row, 0), QItemSelectionModel::Select | QItemSelectionModel::Clear);

    saveBreakpoints();
}

void BreakPointManager::moveDown()
{
    QModelIndex current = selectionModel()->currentIndex();
    int row = current.row();
    ++row;
    if (row == m_breakpointsList.size())
        row = 0;

    // swap current.row() and row
    BreakPoint *b = m_breakpointsList.at(row);
    m_breakpointsList[row] = m_breakpointsList.at(current.row());
    m_breakpointsList[current.row()] = b;

    QModelIndex topLeft = current.sibling(current.row(), 0);
    QModelIndex bottomRight = current.sibling(row, 2);
     dataChanged(topLeft, bottomRight);
    selectionModel()->setCurrentIndex(current.sibling(row, 0), QItemSelectionModel::Select | QItemSelectionModel::Clear);

    saveBreakpoints();
}

/* Returns the breakpoint at the given file and line number, or 0 if no such breakpoint exists. */
BreakPoint *BreakPointManager::findBreakpoint(const QString &filePath, int lineNumber)
{
    QFileInfo fi(filePath);
    QString path = fi.path();
    if (m_breakpointsMap.contains(path)) {
                foreach (BreakPoint *breakpoint, m_breakpointsMap.value(path)->values(fi.fileName())) {
                if (breakpoint->lineNumber() == lineNumber)
                    return breakpoint;
            }
    }
    return 0;
}

void BreakPointManager::addBreakpointToMap(BreakPoint *breakpoint)
{
    const QFileInfo fi(breakpoint->fileName());
    const QString &path = fi.path();
    if (!m_breakpointsMap.contains(path))
        m_breakpointsMap.insert(path, new FileNameBreakpointsMap());
    m_breakpointsMap.value(path)->insert(fi.fileName(), breakpoint);
}

/* Adds a breakpoint to the internal data structures. The 'userset' parameter
 * determines whether action status should be updated and whether the bookmarks
 * should be saved to the session settings.
 */
void BreakPointManager::addBreakpoint(BreakPoint *breakpoint, bool userset)
{
    beginInsertRows(QModelIndex(), m_breakpointsList.size(), m_breakpointsList.size());

    addBreakpointToMap(breakpoint);

    m_breakpointsList.append(breakpoint);
    updateBreakPoint(breakpoint, true);

    endInsertRows();
    if (userset) {
        updateActionStatus();
        saveBreakpoints();
    }
    selectionModel()->setCurrentIndex(index(m_breakpointsList.size()-1 , 0, QModelIndex()), QItemSelectionModel::Select | QItemSelectionModel::Clear);

}

/* Adds a new breakpoint based on information parsed from the string. */
void BreakPointManager::addBreakpoint(const QString &s)
{
    // index3 is a frontier beetween note text and other bookmarks data
    int index3 = s.lastIndexOf(QLatin1Char('\t'));
    if (index3 < 0)
        index3 = s.size();
    int index2 = s.lastIndexOf(QLatin1Char(':'), index3 - 1);
    int index1 = s.indexOf(QLatin1Char(':'));

    if (index3 != -1 || index2 != -1 || index1 != -1) {
        const QString &filePath = s.mid(index1+1, index2-index1-1);
        const QString &note = s.mid(index3 + 1);
        const int lineNumber = s.midRef(index2 + 1, index3 - index2 - 1).toInt();
        if (!filePath.isEmpty() && !findBreakpoint(filePath, lineNumber)) {
            BreakPoint *b = new BreakPoint(lineNumber, this);
            b->updateFileName(filePath);
            b->setNote(note);
            addBreakpoint(b, false);
        }
    } else {
        qDebug() << "BreakPointManager::addBreakpoint() Invalid breakpoint string:" << s;
    }
}

/* Puts the breakpoint in a string for storing it in the settings. */
QString BreakPointManager::bookmarkToString(const BreakPoint *b)
{
    const QLatin1Char colon(':');
    // Using \t as delimiter because any another symbol can be a part of note.
    const QLatin1Char noteDelimiter('\t');
    return colon + b->fileName() +
           colon + QString::number(b->lineNumber()) +
           noteDelimiter + b->note();
}

/* Saves the bookmarks to the session settings. */
void BreakPointManager::saveBreakpoints()
{
    QStringList list;
            foreach (const BreakPoint *breakpoint, m_breakpointsList)
            list << bookmarkToString(breakpoint);

    // TODO save list value;
//    SessionManager::setValue(QLatin1String("Breakpoints"), list);
}

void BreakPointManager::operateTooltip(QWidget *widget, const QPoint &pos, BreakPoint *mark)
{
    if (!mark)
        return;

    if (mark->note().isEmpty()) {
        QToolTip::hideText();
    }
    else {
        QToolTip::showText(pos, mark->note(), widget);
    }
}

/* Loads the bookmarks from the session settings. */
void BreakPointManager::loadBreakpoints()
{
    removeAllBreakpoints();
    // TODO load Breakpoint
//    const QStringList &list = SessionManager::value(QLatin1String("Breakpoints")).toStringList();
//            foreach (const QString &bookmarkString, list)
//            addBreakpoint(bookmarkString);

    updateActionStatus();
}

//void BreakPointManager::handleBreakpointTooltipRequest(IEditor *editor, const QPoint &pos, int line)
//{
//    BreakPoint *mark = findBreakpoint(editor->document()->filePath().toString(), line);
//    operateTooltip(editor->widget(), pos, mark);
//}

BreakPointManager *BreakPointManager::instance() {
    static BreakPointManager* mPtr = nullptr;
    if(mPtr == nullptr) {
        mPtr = new BreakPointManager();
    }
    return mPtr;
}

QList<BreakPoint *> BreakPointManager::getBreakPoints(QString fileName) {
    const QFileInfo fi(fileName);
    const QString &path = fi.path();
    if (m_breakpointsMap.contains(path)) {
        return m_breakpointsMap.value(path)->values(fi.fileName());
    }
    return QList<BreakPoint *>();
}

BreakPointView::BreakPointView(QWidget *parent) : QListView(parent) {
    m_model = BreakPointManager::instance();

    setItemDelegate(new BreakPointDelegate);
    setModel(m_model);

    connect(this, &BreakPointView::doubleClicked, [this](const QModelIndex& index) {
        m_model->gotoBreakpoint(m_model->data(index, Qt::DisplayRole).value<BreakPoint*>());
    });

}

BreakPointView::~BreakPointView() {

}
