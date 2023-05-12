#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <Windows.h>
#include <QPixmap>
#include <QProcess>
#include <QScreen>




QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_button_A_clicked();
    void on_button_B_clicked();
    void updateGenshinScreen();



private:
    Ui::MainWindow *ui;
    QTimer *timer;
    HWND genshinHWND;
};
#endif // MAINWINDOW_H
