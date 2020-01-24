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
#include <QtCharts/QLineMarkerLegendMarker>
#include <private/qlinemarker_p.h>
#include <private/qlinemarkerlegendmarker_p.h>

QT_CHARTS_BEGIN_NAMESPACE

/*!
  \internal
*/
QLineMarkerLegendMarker::QLineMarkerLegendMarker(QtCharts::QLineMarker *marker,
                                                 QtCharts::QLegend *legend,
                                                 QObject *parent) :
    QLegendMarker(*new QLineMarkerLegendMarkerPrivate(this, marker, legend), parent)
{
    d_ptr->updated();
}

QLineMarkerLegendMarker::~QLineMarkerLegendMarker()
{

}

QLineMarker *QLineMarkerLegendMarker::series()
{
    Q_D(QLineMarkerLegendMarker);
    return static_cast<QLineMarker*>(d->m_marker);
}

/*!
    \internal
*/
QLineMarkerLegendMarker::QLineMarkerLegendMarker(QLineMarkerLegendMarkerPrivate &d, QObject *parent) :
    QLegendMarker(d, parent)
{

}

QLineMarkerLegendMarkerPrivate::QLineMarkerLegendMarkerPrivate(QtCharts::QLineMarkerLegendMarker *q,
                                                               QLineMarker *marker,
                                                               QtCharts::QLegend *legend) :
    QLegendMarkerPrivate(q, legend),
    q_ptr(q),
    m_marker(marker)
{
    connect(m_marker, &QLineMarker::nameChanged, this, &QLineMarkerLegendMarkerPrivate::updated);
    connect(m_marker->d_func(), &QLineMarkerPrivate::updated, this, &QLineMarkerLegendMarkerPrivate::updated);
}

QObject *QLineMarkerLegendMarkerPrivate::relatedObject()
{
    return m_marker;
}

QAbstractSeries *QLineMarkerLegendMarkerPrivate::series()
{
    return m_marker;
}

void QLineMarkerLegendMarkerPrivate::updated()
{
    bool labelChanged = false;
    bool brushChanged = false;

    if (!m_customLabel && (m_item->label() != m_marker->name())) {
        m_item->setLabel(m_marker->name());
        labelChanged = true;
    }

    QBrush emptyBrush;
    if (!m_customBrush
            && (m_item->brush() == emptyBrush
                || m_item->brush().color() != m_marker->pen().color())) {
        m_item->setBrush(QBrush(m_marker->pen().color()));
        brushChanged = true;
    }
    m_item->setSeriesBrush(m_marker->brush());
    m_item->setSeriesPen(m_marker->pen());

    invalidateLegend();

    if (labelChanged)
        emit q_ptr->labelChanged();
    if (brushChanged)
        emit q_ptr->brushChanged();
}

QT_CHARTS_END_NAMESPACE
