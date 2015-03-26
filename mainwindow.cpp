#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ptreetextitem.h"
#include "pconfirmclose.h"
#include "pstatsdialog.h"

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QDebug>
#include <QFileDialog>
#include <QTextDocumentWriter>
#include <QDirIterator>
#include <QDialogButtonBox>
#include <QCloseEvent>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    CreateTreeContextMenu();
    PTreeTextItem *initialDoc = new PTreeTextItem("NewProject");
    inFocusEdit = ui->textEditMain;
    ui->textEditMain->documentLabel = ui->labelViewMain;
    ui->textEditOther->documentLabel = ui->labelViewOther;
    ui->treeWidget->addTopLevelItem(initialDoc);
    ui->textEditMain->setDocument(initialDoc);
    ui->multiViewLabels->hide();
    ui->textEditOther->hide();
    connect(qApp, SIGNAL(focusChanged(QWidget*,QWidget*)), this, SLOT(onFocusChanged(QWidget*, QWidget*)));
    projectDirString = QString();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::CreateTreeContextMenu()
{
    treeContextMenu = new QMenu();
    treeContextMenu->addAction(ui->actionTreeItemRename);
    treeContextMenu->addAction(ui->actionTreeItemDelete);
    treeContextMenu->addAction(ui->actionTreeItemOpenInOtherView);
}

void MainWindow::closeEvent(QCloseEvent *closeEvent)
{
    PConfirmClose *confirmCloseDialog = new PConfirmClose();
    int dialogResult = confirmCloseDialog->exec();
    if (dialogResult == QDialogButtonBox::Yes || dialogResult == QDialogButtonBox::No)
    {
        if (dialogResult == QDialogButtonBox::Yes)
        {
            if (projectDirString.isNull())
            {
                projectDirString = QFileDialog::getSaveFileName(this, "Save As...", QString(), "Directory", 0, QFileDialog::ShowDirsOnly);
                if (projectDirString.isNull())
                {
                    closeEvent->ignore();
                    return;
                }
                QDir().mkpath(projectDirString);
            }
            SaveProject();
        }
        close();
    }
    else
    {
        closeEvent->ignore();
    }
}

void MainWindow::OpenInOtherView(PTreeTextItem *item)
{
    ui->textEditOther->setDocument(item);
    ui->textEditOther->show();

    ui->labelViewOther->setText(item->text(0));
    ui->multiViewLabels->show();
}

void MainWindow::ClearProject()
{
    ui->treeWidget->clear();
}

void MainWindow::SaveProject()
{
    QTreeWidgetItemIterator iter(ui->treeWidget);
    while (*iter)
    {
        SaveItem(dynamic_cast<PTreeTextItem*>(*iter));
        ++iter;
    }
}

void MainWindow::OpenProject(QString pathToProjectFolder)
{
    projectDirString = pathToProjectFolder;
    OpenItemsRecursively(QDir(pathToProjectFolder), NULL);
}

void MainWindow::OpenItemsRecursively(QDir directory, PTreeTextItem* parent)
{
    QStringList fileList = directory.entryList();
    for (QString fileName : fileList)
    {
        qDebug() << fileName;
        if (fileName.endsWith(".html"))
        {
            //todo: move to PTreeTextItem.cpp
            QString documentName = fileName.section(".html", 0, 0);
            qDebug() << "endswith .html!" << fileName.section(".html", 0, 0);
            qDebug() << directory.absolutePath() + '/' + fileName;

            QFile docFile(directory.absolutePath() + '/' + fileName);
            if (!docFile.open(QIODevice::ReadOnly | QIODevice::Text))
                return;

            QString asHtml;
            QTextStream in(&docFile);
            while (!in.atEnd()) {
                asHtml.append(in.readLine());
            }

            PTreeTextItem* newItem = new PTreeTextItem(QUrl::fromPercentEncoding(documentName.toUtf8()));
            newItem->getDocument()->setHtml(asHtml);
            if (parent)
            {
                parent->addChild(newItem);
                parent->setExpanded(true);
            }
            else
            {
                ui->treeWidget->addTopLevelItem(newItem);
            }
            newItem->lastSavedAs = QFileInfo(directory.absolutePath() + '/' + fileName);
            //check if there's a directory of the same name
            //recurse into directory
            qDebug() << "going to: " << directory.absolutePath() + '/' + documentName;
            OpenItemsRecursively(directory.absolutePath() + '/' + documentName, newItem);
        }
    }
}

