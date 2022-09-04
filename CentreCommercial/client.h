#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QtGui>
#include <QtSql>
#include <QtCore>


class Client
{
public:
    Client();

    Client(int,QString,QString);
    Client(QString,QString);

    bool ajouter();
    bool supprimer(int);

    QSqlQueryModel * afficherecherche(QString);
    QSqlQueryModel * triafficher(QString);
    QSqlQueryModel * afficher();
    QSqlQueryModel * remplircomboclient();
    QSqlQuery request(QString);
    bool modifier(QString,QString,QString);

    QSqlQuery login(QString,QString);
    QSqlQuery checkemail(QString);

private:
    int id;
    QString email;
    QString mdp;

};

#endif // CLIENT_H
