/****************************************************************************
**
** Copyright (C) 2020 Miklos Marton <martonmiklosqdev@gmail.com>
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
#ifndef LINEMARKERITEM_H
#define LINEMARKERITEM_H

#include <QtCharts/QChart>
#include <QtCharts/QChartGlobal>
#include <QtCharts/private/qchartglobal_p.h>
#include <QtGui/QPen>
#include <private/chartitem_p.h>
#include <private/qlinemarker_p.h>

QT_CHARTS_BEGIN_NAMESPACE

class QLineMarker;

class Q_CHARTS_PRIVATE_EXPORT LineMarkerItem : public ChartItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit LineMarkerItem(QLineMarker *marker, QGraphicsItem *item = nullptr);
    ~LineMarkerItem() = default;

    //from QGraphicsItem
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public Q_SLOTS:
    void handleUpdated();
    void handleDomainUpdated();

private:
    QLineMarker *m_marker = nullptr;
    QLineF m_line;
    QLineF m_drawnLine;
    QRectF m_boundingRect;
    QPen m_linePen;
    bool m_pointsVisible = false;
    void calculateBoundingRect();
};

QT_CHARTS_END_NAMESPACE

#endif // LINEMARKERITEM_H