void MainWindow::SaveItem(PTreeTextItem* item)
{
    item->saveItem(projectDirString);
}

void MainWindow::CreateNewItem(PEDocumentType newItemType)
{
    QString* newItemName;
    if (newItemType == NOTE)
    {
        newItemName = new QString("NewNote");
    }
    else if (newItemType == DOCUMENT)
    {
        newItemName = new QString("NewDocument");
    }

    PTreeTextItem* newItem = new PTreeTextItem();
    QTreeWidgetItem* currentItem = ui->treeWidget->currentItem();
    if (currentItem)
    {
        newItem->setText(0, *newItemName);
        currentItem->addChild(newItem);
        currentItem->setExpanded(true);
    }
    else
    {
        newItem->setText(0, *newItemName);
        ui->treeWidget->addTopLevelItem(newItem);
    }

    ui->treeWidget->setCurrentItem(newItem);

    on_actionTreeItemRename_triggered();
}

void MainWindow::onTreeWidgetContextMenu(const QPoint& pos)
{
    QAction *action = treeContextMenu->exec(ui->treeWidget->mapToGlobal(pos));
}

void MainWindow::onTreeWidgetItemDoubleClicked(QTreeWidgetItem *item)
{
    PTreeTextItem *pItem = dynamic_cast<PTreeTextItem*>(item);
    qDebug() << pItem->getDocument()->toHtml();
    ui->labelViewMain->setText(item->text(0));
    ui->textEditMain->setDocument(pItem);
}

void MainWindow::onTextCursorMoved()
{
    updateTools();
}

void MainWindow::updateTools()
{
    ui->ButtonBold->setChecked(inFocusEdit->fontWeight() == QFont::Bold);
    ui->ButtonItalic->setChecked(inFocusEdit->fontItalic());
    ui->ButtonUnderline->setChecked(inFocusEdit->fontUnderline());
    //ui->ButtonStrike->setChecked(textEditor->);
}

void MainWindow::setTextAlignLeft()
{
    inFocusEdit->setAlignment(Qt::AlignLeft);
}

void MainWindow::setTextAlignCenter()
{
    inFocusEdit->setAlignment(Qt::AlignCenter);
}

void MainWindow::setTextAlignRight()
{
    inFocusEdit->setAlignment(Qt::AlignRight);
}

void MainWindow::on_actionCopy_triggered()
{
    //connected to default QTextEdit copy
}

void MainWindow::on_actionCut_triggered()
{
    //connected to default QTextEdit cut
}

void MainWindow::on_actionPaste_triggered()
{
    //connected to default QTextEdit paste
}

void MainWindow::on_actionAlignLeft_triggered()
{
    //implemented elsewhere, delete later
}

void MainWindow::on_actionAlignCenter_triggered()
{
    //implemented elsewhere, delete later
}

void MainWindow::on_actionAlignRight_triggered()
{
    //implemented elsewhere, delete later
}

void MainWindow::on_actionDocument_triggered()
{
    CreateNewItem(DOCUMENT);
}

void MainWindow::on_actionNote_triggered()
{
    CreateNewItem(NOTE);
}

void MainWindow::on_actionTreeItemRename_triggered()
{
    QTreeWidgetItem* currentItem = ui->treeWidget->currentItem();
    if (currentItem)
    {
        currentItem->setFlags(currentItem->flags() | Qt::ItemIsEditable);
        ui->treeWidget->editItem(currentItem);
    }
}

