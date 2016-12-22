//===- FileEditorColorConfig.cpp - ART-GUI Config --------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//

#include "FileEditorColorConfig.h"

#include <QGridLayout>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QColorDialog>
#include <QHeaderView>

FileEditorColorConfig::FileEditorColorConfig(QWidget *parent)
    :QWidget(parent)
{
    // init item
    m_colorTable = new QTableWidget(KSyntaxHighlighting::Theme::TemplateReadOnlyPlaceholder+1, 2, this);

    m_colorTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    auto header = m_colorTable->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
    header->setStretchLastSection(false);
    header->hide();
    m_colorTable->verticalHeader()->hide();
    m_colorTable->setSelectionMode(QAbstractItemView::NoSelection);


    for(auto i = 0; i <= KSyntaxHighlighting::Theme::TemplateReadOnlyPlaceholder; i++) {
        QTableWidgetItem* name = new QTableWidgetItem(KSyntaxHighlighting::Theme::getEditorColorRoleName(i, true));
        QTableWidgetItem* color = new QTableWidgetItem();
        color->setData(Qt::UserRole, i);
        m_colorTable->setItem(i, 0, name);
        m_colorTable->setItem(i, 1, color);
    }

    // connect signal slots
    connect(m_colorTable, &QTableWidget::cellDoubleClicked, [this](int row, int column){
        if(m_theme.isReadOnly()) {
            return;
        }
        if(column != 1) {
            return;
        }
        auto item = m_colorTable->currentItem();
        auto role = (KSyntaxHighlighting::Theme::EditorColorRole)item->data(Qt::UserRole).toInt();

        QColor color;
        color = QColorDialog::getColor(m_theme.editorColor(role), this);
        if(color.isValid()) {
            m_theme.setEditorColor(role, color.rgb());
            item->setBackgroundColor(color);
            formatUpdate();
        }
    });

    // setup layout
    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget(m_colorTable);
    setLayout(layout);
}

void FileEditorColorConfig::setTheme(KSyntaxHighlighting::Theme theme)
{
    m_theme = theme;

    // connect signal slots
    for(auto i = 0; i < m_colorTable->rowCount(); i++) {
        auto item = m_colorTable->item(i, 1);
        auto role = (KSyntaxHighlighting::Theme::EditorColorRole)item->data(Qt::UserRole).toInt();
        item->setBackground(QBrush(m_theme.editorColor(role)));
    }
}
