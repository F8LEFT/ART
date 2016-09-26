//===- StatusLabel.cpp - ART-GUI MainWindow ---------------------*- C++ -*-===//

#include "StatusLabel.h"
#include <QTextDocument>

StatusLabel::StatusLabel(QStatusBar* parent) : QLabel(parent)
{
    this->setFrameStyle(QFrame::Sunken | QFrame::Panel);    // sunken sytle
    //this->setStyleSheet("QLabel { background-color : #c0c0c0; }");
    this->setTextFormat(Qt::RichText);  // rich text

}

void StatusLabel::logUpdate(QString message)
{
    if (labelText.contains('\n'))
        labelText = "";
    // Split each newline into a separate string
    QStringList lineList = message.split('\n', QString::SkipEmptyParts);

    // Split each newline into a separate string
    if (lineList.size() > 0)
    {
        // Get a substring for the last line only
        labelText += lineList[lineList.size() - 1] + "\n";
    }
    else
    {
        // Append to the existing message
        labelText += message;
    }

    // We want to trim every \n from the visual display
    setText(Qt::convertFromPlainText(QString(labelText).replace("\n", "")));
}