void MainWindow::on_actionTreeItemDelete_triggered()
{
    if (!ui->treeWidget->currentItem())
        return;

    PTreeTextItem *itemToDelete = dynamic_cast<PTreeTextItem*>(ui->treeWidget->currentItem());

    if (itemToDelete->getDocument() == ui->textEditMain->document())
    {
        if (ui->treeWidget->itemAt(0, 0))
        {
            PTreeTextItem *newFocus = dynamic_cast<PTreeTextItem*>(ui->treeWidget->itemAt(0, 0));
            ui->textEditMain->setDocument(newFocus);
        }
        else
        {
            ui->textEditMain->setEnabled(false);
            ui->textEditMain->setDocument(static_cast<PTreeTextItem*>(NULL));
        }
    }
    if (itemToDelete->getDocument() == ui->textEditOther->document())
    {
        closeOtherView(false);
    }

    delete itemToDelete;
}

void MainWindow::on_actionSave_All_triggered()
{
    if (projectDirString.isNull())
    {
        on_actionSave_Project_As_triggered();
    }
    else
    {
        SaveProject();
    }
}

void MainWindow::on_actionSave_Project_As_triggered()
{
    projectDirString = QFileDialog::getSaveFileName(this, "Save As...", QString(), "Directory", 0, QFileDialog::ShowDirsOnly);
    if (projectDirString.isNull())
        return;

    QDir().mkpath(projectDirString);
    SaveProject();
}

void MainWindow::on_actionSave_triggered()
{
    SaveItem(dynamic_cast<PTreeTextItem*>(ui->treeWidget->currentItem()));
}

void MainWindow::on_actionFullscreen_triggered()
{
    this->setWindowState(this->windowState() ^ Qt::WindowFullScreen);
}

void MainWindow::on_actionTreeItemOpenInOtherView_triggered()
{
    PTreeTextItem *item = dynamic_cast<PTreeTextItem*>(ui->treeWidget->currentItem());
    OpenInOtherView(item);
}

void MainWindow::toggleTextBold(bool b)
{
    inFocusEdit->setTextBold(b);
}

void MainWindow::toggleTextItalic(bool b)
{
    inFocusEdit->setFontItalic(b);
}

void MainWindow::toggleTextUnderline(bool b)
{
    inFocusEdit->setFontUnderline(b);
}

void MainWindow::toggleTextStrikethrough(bool b)
{
    inFocusEdit->setFontUnderline(b);
}

void MainWindow::setInFocusEdit(PTextEdit* editor)
{
    inFocusEdit = editor;
    updateTools();
}

void MainWindow::onFocusChanged(QWidget *oldFocus, QWidget *newFocus)
{
    if (newFocus == ui->textEditMain) setInFocusEdit(ui->textEditMain);
    else if (newFocus == ui->textEditOther) setInFocusEdit(ui->textEditOther);
}

void MainWindow::closeOtherView(bool bKeepUsingOtherDoc)
{
    if (bKeepUsingOtherDoc)
    {
        ui->textEditMain->setDocument(ui->textEditOther->getItem());
    }
    setInFocusEdit(ui->textEditMain);
    updateTools();
    ui->textEditOther->hide();
    ui->multiViewLabels->hide();
}

void MainWindow::on_actionOpen_triggered()
{
    PConfirmClose *confirmCloseDialog = new PConfirmClose();
    int dialogResult = confirmCloseDialog->exec();
    if (dialogResult == QDialogButtonBox::Yes || dialogResult == QDialogButtonBox::No)
    {
        if (dialogResult == QDialogButtonBox::Yes)
        {
            on_actionSave_All_triggered();
        }
        ClearProject(); //BAAAAD
        OpenProject(QFileDialog::getExistingDirectory());
        ui->textEditMain->setDocument(dynamic_cast<PTreeTextItem*>(ui->treeWidget->itemAt(0, 0)));
    }
}

void MainWindow::on_actionStats_triggered()
{
    PStatsDialog* statsDialog = new PStatsDialog(ui->textEditMain->getItem(), PTreeTextItem::getItemList(ui->treeWidget));
    statsDialog->show();
}
