#ifndef CRASHDIALOG_H
#define CRASHDIALOG_H
#include "kppcommon_global.h"
#include <QDialog>

namespace Ui {
class KPPCOMMONSHARED_EXPORT CrashDialog;
}

class KPPCOMMONSHARED_EXPORT CrashDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CrashDialog(QWidget *parent = 0);
    ~CrashDialog();

    void setMessage(QStringList msgs);
private:
    Ui::CrashDialog *ui;

    // QDialog interface
public slots:


    // QWidget interface
protected:
    void showEvent(QShowEvent *);
};

#endif // CRASHDIALOG_H
