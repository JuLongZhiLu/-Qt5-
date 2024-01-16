#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSysInfo>
#include <QMediaPlayer>
#include <QUrl>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*设置label的各种属性*/
    initLabel();

    timer=new QTimer(this);

    connect(timer,&QTimer::timeout,this,&MainWindow::countDown);
    connect(ui->start,&QPushButton::clicked,[this](){
        qDebug()<<"启动";
        qDebug()<<remainingTime;
        timer->start(1000);
    });
    connect(ui->stop,&QPushButton::clicked,[this](){
        timer->stop();
    });
    connect(ui->pushButton,&QPushButton::clicked,[this](){
        test();
    });
    connect(ui->reset,&QPushButton::clicked,[this](){
        timer->stop();
        remainingTime = 25 * 60;
        minutes = remainingTime / 60;
        seconds = remainingTime % 60;
        displayText=QString("%1:%2").arg(minutes,2,10,QLatin1Char('0')).arg(seconds,2,10,QLatin1Char('0'));
        ui->label->setText(displayText);
    });

    initTrayMenu();


    /*设置窗口标题*/
    this->setWindowTitle("巨龙番茄钟");


}

// 显示通知的槽函数
void MainWindow::showNotification()
{
    // 在右下角弹出通知
    trayIcon->showMessage("提醒", "您的番茄钟已完成", QSystemTrayIcon::Information, 2000);
}

void MainWindow::initTrayMenu()
{
    // 创建系统托盘图标
    trayIcon = new QSystemTrayIcon(this->style()->standardIcon(static_cast<QStyle::StandardPixmap>(0)), this);

    // 创建托盘菜单
    trayMenu = new QMenu(this);

    // 添加一个动作到菜单，用于触发通知
    QAction *notifyAction = new QAction("Show Notification", this);
    connect(notifyAction, &QAction::triggered, this, &MainWindow::showNotification);
    trayMenu->addAction(notifyAction);

    // 设置托盘菜单
    trayIcon->setContextMenu(trayMenu);

    // 显示系统托盘图标
    trayIcon->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initLabel()
{
    remainingTime = 25 * 60;
    minutes = remainingTime / 60;
    seconds = remainingTime % 60;
    displayText=QString("%1:%2").arg(minutes,2,10,QLatin1Char('0')).arg(seconds,2,10,QLatin1Char('0'));
    ui->label->setText(displayText);

    /*设置label的字体*/
    font.setPointSize(80);
    ui->label->setFont(font);

    /*设置标签内容居中显示*/
    ui->label->setAlignment(Qt::AlignCenter);

}

void MainWindow::playSystemAlertSound()
{
    QMediaPlayer *player=new QMediaPlayer(this);

      // 设置系统提示音
      if (QSysInfo::productType() == "windows")
        player->setMedia(QUrl::fromLocalFile("C:/Windows/Media/Windows Logon.wav"));

      // 播放系统提示音
      player->setVolume(50); // 设置音量
      player->setPlaybackRate(1.0); // 设置播放速度
      player->play();
}

void MainWindow::countDown()
{
    qDebug()<<"countDnow";
    remainingTime--;
    minutes=remainingTime/60;
    seconds=remainingTime%60;
    displayText=QString("%1:%2").arg(minutes,2,10,QLatin1Char('0')).arg(seconds,2,10,QLatin1Char('0'));
    ui->label->setText(displayText);

    if(remainingTime==0)
    {
        timer->stop();
        playSystemAlertSound();
        showNotification();
    }
}

void MainWindow::test()
{
    remainingTime=3;
    minutes=remainingTime/60;
    seconds=remainingTime%60;
}

