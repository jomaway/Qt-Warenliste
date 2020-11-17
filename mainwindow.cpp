#include "inventorymodel.h"
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

    model = new InventoryModel();
    ui->inventoryView->setModel(model);
    // TODO: Find out how to hide the verticalHeader on a QTableView and add this in the next line!
    /*FIXME*/
    // TODO: Open the help and find out what the next two lines are for. Add a short comment for each line!
    ui->inventoryView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->inventoryView->setSelectionBehavior(QAbstractItemView::SelectRows);

    // Add shortcut
    auto shortc_del = new QShortcut(Qt::Key_Delete, this->ui->inventoryView);
    connect(shortc_del, SIGNAL(activated()), this, SLOT(Key_Delete_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnAdd_clicked()
{
    auto id = this->ui->leditID->text().trimmed().toInt();
    if (id < 1000) {
        this->statusBar()->showMessage(tr("Error: ID needs to have 4 Digits! And must only contain Numbers"));
        return;
    }
    auto desc = this->ui->leditDescription->text().trimmed();
    auto cost = this->ui->leditCosts->text().toDouble();

    // Add new row to table
    auto newArticle = Article({id, desc, cost, 100});
    model->add(newArticle);

    // clear all input fields
    this->clearAllLineEditFields();
}

void MainWindow::clearAllLineEditFields()
{
    this->ui->leditID->clear();
    this->ui->leditDescription->clear();
    this->ui->leditCosts->clear();

}



void MainWindow::Key_Delete_clicked()
{
    // TODO: Find out how to detect which row is selected and correct the next line!
    auto rowIndex = this->ui->inventoryView->/*FIXME*/.first().row();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Lösche Artikel"),
                                  tr("Soll der Artikel wirklich gelöscht werden?"),
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        // delete Artikel
        model->remove(rowIndex);
    } else {
      // do nothing
    }
}

void MainWindow::on_actionOpen_triggered()
{
    //FIXME
}

void MainWindow::on_actionSave_triggered()
{
    //FIXME
}
