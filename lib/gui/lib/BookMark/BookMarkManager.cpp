//===- BookMarkManager.cpp - ART-GUI BookMark -------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#include "BookMark/BookMarkManager.h"

#include <utils/ScriptEngine.h>


BookMarkManager::BookMarkManager(QObject *parent)
    :QObject(parent)
{
    ScriptEngine* script = ScriptEngine::instance();

    connect(script, SIGNAL(projectOpened(QStringList)), this, SLOT(onProjectOpened(QStringList)));
    connect(script, SIGNAL(projectClosed(QStringList)), this, SLOT(onProjectClosed()));
}

BookMarkManager *BookMarkManager::instance(QWidget* parent)
{
    static BookMarkManager* mPtr = nullptr;
    if(mPtr == nullptr) {
        Q_ASSERT (parent != nullptr && "BookMarkManager must init by WorkSpace");
        mPtr = new BookMarkManager(parent);
    }
    return mPtr;
}

// INFO BookMark* and QListWidgetItem* will be deleted in WorkSpace.cpp
// when delBookMark invoked.
BookMark *BookMarkManager::addBookMark(QString file)
{

    BookMark* pBook = new BookMark(file);
    QListWidgetItem* pItem = new QListWidgetItem;

    auto& pFileBookMap = mBookMap[file];
    pFileBookMap[pBook] = pItem;

    emit addBookMark(pBook, pItem);
    return pBook;
}

bool BookMarkManager::delBookMark(QString file, BookMark *bookMark)
{
    auto &pFileBookMap = mBookMap[file];

    auto it = pFileBookMap.find(bookMark);
    if (it != pFileBookMap.end()) {
        emit delBookMark(it.value());
        pFileBookMap.erase(it);
    }
}

QMap<BookMark *,QListWidgetItem *> &BookMarkManager::getFileBookMark (QString file)
{
    return mBookMap[file];;
}

BookMark * BookMarkManager::findBookMark (
        const QMap<BookMark *,QListWidgetItem *> &map,int iLine)
{
    for(auto it = map.begin (), itEnd = map.end (); it != itEnd; it++) {
        if(it.key ()->line () == iLine) {
            return it.key ();
        }
    }
    return nullptr;
}

void BookMarkManager::onProjectOpened (QStringList args)
{

}

void BookMarkManager::onProjectClosed()
{
    for(auto it = mBookMap.begin(), itEnd = mBookMap.end(); it != itEnd; it++) {
        for(auto fileMap = it.value ().begin (), fileMapEnd = it.value ().end ();
                fileMap != fileMapEnd; fileMap++) {
            emit delBookMark(fileMap.value());
        }
        it->clear ();
    }
    mBookMap.clear();
}




