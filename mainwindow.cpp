#include "mainwindow.h"
#include "./ui_mainwindow.h"









void pressF3() {
    QString autoHotkeyExecutablePath = "C:/Program Files/AutoHotkey/v2/AutoHotkey64.exe";
    QString scriptPath = QCoreApplication::applicationDirPath() +"/press_f3.ahk";

    // 开始AutoHotkey进程并运行脚本
    QProcess::startDetached(autoHotkeyExecutablePath, QStringList() << scriptPath);

}



QImage hbitmapToQImage(HBITMAP hbitmap, int w, int h)
{

    BITMAPINFOHEADER bi;
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = w;
    bi.biHeight = -h; // top-down
    bi.biPlanes = 1;
    bi.biBitCount = 32;
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;

    QImage image(w, h, QImage::Format_RGB32);
    HDC hdc = GetDC(NULL);
    GetDIBits(hdc, hbitmap, 0, h, image.bits(), (BITMAPINFO*)&bi, DIB_RGB_COLORS);
    ReleaseDC(NULL, hdc);

    return image;
}

QPixmap captureWindow(HWND hwnd) {
    HDC hdcWindow = GetWindowDC(hwnd);
    RECT windowRect;
    GetWindowRect(hwnd, &windowRect);

    // 获取边框和标题栏的大小
    RECT clientRect;
    GetClientRect(hwnd, &clientRect);
    AdjustWindowRect(&clientRect, GetWindowLong(hwnd, GWL_STYLE), FALSE);

    int borderWidth = (windowRect.right - windowRect.left - clientRect.right) / 2;
    int titleBarHeight = (windowRect.bottom - windowRect.top - clientRect.bottom) - borderWidth;

    int width = windowRect.right - windowRect.left - 2 * borderWidth;
    int height = windowRect.bottom - windowRect.top - titleBarHeight - borderWidth;

    HDC hdcMem = CreateCompatibleDC(hdcWindow);
    HBITMAP hbitmap = CreateCompatibleBitmap(hdcWindow, width, height);
    HGDIOBJ hOld = SelectObject(hdcMem, hbitmap);
    BitBlt(hdcMem, 0, 0, width, height, hdcWindow, borderWidth, titleBarHeight, SRCCOPY);
    SelectObject(hdcMem, hOld);

    QImage image = hbitmapToQImage(hbitmap, width, height);
    QPixmap pixmap = QPixmap::fromImage(image);

    DeleteObject(hbitmap);
    DeleteDC(hdcMem);
    ReleaseDC(hwnd, hdcWindow);

    return pixmap;
}



void simulateKeybord(WPARAM key, HWND hwnd){

   // pressF3();

    if(hwnd != NULL){
        qDebug()<<"F3";
        SetForegroundWindow(hwnd);
        pressF3();
    }


}



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->move((QGuiApplication::primaryScreen()->geometry().width() - this->width())/2, (QGuiApplication::primaryScreen()->geometry().height() - this->height())/2);

    //init genshinHWND

    LPCWSTR targetAppName = L"Genshin Impact";
    genshinHWND = FindWindow(NULL, targetAppName);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateGenshinScreen);
    timer->start(10); // 设置捕获画面的时间间隔，单位为毫秒







}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_button_A_clicked()
{
    qDebug()<<"wish";
    ui->stackedWidget->setCurrentIndex(0);

    simulateKeybord((WPARAM)VK_F3, genshinHWND);




}


void MainWindow::on_button_B_clicked()
{
    qDebug()<<"clicked button B";
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::updateGenshinScreen(){
    if(genshinHWND != NULL){
     //   ui->genshinScreen->setPixmap(captureWindow(genshinHWND));



    }
}

