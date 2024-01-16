#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFont>
#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QTimer>
#include <QMenu>
#include <QAction>
#include <QStyle>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initLabel();
    void test();
    void playSystemAlertSound();

public slots:
    void countDown();
    // 显示通知的槽函数
    void showNotification();
    void initTrayMenu();

private:
    Ui::MainWindow *ui;
    // 设置倒计时的初始值（25分钟）
    int remainingTime;
    int minutes;
    int seconds;
    QString displayText;
    QFont font;
    QTimer *timer;
    QSystemTrayIcon *trayIcon;
    QMenu *trayMenu;
};
#endif // MAINWINDOW_H
