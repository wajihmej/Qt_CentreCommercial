#ifndef PARKING_H
#define PARKING_H
#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QtGui>
#include <QtSql>
#include <QtCore>

class Parking
{
public:
    Parking();
    Parking(int,QString,QString,int);
    Parking(QString,QString,int);

    bool ajouter();
    bool supprimer(int);

    QSqlQueryModel * afficherecherche(QString);
    QSqlQueryModel * triafficher(QString);
    QSqlQueryModel * afficher();
    QSqlQueryModel * remplircomboparking();
    QSqlQuery request(QString);
    bool modifier(QString,QString,QString,QString);
    int dispo();
    int nondispo();

private:
    int id;
    QString nom;
    QString etat;
    int nbplace;

};

#endif // PARKING_H
