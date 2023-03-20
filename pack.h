#ifndef PACK_H
#define PACK_H
#include "connection.h"
#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTableView>
#include <QMessageBox>
#include <QFile>
#include <QCoreApplication>
#include <QFileDialog>
#include <QTextDocument>
#include <QTextStream>


class Pack
{
public:
    Pack();
    Pack(int,QString,QString,QDate);

    QSqlQueryModel * affichPack();
    QSqlQueryModel * triPackQTE();
    QSqlQueryModel * triPackNOM();
    QSqlQueryModel * triPackBRAND();

    bool ajoutPack();
    bool supprimPack(QString);
    QSqlQueryModel * searchPack(QString);  //recherche par koll chay XD
    bool modifierAdo(QString,int);
    void generatePdf(QTableView *tableView);
    void genereExcel(QTableView *table);



private:
int idp;
int qte;
QString nom;
QString brand;
QDate dates;


};

#endif // PACK_H
