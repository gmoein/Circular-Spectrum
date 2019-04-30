#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    decoder=new QAudioDecoder;
    connect(decoder, SIGNAL(bufferReady()), this, SLOT(readBuffer()));
    connect(decoder, SIGNAL(finished()), this, SLOT(decfinished()));

    ao=new QAudioOutput();
    ui->widget->addGraph();
    ui->widget->addGraph();
    ui->widget->graph(1)->setPen(QPen(Qt::red));
    ui->widget_2->addGraph();
    ui->widget_2->addGraph();
    ui->widget_2->graph(1)->setPen(QPen(Qt::red));
    setWindowTitle("Arak University of Technology, DSP Course, Circular Spectrum");
    setWindowIcon(QIcon("hs.png"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::positionChanged(qint64 N)
{

}

void MainWindow::readBuffer()
{
    QAudioBuffer b = decoder->read();
    byteArr.append(b.constData<char>(), b.byteCount());
}

void MainWindow::aonotify()
{
    qint64 N = ao->processedUSecs()/1000;
    double D = 1000*(double)ab.buffer().length()/2/2/decoder->audioFormat().sampleRate();
    ui->horizontalSlider_3->setValue(N*ui->horizontalSlider_3->maximum()/D);
    qint64 NBias = 2 * N*decoder->audioFormat().sampleRate()/1000;
    qint64 NSamples = ao->notifyInterval()*decoder->audioFormat().sampleRate()/1000;
    QVector<double> x,y1,y2 ;
    if(2*(NBias+2*NSamples + 1)>=ab.buffer().length())return;
    for (int i=0; i<NSamples; ++i)
    {
        x.append((NBias+i)/2/(double)decoder->audioFormat().sampleRate());
        y1.append(*( ( (qint16 *)ab.buffer().data() )+ 2*i + NBias) );
        y2.append(*( ( (qint16 *)ab.buffer().data() )+ 2*i + 1 + NBias) );
    }
    ui->widget->graph(0)->setData(x, y1);
    ui->widget->graph(1)->setData(x, y2);
    ui->widget->xAxis->setLabel("Time (Sec)");
    ui->widget->yAxis->setLabel("Amp.");
    ui->widget->rescaleAxes();
    ui->widget->yAxis->setRange(-pow(2,15), pow(2,15));
    ui->widget->replot();

    int NFFT=log2(y1.length());
    NFFT=pow(2,NFFT);

    Acomplex *xFFT = new Acomplex[NFFT];
    for (int i = 0; i < NFFT; ++i) {
        xFFT[i]=Acomplex(y1.at(i)/pow(2,15),0);
    }
    CFFT::Forward(xFFT,NFFT);
    QVector<double> Y1,Y2,F;
    for (int i = 0; i < NFFT/2; ++i) {
        Y1.append(10*log10(xFFT[i].norm()/NFFT));
        F.append(i*decoder->audioFormat().sampleRate()/NFFT);
    }
    for (int i = 0; i < NFFT; ++i) {
        xFFT[i]=Acomplex(y2.at(i)/pow(2,15),0);
    }
    CFFT::Forward(xFFT,NFFT);
    for (int i = 0; i < NFFT/2; ++i) {
        Y2.append(10*log10(xFFT[i].norm()/NFFT));
    }
    ui->widget_2->graph(0)->setData(F, Y1);
    ui->widget_2->graph(1)->setData(F, Y2);
    ui->widget_2->rescaleAxes();
    ui->widget_2->xAxis->setRange(0, F.last()*ui->horizontalSlider_2->value()/99.0);
    ui->widget_2->yAxis->setRange(-30, 20);

    ui->widget_2->xAxis->setLabel("Freq. (Hz)");
    ui->widget_2->yAxis->setLabel("Spectrum (dB)");
    ui->widget_2->replot();

    ui->widget_3->x.clear();
    double a = ui->horizontalSlider_2->value()/99.0;
    double Min = 1e10;
    double Max = -1e10;
    for (int i = 0; i < Y2.length()*a; ++i) {
        if(Y2.at(i)<Min)Min=Y2.at(i);
        if(Y2.at(i)>Max)Max=Y2.at(i);
    }
    for (int i = 0; i < Y2.length()*a; ++i) {
        double b=(Y2.at(i)+20)/30;
        if(b>1)b=1;
        if(b<0)b=0;
        ui->widget_3->x.append(b);
    }
    ui->widget_3->repaint();
}

void MainWindow::decfinished()
{
    ab.setData(byteArr);
    ab.open(QIODevice::ReadOnly);
    ab.reset();
    delete ao;
    ao=new QAudioOutput(decoder->audioFormat());
    ao->setNotifyInterval(100);
    connect(ao, SIGNAL(notify()), this, SLOT(aonotify()));
    ao->start(&ab);
    ui->pushButton_3->setText("pause");
    setEnabled(true);
}

void MainWindow::on_pushButton_clicked()
{
}

void MainWindow::on_pushButton_2_clicked()
{
    QString s = QFileDialog::getOpenFileName(this,"Open","","*.mp3");
    if(s.isEmpty())return;
    decoder->setSourceFilename(s);
    decoder->start();
    setEnabled(false);
}

void MainWindow::on_pushButton_3_clicked()
{
    if(ui->pushButton_3->text().startsWith("play")){
        ui->pushButton_3->setText("pause");
        ao->resume();
    }else{
        ui->pushButton_3->setText("play");
        ao->suspend();
    }
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ui->lineEdit->setText(QString::number(value/100.0));
    on_pushButton_4_clicked();
}

void MainWindow::on_pushButton_4_clicked()
{
    int s = ui->lineEdit->text().toDouble()*1000;
    ao->setNotifyInterval(s);
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{

}

void MainWindow::on_pushButton_5_clicked()
{
    int N = ui->lineEdit_2->text().toInt();
    qint16 x;
    double y;
    for (int i = 0; i < byteArr.length()/2/2-2*N-2; ++i) {
        y=0;
        for (int j = 0; j < N; ++j) {
            y+=((qint16 *)byteArr.data())[2*(i+j)];
        }
        x=y/N;
        ((qint16 *)ab.buffer().data())[2*i]=x;
        y=0;
        for (int j = 0; j < N; ++j) {
            y+=((qint16 *)byteArr.data())[2*(i+j)+1];
        }
        x=y/N;
        ((qint16 *)ab.buffer().data())[2*i+1]=x;
    }
}
