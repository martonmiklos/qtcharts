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

#include <QtCharts/QLineMarker>
#include <QtCharts/QValueAxis>
#include <QtGui/QPainter>
#include <private/chartpresenter_p.h>
#include <private/charttheme_p.h>
#include <private/chartthememanager_p.h>
#include <private/linemarkeritem_p.h>
#include <private/polardomain_p.h>
#include <private/qlinemarker_p.h>

QT_CHARTS_BEGIN_NAMESPACE

LineMarkerItem::LineMarkerItem(QLineMarker *marker, QGraphicsItem *item)
    : ChartItem(marker->d_func(), item),
      m_marker(marker)
{
    connect(marker->d_func(), &QLineMarkerPrivate::updated, this, &LineMarkerItem::handleUpdated);
    handleUpdated();
}

QRectF LineMarkerItem::boundingRect() const
{
    return m_boundingRect;
}

void LineMarkerItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->setPen(m_marker->pen());
    painter->setBrush(m_marker->brush());
    painter->drawLine(m_drawnLine);
}

void LineMarkerItem::handleUpdated()
{
    QValueAxis *axis = nullptr;
    // find the first attached axis which is parallel to the marker
    const auto attachedAxes = m_marker->attachedAxes();
    for (auto attachedAxis : attachedAxes) {
        if (attachedAxis->type() != QAbstractAxis::AxisTypeValue)
            continue;
        if (attachedAxis->orientation() ==  m_marker->orientation()) {
            axis = static_cast<QValueAxis *>(attachedAxis);
            break;
        }
    }

    if (axis == nullptr)
        return;

    prepareGeometryChange();
    if (axis->orientation() == Qt::Horizontal) {
        m_line = QLineF(axis->min(), m_marker->position(),
                        axis->max(), m_marker->position());
        m_boundingRect.setHeight(m_marker->pen().width());
        m_boundingRect.setWidth(m_line.length() + m_marker->pen().width());
    } else if (axis->orientation() == Qt::Vertical) {
        m_line = QLineF(m_marker->position(), axis->min(),
                        m_marker->position(), axis->max());
        m_boundingRect.setWidth(m_marker->pen().width());
        m_boundingRect.setHeight(m_line.length());
    }
    m_boundingRect.setX(m_line.x1());
    update();
}

void LineMarkerItem::handleDomainUpdated()
{
    QVector<QPointF> linePoints;
    linePoints << m_line.p1() << m_line.p2();
    QVector<QPointF> points = domain()->calculateGeometryPoints(linePoints);
    if (points.length() == 2) {
        m_drawnLine.setP1(points.first());
        m_drawnLine.setP2(points.at(1));
        handleUpdated();
    }
}

QT_CHARTS_END_NAMESPACE

#include "moc_linemarkeritem_p.cpp"
