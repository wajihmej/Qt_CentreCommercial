#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "parkinginterface.h"
#include "espaceadmin.h"
#define EMAIL_RX "^[_a-zA-Z0-9-]+(\\.[_a-zA-Z0-9-]+)*@+([a-zA-Z-]{0,10}[\\.[a-zA-Z-]{2,4})*$"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Login");
    //init
    ui->mdp->setEchoMode(QLineEdit::Password);

    QRegExp rxmail(EMAIL_RX);
    QRegExpValidator *valiemail = new QRegExpValidator(rxmail,this);
    ui->email->setValidator(valiemail);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_inscription_clicked()
{
    QSqlQuery query;
    QString email = ui->email->text();
    QString mdp = ui->mdp->text();

    if(email!="" && mdp !="")
    {
        query =tmpclient.checkemail(email);
        if(query.exec())
        {
            if(query.next())
            {
                ui->msg->setText("Email existe déja.");

            }
            else
            {
                Client c(email,mdp);

                bool test = c.ajouter();
                if(test){
                    ui->msg->setText("");

                    QMessageBox::information(nullptr, QObject::tr("Inscription"),
                    QObject::tr("Client ajouté.\n" "Click Cancel to exit."), QMessageBox::Cancel);

                    }
                      else
                      {
                          QMessageBox::critical(nullptr, QObject::tr("Inscription"),
                                      QObject::tr("Erreur !.\n"
                                                  "Click Cancel to exit."), QMessageBox::Cancel);
                      }
            }
        }

    }
    else
    {
        ui->msg->setText("Verifier les champs.");
    }

}

void MainWindow::on_seconnecter_clicked()
{
    QSqlQuery query;

    QString email = ui->email->text();
    QString mdp = ui->mdp->text();

    if(email!="" && mdp !="")
    {
        if(email =="admin" && mdp == "admin")
        {
            MainWindow::close();
            EspaceAdmin *m = new EspaceAdmin();
            m->show();
        }
        else
        {

            query =tmpclient.login(email,mdp);
            if(query.exec())
            {
                if(query.next())
                {
                    MainWindow::close();
                    ParkingInterface *m = new ParkingInterface();
                    m->show();

                }
                else
                {
                    ui->msg->setText("Nom utilisateur ou mdp incorrect.");
                }
            }


        }
    }
    else
    {
        ui->msg->setText("Verifier les champs.");
    }

}
