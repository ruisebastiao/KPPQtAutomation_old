#ifndef KPPADJUSTABLELISTVIEW_H
#define KPPADJUSTABLELISTVIEW_H

#include "kppcommon_global.h"
#include <QWidget>
#include <QListView>
#include "qstyleditemdelegate.h"
#include "kppeditbox.h"
#include "qeasingcurve.h"
#include "QSwipeGesture"

class KPPCOMMONSHARED_EXPORT QAdjustableListItemDelegate : public QStyledItemDelegate
{
public:
     QAdjustableListItemDelegate(QObject* parent = 0)
         : QStyledItemDelegate(parent)
     {


     }

     QSize sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const
     {

         //return QStyledItemDelegate::sizeHint(option,index);

         QSize s;
            s = QSize(option.decorationSize.width(), option.decorationSize.height());
            //if(currentIndex == index.row())
            //{
                s.setHeight(50);
                //s.setHeight(150);
            //}
            return s;
     }
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const{
        KPPEditBox *editor = new KPPEditBox(parent);
        QString txt=index.data().toString();
        //editor->setText(txt);
//             editor->setMinimum(0);

//             editor->setMaximum(100);

             return editor;
    }

     // QAbstractItemDelegate interface
    void setEditorData(QWidget *editor,
                                         const QModelIndex &index) const
    {
        QString value = index.data().toString();

        QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
        lineEdit->setText(value);
    }

};

class KPPCOMMONSHARED_EXPORT KPPAdjustableListView : public QListView

{
    Q_OBJECT    
public:
    explicit KPPAdjustableListView(QWidget *parent = 0);
    void setModel(QAbstractItemModel *model);
    QSize sizeHint() const;
    void AdjustContents(int finalValue=-1, QEasingCurve animStyle=QEasingCurve::OutBack);

private:


    bool gestureEvent(QGestureEvent *event);
    void swipeTriggered(QSwipeGesture *gesture);
signals:
    void selectionChangedSignal(const QItemSelection &selected, const QItemSelection &deselected);
    void SwipedLeft();
    void SwipedRight();
protected:



    //void show();



    void rowsInserted(const QModelIndex &parent, int start, int end);

    void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles);

    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);

    //void ro

private slots:
    void rowsRemoved(const QModelIndex &parent, int first, int last);
    void AnimationFinished();
public slots:


    // QAbstractItemView interface
public:
    //bool event(QEvent *event);
    int sizeHintForRow(int row) const;

    // QObject interface
public:
    bool event(QEvent *);
    void setGrabEnable(bool enable);
};

#endif // KPPADJUSTABLELISTVIEW_H
