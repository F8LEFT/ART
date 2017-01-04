//===- BookMarkManager.cpp - ART-GUI BookMark -------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#include "BookMark/BookMarkManager.h"
#include "BookMarkDelegate.h"

#include <utils/ScriptEngine.h>
#include <utils/CmdMsgUtil.h>

#include <QPixmap>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QToolTip>
#include <QDebug>


//BookMarkManager::BookMarkManager(QObject *parent)
//    :QObject(parent)
//{
//    ScriptEngine* script = ScriptEngine::instance();
//
//    connect(script, SIGNAL(projectOpened(QStringList)), this, SLOT(onProjectOpened(QStringList)));
//    connect(script, SIGNAL(projectClosed(QStringList)), this, SLOT(onProjectClosed()));
//}
//
//BookMarkManager *BookMarkManager::instance(QWidget* parent)
//{
//    static BookMarkManager* mPtr = nullptr;
//    if(mPtr == nullptr) {
//        Q_ASSERT (parent != nullptr && "BookMarkManager must init in WorkSpace");
//        mPtr = new BookMarkManager(parent);
//    }
//    return mPtr;
//}
//
//// INFO BookMark* and QListWidgetItem* will be deleted in WorkSpace.cpp
//// when delBookMark invoked.
//BookMark *BookMarkManager::addBookMark(QString file)
//{
//    BookMark* pBook = new BookMark(file);
//    QListWidgetItem* pItem = new QListWidgetItem;
//
//    auto& pFileBookMap = mBookMap[file];
//    pFileBookMap[pBook] = pItem;
//
//    addBookMark(pBook, pItem);
//    return pBook;
//}
//
//bool BookMarkManager::delBookMark(QString file, BookMark *bookMark)
//{
//    auto &pFileBookMap = mBookMap[file];
//
//    auto it = pFileBookMap.find(bookMark);
//    if (it != pFileBookMap.end()) {
//        delBookMark(it.value());
//        pFileBookMap.erase(it);
//    }
//    return true;
//}
//
//QMap<BookMark *,QListWidgetItem *> &BookMarkManager::getFileBookMark (QString file)
//{
//    return mBookMap[file];;
//}
//
//BookMark * BookMarkManager::findBookMark (
//        const QMap<BookMark *,QListWidgetItem *> &map,int iLine)
//{
//    for(auto it = map.begin (), itEnd = map.end (); it != itEnd; it++) {
//        if(it.key ()->line () == iLine) {
//            return it.key ();
//        }
//    }
//    return nullptr;
//}
//
//void BookMarkManager::onProjectOpened (QStringList args)
//{
//
//}
//
//void BookMarkManager::onProjectClosed()
//{
//    for(auto it = mBookMap.begin(), itEnd = mBookMap.end(); it != itEnd; it++) {
//        for(auto fileMap = it.value ().begin (), fileMapEnd = it.value ().end ();
//                fileMap != fileMapEnd; fileMap++) {
//            delBookMark(fileMap.value());
//        }
//        it->clear ();
//    }
//    mBookMap.clear();
//}

BookMarkManager::BookMarkManager() :
        m_bookmarkIcon(QPixmap(":/images/bookmark.png")),
        m_selectionModel(new QItemSelectionModel(this, this))
{
//    connect(ICore::instance(), &ICore::contextChanged,
//            this, &BookMarkManager::updateActionStatus);

//    connect(SessionManager::instance(), &SessionManager::sessionLoaded,
//            this, &BookMarkManager::loadBookmarks);

    updateActionStatus();
}

BookMarkManager::~BookMarkManager()
{
    DirectoryFileBookmarksMap::iterator it, end;
    end = m_bookmarksMap.end();
    for (it = m_bookmarksMap.begin(); it != end; ++it) {
        FileNameBookmarksMap *bookmarks = it.value();
        qDeleteAll(*bookmarks);
        delete bookmarks;
    }
}

QItemSelectionModel *BookMarkManager::selectionModel() const
{
    return m_selectionModel;
}

bool BookMarkManager::hasBookmarkInPosition(const QString &fileName, int lineNumber)
{
    return findBookmark(fileName, lineNumber);
}

QModelIndex BookMarkManager::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid())
        return QModelIndex();
    else
        return createIndex(row, column);
}

QModelIndex BookMarkManager::parent(const QModelIndex &) const
{
    return QModelIndex();
}

int BookMarkManager::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    else
        return m_bookmarksList.count();
}

