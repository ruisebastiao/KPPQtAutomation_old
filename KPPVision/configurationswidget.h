#ifndef CONFIGURATIONSWIDGET_H
#define CONFIGURATIONSWIDGET_H

#include <QWidget>
#include <QtGui>
#include <kpppushbutton.h>
#include "kppvision.h"
#include "swipegesturerecognizer.h"
#include "settings.h"
#include "kpphardware.h"
#include "qgraphicswidget.h"
#include "kppvisionlist.h"

using namespace Vision;
using namespace IDS;

namespace Ui {
class KPPVISIONSHARED_EXPORT ConfigurationsWidget;
}

class KPPVISIONSHARED_EXPORT ConfigurationsWidget : public QWidget
{
    Q_OBJECT
    Q_ENUMS(State)
public:
    enum State {
        Visible=0x00,
        Hiden=0x01
    };
    explicit ConfigurationsWidget(QWidget *parent = 0);
    ~ConfigurationsWidget();

    State state() const;
    void setState(const State &state);

    State ToogleState();
    KPPVision *getSelectedProject() const;

    void setSelectedProject(KPPVision *value);
    void setSelectedInspection(Inspection *SelectedInspection);
    void setSelectedRequest(Request *SelectedRequest);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);
private slots:
    void animationFinished();
    void on_bt_exit_clicked();

    void on_bt_select_clicked();

    void on_bt_save_settings_clicked();

    void CurrentIndexChanged(int);


    void IDSCameraStateChanged(IDSCamera::CameraState);
    void IDSCameraRunModeChaged(IDSCamera::CameraRunMode);
    void NewImageSlot(QPixmap newpixmap);


    void on_bt_addproj_clicked();
    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void on_bt_removeproj_clicked();


    void on_bt_snap_clicked();



    void on_bt_cont_capture_clicked();

    void on_bt_idscameras_refresh_clicked();

    void on_bt_initializecam_clicked();


    void on_check_morecameraoptions_stateChanged(int arg1);


    void on_bt_addreq_clicked();

    void on_bt_removereq_clicked();

    void on_bt_addinsp_clicked();

    void on_bt_removeinsp_clicked();



    void on_bt_addroi_clicked();

    void on_bt_removeroi_clicked();

public slots:


private:

    QGraphicsProxyWidget *Graphicswidget_image_holder;
    QWidget *widget_image_holder;
    IDSCamera *selectedcam;
    QGraphicsScene*  scene;
    QGraphicsPixmapItem *m_PixmapItem;
    QPropertyAnimation *animate;
    State m_state;
    QPoint offset;
    Ui::ConfigurationsWidget *ui;
    KPPVision *m_SelectedProject;
    Request *m_SelectedRequest;
    Inspection* m_SelectedInspection;
    ROI* m_SelectedROI;

    Request *SelectedRequest() const;


    void setSelectedROI(ROI *SelectedROI);
protected:
    void showEvent(QShowEvent *);

    // QObject interface
public:



};

#endif // CONFIGURATIONSWIDGET_H
