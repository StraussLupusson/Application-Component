#include <QCoreApplication>

#include "jsonfile.h"
#include <QDebug>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    JsonFile *file = new JsonFile("/home/wwl/config.json");
    qDebug()<<file->value({"p1","pp1","ppp1","pppp1","ppppp1"});
    //file->setValue({"p1","pp2","ppp1","pppp1","ppppp1"},false);
    qDebug()<<""<<file->value({"p1","pp2"});
    delete file;
    return a.exec();
}
