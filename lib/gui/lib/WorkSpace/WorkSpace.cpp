//===- WorkSpace.cpp - ART-GUI WorkSpace ------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#include "WorkSpace/WorkSpace.h"
#include "ui_WorkSpace.h"

#include "TabWidget.h"

#include <utils/Configuration.h>

WorkSpace::WorkSpace(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorkSpace)
{
    ui->setupUi(this);

    // init Tab widget
    mTabWidget = new MHTabWidget(this);
    ui->mRightTopFrameLayout->addWidget(mTabWidget);
}

WorkSpace::~WorkSpace()
{
    delete ui;
}


void WorkSpace::setTab(QWidget *widget)
{
    for(int i = 0; i < mTabWidget->count(); i++)
    {
        if(mTabWidget->widget(i) == widget)
        {
            mTabWidget->setCurrentIndex(i);
            break;
        }
    }
}

void WorkSpace::loadTabOrder()
{
    QList<QPair<QWidget*, QString>> tabIndexToWidget;

    Configuration *config = Config();
    // Get tabIndex for each widget and add them to tabIndexToWidget
    for(int i = 0; i < mWidgetList.size(); i++)
    {
        QString tabName = mWidgetNativeNameList[i];
        unsigned tabIndex = config->getUint("TabOrder", tabName);
        tabIndexToWidget.insert(tabIndex, qMakePair(mWidgetList[i], tabName));
    }

    // Setup tabs
    for(auto & widget : tabIndexToWidget)
        addQWidgetTab(widget.first, widget.second);
}

void WorkSpace::addQWidgetTab(QWidget *qWidget, QString nativeName)
{
    mTabWidget->addTabEx(qWidget, qWidget->windowIcon(),
                         qWidget->windowTitle(), nativeName);
}

void WorkSpace::addQWidgetTab(QWidget *qWidget)
{
    addQWidgetTab(qWidget, qWidget->windowTitle());
}

void WorkSpace::showQWidgetTab(QWidget *qWidget)
{
    qWidget->show();
    qWidget->setFocus();
    setTab(qWidget);
}

void WorkSpace::closeQWidgetTab(QWidget *qWidget)
{
    for(int i = 0; i < mTabWidget->count(); i++)
    {
        if(mTabWidget->widget(i) == qWidget)
        {
            mTabWidget->DeleteTab(i);
            break;
        }
    }
}

void WorkSpace::tabMovedSlot(int from, int to)
{
    for(int i = 0; i < mTabWidget->count(); i++)
    {
        QString tabName = mTabWidget->getNativeName(i);
        Config()->setUint("TabOrder", tabName, i);
    }
}
