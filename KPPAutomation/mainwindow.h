#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "kppvision.h"
#include "configurationswidget.h"
#include "QToolButton"
#include "visionwindow.h"




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


    void LoadDone(QObject *Sender);


public slots:
    void focusChanged(QWidget* old, QWidget* now);
protected:
    void mousePressEvent(QMouseEvent *event);
private:
    Ui::MainWindow *ui;

    bool FirstRun;

    VisionWindow* visionmodule;

    void SetupSideMenu();
    bool IsLineEdit(const QWidget *widget);
};

#endif // MAINWINDOW_H
