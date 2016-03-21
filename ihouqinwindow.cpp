#include "ihouqinwindow.h"
#include <windows.h>

IHouQinWindow::IHouQinWindow()
{
    createAction();
    createMenu();
    statusBar();
    QObject::connect(this,&IHouQinWindow::sigARWComplete,
            this,&IHouQinWindow::sltOpenCSV);
    QObject::connect(this,&IHouQinWindow::sigOpenCSVWithName,
            this,&IHouQinWindow::sltOpenCSVWithName);
}

void IHouQinWindow::createAction()
{
    pactAccRatio = new QAction(tr("&AccRatio"),this);
    pactOpenCSV = new QAction(tr("&OpenCSV"),this);
    pactAbout = new QAction(tr("&About"),this);
    pactAboutQt = new QAction(tr("About &Qt"),this);

    pactAccRatio->setStatusTip(tr("Open CSV & Do AccRatio"));
    pactOpenCSV->setStatusTip(tr("Open a CSV file.."));
    pactAbout->setStatusTip(tr("About this Product"));
    pactAboutQt->setStatusTip(tr("Show Qt Information"));

    pactOpenCSV->setShortcut(QKeySequence::Open);

    connect(pactAccRatio,&QAction::triggered,
            this,&IHouQinWindow::sltAccRatio);
    connect(pactOpenCSV,&QAction::triggered,this,
            &IHouQinWindow::sltOpenCSVDrt);
    connect(pactAbout,&QAction::triggered,this,
            &IHouQinWindow::sltAbout);
    connect(pactAboutQt,&QAction::triggered,
            &QApplication::aboutQt);
}

void IHouQinWindow::createMenu()
{
    pmenu = menuBar();
    pmenuFile = pmenu->addMenu(tr("&File"));
    pmenuProc = pmenu->addMenu(tr("&Proc")); 
    pmenuHelp = pmenu->addMenu(tr("&Help"));

    pmenuFile->addAction(pactOpenCSV);
    pmenuProc->addAction(pactAccRatio);
    pmenuHelp->addAction(pactAbout);
    pmenuHelp->addAction(pactAboutQt);
}

void IHouQinWindow::sltAbout()
{
    QMessageBox *msgbox = new QMessageBox(this);
    msgbox->setText(tr("This product is used inside sto.\n\
Any distrubution outside sto will be condamned."));
    msgbox->addButton(QMessageBox::Ok);
    msgbox->setWindowTitle(tr("About"));
    msgbox->setIcon(QMessageBox::Information);
    msgbox->exec();
}

void IHouQinWindow::sltAccRatio()
{
    QString qszfileName = QFileDialog::getOpenFileName(
            this,
            tr("Open..."),
            tr(""),
            tr("CSV File (*.csv)")
            );
    HINSTANCE DLLinst = NULL;
    DLLinst = LoadLibrary(L"accratiodll.dll");

    if(!DLLinst)
        exit(1);
    
    DLLAR AR;
    AR = (DLLAR)GetProcAddress(DLLinst,"AR");
    if(!AR)
        exit(2);
    string str = qszfileName.toStdString();

    int nRtn = AR(str);
    if(nRtn == 1)
    {
        QMessageBox *msg = new QMessageBox(this);
        msg->setText(tr("\
The file chosen cannot be fetched, please put the\n\
file under pure ENGLISH address and try again."));
        msg->setWindowTitle(tr("File Path Error"));
        msg->setIcon(QMessageBox::Warning);
        msg->addButton(QMessageBox::Ok);
        msg->exec();
    }
    else if(nRtn == 2)
    {
        QMessageBox *msg = new QMessageBox(this);
        msg->setText(tr("\
Cannot find last day's record in .\\arbackup.\n\
Please be aware that you should generate\n\
every day's record day by day since 2016Y3M1D."));
        msg->setWindowTitle(tr("File Missing"));
        msg->setIcon(QMessageBox::Warning);
        msg->addButton(QMessageBox::Ok);
        msg->exec();
    }
    else if(nRtn == 3)
    {
//        QMessageBox *msg = new QMessageBox(this);
//        msg->setText(tr("\
//You do not select any file. Please try again.  "));
//        msg->setWindowTitle(tr("Attention"));
//        msg->setIcon(QMessageBox::Warning);
//        msg->addButton(QMessageBox::Ok);
//        msg->exec();
    }
    else
        emit sigARWComplete(nRtn);//represents date.
}

