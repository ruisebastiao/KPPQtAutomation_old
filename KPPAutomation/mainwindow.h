#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "kppvision.h"
#include "configurationswidget.h"
#include "QToolButton"





using namespace Vision;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void ActionButtonClicked(QToolButton *buttonClicked);
    void bt_Cliked();


    void on_treeWidget_clicked(const QModelIndex &index);

    void LoadDone(QObject *Sender);
    void VisionTreeListSelectionChanged(QObject *);

    void InspectionInserted(QModelIndex,int,int);

    void on_pushButton_clicked();

public slots:
    void focusChanged(QWidget* old, QWidget* now);
protected:
    void mousePressEvent(QMouseEvent *event);
private:
    Ui::MainWindow *ui;
    ConfigurationsWidget *configs;
    KPPVision *vision;
    bool FirstRun;
    //IDSCamera *camera;

    void SetupSideMenu();
    bool IsLineEdit(const QWidget *widget);
};

#endif // MAINWINDOW_H
