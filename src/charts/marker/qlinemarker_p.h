/****************************************************************************
**
** Copyright (C) 2020 Miklos Marton <martonmiklosqdev@gmail.com>
**
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

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
#ifndef QLINEMARKER_P_H
#define QLINEMARKER_P_H

#include <private/qabstractseries_p.h>
#include <QtCharts/qvalueaxis.h>
#include <QtCharts/private/qchartglobal_p.h>

QT_CHARTS_BEGIN_NAMESPACE

class QLineMarker;
class QAbstractAxis;

class Q_CHARTS_PRIVATE_EXPORT QLineMarkerPrivate : public QAbstractSeriesPrivate
{
    Q_OBJECT
public:
    QLineMarkerPrivate(QLineMarker *q);

    void initializeDomain();
    void initializeAxes();
    void initializeTheme(int index, ChartTheme* theme, bool forced = false);
    void initializeGraphics(QGraphicsItem* parent);
    void initializeAnimations(QChart::AnimationOptions options, int duration,
                                      QEasingCurve &curve);

    QList<QLegendMarker*> createLegendMarkers(QLegend* legend);

    QAbstractAxis::AxisType defaultAxisType(Qt::Orientation) const;
    QAbstractAxis* createDefaultAxis(Qt::Orientation) const;

    bool setPosition(qreal position);
    bool setOrientation(Qt::Orientation orientation);
    void axesUpdated();

Q_SIGNALS:
    void updated();

private:
    //Q_DECLARE_PUBLIC(QLineMarker)
    inline QLineMarker* q_func();
    inline const QLineMarker* q_func() const;
    friend class QLineMarker;

    qreal m_position = 0.0;
    Qt::Orientation m_orientation;

    QPen m_pen;
    QBrush m_brush;
    bool m_pointsVisible;
    QString m_pointLabelsFormat;
    bool m_pointLabelsVisible;
    QFont m_pointLabelsFont;
    QColor m_pointLabelsColor;
    bool m_pointLabelsClipping;

    QValueAxis *parallelAxis();
};

QT_CHARTS_END_NAMESPACE

#endif // QLINEMARKER_P_H
