#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <opencv2/opencv.hpp>
#include <QInputDialog>
#include<algorithm>
using namespace cv;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

double brightness(double r, double g, double b){
    double y = 0.2126*r + 0.7152*g + 0.0722 * b;
    return y;
}



void MainWindow::on_menuBt_clicked()
{
    fileName = QFileDialog::getOpenFileName(this, "Выбрать изображение", "\\", "Выбрать изображения (*.jpeg *.jpg *.gif *.tif *.bmp *.png *.pcx)");
    qDebug() << fileName;
    QImage img(fileName);
    QPixmap dd = QPixmap::fromImage(img);
    img2 = imread(fileName.toStdString(), 1);
}


void MainWindow::on_pushButton_clicked()
{
    const char *initialWinName = "Initial Image",
        *equalizedWinName = "Equalized Image";
      // загрузка изображения
      // преобразование в оттенки серого
      cvtColor(img2, grayImg, COLOR_RGB2GRAY);
      // выравнивание гистограммы
      equalizeHist(grayImg, equalizedImg);

      // отображение исходного изображения и гистограмм
      namedWindow("first", WINDOW_AUTOSIZE);
      imshow("first", img2);
      namedWindow(equalizedWinName, WINDOW_AUTOSIZE);
      imshow(equalizedWinName, equalizedImg);
      waitKey();
      // закрытие окон
      destroyAllWindows();
      // осовобождение памяти
}


void MainWindow::on_elementBt_clicked()
{
    bool ok;
        QString oper = QInputDialog::getText(this, "", "enter + or * or neg or sqr or sqrt", QLineEdit::Normal, "", &ok);
   if(ok){
       bool ok2 = false;
       QString add;
       while(!ok2 && (oper == "+" || oper == "*")){
           add = QInputDialog::getText(this, "", "enter number", QLineEdit::Normal, "", &ok2);
       }
       Mat newImg = img2.clone();
       qDebug() << add.toInt();
       if(oper == "+"){
           for (int i = 0; i < newImg.rows; i++)
               for (int j = 0; j < newImg.cols; j++){
                   newImg.at<Vec3b>(i, j)[0]+= add.toInt();
                   newImg.at<Vec3b>(i, j)[1]+= add.toInt();
                   newImg.at<Vec3b>(i, j)[2]+= add.toInt();
               }
       }
       if(oper == "*"){
           for (int i = 0; i < newImg.rows; i++)
               for (int j = 0; j < newImg.cols; j++){
                   newImg.at<Vec3b>(i, j)[0]*= add.toInt();
                   newImg.at<Vec3b>(i, j)[1]*= add.toInt();
                   newImg.at<Vec3b>(i, j)[2]*= add.toInt();
               }
       }
       if(oper == "sqrt"){
           int rm = 0, gm = 0, bm = 0;
           for (int i = 0; i < newImg.rows; i++)
               for (int j = 0; j < newImg.cols; j++){
                   rm = std::max(rm, (int)newImg.at<Vec3b>(i, j)[0]);
                   gm = std::max(gm, (int)newImg.at<Vec3b>(i, j)[1]);
                   bm = std::max(bm, (int)newImg.at<Vec3b>(i, j)[3]);
               }
           for (int i = 0; i < newImg.rows; i++)
               for (int j = 0; j < newImg.cols; j++){
                   newImg.at<Vec3b>(i, j)[0] =sqrt(newImg.at<Vec3b>(i, j)[0]*1.0/(rm*1.0))*255.0;
                   newImg.at<Vec3b>(i, j)[1] = sqrt(newImg.at<Vec3b>(i, j)[0]*1.0/(rm*1.0))*255.0;
                   newImg.at<Vec3b>(i, j)[2] = sqrt(newImg.at<Vec3b>(i, j)[0]*1.0/(rm*1.0))*255.0;
               }
            cvtColor(newImg, newImg, COLOR_RGB2GRAY);
       }
       if(oper == "sqr"){
           int rm = 0, gm = 0, bm = 0;
           for (int i = 0; i < newImg.rows; i++)
               for (int j = 0; j < newImg.cols; j++){
                   rm = std::max(rm, (int)newImg.at<Vec3b>(i, j)[0]);
                   gm = std::max(gm, (int)newImg.at<Vec3b>(i, j)[1]);
                   bm = std::max(bm, (int)newImg.at<Vec3b>(i, j)[3]);
               }
           for (int i = 0; i < newImg.rows; i++)
               for (int j = 0; j < newImg.cols; j++){
                   newImg.at<Vec3b>(i, j)[0] = (newImg.at<Vec3b>(i, j)[0]*1.0/(rm*1.0))*(newImg.at<Vec3b>(i, j)[0]*1.0/(rm*1.0))*255.0;
                   newImg.at<Vec3b>(i, j)[1] = (newImg.at<Vec3b>(i, j)[1]*1.0/(gm*1.0))*(newImg.at<Vec3b>(i, j)[1]*1.0/(gm*1.0))*255.0;
                   newImg.at<Vec3b>(i, j)[2] = (newImg.at<Vec3b>(i, j)[2]*1.0/(bm*1.0))*(newImg.at<Vec3b>(i, j)[2]*1.0/(bm*1.0))*255.0;
               }
           cvtColor(newImg, newImg, COLOR_RGB2GRAY);
       }
       if(oper == "neg"){
           for (int i = 0; i < newImg.rows; i++)
               for (int j = 0; j < newImg.cols; j++){
                   newImg.at<Vec3b>(i, j)[0] = 255-newImg.at<Vec3b>(i, j)[0];
                   newImg.at<Vec3b>(i, j)[1] = 255-newImg.at<Vec3b>(i, j)[1];
                   newImg.at<Vec3b>(i, j)[2] = 255-newImg.at<Vec3b>(i, j)[2];

               }
       }
       namedWindow("first", WINDOW_AUTOSIZE);
       imshow("first", img2);
       namedWindow("added", WINDOW_AUTOSIZE);
       imshow("added", newImg);
       waitKey();

   }
}