//int BookMarkManager::columnCount(const QModelIndex &parent) const
//{
//    if (parent.isValid())
//        return 0;
//    return 3;
//}

QVariant BookMarkManager::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.column() !=0 || index.row() < 0 || index.row() >= m_bookmarksList.count())
        return QVariant();

    BookMark *bookMark = m_bookmarksList.at(index.row());
    if(role == Qt::DisplayRole)
        return QVariant::fromValue<BookMark*>(bookMark);
    if (role == BookMarkManager::Filename)
        return bookMark->fileName();
    if (role == BookMarkManager::LineNumber)
        return bookMark->lineNumber();
    if (role == BookMarkManager::Directory)
        return QFileInfo(bookMark->fileName()).path();
    if (role == BookMarkManager::LineText)
        return bookMark->lineText();
    if (role == BookMarkManager::Note)
        return bookMark->note();
    if (role == Qt::ToolTipRole)
        return QDir::toNativeSeparators(bookMark->fileName());
    return QVariant();
}

Qt::ItemFlags BookMarkManager::flags(const QModelIndex &index) const
{
    if (!index.isValid() || index.column() !=0 || index.row() < 0 || index.row() >= m_bookmarksList.count())
        return Qt::NoItemFlags;
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled;
}

void BookMarkManager::toggleBookmark(const QString &fileName, int lineNumber)
{
    if (lineNumber <= 0 || fileName.isEmpty())
        return;

    // Remove any existing bookmark on this line
    if (BookMark *mark = findBookmark(fileName, lineNumber)) {
        // TODO check if the bookmark is really on the same markable Interface
        deleteBookmark(mark);
        return;
    }

    // Add a new bookmark if no bookmark existed on this line
    BookMark *mark = new BookMark(lineNumber, this);
    mark->updateFileName(fileName);
    addBookmark(mark);
}

void BookMarkManager::updateBookmark(BookMark *bookmark)
{
    const int idx = m_bookmarksList.indexOf(bookmark);
    if (idx == -1)
        return;

    dataChanged(index(idx, 0, QModelIndex()), index(idx, 2, QModelIndex()));
    saveBookmarks();
}

void BookMarkManager::updateBookmarkFileName(BookMark *bookmark, const QString &oldFileName)
{
    if (oldFileName == bookmark->fileName())
        return;

    if (removeBookmarkFromMap(bookmark, oldFileName))
        addBookmarkToMap(bookmark);

    updateBookmark(bookmark);
}

void BookMarkManager::removeAllBookmarks()
{
    if (m_bookmarksList.isEmpty())
        return;
    beginRemoveRows(QModelIndex(), 0, m_bookmarksList.size() - 1);

    DirectoryFileBookmarksMap::const_iterator it, end;
    end = m_bookmarksMap.constEnd();
    for (it = m_bookmarksMap.constBegin(); it != end; ++it) {
        FileNameBookmarksMap *files = it.value();
        FileNameBookmarksMap::const_iterator jt, jend;
        jend = files->constEnd();
        for (jt = files->constBegin(); jt != jend; ++jt) {
            delete jt.value();
        }
        files->clear();
        delete files;
    }
    m_bookmarksMap.clear();
    m_bookmarksList.clear();
    endRemoveRows();
}

bool BookMarkManager::removeBookmarkFromMap(BookMark *bookmark, const QString &fileName)
{
    bool found = false;
    const QFileInfo fi(fileName.isEmpty() ? bookmark->fileName() : fileName);
    if (FileNameBookmarksMap *files = m_bookmarksMap.value(fi.path())) {
        FileNameBookmarksMap::iterator i = files->begin();
        while (i != files->end()) {
            if (i.value() == bookmark) {
                files->erase(i);
                found = true;
                break;
            }
            ++i;
        }
        if (files->count() <= 0) {
            m_bookmarksMap.remove(fi.path());
            delete files;
        }
    }
    return found;
}

void BookMarkManager::deleteBookmark(BookMark *bookmark)
{
    int idx = m_bookmarksList.indexOf(bookmark);
    beginRemoveRows(QModelIndex(), idx, idx);

    removeBookmarkFromMap(bookmark);
    delete bookmark;

    m_bookmarksList.removeAt(idx);
    endRemoveRows();

    if (selectionModel()->currentIndex().isValid())
        selectionModel()->setCurrentIndex(selectionModel()->currentIndex(), QItemSelectionModel::Select | QItemSelectionModel::Clear);

    updateActionStatus();
    saveBookmarks();
}

