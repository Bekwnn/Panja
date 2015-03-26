#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ptreetextitem.h"
#include "ptextedit.h"
#include <QMainWindow>
#include <QMenu>
#include <QDir>
#include <QTreeWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    enum PEDocumentType {
        DOCUMENT,
        NOTE
    };
protected:
    void closeEvent(QCloseEvent *closeEvent);
    void CreateTreeContextMenu();
    void ClearProject();
    void SaveProject();
    void OpenProject(QString pathToProjectFolder);
    void SaveItem(PTreeTextItem *item);
    void OpenInOtherView(PTreeTextItem *item);
    void OpenItemsRecursively(QDir directory, PTreeTextItem *parent);
    void UpdateViewLabels();
    PTextEdit *inFocusEdit;
    QMenu *treeContextMenu;
    QString projectDirString;
    void CreateNewItem(PEDocumentType newItemType);
    Ui::MainWindow *ui;

public:
    const PTextEdit* getInFocusEdit() { return inFocusEdit; }
    void setInFocusEdit(PTextEdit* edit);

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void updateTools();

    void onTreeWidgetContextMenu(const QPoint &pos);

    void onTreeWidgetItemDoubleClicked(QTreeWidgetItem *item);

    void toggleTextBold(bool b);

    void toggleTextItalic(bool b);

    void toggleTextUnderline(bool b);

    void toggleTextStrikethrough(bool b);

    void onTextCursorMoved();

    void setTextAlignLeft();

    void setTextAlignCenter();

    void setTextAlignRight();

    void closeOtherView(bool bKeepUsingOtherDoc);

private slots:
    void onFocusChanged(QWidget *oldFocus, QWidget *newFocus);

    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionAlignLeft_triggered();

    void on_actionAlignCenter_triggered();

    void on_actionAlignRight_triggered();

    void on_actionSave_triggered();

    void on_actionDocument_triggered();

    void on_actionNote_triggered();

    void on_actionTreeItemRename_triggered();

    void on_actionTreeItemDelete_triggered();

    void on_actionSave_All_triggered();

    void on_actionSave_Project_As_triggered();

    void on_actionFullscreen_triggered();

    void on_actionTreeItemOpenInOtherView_triggered();
    void on_actionOpen_triggered();
    void on_actionStats_triggered();
};

#endif // MAINWINDOW_H
