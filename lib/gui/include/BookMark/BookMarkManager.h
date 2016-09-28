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

#include <QAbstractItemModel>
#include <QIcon>
#include <QMap>
#include <QListWidgetItem>
#include <QObject>
#include "BookMark.h"
class BookMarkManager: public QObject
{
    Q_OBJECT
public:
    BookMarkManager(QObject* parnet = nullptr);
    static BookMarkManager* instance(QWidget* parent = nullptr);

    static BookMark* addBookMark();
    static bool delBookMark(BookMark* bookMark);

    BookMark* findBookMark(QString filePath, int iLine);

signals:
    void addBookMark(BookMark* bookMark, QListWidgetItem* listItem);
    void delBookMark(QListWidgetItem* listItem);
public slots:
    void onProjectOpened(QStringList args);
    void onProjectClosed();
private:
    const QIcon m_bookmarkIcon;

    QMap<BookMark*, QListWidgetItem*> mBookMap;
};


#endif //PROJECT_BOOKMARKMANAGER_H
