#include "inventorymodel.h"


// TODO: look through the entire file and fix all /*FIXME*/ statements with a correct solution!
// there should be 8 in this file

InventoryModel::InventoryModel(QObject *parent)
    : QAbstractTableModel(parent)
{

    // Generate some random values
    productList.append(Article({1241,"Schampoo", 3.44, 12}));
    productList.append(Article({6243,"Rasierer",  54.99, 4}));
    productList.append(Article({9413,"Bleistift", 1.49, 234}));
}

QVariant InventoryModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    if (/*FIXME*/ == Qt::Horizontal) {
        switch (section) {
        case ModelColumn::ID:
            return tr("ID");
        case ModelColumn::DESC:
            return tr("Artikel");
        case ModelColumn::/*FIXME*/:
            return tr("Preis");
        case ModelColumn::/*FIXME*/
            return tr("Anzahl");
        }
    }
    return QVariant();
}


int InventoryModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return /*FIXME*/ ;
}

int InventoryModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return COLUMNS;
}

QVariant InventoryModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole) {
        /*FIXME*/  article = this->productList.at(index.row());
        return article.at(/*FIXME*/ );
    }

    return QVariant();
}

bool InventoryModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    return false;
}

Qt::ItemFlags InventoryModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractTableModel::flags(index);

}

void InventoryModel::add(Article article)
{
    beginInsertRows(QModelIndex(), 0, 0);
    this->productList./*FIXME*/ (article);
    endInsertRows();
}

void InventoryModel::remove(int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    this->productList.removeAt(index);
    /*FIXME*/
}
