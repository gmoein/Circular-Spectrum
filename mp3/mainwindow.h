#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QDebug>
#include <QAudioDecoder>
#include <QAudioOutput>
#include <QBuffer>
#include <QFileDialog>
#include "fft.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    QAudioDecoder *decoder;
    QAudioOutput *ao;
    QByteArray byteArr;
    QBuffer ab;

public slots:
    void positionChanged(qint64);
    void readBuffer();
    void aonotify();
    void decfinished();
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_horizontalSlider_valueChanged(int value);
    void on_pushButton_4_clicked();
    void on_horizontalSlider_2_valueChanged(int value);
    void on_pushButton_5_clicked();
};

#endif // MAINWINDOW_H
