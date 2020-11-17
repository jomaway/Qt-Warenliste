#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include /*FIXME*/

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnAdd_clicked();

    void Key_Delete_clicked();
    void on_actionOpen_triggered();

    void on_actionSave_triggered();

private:
    Ui::MainWindow *ui;
    InventoryModel *model;
    void clearAllLineEditFields();
    void deleteArtikel(int rowIndex);
    void addRow(QString id, QString desc, QString cost);
};
#endif // MAINWINDOW_H
