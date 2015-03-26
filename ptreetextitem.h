#ifndef PTREETEXTITEM_H
#define PTREETEXTITEM_H

#include <QTextDocument>
#include <QTreeWidgetItem>
#include <QFileInfo>
#include <QDir>
#include <cstdint>
#include <QObject>
#include <QList>

class PTreeTextItem : public QTreeWidgetItem
{
public:
    PTreeTextItem();
    PTreeTextItem(QString name);
    ~PTreeTextItem();

    QTextDocument* getDocument() { return document; }
    void saveItem(QDir projectDir);
    static QList<PTreeTextItem*> getItemList(const QTreeWidget& tree);
    QFileInfo lastSavedAs;
private:
    QTextDocument* document;
};

#endif // PTREETEXTITEM_H
