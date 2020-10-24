#ifndef JSONFILE_H
#define JSONFILE_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonValue>
#include <QStringList>
class JsonFile
{
public:
    JsonFile(QString file);
    QJsonValue value(QStringList keys);//get key-value
    void setValue(QStringList keys,QJsonValue subvalue);//set key-value
    void save();//save file
    ~ JsonFile();

private:
    QJsonObject m_obj;
    QJsonDocument m_doc;
    QString m_file;

};

#endif // JSONFILE_H
