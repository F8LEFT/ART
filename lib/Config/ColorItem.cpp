//===- ColorItem.cpp - ART-GUI Config --------------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===---------------------------------------------------------------------===//


#include "ColorItem.h"

#include <QtWidgets>

ColorItem::ColorItem(QWidget *parent, const QString &name):
        QWidget(parent),
        m_rgb(0)
{
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    QLabel *label = new QLabel(this);
    label->setText(name);
    m_colorBtn = new ColorButton(this);
    m_clearBtn = new QPushButton(this);
    m_clearBtn->setIcon(QIcon(":/images/close.png"));

    layout->addWidget(label);
    layout->addWidget(m_colorBtn);
    layout->addWidget(m_clearBtn);

    setLayout(layout);

    connect(m_colorBtn, &QPushButton::clicked, [this]() {
        QColor color;
        color = QColorDialog::getColor(QColor(m_rgb), this);
        if(color.isValid()) {
            setColor(color.rgb());
            colorChanged(m_rgb, m_data);
        }
    });

    connect(m_clearBtn, &QPushButton::clicked, [this]() {
        setColor(0);
        colorChanged(m_rgb, m_data);
    });
}

void ColorItem::setColor(QRgb c)
{
    m_rgb = c;
    m_colorBtn->paintColor(m_rgb);
}

void ColorItem::setClearBtnEnable(bool b)
{
    m_clearBtn->setVisible(b);
}

bool ColorItem::isClearBtnEnable()
{
    return m_clearBtn->isVisible();
}

void ColorButton::paintColor(QRgb rgb)
{
    m_rgb = rgb;
    repaint();
}

void ColorButton::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event);

    QPainter painter(this);

    QStyleOptionButton opt;
    opt.rect = rect();
    opt.palette = palette();

    style()->drawControl(QStyle::CE_PushButton, &opt, &painter, this);
    style()->subElementRect(QStyle::SE_PushButtonContents, &opt, this);
    opt.rect.adjust(1, 1, -1, -1);

    if(m_rgb != 0) {
        QColor c(m_rgb);
        painter.fillRect(opt.rect, c);
    } else {
        painter.fillRect(opt.rect, Qt::white);
        painter.drawText(opt.rect, tr("None"), QTextOption(Qt::AlignCenter));
    }

    qDrawShadePanel(&painter, opt.rect, opt.palette, true, 1, NULL);
}

