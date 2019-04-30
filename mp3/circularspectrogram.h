#ifndef CIRCULARSPECTROGRAM_H
#define CIRCULARSPECTROGRAM_H

#include <QWidget>
#include <QPainter>
#include <QtMath>

class CircularSpectrogram : public QWidget
{
    Q_OBJECT
public:
    explicit CircularSpectrogram(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    QVector<double> x;
    QPolygon poly(double t,double A);
signals:

public slots:
};

#endif // CIRCULARSPECTROGRAM_H
