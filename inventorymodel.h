#ifndef PRODUCTSMODEL_H
#define PRODUCTSMODEL_H

#include <QAbstractTableModel>
#include <QList>


// Some helper classes
enum ModelColumn {
    ID = 0,
    DESC = 1,
    PRICE = 2,
    COUNT = 3
};

// This class capsulates all data items
struct Article
{
    int id;
    QString desc;
    double price;
    int count;

    QVariant at(int columnIndex){
        switch (columnIndex) {
        case ModelColumn::ID:
            return id;
        case ModelColumn::DESC:
            return desc;
        case ModelColumn::PRICE:
            return price;
        case ModelColumn::COUNT:
            return count;
        default:
            return QVariant();
        }
    }
};



class InventoryModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit InventoryModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    void add(Article article);
    void remove(int index);

private:
    // TODO: Find out where this variable is used and set it to a correct value!
    static const int COLUMNS = /*FIXME*/;

    // Here is all the data stored!
    // TODO: There is a small mistake. Check the compiler error and correct it
    QList<> productList;
};

#endif // PRODUCTSMODEL_H
