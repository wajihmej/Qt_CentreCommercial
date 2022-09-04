#include "parking.h"

Parking::Parking()
{

}
//Constructeur pour Afficher

Parking::Parking(int id,QString nom,QString etat,int nbplace)
{
    this->id=id;
    this->nom=nom;
    this->etat=etat;
    this->nbplace=nbplace;

}

//Constructeur pour Ajouter

Parking::Parking(QString nom,QString etat,int nbplace)
{
    this->nom=nom;
    this->etat=etat;
    this->nbplace=nbplace;

}


//*******AJOUTER

bool Parking::ajouter()
{
QSqlQuery query;

query.prepare("INSERT INTO Parking (nom, etat, nbplace) "
                    "VALUES (:nom, :etat, :nbplace)");


query.bindValue(":nom", nom);
query.bindValue(":etat", etat);
query.bindValue(":nbplace", nbplace);


return    query.exec();
}

//******AFFICHER

QSqlQueryModel * Parking::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from Parking");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Etat"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Nombre de place"));

    return model;
}

//*******SUPPRIMPER

bool Parking::supprimer(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
query.prepare("Delete from Parking where ID = :id ");
query.bindValue(":id", res);
return    query.exec();
}



//*******MODIFIER

bool Parking::modifier(QString nom, QString etat,QString nbplace,QString id)
{
QSqlQuery query;

query.prepare("UPDATE Parking SET nom= :nom, etat= :etat , nbplace= :nbplace WHERE  ID = :id ");


query.bindValue(":id", id);
query.bindValue(":nom", nom);
query.bindValue(":etat", etat);
query.bindValue(":nbplace", nbplace);


return    query.exec();
}

//******REMPLIR COMBO BOX

QSqlQueryModel * Parking::remplircomboparking()
{
    QSqlQueryModel * mod= new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("select ID from Parking");
    query.exec();
    mod->setQuery(query);
    return mod;
}


QSqlQuery Parking::request(QString id)
{
    QSqlQuery query;
    query.prepare("select * from Parking where ID= '"+id+"'");
    query.addBindValue(id);
    query.exec();
    return query;
}

//******RECHERCHE AVANCEE

QSqlQueryModel * Parking::afficherecherche(QString res)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("select * from Parking  where (nom LIKE '%"+res+"%' OR id LIKE '%"+res+"%' OR nbplace LIKE '%"+res+"%')");
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Etat"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Nombre de place"));


    return model;
}

//******AFFICHER TRI

QSqlQueryModel * Parking::triafficher(QString col)
{QSqlQueryModel * model= new QSqlQueryModel();

    QSqlQuery query;
    query.prepare("select * from Parking order by "+col);
    query.exec();


model->setQuery(query);

model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Etat"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Nombre de place"));


return model;
}


//STAT

int Parking::dispo(){
    QSqlQuery query;
     query.prepare("select  * from Parking  WHERE etat= 'Disponible'");
     query.exec();
      int total=0;

     while(query.next()){
       total++;

     }


     return total;
}


int Parking::nondispo(){
    QSqlQuery query;
     query.prepare("select  * from Parking  WHERE etat = 'Non disponible'");
     query.exec();
      int total=0;

     while(query.next()){
       total++;

     }


     return total;
}
