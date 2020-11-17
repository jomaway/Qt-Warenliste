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


bool InventoryModel::saveTo(QString filename)
{
    // Open file
    QFile file(filename);
    if (file.open(QFile::WriteOnly | QFile::Truncate | QFile::Text)) {
        // Create an TextStream to write to the file! Takes the filehandler as argument.
        QTextStream out(&file);
        for (auto article : productList) {
            out << article.id << "," << article.desc << "," << article.price << "," << article.count << Qt::endl;
        }
        // Make sure everything get's written to the file.
        /*FIXME*/

        // REMEMBER to close the file if you opened it!
        file.close();
        return true;
    }else {
        return false;
    }
}

bool InventoryModel::openFrom(QString filename)
{
    // Open the file
    QFile file(filename);
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        // clear current list.
        beginRemoveRows(QModelIndex(), 0, productList.count()-1);
        this->productList.clear();
        endRemoveRows();

        // create TextStream
        QTextStream in(&file);
        // read line by line untill eof
        while(!in.atEnd()) {
            // Read a line into the line variable (type of QString)
            auto line = in.readLine();
            // split the Qstring into multiple Qstrings. Uses a comma as delimiter
            // this returns a QStringList
            // Exmaple: "0001, Artikel, 0.00" -> "0001" and "Artikel" and "0.00"
            auto values = line.split(',');
            // Add line to table by using the addRow method
            add(Article({values.at(0).toInt(), values.at(1), values.at(2).toDouble(), values.at(3).toInt()}));
        }
        // close the file
        file.close();
        return true;
    } else {
        return false;
    }
}
