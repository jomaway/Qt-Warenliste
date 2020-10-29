#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QShortcut>
#include <QFile>
#include <QTextStream>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->ui->tableProducts->horizontalHeader()->resizeSection(1, 350);

    // Add shortcut
    auto shortc_del = new QShortcut(Qt::Key_Delete, this->ui->tableProducts);
    connect(shortc_del, SIGNAL(activated()), this, SLOT(Key_Delete_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnAdd_clicked()
{
    auto id = this->ui->leditID->text().trimmed();
    if (id.length() != 4) {
        this->statusBar()->showMessage(tr("Error: ID needs to have 4 Digits!"));
        return;
    }
    auto desc = this->ui->leditDescription->text().trimmed();
    auto cost = this->ui->leditCosts->text();

    // Add new row to table
    addRow(id,desc,cost);

    // clear all input fields
    this->clearAllLineEditFields();
}

void MainWindow::clearAllLineEditFields()
{
    this->ui->leditID->clear();
    this->ui->leditDescription->clear();
    this->ui->leditCosts->clear();

}

void MainWindow::deleteArtikel(int rowIndex)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Lösche Artikel"),
                                  tr("Soll der Artikel wirklich gelöscht werden?"),
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        // delete Artikel
        this->ui->tableProducts->removeRow(rowIndex);
    } else {
      // do nothing
    }
}

void MainWindow::addRow(QString id, QString desc, QString cost)
{
    // Add new row to table
    auto table = this->ui->tableProducts;
    auto row_count = table->rowCount();
    table->setRowCount(row_count +1);

    // Add content to cell
    auto idItem = new QTableWidgetItem(id);
    // Make idTable not Editable
    idItem->setFlags(idItem->flags() &  ~Qt::ItemIsEditable);

    table->setItem(row_count, 0, idItem );
    table->setItem(row_count, 1, new QTableWidgetItem(desc));
    table->setItem(row_count, 2, new QTableWidgetItem(cost));
}

void MainWindow::Key_Delete_clicked()
{
    auto cell = this->ui->tableProducts->selectedItems().first();
    this->deleteArtikel(cell->row());
}

void MainWindow::on_actionOpen_triggered()
{
    // Open the file
    QFile file("liste.csv");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream in(&file);
        this->ui->tableProducts->setRowCount(0);
        // read line by line untill eof
        while(!in.atEnd()) {
            auto line = in.readLine();
            auto values = line.split(',');
            // Add line to table.
            addRow(values.at(0), values.at(1), values.at(2));
        }
        // close the file
        file.close();
        this->ui->statusbar->showMessage(tr("List opened"));
    } else {
        this->ui->statusbar->showMessage(tr("could not open the specified file: (liste.csv)"));
    }
}

void MainWindow::on_actionSave_triggered()
{
    QFile file("liste.csv");
    if (file.open(QFile::WriteOnly | QFile::Truncate | QFile::Text)) {
        QTextStream out(&file);
        // Get data from widget.
        for (int row = 0; row<this->ui->tableProducts->rowCount(); ++row) {
            for (int col=0; col<this->ui->tableProducts->columnCount() ; ++col) {
                auto value = this->ui->tableProducts->item(row,col)->text().replace(',','.');
                out << value;
                // add a comma after each element, except the last one!
                if ( col != this->ui->tableProducts->columnCount() -1) {
                    out << ",";
                }
            }
            // New line
            out << Qt::endl;
        }
        file.flush();
        file.close();

        this->ui->statusbar->showMessage(tr("List saved"));
    } else {
        this->ui->statusbar->showMessage(tr("could not open the specified file: (liste.csv)"));
    }
}
