#ifndef OPER_VIS_PLUGIN_H
#define OPER_VIS_PLUGIN_H

#include <qstring.h>
#include <qstringlist.h>
#include <qmap.h>
#include <qicon.h>
#include <QList>
#include <QPair>
#include <QObject>
#include <QVariant>
#include <stdlib.h>
#include <stdexcept>

using namespace std;

class OperVisExc : public exception {
    QString descr;

    public:
        explicit OperVisExc(const QString &descr);
        virtual const char *what(void);
        virtual ~OperVisExc(void) throw();
};

class oveInVal : public OperVisExc {
    public:
        explicit oveInVal(const QString &descr);
        virtual ~oveInVal(void) throw();
};

class oveNoDev : public OperVisExc {
    public:
        explicit oveNoDev(const QString &descr);
        virtual ~oveNoDev(void) throw();
};

class OVPlugin;
class PluginManager;
class OVPluginParam : public QObject {
	Q_OBJECT

	QString devName;
	QString compName;
	OVPlugin* host;

	void sendUpdated(QVariant value)
	{
		emit valueUpdated(value);
	}

	friend class OVPlugin;

	// yes, they're private
	// for use in OVPlugin only
	OVPluginParam() {}
	OVPluginParam(const OVPluginParam&) {}
	~OVPluginParam() {}
public:
	QString getDevName() const {return devName;}
	QString getCompName() const {return compName;}

public slots:
	void setValue(QVariant value);

signals:
	void valueUpdated(QVariant value);
};

/// Base class for all plugins
class OVPlugin {
	/// Plugin's generic name (as defined in the .fobd file)
	QString name;

	/// Name of the .so file
	QString fileName;

	/// Name of the instance of plugin (set on cfgedit when the plugin is created)
	QString instanceName;

	typedef QMap<QString, OVPluginParam*> ParamSubMap;
	QMap<QString, ParamSubMap> paramMap;

protected:
	QString makeFullName(const QString &devName, const QString &compName)
	{
		return devName + "::" + compName;
	}

	/// Set of icons. Normally it contains two icons: on and off
	QIcon icons;

	OVPluginParam* makeParam(const QString &devName, const QString &compName);
	void sendParam(OVPluginParam* param, QVariant value);

public:
	OVPlugin()
	{}

	void setFileName(const QString &newFileName)
	{
		fileName = newFileName;
	}

	const QString &getFileName(void) const
	{
		return fileName;
	}

	void setName(const QString &newName)
	{
		// FIXME: add simple format tests:
		// - no spaces
		// - no double-dots
		name = newName;
	}

	const QString &getName(void) const
	{
		return name;
	}

	void setInstanceName(const QString &newName)
	{
		// FIXME: add simple format tests:
		// - no spaces
		// - no double-dots
		instanceName = newName;
	}

	const QString &getInstanceName(void) const
	{
		return instanceName;
	}

	virtual QWidget* getMainWidget()
	{
		return NULL;
	}

	/// Reimplement the following two functions if you need to save
	/// additional data about this plugin in config files.
    virtual void setSettings(QString s) {}
	virtual QString getSettings(void) { return QString(""); }

	/// Sets the tooltip
    virtual void setTooltip(const QString& s) {}

	virtual QIcon getIcons(void)
	{
		return this->icons;
	}

	virtual bool start() = 0;
	virtual void stop() = 0;
	virtual void updateValue(OVPluginParam* param, QVariant newValue) = 0;

	virtual OVPluginParam* getParam(const QString &devName, const QString &compName);

	virtual ~OVPlugin()
	{
		foreach(const ParamSubMap& subMap, paramMap)
			foreach(OVPluginParam* param, subMap)
				delete param;
	}
};

/// Base class for user-frame plugins
class UserFrameOVPlugin: public OVPlugin {
	enum DataType {
		dt_int8,
		dt_uint8,
		dt_int16,
		dt_uint16,
		dt_int32,
		dt_uint32,
		dt_int64,
		dt_uint64,
		dt_float,
		dt_double,
		dt_bool,
		dt_unknown
	};

	friend class PluginManager;

public:
	UserFrameOVPlugin();
	virtual ~UserFrameOVPlugin();

	virtual void updateValue(OVPluginParam* param, QVariant newValue);
	virtual bool start() = 0;
	virtual void stop() = 0;
	virtual QWidget* getMainWidget() = 0;
	virtual void setTooltip(const QString& s) = 0;

	void makeScreenShot(QString absoluteFileName);

protected:
	struct ParamInfo {
		DataType type;
		void *ptr;
	};
	void addParam(QString devName, QString compName, void *ptr);

private:
	QMap<QString, OVPluginParam*> mParams;
	QMap<QString, ParamInfo> mParamsInfo;
};

/*! Интерфейс для изменения значения параметров.
 * Используется для интеграции устройств ввода.
 */
class IProperty: public QObject {
	Q_OBJECT
signals:
	void valueUpdated(QVariant);
public:
	void sendValue(QVariant value)
	{
		emit valueUpdated(value);
	}
	virtual ~IProperty() {}
};

extern OVPlugin* makePlugin(const QString &fileName, PluginManager &man);
extern void killPlugin(OVPlugin &plugin);

#define OVP_INITIALIZE(class_name)\
extern "C" void *initialize(void)\
{\
	return (void*)(new class_name());\
}

#define OVP_FINALIZE(class_name)\
extern "C" void finalize(void *obj)\
{\
	if (!obj)\
		return;\
	class_name *p = static_cast<class_name *>(obj);\
	if (!p)\
		return;\
	delete p;\
}

#define OVP(class_name)\
	OVP_INITIALIZE(class_name)\
	OVP_FINALIZE(class_name)

#endif /* OPER_VIS_PLUGIN_H */
