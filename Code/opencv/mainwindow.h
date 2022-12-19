#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString fileName;
    cv::Mat img2;
    cv::Mat grayImg, equalizedImg;

private slots:
    void on_menuBt_clicked();
    void on_pushButton_clicked();

    void on_elementBt_clicked();

    void on_threshold1_clicked();

    void on_threshold2_clicked();

    void on_adaptive_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
