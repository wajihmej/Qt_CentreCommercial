#ifndef ESPACEADMIN_H
#define ESPACEADMIN_H

#include <QMainWindow>
#include "parking.h"
#include "client.h"
#include <QSystemTrayIcon>

namespace Ui {
class EspaceAdmin;
}

class EspaceAdmin : public QMainWindow
{
    Q_OBJECT

public:
    explicit EspaceAdmin(QWidget *parent = nullptr);
    ~EspaceAdmin();

private slots:
    void on_deconnexion_clicked();
    void refresh();
    void statrefresh();

    void on_client_comboBox_modif_currentIndexChanged(const QString &arg1);

    void on_client_comboBox_supp_currentIndexChanged(const QString &arg1);

    void on_client_SupprimerBouton_clicked();

    void on_client_ModifierBouton_clicked();

    void on_client_recherche_cursorPositionChanged(int arg1, int arg2);

    void on_parking_AjouterBouton_clicked();

    void on_parking_comboBox_modif_currentIndexChanged(const QString &arg1);

    void on_parking_comboBox_supp_currentIndexChanged(const QString &arg1);

    void on_parking_ModifierBouton_clicked();

    void on_parking_SupprimerBouton_clicked();

    void on_parking_recherche_cursorPositionChanged(int arg1, int arg2);

    void on_comboBox_Tri_currentIndexChanged(const QString &arg1);

    void on_PDF_clicked();

private:
    Ui::EspaceAdmin *ui;
    Client tmpclient;
    Parking tmpparking;
    QSystemTrayIcon * trayIcon;

};

#endif // ESPACEADMIN_H
