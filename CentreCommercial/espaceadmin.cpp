#include "espaceadmin.h"
#include "ui_espaceadmin.h"
#include "mainwindow.h"
#include <QMessageBox>
#include<QtCharts>
#include<QChartView>
#include<QPieSeries>

#include <QtPrintSupport/QPrintDialog>
#include <QPrinter>
#include <QPrintPreviewDialog>

EspaceAdmin::EspaceAdmin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EspaceAdmin)
{
    ui->setupUi(this);

    setWindowTitle("Espace Admin");
    //Column size
    ui->tableView_client->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//client
    ui->tableView_parking->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//parking

    //Validation
    QIntValidator *num = new QIntValidator(1,9999);
    ui->parking_nbplace->setValidator(num);
    ui->parking_nbplace_modif->setValidator(num);

    //combo PARKING
    //TRI
    QStringList list;
    list << "" << "Nom" << "etat" << "nbplace";

    ui->comboBox_Tri->addItems(list);
    //ETAT
    QStringList listetat;
    listetat << "Disponible" << "Non disponible";

    ui->parking_comboBox_etat->addItems(listetat);
    ui->parking_comboBox_etat_modif->addItems(listetat);

    //refresh tables
    refresh();

}

EspaceAdmin::~EspaceAdmin()
{
    delete ui;
}

void EspaceAdmin::refresh()
{
    //Client
    ui->tableView_parking->setModel(tmpparking.afficher());
    ui->client_comboBox_supp->setModel(tmpclient.remplircomboclient());
    ui->client_comboBox_modif->setModel(tmpclient.remplircomboclient());

    //Parking
    ui->tableView_client->setModel(tmpclient.afficher());
    ui->parking_comboBox_supp->setModel(tmpparking.remplircomboparking());
    ui->parking_comboBox_modif->setModel(tmpparking.remplircomboparking());

    //STAT
    statrefresh();
}


void EspaceAdmin::on_deconnexion_clicked()
{
    EspaceAdmin::close();
    MainWindow *m = new MainWindow();
    m->show();

}

void EspaceAdmin::on_client_comboBox_modif_currentIndexChanged(const QString &arg1)
{
    QSqlQuery query;

    QString id = ui->client_comboBox_modif->currentText();

    query =tmpclient.request(id);
    if(query.exec())
    {
        while(query.next())
        {
            ui->client_email_modif->setText(query.value(1).toString());
            ui->client_mdp_modif->setText(query.value(2).toString());
        }
    }

}

void EspaceAdmin::on_client_comboBox_supp_currentIndexChanged(const QString &arg1)
{
    QSqlQuery query;

    QString id = ui->client_comboBox_supp->currentText();

    query =tmpclient.request(id);
    if(query.exec())
    {
        while(query.next())
        {
            ui->client_email_supp->setText(query.value(1).toString());
            ui->client_mdp_supp->setText(query.value(2).toString());
        }
    }

}