BookMark *BookMarkManager::bookmarkForIndex(const QModelIndex &index) const
{
    if (!index.isValid() || index.row() >= m_bookmarksList.size())
        return 0;
    return m_bookmarksList.at(index.row());
}

bool BookMarkManager::gotoBookmark(BookMark *bookmark)
{
    QStringList args;
    args<< bookmark->fileName()
        << QString::number(bookmark->lineNumber());
    cmdexec("OpenFile", args, CmdMsg::script, true, false);
    return true;
}

//void BookMarkManager::nextInDocument()
//{
//    documentPrevNext(true);
//}
//
//void BookMarkManager::prevInDocument()
//{
//    documentPrevNext(false);
//}
//
//void BookMarkManager::documentPrevNext(bool next)
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
//    const QList<BookMark *> marks = m_bookmarksMap.value(fi.path())->values(fi.fileName());
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

void BookMarkManager::next()
{
    QModelIndex current = selectionModel()->currentIndex();
    if (!current.isValid())
        return;
    int row = current.row();
    ++row;
    while (true) {
        if (row == m_bookmarksList.size())
            row = 0;

        BookMark *bk = m_bookmarksList.at(row);
        if (gotoBookmark(bk)) {
            QModelIndex newIndex = current.sibling(row, current.column());
            selectionModel()->setCurrentIndex(newIndex, QItemSelectionModel::Select | QItemSelectionModel::Clear);
            return;
        }
        deleteBookmark(bk);
        if (m_bookmarksList.isEmpty()) // No bookmarks anymore ...
            return;
    }
}

void BookMarkManager::prev()
{
    QModelIndex current = selectionModel()->currentIndex();
    if (!current.isValid())
        return;

    int row = current.row();
    while (true) {
        if (row == 0)
            row = m_bookmarksList.size();
        --row;
        BookMark *bk = m_bookmarksList.at(row);
        if (gotoBookmark(bk)) {
            QModelIndex newIndex = current.sibling(row, current.column());
            selectionModel()->setCurrentIndex(newIndex, QItemSelectionModel::Select | QItemSelectionModel::Clear);
            return;
        }
        deleteBookmark(bk);
        if (m_bookmarksList.isEmpty())
            return;
    }
}

BookMarkManager::State BookMarkManager::state() const
{
//    if (m_bookmarksMap.empty())
        return NoBookMarks;

//    IEditor *editor = EditorManager::currentEditor();
//    if (!editor)
//        return HasBookMarks;
//
//    const QFileInfo fi = editor->document()->filePath().toFileInfo();
//
//    const DirectoryFileBookmarksMap::const_iterator dit = m_bookmarksMap.constFind(fi.path());
//    if (dit == m_bookmarksMap.constEnd())
//        return HasBookMarks;
//
//    return HasBookmarksInDocument;
}

void BookMarkManager::updateActionStatus()
{
//    IEditor *editor = EditorManager::currentEditor();
//    const bool enableToggle = editor && !editor->document()->isTemporary();
    bool enableToggle = true;
    updateActions(enableToggle, state());
}

void BookMarkManager::moveUp()
{
    QModelIndex current = selectionModel()->currentIndex();
    int row = current.row();
    if (row == 0)
        row = m_bookmarksList.size();
    --row;

    // swap current.row() and row

    BookMark *b = m_bookmarksList.at(row);
    m_bookmarksList[row] = m_bookmarksList.at(current.row());
    m_bookmarksList[current.row()] = b;

    QModelIndex topLeft = current.sibling(row, 0);
    QModelIndex bottomRight = current.sibling(current.row(), 2);
    dataChanged(topLeft, bottomRight);
    selectionModel()->setCurrentIndex(current.sibling(row, 0), QItemSelectionModel::Select | QItemSelectionModel::Clear);

    saveBookmarks();
}

void BookMarkManager::moveDown()
{
    QModelIndex current = selectionModel()->currentIndex();
    int row = current.row();
    ++row;
    if (row == m_bookmarksList.size())
        row = 0;

    // swap current.row() and row
    BookMark *b = m_bookmarksList.at(row);
    m_bookmarksList[row] = m_bookmarksList.at(current.row());
    m_bookmarksList[current.row()] = b;

    QModelIndex topLeft = current.sibling(current.row(), 0);
    QModelIndex bottomRight = current.sibling(row, 2);
     dataChanged(topLeft, bottomRight);
    selectionModel()->setCurrentIndex(current.sibling(row, 0), QItemSelectionModel::Select | QItemSelectionModel::Clear);

    saveBookmarks();
}

