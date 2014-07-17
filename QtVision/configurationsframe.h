#ifndef CONFIGURATIONSFRAME_H
#define CONFIGURATIONSFRAME_H

#include <QFrame>

namespace Ui {
class ConfigurationsFrame;
}

class ConfigurationsFrame : public QFrame
{
    Q_OBJECT

public:
    explicit ConfigurationsFrame(QWidget *parent = 0);
    ~ConfigurationsFrame();

protected:
    void resizeEvent(QResizeEvent *event);
private:
    Ui::ConfigurationsFrame *ui;
};

#endif // CONFIGURATIONSFRAME_H