void EspaceAdmin::on_client_SupprimerBouton_clicked()
{
    QMessageBox::StandardButton reply =QMessageBox::question(this,
                          "Supprimer","Voulez-vous vraiment supprimer ?",
                          QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        bool test=tmpclient.supprimer(ui->client_comboBox_supp->currentText().toInt());
        if(test)
        {
            //refresh combobox + tableau
            refresh();


            //NOTIFICATION
            trayIcon = new QSystemTrayIcon(this);
            trayIcon->setVisible(true);
            trayIcon->setIcon(this->style()->standardIcon(QStyle::SP_DesktopIcon));
            trayIcon->setToolTip("Supprimer" "\n"
                            "Supprimer avec sucées");
            trayIcon->showMessage("Supprimer","Supprimer avec sucées",QSystemTrayIcon::Critical,1500);
            trayIcon->show();


        }
        else
        {
            QMessageBox::critical(this, QObject::tr("Supprimer un client"),
                        QObject::tr("Erreur !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }

    }

}

void EspaceAdmin::on_client_ModifierBouton_clicked()
{
    if((ui->client_mdp_modif->toPlainText() != "") &&(ui->client_email_modif->toPlainText() != ""))
    {
        if(tmpclient.modifier(ui->client_email_modif->toPlainText(),ui->client_mdp_modif->toPlainText(),ui->client_comboBox_modif->currentText()))
        {
            //refresh combobox + tableau
            refresh();

            //NOTIFICATION
            trayIcon = new QSystemTrayIcon(this);
            trayIcon->setVisible(true);
            trayIcon->setIcon(this->style()->standardIcon(QStyle::SP_DesktopIcon));
            trayIcon->setToolTip("Modifier" "\n"
                            "Modifier avec sucées");
            trayIcon->showMessage("Modifier","Modifier avec sucées",QSystemTrayIcon::Warning,1500);
            trayIcon->show();


        }
        else
        {
            QMessageBox::critical(this, QObject::tr("Modifier un client"),
                        QObject::tr("Erreur !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }


    }

}

void EspaceAdmin::on_client_recherche_cursorPositionChanged(int arg1, int arg2)
{
    ui->tableView_client->setModel(tmpclient.afficherecherche(ui->client_recherche->text()));

    QString test =ui->client_recherche->text();

    if(test=="")
    {
        ui->tableView_client->setModel(tmpclient.afficher());//refresh
    }

}

//PARKING

void EspaceAdmin::on_parking_AjouterBouton_clicked()
{
    if(ui->parking_nom->text() != "" && ui->parking_nbplace->text() !="")
    {
        Parking park(ui->parking_nom->text(),ui->parking_comboBox_etat->currentText(),ui->parking_nbplace->text().toInt());
        bool test = park.ajouter();
        if(test)
    {
            //refresh combobox + tableau

            refresh();

            //NOTIFICATION
            trayIcon = new QSystemTrayIcon(this);
            trayIcon->setVisible(true);
            trayIcon->setIcon(this->style()->standardIcon(QStyle::SP_DesktopIcon));
            trayIcon->setToolTip("Ajouter" "\n"
                            "Ajouter avec sucées");
            trayIcon->showMessage("Ajouter","Ajouter avec sucées",QSystemTrayIcon::Information,1500);
            trayIcon->show();


            }
              else
              {
                  QMessageBox::critical(nullptr, QObject::tr("Ajouter un PARKING"),
                              QObject::tr("Erreur !.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
              }
    }
    else{
        QMessageBox::critical(nullptr, QObject::tr("Verifier les champs"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void EspaceAdmin::on_parking_comboBox_modif_currentIndexChanged(const QString &arg1)
{
    QSqlQuery query;

    QString id = ui->parking_comboBox_modif->currentText();

    query =tmpparking.request(id);
    if(query.exec())
    {
        while(query.next())
        {
            ui->parking_nom_modif->setText(query.value(1).toString());
            ui->parking_comboBox_etat_modif->setCurrentText(query.value(2).toString());
            ui->parking_nbplace_modif->setText(query.value(3).toString());
        }
    }

}

void EspaceAdmin::on_parking_comboBox_supp_currentIndexChanged(const QString &arg1)
{
    QSqlQuery query;

    QString id = ui->parking_comboBox_supp->currentText();

    query =tmpparking.request(id);
    if(query.exec())
    {
        while(query.next())
        {
            ui->parking_nom_supp->setText(query.value(1).toString());
            ui->parking_etat_supp->setText(query.value(2).toString());
            ui->parking_nbplace_supp->setText(query.value(3).toString());
        }
    }

}

void EspaceAdmin::on_parking_ModifierBouton_clicked()
{
    if((ui->parking_nom_modif->text() != "") &&(ui->parking_nbplace_modif->text() != ""))
    {
        if(tmpparking.modifier(ui->parking_nom_modif->text(),ui->parking_comboBox_etat_modif->currentText(),ui->parking_nbplace_modif->text(),ui->parking_comboBox_modif->currentText()))
        {
            //refresh combobox + tableau
            refresh();
            //NOTIFICATION
            trayIcon = new QSystemTrayIcon(this);
            trayIcon->setVisible(true);
            trayIcon->setIcon(this->style()->standardIcon(QStyle::SP_DesktopIcon));
            trayIcon->setToolTip("Modifier" "\n"
                            "Modifier avec sucées");
            trayIcon->showMessage("Modifier","Modifier avec sucées",QSystemTrayIcon::Warning,1500);
            trayIcon->show();

        }
        else
        {
            QMessageBox::critical(this, QObject::tr("Modifier un PARKING"),
                        QObject::tr("Erreur !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }


    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Verifier les champs"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void EspaceAdmin::on_parking_SupprimerBouton_clicked()
{
    QMessageBox::StandardButton reply =QMessageBox::question(this,
                          "Supprimer","Voulez-vous vraiment supprimer ?",
                          QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        bool test=tmpparking.supprimer(ui->parking_comboBox_supp->currentText().toInt());
        if(test)
        {
            //refresh combobox + tableau
            refresh();

            //NOTIFICATION
            trayIcon = new QSystemTrayIcon(this);
            trayIcon->setVisible(true);
            trayIcon->setIcon(this->style()->standardIcon(QStyle::SP_DesktopIcon));
            trayIcon->setToolTip("Supprimer" "\n"
                            "Supprimer avec sucées");
            trayIcon->showMessage("Supprimer","Supprimer avec sucées",QSystemTrayIcon::Critical,1500);
            trayIcon->show();

        }
        else
        {
            QMessageBox::critical(this, QObject::tr("Supprimer un PARKING"),
                        QObject::tr("Erreur !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }

    }
}

void EspaceAdmin::on_parking_recherche_cursorPositionChanged(int arg1, int arg2)
{
    ui->tableView_parking->setModel(tmpparking.afficherecherche(ui->parking_recherche->text()));

    QString test =ui->parking_recherche->text();

    if(test=="")
    {
        ui->tableView_parking->setModel(tmpparking.afficher());//refresh
    }

}

void EspaceAdmin::on_comboBox_Tri_currentIndexChanged(const QString &arg1)
{


    if(ui->comboBox_Tri->currentText()=="")
    {
        ui->tableView_parking->setModel(tmpparking.afficher());//refresh
    }
    else
    {
        ui->tableView_parking->setModel(tmpparking.triafficher(ui->comboBox_Tri->currentText()));
    }

}


// STATISTIQUE

void EspaceAdmin::statrefresh()
{
    QLabel *label = new QLabel("", this);

    QPieSeries *series=new QPieSeries();

    series->append("PARKING disponible :" ,tmpparking.dispo());
    series->append("PARKING ,on disponible :" ,tmpparking.nondispo());

    QPieSlice *slice1=series->slices().at(1);
    slice1->setExploded(true);

    QChart *chart =new QChart();
    chart->addSeries(series);
    chart->setTitle("statistiques");
    chart->setAnimationOptions(QChart::AllAnimations);

    QChartView *chartview=new QChartView(chart);
    chartview->setUpdatesEnabled(true);
    QGridLayout *mainLayout=new QGridLayout();
    mainLayout->addWidget(chartview,0,0);

    ui->statistiques->setLayout(mainLayout);
    ui->statistiques->layout()->update();


}



void EspaceAdmin::on_PDF_clicked()
{
    QString strStream;
               QTextStream out(&strStream);
               const int rowCount = ui->tableView_client->model()->rowCount();
               const int columnCount =ui->tableView_client->model()->columnCount();

               out <<  "<html>\n"
                       "<head>\n"
                       "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                       <<  QString("<title>%1</title>\n").arg("eleve")
                       <<  "</head>\n"
                       "<body bgcolor=#F4B8B8 link=#5000A0>\n"
                          // "<img src='C:/Users/ksemt/Desktop/final/icon/logo.webp' width='20' height='20'>\n"
                           "<img src='C:/Users/DeLL/Desktop/logooo.png' width='100' height='100'>\n"
                           "<h1> Liste des Client </h1>"
                            "<h1>  </h1>"

                           "<table border=1 cellspacing=0 cellpadding=2>\n";


               // headers
                   out << "<thead><tr bgcolor=#f0f0f0>";
                   for (int column = 0; column < columnCount; column++)
                       if (!ui->tableView_client->isColumnHidden(column))
                           out << QString("<th>%1</th>").arg(ui->tableView_client->model()->headerData(column, Qt::Horizontal).toString());
                   out << "</tr></thead>\n";
                   // data table
                      for (int row = 0; row < rowCount; row++) {
                          out << "<tr>";
                          for (int column = 0; column < columnCount; column++) {
                              if (!ui->tableView_client->isColumnHidden(column)) {
                                  QString data = ui->tableView_client->model()->data(ui->tableView_client->model()->index(row, column)).toString().simplified();
                                  out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                              }
                          }
                          out << "</tr>\n";
                      }
                      out <<  "</table>\n"
                          "</body>\n"
                          "</html>\n";

                      QTextDocument *document = new QTextDocument();
                      document->setHtml(strStream);

                      QPrinter printer;

                      QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
                      if (dialog->exec() == QDialog::Accepted) {
                          document->print(&printer);
                   }

}
