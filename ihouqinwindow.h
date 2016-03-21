#define _VAR_ 
#define _FUNC_
#define _WINDOW_
#include <QtWidgets/QtWidgets>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include <QTextCodec>
#include "pushbutton.h"
using namespace std;

typedef int (*DLLAR)(string);
typedef string (*DLLTFILE_NAME_GEN)(int);

namespace QTCONST
{
    const QSize EXSIZE = QSize(25,40);
}

class IHouQinWindow : public QMainWindow
{
    Q_OBJECT
public:
    IHouQinWindow();
public slots:
    void sltAccRatio();
    void sltAbout();
    void sltOpenCSV(int);
    void sltOpenCSVDrt();
    void sltOpenCSVWithName(QString);
    void sltOpenNewWindowID();
signals:
    void sigARWComplete(int);
    void sigOpenCSVWithName(QString);

private _FUNC_:
    void createAction();
    void createMenu();

private _WINDOW_:
    QMenuBar *pmenu;
    QMenu *pmenuFile;
    QMenu *pmenuProc;
    QMenu *pmenuHelp;
    QAction *pactAccRatio;
    QAction *pactOpenCSV;
    QAction *pactAbout;
    QAction *pactAboutQt;
    QPushButton **pqpbNewWindow;
    QScrollArea *pscrollArea;
    //QScrollArea *pscrollAreaID;
    QGridLayout *pqgLayout;
    QVBoxLayout *qvbLayoutID;
    QLabel **label;
    QLabel **id;
    QStringList *pstrlistChart;
    QStringList *pstrlistName;
    QStringList *pstrlistDetail;
    QStringList *pstrlistSplit;

private:
    int m_nRow;
    int m_nColumn;
    QMap<QObject*,int> *qmpButtonIDX;
};
