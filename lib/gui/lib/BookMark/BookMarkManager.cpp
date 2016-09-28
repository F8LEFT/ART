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

BookMark *BookMarkManager::addBookMark()
{
    BookMarkManager* mPtr = BookMarkManager::instance ();

    BookMark* pBook = new BookMark;
    QListWidgetItem* pItem = new QListWidgetItem;


    mPtr->mBookMap.insert(pBook, pItem);
    emit mPtr->addBookMark(pBook, pItem);
    return pBook;
}

bool BookMarkManager::delBookMark(BookMark *bookMark)
{
    BookMarkManager* mPtr = BookMarkManager::instance ();

    auto it = mPtr->mBookMap.find(bookMark);
    if (it != mPtr->mBookMap.end()) {
        emit mPtr->delBookMark(it.value());
        mPtr->mBookMap.erase(it);
    }
}

void BookMarkManager::onProjectOpened (QStringList args)
{

}

void BookMarkManager::onProjectClosed()
{
    for(auto it = mBookMap.begin(); it != mBookMap.end(); it++) {
        emit delBookMark(it.value());
    }
    mBookMap.clear();
}

