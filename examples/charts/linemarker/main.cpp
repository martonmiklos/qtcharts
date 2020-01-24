/****************************************************************************
**
** Copyright (C) 2020 Miklos Marton <martonmiklosqdev@gmail.com>
** Copyright (C) 2020 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtCharts/QChartView>
#include <QtCharts/QLineMarker>
#include <QtCharts/QLineSeries>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//![1]
    QLineSeries *series = new QLineSeries();
//![1]

//![2]
    series->append(0, 6);
    series->append(2, 4);
    series->append(3, 8);
    series->append(7, 4);
    series->append(10, 5);
    *series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);
    series->setName("Example series");
//![2]


//![3]
    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();

    auto lowerLimitMarker = new QLineMarker();
    lowerLimitMarker->setPosition(2.8);
    lowerLimitMarker->setOrientation(Qt::Horizontal);
    chart->addSeries(lowerLimitMarker);
    auto pen2 = lowerLimitMarker->pen();
    pen2.setColor(Qt::red);
    lowerLimitMarker->setPen(pen2);
    lowerLimitMarker->attachAxis(chart->axes(Qt::Horizontal).first());
    lowerLimitMarker->attachAxis(chart->axes(Qt::Vertical).first());
    lowerLimitMarker->setName("Lower limit");

    auto upperLimitMarker = new QLineMarker();
    upperLimitMarker->setPosition(6.7);
    upperLimitMarker->setOrientation(Qt::Horizontal);
    chart->addSeries(upperLimitMarker);
    auto pen = upperLimitMarker->pen();
    pen.setColor(Qt::red);
    pen.setWidth(1);
    upperLimitMarker->setPen(pen);
    upperLimitMarker->attachAxis(chart->axes(Qt::Horizontal).first());
    upperLimitMarker->attachAxis(chart->axes(Qt::Vertical).first());
    upperLimitMarker->setName("Upper limit");

    chart->setTitle("Simple line marker example");

    chart->legend()->setVisible(true);
//![3]

//![4]
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
//![4]


//![5]
    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(400, 300);
    window.setWindowTitle("Simple line marker example");
    window.show();
//![5]

    return a.exec();
}
