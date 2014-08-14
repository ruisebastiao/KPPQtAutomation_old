#ifndef VISIONWINDOW_H
#define VISIONWINDOW_H

#include "kppvision_global.h"
#include <QFrame>
#include "kppvision.h"
#include "configurationswidget.h"

namespace Ui {
class KPPVISIONSHARED_EXPORT VisionWindow;
}

class KPPVISIONSHARED_EXPORT VisionWindow : public QFrame
{
    Q_OBJECT

public:
    explicit VisionWindow(QWidget *parent = 0);
    ~VisionWindow();
    void toogleSideMenu();

private slots:
    void VisionTreeListSelectionChanged(QObject *newselection);
    void InspectionInserted(QModelIndex index, int start, int end);


    void on_bt_toogleSideMenu_clicked(bool checked);

private:
    Ui::VisionWindow *ui;

    ConfigurationsWidget *configs;
    KPPVision *vision;
};

#endif // VISIONWINDOW_H
