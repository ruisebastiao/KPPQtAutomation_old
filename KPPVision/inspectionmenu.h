#ifndef INSPECTIONMENU_H
#define INSPECTIONMENU_H

#include <QFrame>
#include "kppanimatedframe.h"

#include "inspection.h"

namespace Ui {
class InspectionMenu;
}

class InspectionMenu : public KPPAnimatedFrame
{
    Q_OBJECT

public:
    explicit InspectionMenu(QWidget *parent = 0);
    ~InspectionMenu();

    Vision::Inspection *SelectedInspection();
    void setSelectedInspection(Vision::Inspection *SelectedInspection);
private slots:
    void on_pushButton_clicked();

private:
    Ui::InspectionMenu *ui;
    Vision::Inspection* m_SelectedInspection;
};

#endif // INSPECTIONMENU_H
