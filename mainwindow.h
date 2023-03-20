#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "pack.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Pack drivr;
    Connection dbObj ;
    QString errormsg="";
    int key=0;

private slots:

    void on_login_pb_clicked();

    void on_add_return_pb_clicked();

    void on_add_pb_clicked();

    void on_refresh_pb_clicked();

    void on_back0_pb_clicked();

    void on_search_LE_textChanged(const QString &arg1);

    void on_name_sort_radioBtn_clicked();

    void on_brand_sort_radioBtn_clicked();

    void on_qte_sort_radioBtn_clicked();

    void on_delete_pb_clicked();

    void on_pushButton_7_clicked();

    void on_extractCSV_pb_clicked();

    void on_back1_pb_clicked();

    void on_edit_pb_clicked();

    void on_commandLinkButton_clicked();

    void on_help_clb_clicked();

    void on_help_pb_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