void MainWindow::on_threshold1_clicked()
{
    Mat newImg = img2.clone();
    double t = 0.5;
    double lastT = 0;
    while(std::abs(t - lastT) > 0.00001){
        lastT = t;
        double mu1 = 0, mu2 = 0, k1 = 0, k2 = 0;
        for (int i = 0; i < newImg.rows; i++)
            for (int j = 0; j < newImg.cols; j++){
                double br = brightness(newImg.at<Vec3b>(i, j)[0], newImg.at<Vec3b>(i, j)[1], newImg.at<Vec3b>(i, j)[2]);
                if(br > t){
                    mu1 += br;
                    k1++;
                } else {
                    mu2 += br;
                    k2++;
                }
            }
        if(k1 > 0)mu1 /= k1;
        if(k2 > 0)mu2 /= k2;
        t = (mu1+ mu2)/2.0;
    }
    qDebug() << t;
    for (int i = 0; i < newImg.rows; i++)
        for (int j = 0; j < newImg.cols; j++){
             double br = brightness(newImg.at<Vec3b>(i, j)[0], newImg.at<Vec3b>(i, j)[1], newImg.at<Vec3b>(i, j)[2]);
             if(br >= t){
                 newImg.at<Vec3b>(i, j)[0] = 255;
                 newImg.at<Vec3b>(i, j)[1] = 255;
                 newImg.at<Vec3b>(i, j)[2] = 255;
             }
        }
    namedWindow("first", WINDOW_AUTOSIZE);
    imshow("first", img2);
    namedWindow("threasholded", WINDOW_AUTOSIZE);
    imshow("threasholded", newImg);
    waitKey();
}


void MainWindow::on_threshold2_clicked()
{
    Mat newImg = img2.clone();
    namedWindow("first", WINDOW_AUTOSIZE);
    imshow("first", newImg);
    cvtColor(newImg, newImg, COLOR_RGB2GRAY);
    threshold(newImg, newImg, 0,255, THRESH_OTSU);
    namedWindow("threasholded otsu", WINDOW_AUTOSIZE);
    imshow("threasholded otsu", newImg);
    waitKey();
}


void MainWindow::on_adaptive_clicked()
{
    Mat newImg = img2.clone();
    namedWindow("first", WINDOW_AUTOSIZE);
    imshow("first", newImg);
    cvtColor(newImg, newImg, COLOR_RGB2GRAY);
    adaptiveThreshold(newImg, newImg, 250, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 11, 12);
    namedWindow("threasholded adaptive", WINDOW_AUTOSIZE);
    imshow("threasholded adaptive", newImg);
    waitKey();

}

