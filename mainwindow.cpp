#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dbObj.createconnect();
      ui->quantity_LE->setValidator(new QIntValidator(0,999,this));
        ui->updQuantity_LE->setValidator(new QIntValidator(0,999,this));
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_login_pb_clicked()
{
    if ( ui->usrname_LE->text()=="user"  && ui->pswd_LE->text()=="user" ) {

    ui->stackedWidget->setCurrentIndex(1);
     ui->tabvPack->setModel(drivr.affichPack());
         dbObj.createconnect();
        }
    else{

        QMessageBox::information(nullptr, QObject::tr("Unregistred entry "),
                                  QObject::tr("Contact admin to regain access \n"
                                              "Click OK to exit."), QMessageBox::Ok);
    }

}

//this takes u to adding page
void MainWindow::on_add_pb_clicked()
{
   ui->stackedWidget->setCurrentIndex(2);
}

//this fills the data and if valid returns
void MainWindow::on_add_return_pb_clicked()
{
    //getting user input
    QDate dat=QDate::currentDate();
    QString nam,brnd;
    int qty;
    nam=ui->name_LE->text();
    brnd=ui->brand_LE->text();
    qty=ui->quantity_LE->text().toInt();
    bool testi=true;

    //testing if input is valid
    if(ui->name_LE->text().isEmpty()){errormsg="Name not valid. ";testi=false;}
    if(ui->brand_LE->text().isEmpty()){errormsg="Brand not valid." ;testi=false;}
    if(ui->quantity_LE->text().isEmpty()){errormsg= errormsg.append("Quantity not valid. ");testi=false;}
    //sending query
    if (testi){
    Pack pp(qty,nam,brnd,dat);
    pp.ajoutPack();
    //updating view
    ui->tabvPack->setModel(drivr.affichPack());
    ui->stackedWidget->setCurrentIndex(1);
    } else {
        ui->add_error_label->clear();
        ui->add_error_label->setText(errormsg);
            }
//end
}


void MainWindow::on_refresh_pb_clicked()
{
      ui->tabvPack->setModel(drivr.affichPack());
}


void MainWindow::on_back0_pb_clicked()
{
       ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_search_LE_textChanged(const QString &arg1)
{
QString inpt;
inpt=ui->search_LE->text();
ui->tabvPack->setModel( drivr.searchPack(inpt) );
}

void MainWindow::on_name_sort_radioBtn_clicked()
{
   ui->tabvPack->setModel(drivr.triPackNOM());
}

void MainWindow::on_brand_sort_radioBtn_clicked()
{
   ui->tabvPack->setModel(drivr.triPackBRAND());
}

void MainWindow::on_qte_sort_radioBtn_clicked()
{
   ui->tabvPack->setModel(drivr.triPackQTE());
}

void MainWindow::on_delete_pb_clicked()
{
    QString name;
            QModelIndex index=ui->tabvPack->selectionModel()->currentIndex();
            QVariant value=index.sibling(index.row(),index.column()).data(); //will get the value of the clicked cell.
            name=value.toString();

       drivr.supprimPack(name);
        ui->tabvPack->setModel(drivr.affichPack());


}



void MainWindow::on_extractCSV_pb_clicked()
{
 drivr.genereExcel(ui->tabvPack)   ;
}

void MainWindow::on_back1_pb_clicked()
{
     ui->stackedWidget->setCurrentIndex(1);
}





void MainWindow::on_edit_pb_clicked()
{
    QString name;
    int q;
            QModelIndex index=ui->tabvPack->selectionModel()->currentIndex();
            QVariant value=index.sibling(index.row(),index.column()).data(); //will get the value of the clicked cell.
            name=value.toString();



            q= ui->updQuantity_LE->text().toInt();
            drivr.modifierAdo(name,q);

  //ui->updQuantity_LE->setEchoMode(QLineEdit::NoEcho);
ui->tabvPack->setModel(drivr.affichPack());

}




void MainWindow::on_help_pb_clicked()
{
           ui->stackedWidget->setCurrentIndex(3);
}
