//===- BookMarkManager.h - ART-GUI BookMark ---------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines manager to manage bookmark.
//
//===----------------------------------------------------------------------===//

#ifndef PROJECT_BOOKMARKMANAGER_H
#define PROJECT_BOOKMARKMANAGER_H

#include <QAbstractListModel>
#include <QIcon>
#include <QMap>
#include <QListWidgetItem>
#include <QObject>
#include "BookMark.h"
//class BookMarkManager: public QObject
//{
//    Q_OBJECT
//public:
//    BookMarkManager(QObject* parnet = nullptr);
//    static BookMarkManager* instance(QWidget* parent = nullptr);
//
//    BookMark* addBookMark(QString file);
//    bool delBookMark(QString file, BookMark* bookMark);
//    QMap<BookMark*, QListWidgetItem*> &getFileBookMark(QString file);
//
//    static BookMark* findBookMark(
//            const QMap<BookMark*, QListWidgetItem*> & map,int iLine);
//signals:
//    void addBookMark(BookMark* bookMark, QListWidgetItem* listItem);
//    void delBookMark(QListWidgetItem* listItem);
//public slots:
//    void onProjectOpened(QStringList args);
//    void onProjectClosed();
//private:
//    const QIcon m_bookmarkIcon;
//
//    QMap<QString, QMap<BookMark*, QListWidgetItem*>> mBookMap;
//};


class BookMarkManager: public QAbstractListModel {
    Q_OBJECT

public:
    BookMarkManager();
    ~BookMarkManager();

    static BookMarkManager* instance();

    QIcon bookmarkIcon() const { return m_bookmarkIcon; }

    void updateBookmark(BookMark *bookmark);
    void updateBookmarkFileName(BookMark *bookmark, const QString &oldFileName);
    void deleteBookmark(BookMark *bookmark); // Does not remove the mark
    void removeAllBookmarks();
    BookMark *bookmarkForIndex(const QModelIndex &index) const;

    enum State { NoBookMarks, HasBookMarks, HasBookmarksInDocument };
    State state() const;

    // Model stuff
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
//    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;


    // this QItemSelectionModel is shared by all views
    QItemSelectionModel *selectionModel() const;

    bool hasBookmarkInPosition(const QString &fileName, int lineNumber);

    enum Roles {
        Filename = Qt::UserRole,
        LineNumber = Qt::UserRole + 1,
        Directory = Qt::UserRole + 2,
        LineText = Qt::UserRole + 3,
        Note = Qt::UserRole + 4,

    };

//    void handleBookmarkTooltipRequest(Core::IEditor *editor, const QPoint &pos, int line);

    void toggleBookmark(const QString &fileName, int lineNumber);
//    void nextInDocument();
//    void prevInDocument();
    void next();
    void prev();
    void moveUp();
    void moveDown();
    bool gotoBookmark(BookMark *bookmark);

    QList<BookMark *> getBookMarks(QString fileName);
signals:
    void updateActions(bool enableToggle, int state);
    void currentIndexChanged(const QModelIndex &);

private:
    void updateActionStatus();
    void loadBookmarks();

//    void documentPrevNext(bool next);

    BookMark *findBookmark(const QString &filePath, int lineNumber);
    void addBookmark(BookMark *bookmark, bool userset = true);
    void addBookmark(const QString &s);
    void addBookmarkToMap(BookMark *bookmark);
    bool removeBookmarkFromMap(BookMark *bookmark, const QString &fileName = QString());
    static QString bookmarkToString(const BookMark *b);
    void saveBookmarks();
    void operateTooltip(QWidget *widget, const QPoint &pos, BookMark *mark);

    typedef QMultiMap<QString, BookMark *> FileNameBookmarksMap;
    typedef QMap<QString, FileNameBookmarksMap *> DirectoryFileBookmarksMap;

    DirectoryFileBookmarksMap m_bookmarksMap;

    const QIcon m_bookmarkIcon;

    QList<BookMark *> m_bookmarksList;
    QItemSelectionModel *m_selectionModel;
};

class BookMarkView: public QListView {
    Q_OBJECT
public:
    BookMarkView(QWidget* parent = nullptr);
    ~BookMarkView();

};


#endif //PROJECT_BOOKMARKMANAGER_H
