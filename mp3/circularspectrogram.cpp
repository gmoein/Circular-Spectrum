#include "circularspectrogram.h"

CircularSpectrogram::CircularSpectrogram(QWidget *parent) : QWidget(parent)
{
}

void CircularSpectrogram::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::HighQualityAntialiasing);
    p.drawPixmap(0,0,QPixmap("hs.png"));
    p.setPen(QColor(100,0,0,0));
    p.setBrush(QColor(0,200,0,120));
    for (int i = 0; i < x.length(); ++i) {
        p.drawPolygon(poly(-270.0*i/x.length(),x.at(i)));
    }
}

QPolygon CircularSpectrogram::poly(double t, double A)
{
    QPolygon pol;
    double R = 250;
    int S = 2*x.length();
    pol.append(QPoint(R/2+(R/2*(1-A))*cos(qDegreesToRadians(t-360.0/S)),
                      R/2+(R/2*(1-A))*sin(qDegreesToRadians(t-360.0/S))));
    pol.append(QPoint(R/2+(R/2*(1-A))*cos(qDegreesToRadians(t+360.0/S)),
                      R/2+(R/2*(1-A))*sin(qDegreesToRadians(t+360.0/S))));
    pol.append(QPoint(R/2+R/2*cos(qDegreesToRadians(t+360.0/S)),
                      R/2+R/2*sin(qDegreesToRadians(t+360.0/S))));
    pol.append(QPoint(R/2+R/2*cos(qDegreesToRadians(t-360.0/S)),
                      R/2+R/2*sin(qDegreesToRadians(t-360.0/S))));
    return pol;
}