void IHouQinWindow::sltOpenCSVWithName(QString qszfileName)
{
    QFile file(qszfileName);
    if(qszfileName.isNull())
        return ;
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        return ;
    }
    QTextStream in(&file);
    QString qszTemp;
    int m_nRow = 0;
    do
    {
        qszTemp = in.readLine();
        m_nRow ++;
    }while(!qszTemp.isNull());
    in.seek(0);

    QString qszfileLine = in.readLine();
    pstrlistChart = new QStringList;
    *pstrlistChart = qszfileLine.split(",");
    m_nColumn = pstrlistChart->size();
    
    label = new QLabel*[m_nRow * m_nColumn];
    int nColumn = 0;
    int nMark = 0;
    if(m_nColumn==0)
        return;
    else if(m_nColumn==1) nColumn = m_nColumn;
    else 
    {
        nColumn = m_nColumn - 1;
        nMark = 1;
        pqpbNewWindow = new QPushButton*[m_nRow];
    }
    int nRow = 0;
    pqgLayout = new QGridLayout(this);
    qmpButtonIDX = new QMap<QObject*,int>;
    pstrlistDetail = new QStringList;
    pstrlistName = new QStringList;
    while(!qszfileLine.isNull())
    {
        for(int i = 0; i < nColumn; i ++)
        {
            label[nRow*m_nColumn + i] = new QLabel(
                    pstrlistChart->at(i),
                    this,
                    Qt::Window
                    );
            pqgLayout->addWidget(
                    label[nRow*m_nColumn + i],
                    nRow,
                    i,
                    Qt::AlignHCenter|Qt::AlignVCenter
                    );
        }
        if(nMark&&nRow>0)//add Pushbutton
        {
            (*pstrlistDetail)<<(const QString)(pstrlistChart->at(m_nColumn-1));
            (*pstrlistName)<<(const QString)(pstrlistChart->at(0));
            pqpbNewWindow[nRow] = new QPushButton(tr("See More"),this);
            qmpButtonIDX->insert(pqpbNewWindow[nRow],nRow);
            connect(pqpbNewWindow[nRow],&QPushButton::clicked,
                    this,&IHouQinWindow::sltOpenNewWindowID);
            pqgLayout->addWidget(
                    pqpbNewWindow[nRow],
                    nRow,
                    nColumn,
                    Qt::AlignHCenter|Qt::AlignVCenter
                    );
        }
        qszfileLine.clear();
        qszfileLine = in.readLine();
        *pstrlistChart = qszfileLine.split(",");
//        if(pstrlistChart->size()!=m_nColumn)
//        { 
//            exit(pstrlistChart->size());
//            exit(m_nColumn);
//            QMessageBox *msg = new QMessageBox(this);
//            msg->setText(tr("\
//You are opening a CSV file which is not supported\n\
//to display in ihouqin.exe. Please select CSV file from\n\
//\\arbackup\\or\\arresult\\."));
//            msg->setWindowTitle(tr("Undefined File Type"));
//            msg->setIcon(QMessageBox::Warning);
//            msg->addButton(QMessageBox::Ok);
//            msg->exec();
//            return ;
//        }
        nRow ++;
    }
    QDialog *dlg = new QDialog(this);
    delete dlg->layout();
    dlg->setLayout(pqgLayout);
    pscrollArea = new QScrollArea(this);
    pscrollArea->setWidget(dlg);
    pscrollArea->setBackgroundRole(QPalette::Base);
    setCentralWidget(pscrollArea);
    resize(dlg->size()+=QTCONST::EXSIZE);
}

void IHouQinWindow::sltOpenNewWindowID()
{
    QObject* nSender = sender();
    int nRow = qmpButtonIDX->value(nSender);
    pstrlistSplit = new QStringList;
    *pstrlistSplit = (pstrlistDetail->at(nRow-1)).split(";");
    int nSize = pstrlistSplit->size()-1;
    if(!nSize)//no elements
        return;
    id = new QLabel*[nSize];
    qvbLayoutID = new QVBoxLayout(this);
    for(int i = 0; i< nSize; i++)
    {
        id[i] = new QLabel(this);
        id[i]->setText(pstrlistSplit->at(i));
        qvbLayoutID->addWidget(id[i]);
    }
    QDialog *dlg = new QDialog(this);
    dlg->resize(150,0);
    dlg->setWindowTitle(pstrlistName->at(nRow - 1));
    dlg->setLayout(qvbLayoutID);
    dlg->show();
}

void IHouQinWindow::sltOpenCSV(int nDate)
    //nDate used to generate fileName of *b.csv
{
    HINSTANCE DLLinst = NULL;
    DLLinst = LoadLibrary(L"accratiodll.dll");
    if(!DLLinst)
        exit(1);

    DLLTFILE_NAME_GEN dlltfng = (DLLTFILE_NAME_GEN)
        GetProcAddress(DLLinst,"TFILE_NAME_GEN");
    if(!dlltfng)
        exit(2);
    QString qszfileName("arresult/");
    qszfileName.append(dlltfng(nDate).c_str());
    
    emit sigOpenCSVWithName(qszfileName);
}

void IHouQinWindow::sltOpenCSVDrt()
{
    QString qszfileName = QFileDialog::getOpenFileName(
            this,
            tr("Open CSV file"),
            tr(""),
            tr("CSV File(*.csv)")
            );
    emit sigOpenCSVWithName(qszfileName);
}
