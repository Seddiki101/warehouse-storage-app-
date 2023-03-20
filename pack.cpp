#include "pack.h"
Pack::Pack()
{

}


Pack::Pack(int q,QString n,QString b,QDate d)
{
//this->idp=i;
this->qte=q;
this->nom=n;
this->brand=b;
this->dates=d;
}


QSqlQueryModel * Pack::affichPack(){    
    QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("select NOM,BRAND,QTE,DATES from Storage")	;
model->setHeaderData(0,Qt::Horizontal,QObject::tr("nom"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("marque"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("quantity"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("date d'ajout"));
    return model;
}

QSqlQueryModel * Pack::triPackQTE(){
    QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("select NOM,BRAND,QTE,DATES from Storage ORDER BY QTE DESC ")	;
model->setHeaderData(0,Qt::Horizontal,QObject::tr("nom"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("marque"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("quantity"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("date d'ajout"));
    return model;
}


QSqlQueryModel * Pack::triPackNOM(){
    QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("select NOM,BRAND,QTE,DATES from Storage ORDER BY NOM ")	;
model->setHeaderData(0,Qt::Horizontal,QObject::tr("nom"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("marque"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("quantity"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("date d'ajout"));
    return model;
}

QSqlQueryModel * Pack::triPackBRAND(){
    QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("select NOM,BRAND,QTE,DATES from Storage ORDER BY BRAND ")	;
model->setHeaderData(0,Qt::Horizontal,QObject::tr("nom"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("marque"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("quantity"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("date d'ajout"));
    return model;
}

bool Pack::ajoutPack(){
    QSqlQuery query;
    //QString idp_string=QString::number(idp);//not so sure abt this
    QString qte_string=QString::number(qte);

           query.prepare("insert into Storage (QTE,NOM,BRAND,DATES)"
                   "values( :QTE, :NOM, :BRAND, :DATES)");

          // query.bindValue(":IDO",idp_string);
           query.bindValue(":QTE",qte_string);
           query.bindValue(":NOM",nom);
           query.bindValue(":BRAND",brand);
           query.bindValue(":DATES",dates);
         return query.exec();
}




bool Pack::supprimPack(QString name){
    QSqlQuery query;
          query.prepare("DELETE FROM Storage WHERE NOM=:name");
          query.bindValue(":name", name);
          return query.exec();
}




// recherche par nom
QSqlQueryModel * Pack::searchPack(QString recherche){
    QSqlQueryModel* model=new QSqlQueryModel();
    QSqlQuery query;

    if (recherche.length()!=0)
    {
    //old way didn t work for some reason
    //query.prepare(" SELECT NOM,BRAND,QTE,DATES FROM Storage WHERE NOM LIKE '"+recherche+"%' OR BRAND LIKE '"+recherche+"%' ");
    //query.addBindValue(recherche);
    query.prepare("SELECT NOM,BRAND,QTE,DATES FROM Storage where NOM LIKE :cherch OR BRAND LIKE :cherch ");
    query.bindValue(":cherch", QString("%%1%").arg(recherche));
    query.exec();
    model->setQuery(query);
    }
    else
    {
        model->setQuery("SELECT NOM,BRAND,QTE,DATES FROM Storage");
    }
    return model;
}


void Pack::genereExcel(QTableView *table){

    QString filters("CSV files (.csv);;All files (.*)");
    QString defaultFilter("CSV files (*.csv)");
    QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                             filters, &defaultFilter);
          QFile file(fileName);

          QAbstractItemModel *model =  table->model();
          if (file.open(QFile::WriteOnly | QFile::Truncate)) {
              QTextStream data(&file);
              QStringList strList;
              for (int i = 0; i < model->columnCount(); i++) {
                  if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                      strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
                  else
                      strList.append("");
              }
              data << strList.join(";") << "\n";
              for (int i = 0; i < model->rowCount(); i++) {
                  strList.clear();
                  for (int j = 0; j < model->columnCount(); j++) {

                      if (model->data(model->index(i, j)).toString().length() > 0)
                          strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                      else
                          strList.append("");
                  }
                  data << strList.join(";") + "\n";
              }
              file.close();
              QMessageBox::information(nullptr, QObject::tr("GENERATION EXCEL"),
                                        QObject::tr("GENERATION REALISEE AVEC SUCCES\n"
                                                    "Click OK to exit."), QMessageBox::Ok);
          }



}




bool Pack::modifierAdo(QString n,int q){
    QSqlQuery query;
           query.prepare("Update Storage SET QTE=:qty WHERE NOM=:nme ");
           query.bindValue(":nme",n);
           query.bindValue(":qty",q);
         return query.exec();
}
