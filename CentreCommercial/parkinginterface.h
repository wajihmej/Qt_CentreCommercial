#ifndef PARKINGINTERFACE_H
#define PARKINGINTERFACE_H

#include <QMainWindow>
#include "parking.h"

namespace Ui {
class ParkingInterface;
}

class ParkingInterface : public QMainWindow
{
    Q_OBJECT

public:
    explicit ParkingInterface(QWidget *parent = nullptr);
    ~ParkingInterface();

private slots:

    void on_deconnexion_clicked();

private:
    Ui::ParkingInterface *ui;
    Parking tmpparking;
};

#endif // PARKINGINTERFACE_H
