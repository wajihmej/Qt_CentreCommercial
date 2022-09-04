#include "parkinginterface.h"
#include "ui_parkinginterface.h"
#include "mainwindow.h"

ParkingInterface::ParkingInterface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ParkingInterface)
{
    ui->setupUi(this);
    setWindowTitle("Parking");
    //Column size
    ui->TableParking->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //remplir tableau
    ui->TableParking->setModel(tmpparking.afficher());

}

ParkingInterface::~ParkingInterface()
{
    delete ui;
}


void ParkingInterface::on_deconnexion_clicked()
{
    ParkingInterface::close();
    MainWindow *m = new MainWindow();
    m->show();

}
