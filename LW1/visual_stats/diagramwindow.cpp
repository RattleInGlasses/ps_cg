#include "diagramwindow.h"
#include "ui_diagramwindow.h"
#include <QPainter>

DiagramWindow::DiagramWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DiagramWindow)
{
    ui->setupUi(this);
}

DiagramWindow::~DiagramWindow()
{
    delete ui;
}

void DiagramWindow::paintEvent(QPaintEvent *)
{
    int v1 = 100;
    int v2 = 300;
    int v3 = 25;

    int vsum = v1 + v2 + v3;


    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);


    //painter.drawArc(10, 10, 170, 100, 180*16, 180*16);
    int h = 20;
    int startAngle = 0;
    //painter.drawArc(10, 10+h, 170, 100, 180*16, 180*16);

    int v1Angle = 360 * 16 * v1 / vsum;
    int v2Angle = 360 * 16 * v2 / vsum;
    int v3Angle = 360 * 16 - v2Angle - v1Angle;
    auto v1Color = Qt::red;
    auto v2Color = Qt::green;
    auto v3Color = Qt::blue;
//    painter.setPen(QPen(QBrush(v1Color), 0));
//    painter.setBrush(QBrush(v1Color));
//    painter.drawPie(10, 10, 170, 100, startAngle, v1Angle);
//    startAngle += v1Angle;
//    painter.setPen(QPen(QBrush(v2Color), 0));
//    painter.setBrush(QBrush(v2Color));
//    painter.drawPie(10, 10, 170, 100, startAngle, v2Angle);
//    startAngle += v2Angle;
//    painter.setPen(QPen(QBrush(v3Color), 0));
//    painter.setBrush(QBrush(v3Color));
//    painter.drawPie(10, 10, 170, 100, startAngle, v3Angle);


    qreal percent = 0.2;
    QPainterPath path(QPointF(10, 10));
    path.lineTo(10, 10+h);
    path.arcTo(10, -15+h, 300, 50, 180, 180);
    auto curPoint = path.currentPosition();
    path.lineTo(curPoint.x(), curPoint.y()-h);
    path.arcTo(10, -15, 300, 50, 0, -180);




//    qreal percent = 0.2;
//    QPainterPath path(QPointF(10, 10));
//    path.lineTo(10, 10+h);
//    path.arcTo(10, -15+h, 300, 50, 280, 180*percent);
    //auto curPoint = path.currentPosition();
    //path.lineTo(curPoint.x(), curPoint.y()-h);
    //auto curPoint2 = path.currentPosition();
    //path.arcTo(10, -15, curPoint2.x(), curPoint2.y(), 0, -180*percent);

    //path.lineTo(10+300*percent, 10);
    //path.arcTo(10, -15, 300*percent, 50, 0, -180*percent);
    //path.lineTo(10, 10+h);
    //path.lineTo(170, 10+h);

    //path.arcTo(10, 10, 170, 100, 0*16, 10*16);
    //path.lineTo(170, 10);
    //path.lineTo(10, 10);
    //path.arcTo(10, 10+h, 170, 100, 180*16, 180*16);

    painter.setClipRect(10, 10, 180, 25+10+h);
    painter.setPen(QPen(v1Color));
    painter.setBrush(QBrush(v1Color));
    painter.drawPath(path);

    painter.setClipRect(10+180, 10, 300-180, 25+10+h);
    painter.setPen(QPen(v2Color));
    painter.setBrush(QBrush(v2Color));
    painter.drawPath(path);




    //painter.drawLine(10, 10+100/2, 10, 10+100/2+h);
    //painter.drawLine(10+170, 10+100/2, 10+170, 10+100/2+h);
}
