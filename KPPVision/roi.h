#ifndef ROI_H
#define ROI_H

#include "kppvision_global.h"
#include <QObject>
#include "icxmlserializable.h"


namespace Vision
{
class KPPVISIONSHARED_EXPORT ROI : public icXmlSerializable
{
    Q_OBJECT
public:
    explicit ROI(QObject *parent = 0);
    ~ROI();

    ResizableItem *getROIrect() const;
    void setROIrect(ResizableItem *value);

    QString title() const;
    void setTitle(const QString &title);

private:
    virtual bool serialize();
    virtual bool deserialize();

    QString m_title;
    ResizableItem *m_ROIrect;
signals:

public slots:

};

    class KPPVISIONSHARED_EXPORT ROIList:public icXmlSerializable
    {
        Q_OBJECT
    public:
        explicit ROIList(QObject *parent = 0);

        QHash<QString, icXmlSerializable *> ROIs() const;


        ROI *getProject(const QString &name) const;
        ROI *getProjectAt(int pos) const;
    private:
        QHash<QString, icXmlSerializable *>   m_ROIs;
    protected:
        // icXmlSerializable interface
        bool deserialize();
        bool serialize();

        // QAbstractItemModel interface
    public:
        int rowCount(const QModelIndex &parent) const;
        QVariant data(const QModelIndex &index, int role) const;
        bool setData(const QModelIndex &index, const QVariant &value, int role);
        Qt::ItemFlags flags(const QModelIndex &index) const;

    };
}
#endif // ROI_H

