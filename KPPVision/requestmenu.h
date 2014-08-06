#ifndef REQUESTMENU_H
#define REQUESTMENU_H


#include <QFrame>
#include "kppanimatedframe.h"
#include "kppvision.h"
#include "request.h"
#include "qframe.h"

namespace Ui {
class RequestMenu;
}

class RequestMenu : public KPPAnimatedFrame
{
    Q_OBJECT

public:
    explicit RequestMenu(QWidget *parent = 0);
    ~RequestMenu();

    Vision::Request *SelectedRequest();
    void setSelectedRequest(Vision::Request *SelectedRequest);


private slots:
    void on_bt_processrequest_clicked();

private:
    Ui::RequestMenu *ui;
    Vision::Request *m_SelectedRequest;
};

#endif // REQUESTMENU_H
