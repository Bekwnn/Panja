#include "ptreetextitem.h"

#include <QTextDocumentWriter>
#include <QDebug>
#include <QUrl>

PTreeTextItem::PTreeTextItem()
{
    document = new QTextDocument();
    lastSavedAs = QFileInfo();
}

PTreeTextItem::PTreeTextItem(QString name)
{
    document = new QTextDocument();
    lastSavedAs = QFileInfo();
    setText(0, name);
}

PTreeTextItem::~PTreeTextItem()
{

}

void PTreeTextItem::saveItem(QDir projectDir)
{
    QTextDocumentWriter docWriter;
    QString relativePath = QString();
    QTreeWidgetItem* itemTrace = this->QTreeWidgetItem::parent();
    while (itemTrace)
    {
        relativePath.prepend("/" + itemTrace->text(0));
        itemTrace = itemTrace->parent();
    }
    projectDir.mkpath(projectDir.path() + relativePath);
    QString fileName(projectDir.path() + relativePath + "/" + QUrl::toPercentEncoding(this->text(0)).replace("%20", " ") + ".html");
    docWriter.setFormat("HTML");
    docWriter.setFileName(fileName);
    qDebug() << fileName << lastSavedAs.absoluteFilePath() << endl;
    if (lastSavedAs.absoluteFilePath() != fileName && lastSavedAs.absoluteFilePath() != "")
    {
        qDebug() << "MISMATCH:" << fileName << lastSavedAs.absoluteFilePath() << endl;
        QDir oldDir(lastSavedAs.absolutePath());
        QFile::remove(lastSavedAs.absoluteFilePath());
        if (oldDir.count() == 0)
        {
            oldDir.rmdir(lastSavedAs.absolutePath());
        }
    }
    docWriter.write(this->getDocument());
    lastSavedAs = QFileInfo(fileName);
}

QList<PTreeTextItem*> PTreeTextItem::getItemList(QTreeWidget* tree)
{
    QList<PTreeTextItem*> itemList;
    QTreeWidgetItemIterator iter(tree);
    while (*iter)
    {
        itemList.append(dynamic_cast<PTreeTextItem*>(*iter));
        ++iter;
    }
    return itemList;
}
