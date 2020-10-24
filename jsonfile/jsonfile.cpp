
#include "jsonfile.h"
#include <QFile>
#include <QDebug>
JsonFile::JsonFile(QString filepath):m_file(filepath)
{
    QFile file(filepath);
    file.open(QIODevice::Text|QIODevice::ReadOnly);
    QByteArray arr =  file.readAll();
    file.close();
    QJsonParseError parse;
    m_doc = QJsonDocument::fromJson(arr,&parse);
    if(parse.error != QJsonParseError::NoError){
        qDebug()<<"json parse err";
        return;
    }else{
        m_obj =  m_doc.object();
    }

}

QJsonValue JsonFile::value(QStringList keys){
    if(keys.empty())
    {
        qDebug()<<"value::keys.empty()";
        return QJsonValue();
    }
    QJsonObject obj = m_obj;
    int nums = keys.size();
    for(int i = 0;i<nums;i++){
        if(i == (nums-1)){
            if(obj.contains(keys[i])){
                return obj[keys[i]];
            }else{
                qDebug()<<"value::keys.empty()";
                return QJsonValue();
            }
        }
        if(obj.contains(keys[i])){
            if(obj[keys[i]].isObject()){
                obj = obj[keys[i]].toObject();

            }else{
                qDebug()<<"value:: one key is  not exist";
                return QJsonValue();
            }
        }else{
            qDebug()<<"value::keys.empty()";
             return QJsonValue();
        }
    }
    return  QJsonValue();

}

void JsonFile::setValue(QStringList keys, QJsonValue subvalue)
{
    if(keys.empty()){
        qDebug()<<"setValue::keys.empty()";
        return;
    }
    if(keys.size() == 1){
        m_obj[keys.last()] = subvalue;
        qDebug()<<"setValue::ok";
        return ;
    }else{
        QString lk = keys.last();
        QStringList list = keys;
        list.removeLast();
        QJsonValue val = this->value(list);
        QJsonObject obj;
        if(val.isNull()){
           obj[lk] = subvalue;
            qDebug()<<"setValue::one key is  not exist";
        }else{
            if(val.isObject()){
                obj = val.toObject();
                obj[lk] = subvalue;
            }else{
                qDebug()<<"setValue::one key is  not exist,replace the origin value";
                obj[lk] = subvalue;
            }

        }
        setValue(list,obj);
    }
}

void JsonFile::save()
{
    QFile file(m_file);
    file.open(QIODevice::Text|QIODevice::WriteOnly);
    m_doc.setObject(m_obj);
    file.write(m_doc.toJson());
    file.close();
    qDebug()<<"save file";

}


JsonFile::~JsonFile()
{
    save();

}
