#include <QtWidgets/QApplication>
#include "ihouqinwindow.h"

int main(int argc,char* argv[])
{
    QApplication ihqapp(argc,argv);
    QTranslator qtCHN;
    qtCHN.load("ihouqintr_chn.qm");
    ihqapp.installTranslator(&qtCHN);
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);
    IHouQinWindow ihqw;
    ihqw.setWindowTitle(QObject::tr("ihouqin"));
    ihqw.resize(800,600);
    ihqw.show();
    return ihqapp.exec();
}