/* Returns the bookmark at the given file and line number, or 0 if no such bookmark exists. */
BookMark *BookMarkManager::findBookmark(const QString &filePath, int lineNumber)
{
    QFileInfo fi(filePath);
    QString path = fi.path();
    if (m_bookmarksMap.contains(path)) {
                foreach (BookMark *bookmark, m_bookmarksMap.value(path)->values(fi.fileName())) {
                if (bookmark->lineNumber() == lineNumber)
                    return bookmark;
            }
    }
    return 0;
}

void BookMarkManager::addBookmarkToMap(BookMark *bookmark)
{
    const QFileInfo fi(bookmark->fileName());
    const QString &path = fi.path();
    if (!m_bookmarksMap.contains(path))
        m_bookmarksMap.insert(path, new FileNameBookmarksMap());
    m_bookmarksMap.value(path)->insert(fi.fileName(), bookmark);
}

/* Adds a bookmark to the internal data structures. The 'userset' parameter
 * determines whether action status should be updated and whether the bookmarks
 * should be saved to the session settings.
 */
void BookMarkManager::addBookmark(BookMark *bookmark, bool userset)
{
    beginInsertRows(QModelIndex(), m_bookmarksList.size(), m_bookmarksList.size());

    addBookmarkToMap(bookmark);

    m_bookmarksList.append(bookmark);

    endInsertRows();
    if (userset) {
        updateActionStatus();
        saveBookmarks();
    }
    selectionModel()->setCurrentIndex(index(m_bookmarksList.size()-1 , 0, QModelIndex()), QItemSelectionModel::Select | QItemSelectionModel::Clear);
}

/* Adds a new bookmark based on information parsed from the string. */
void BookMarkManager::addBookmark(const QString &s)
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
        if (!filePath.isEmpty() && !findBookmark(filePath, lineNumber)) {
            BookMark *b = new BookMark(lineNumber, this);
            b->updateFileName(filePath);
            b->setNote(note);
            addBookmark(b, false);
        }
    } else {
        qDebug() << "BookMarkManager::addBookmark() Invalid bookmark string:" << s;
    }
}

/* Puts the bookmark in a string for storing it in the settings. */
QString BookMarkManager::bookmarkToString(const BookMark *b)
{
    const QLatin1Char colon(':');
    // Using \t as delimiter because any another symbol can be a part of note.
    const QLatin1Char noteDelimiter('\t');
    return colon + b->fileName() +
           colon + QString::number(b->lineNumber()) +
           noteDelimiter + b->note();
}

/* Saves the bookmarks to the session settings. */
void BookMarkManager::saveBookmarks()
{
    QStringList list;
            foreach (const BookMark *bookmark, m_bookmarksList)
            list << bookmarkToString(bookmark);

    // TODO save list value;
//    SessionManager::setValue(QLatin1String("Bookmarks"), list);
}

void BookMarkManager::operateTooltip(QWidget *widget, const QPoint &pos, BookMark *mark)
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
void BookMarkManager::loadBookmarks()
{
    removeAllBookmarks();
    // TODO load Bookmark
//    const QStringList &list = SessionManager::value(QLatin1String("Bookmarks")).toStringList();
//            foreach (const QString &bookmarkString, list)
//            addBookmark(bookmarkString);

    updateActionStatus();
}

//void BookMarkManager::handleBookmarkTooltipRequest(IEditor *editor, const QPoint &pos, int line)
//{
//    BookMark *mark = findBookmark(editor->document()->filePath().toString(), line);
//    operateTooltip(editor->widget(), pos, mark);
//}

BookMarkManager *BookMarkManager::instance() {
    static BookMarkManager* mPtr = nullptr;
    if(mPtr == nullptr) {
        mPtr = new BookMarkManager();
    }
    return mPtr;
}

QList<BookMark *> BookMarkManager::getBookMarks(QString fileName) {
    const QFileInfo fi(fileName);
    const QString &path = fi.path();
    if (m_bookmarksMap.contains(path)) {
        return m_bookmarksMap.value(path)->values(fi.fileName());
    }
    return QList<BookMark *>();
}

BookMarkView::BookMarkView(QWidget *parent) : QListView(parent) {
    setItemDelegate(new BookMarkDelegate);
    setModel(BookMarkManager::instance());
}

BookMarkView::~BookMarkView() {

}
