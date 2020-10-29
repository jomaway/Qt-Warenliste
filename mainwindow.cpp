#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QShortcut>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QFileDialog>

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
    // Open the File Dialog -> returns a fileName
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open a list"), "", tr("CSV Files(*.csv)"));
    // check if filename is empty.
    if (fileName.isEmpty()) { return; }
    // Open the file
    QFile file(fileName);
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream in(&file);
        this->ui->tableProducts->setRowCount(0);
        // read line by line untill eof
        while(!in.atEnd()) {
            // Read a line into the line variable (type of QString)
            auto line = in.readLine();
            // split the Qstring into multiple Qstrings. Uses a comma as delimiter
            // this returns a QStringList
            // Exmaple: "0001, Artikel, 0.00" -> "0001" and "Artikel" and "0.00"
            auto values = line.split(',');
            // Add line to table by using the addRow method
            addRow(values.at(0), values.at(1), values.at(2));
        }
        // close the file
        file.close();
        this->ui->statusbar->showMessage(tr("List opened"));
    } else {
        this->ui->statusbar->showMessage(tr("could not open the specified file:"));
    }
}

void MainWindow::on_actionSave_triggered()
{
    // Open the File Dialog -> returns the FileName
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save the list"), "", tr("CSV Files(*.csv)"));
    // check if filename is empty and cancel saving
    if (fileName.isEmpty()) { return; }

    // Open file
    QFile file(fileName);
    if (file.open(QFile::WriteOnly | QFile::Truncate | QFile::Text)) {
        // Create an TextStream to write to the file! Takes the filehandler as argument.
        QTextStream out(&file);
        // Get data from widget.
        // Use two loops first for the rows -> second for the columns!
        for (int row = 0; row<this->ui->tableProducts->rowCount(); ++row) {
            for (int col=0; col<this->ui->tableProducts->columnCount() ; ++col) {
                // Get text from the given cell and replace all commas with points.
                // value is of type  QString.
                auto value = this->ui->tableProducts->item(row,col)->text().replace(',','.');
                // write value to the textstream
                out << value;
                // add a comma after each element, except the last one!
                if ( col != this->ui->tableProducts->columnCount() -1) {
                    out << ",";
                }
            }
            // Add a new line
            out << Qt::endl;
        }
        // flush so everything get's written to the file!
        file.flush();
        // REMEMBER to close the file if you opened it!
        file.close();

        // Write a notification to the status bar!
        this->ui->statusbar->showMessage(tr("List saved"));
    } else {
        // On error show message on the statusbar!
        this->ui->statusbar->showMessage(tr("could not open the specified file:"));
    }
}
