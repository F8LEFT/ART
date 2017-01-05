//===- BreakPointManager.h - ART-GUI BreakPoint ---------------------*- C++ -*-===//
//
//                     ANDROID REVERSE TOOLKIT
//
// This file is distributed under the GNU GENERAL PUBLIC LICENSE
// V3 License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines manager to manage breakpoint.
//
//===----------------------------------------------------------------------===//

#ifndef PROJECT_BREAKPOINTMANAGER_H
#define PROJECT_BREAKPOINTMANAGER_H

#include <QAbstractListModel>
#include <QIcon>
#include <QMap>
#include <QListWidgetItem>
#include <QObject>
#include "BreakPoint.h"


class BreakPointManager: public QAbstractListModel {
    Q_OBJECT

public:
    BreakPointManager();
    ~BreakPointManager();

    static BreakPointManager* instance();

    QIcon bookmarkIcon() const { return m_breakpointIcon; }

    void updateBreakpoint(BreakPoint *breakpoint);
    void updateBreakpointFileName(BreakPoint *breakpoint, const QString &oldFileName);
    void deleteBreakpoint(BreakPoint *breakpoint); // Does not remove the mark
    void removeAllBreakpoints();
    BreakPoint *bookmarkForIndex(const QModelIndex &index) const;

    enum State { NoBreakPoints, HasBreakPoints, HasBreakpointsInDocument };
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

    bool hasBreakpointInPosition(const QString &fileName, int lineNumber);

    enum Roles {
        Filename = Qt::UserRole,
        LineNumber = Qt::UserRole + 1,
        Directory = Qt::UserRole + 2,
        LineText = Qt::UserRole + 3,
        Note = Qt::UserRole + 4,

    };

//    void handleBreakpointTooltipRequest(Core::IEditor *editor, const QPoint &pos, int line);

    void toggleBreakpoint(const QString &fileName, int lineNumber);
//    void nextInDocument();
//    void prevInDocument();
    void next();
    void prev();
    void moveUp();
    void moveDown();
    bool gotoBreakpoint(BreakPoint *breakpoint);

    QList<BreakPoint *> getBreakPoints(QString fileName);
signals:
    void updateActions(bool enableToggle, int state);
    void currentIndexChanged(const QModelIndex &);

    void updateBreakPoint(BreakPoint* breakpoint, bool isAdd);
public slots:
    void onProjectOpened(QStringList args);
    void onProjectClosed ();
private:
    void updateActionStatus();
    void loadBreakpoints();

//    void documentPrevNext(bool next);

    BreakPoint *findBreakpoint(const QString &filePath, int lineNumber);
    void addBreakpoint(BreakPoint *breakpoint, bool userset = true);
    void addBreakpoint(const QString &s);
    void addBreakpointToMap(BreakPoint *breakpoint);
    bool removeBreakpointFromMap(BreakPoint *breakpoint, const QString &fileName = QString());
    static QString breakpointToString(const BreakPoint *b);
    void saveBreakpoints();
    void operateTooltip(QWidget *widget, const QPoint &pos, BreakPoint *mark);

    typedef QMultiMap<QString, BreakPoint *> FileNameBreakpointsMap;
    typedef QMap<QString, FileNameBreakpointsMap *> DirectoryFileBreakpointsMap;

    DirectoryFileBreakpointsMap m_breakpointsMap;

    const QIcon m_breakpointIcon;

    QList<BreakPoint *> m_breakpointsList;
    QItemSelectionModel *m_selectionModel;
};

class BreakPointView: public QListView {
    Q_OBJECT
public:
    BreakPointView(QWidget* parent = nullptr);
    ~BreakPointView();

private:
    BreakPointManager* m_model;
};


#endif //PROJECT_BREAKPOINTMANAGER_H
