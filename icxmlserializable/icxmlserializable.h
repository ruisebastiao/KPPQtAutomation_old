#ifndef ICXMLSERIALIZABLE_H
#define ICXMLSERIALIZABLE_H

#include "icxmlserializable_global.h"
#include "QAbstractListModel"
#include "QtCore"
#include "QtXml"


class ICXMLSERIALIZABLESHARED_EXPORT icXmlSerializable: public QAbstractListModel
{
    Q_OBJECT
  public:
      icXmlSerializable(QObject *parent = 0, QString RootId="");
      virtual ~icXmlSerializable();

      QString                     serializeMetaComponent(const QString& metaComponentName);
      bool                        deserializeMetaComponent(const QString& metaComponentName);

      void                        setMetaContent(const QString& theValue);
      QString                     metaContent() const;
      QString                     metaComponent();

      QVariant			 getSerialProperty(const QString& propertyName);
      QString			 getStringProperty(const QString& propertyName);
      bool                        getSerialObject(const QString& objectName, icXmlSerializable *object);
      bool			 getSerialObject(const QString& objectName, icXmlSerializable *object, int index);
      int				 getSerialObjectCount(const QString& objectName);
      QHash< QString, QString >   serialObjects() const;
      QHash< QString, QString >   serialProperties() const;
      void 			 setMetaID(const QString& theValue);
      QString 			 metaID() const;

      void 			 setSerialId(const QString&	theValue);
      QString			 serialId() const;

      QString			 encode(const QString content);
      QString			 decode(const QString content);

      QString          getFilePath() const;
      void             setFilePath(const QString &FilePath);
      bool             Save(QString fileName);
      bool             Save();
      bool             Load();
      bool             Load(QString fileName);


      int rowCount(const QModelIndex &parent = QModelIndex()) const;
      QVariant data(const QModelIndex &index, int role) const;


signals:

      void Loaded(QObject *sender);

protected:


      virtual bool 		deserialize() = 0;
      virtual bool		serialize() = 0;
      void			setSerialProperty(const QString& property, int value);
      void			setSerialProperty(const QString& property, long value);
      void			setSerialProperty(const QString& property, bool value);
      void			setSerialProperty(const QString& property, const QString& value);
      void			setSerialProperty(const QString& property, float value);
      void			setSerialProperty(const QString& property, double value);
      void			setSerialProperty(const QString& property, QDateTime value);
      void			setSerialObject(const QString& property, icXmlSerializable	*);
      void			setSerialObject(const QString& property, QVector<icXmlSerializable	*> vector);
      //void			setSerialObject(const QString& property, QList<icXmlSerializable	*> list);
      void			setSerialObject(const QString& property, QHash<QString, icXmlSerializable	*> hash);
      template <class T>
      void setSerialObject(const QString & pProperty, QList< T* > list)
      {
          QString			buf;
          QString			dummy;
          icXmlSerializable	*item;
              QString                 property = fillSpaces(pProperty);
          int		index;

          buf = "<" + property + ">";
          for (index=0; index < list.size(); index++) {
              item = list.at(index);
              if (item != 0)
                  buf += item->serializeMetaComponent("it_" + property);
          }
          buf +=  "</" + property + ">";

          m_contentItems.append(buf);
      }
      void            setSerialObjecti(const QString &pProperty, icXmlSerializable *item);

  private:

      enum	META_TYPE {
          META_TYPE_OBJECT,
          META_TYPE_VECTOR,
          META_TYPE_LIST,
          META_TYPE_HASH
      };

      static	QString		META_TAG_PREFIX()	{ return "meta_";};			//meta_
      static	QString		META_TAG_KEY()		{ return "meta_key";};		//meta_key
      static	QString		META_TAG_INDEX() 	{ return "meta_index";};	//meta_index
      static	QString		META_TAG_SIZE() 	{ return "meta_size";};		//meta_size
      static	QString		META_TAG_TYPE() 	{ return "meta_type";};		//meta_type
      static	QString		META_TAG_OBJECT() 	{ return "object";};
      static	QString		META_TAG_VECTOR() 	{ return "vector";};
      static	QString		META_TAG_LIST() 	{ return "list";};
      static	QString		META_TAG_HASH() 	{ return "hash";};

      void				addBuffer(const 	QString& buffer);
      QString				buffer();
      QStringList				extractSegments(const QString& content);

      QString                            fillSpaces(const QString& value);
      QString				m_content;
      QString				m_component;
      QStringList				m_properties;
      QStringList				m_contentItems;
      QStringList				m_subItems;
      QHash<QString, QString>		m_elements;
      QHash<QString, QString>		m_serialObjects;
      QHash<QString, QString>		m_serialProperties;
      QString				m_metaID;
      QString				m_serialId;
      QString             m_FilePath;
      QString             m_RootId;
  };


#endif // ICXMLSERIALIZABLE_H
