#include "client.h"

//********Initialisation

//Constructeur par defaut
Client::Client()
{

}

//Constructeur pour Afficher

Client::Client(int id,QString email,QString mdp)
{
    this->id=id;
    this->email=email;
    this->mdp=mdp;

}

//Constructeur pour Ajouter

Client::Client(QString email,QString mdp)
{
    this->id=id;
    this->email=email;
    this->mdp=mdp;

}




//*******AJOUTER

bool Client::ajouter()
{
QSqlQuery query;

query.prepare("INSERT INTO Client (email, mdp) "
                    "VALUES (:email, :mdp)");


query.bindValue(":email", email);
query.bindValue(":mdp", mdp);


return    query.exec();
}

//******AFFICHER

QSqlQueryModel * Client::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from Client");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Email"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Mot de passe"));

    return model;
}

//*******SUPPRIMPER

bool Client::supprimer(int idd)
{
QSqlQuery query;
QString res= QString::number(idd);
query.prepare("Delete from Client where ID = :id ");
query.bindValue(":id", res);
return    query.exec();
}



//*******MODIFIER

bool Client::modifier(QString email, QString mdp,QString id)
{
QSqlQuery query;

query.prepare("UPDATE Client SET email= :email, mdp= :mdp "
                    " WHERE  ID = :id ");


query.bindValue(":id", id);
query.bindValue(":email", email);
query.bindValue(":mdp", mdp);


return    query.exec();
}

//******REMPLIR COMBO BOX

QSqlQueryModel * Client::remplircomboclient()
{
    QSqlQueryModel * mod= new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("select ID from Client");
    query.exec();
    mod->setQuery(query);
    return mod;
}


QSqlQuery Client::request(QString id)
{
    QSqlQuery query;
    query.prepare("select * from Client where ID= '"+id+"'");
    query.addBindValue(id);
    query.exec();
    return query;
}

//******RECHERCHE AVANCEE

QSqlQueryModel * Client::afficherecherche(QString res)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("select * from Client  where (email LIKE '%"+res+"%' OR id LIKE '%"+res+"%')");
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Mot de passe"));


    return model;
}

//******AFFICHER TRI

QSqlQueryModel * Client::triafficher(QString col)
{QSqlQueryModel * model= new QSqlQueryModel();

    QSqlQuery query;
    query.prepare("select * from Client order by "+col);
    query.exec();


model->setQuery(query);

model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Email"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Mot de passe"));


return model;
}

QSqlQuery Client::login(QString email,QString mdp)
{
    QSqlQuery query;
    query.prepare("select * from Client where email= '"+email+"' and mdp='"+mdp+"'");
    query.exec();
    return query;
}

QSqlQuery Client::checkemail(QString email)
{
    QSqlQuery query;
    query.prepare("select * from Client where email= '"+email+"'");
    query.exec();
    return query;
}

