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

#include <QtCharts/qlinemarker.h>
#include <private/charttheme_p.h>
#include <private/linechartitem_p.h>
#include <private/qchart_p.h>
#include <private/qlinemarker_p.h>

QT_CHARTS_BEGIN_NAMESPACE

/*!
    \class QLineMarker
    \inmodule QtCharts
    \brief The QLineMarker class can be used to draw lines running parallel
    with one of the axes spanning the whole range of the parallel axis.

    It could be used to create lines similar to the cursors
    on oscilloscopes, or visualize a scalar limit for data displayed with
    an anotother series.

    \image examples_linemarker.png

    Creating a basic line marker is simple:
    \coder
    auto marker = new QLineMarker();
    marker->setPosition(3.14);
    marker->setOrientation(Qt::Vertical);
    ...
    chart->addSeries(marker);
    marker->attachAxis(chart->axes(Qt::Horizontal)->first());
    marker->attachAxis(chart->axes(Qt::Vertical)->first());
    \endcode
*/

/*!
    \qmltype LineMarker
    \instantiates QLineMarker
    \inqmlmodule QtCharts

    \inherits QAbstractSeries

    \brief Presents a vertical/horizontal line in line charts.

    A line marker is used to draw a line parallel with some of the axes
    to the charts. It could be used to create lines similar to the cursors
    on oscilloscopes, or visualize a scalar limit for data displayed with
    an anotother series.

    The following QML example shows how to create a simple line chart:
    \snippet qmlchart/qml/qmlchart/View2.qml 1
    \beginfloatleft
    \image examples_qmlchart2.png
    \endfloat
    \clearfloat
*/

/*!
    \qmlproperty real LineMarker::width
    The width of the marker. By default, the width is 2.0.
*/

/*!
    \qmlproperty Qt::PenStyle LineMarker::style
    Controls the style of the marker. Set to one of \l{Qt::NoPen}{Qt.NoPen},
    \l{Qt::SolidLine}{Qt.SolidLine}, \l{Qt::DashLine}{Qt.DashLine}, \l{Qt::DotLine}{Qt.DotLine},
    \l{Qt::DashDotLine}{Qt.DashDotLine}, or \l{Qt::DashDotDotLine}{Qt.DashDotDotLine}.
    Using \l{Qt::CustomDashLine}{Qt.CustomDashLine} is not supported in the QML API.
    By default, the style is Qt.SolidLine.

    \sa Qt::PenStyle
*/

/*!
    \qmlproperty Qt::PenCapStyle LineMarker::capStyle
    Controls the cap style of the line. Set to one of \l{Qt::FlatCap}{Qt.FlatCap},
    \l{Qt::SquareCap}{Qt.SquareCap} or \l{Qt::RoundCap}{Qt.RoundCap}. By
    default the cap style is Qt.SquareCap.

    \sa Qt::PenCapStyle
*/

/*!
    Constructs an empty marker object that is a child of \a parent and sets sets the default
    position and orientation specified by the \position and \orientation attrributes.
    When the marker object is added to a QChartView or QChart instance, the ownership
    is transferred.
*/
QLineMarker::QLineMarker(qreal position, Qt::Orientation orientation, QObject *parent) :
    QAbstractSeries(*new QLineMarkerPrivate(this), parent)
{
    Q_D(QLineMarker);
    d->setPosition(position);
    d->setOrientation(orientation);
}

/*!
    Constructs an empty series object that is a child of \a parent.
    When the series object is added to a QChartView or QChart instance, the ownership
    is transferred.
*/
QLineMarker::QLineMarker(QObject *parent):
    QAbstractSeries(*new QLineMarkerPrivate(this), parent)
{

}

/*!
    \internal
*/
QLineMarker::QLineMarker(QLineMarkerPrivate &d, QObject *parent)
    : QAbstractSeries(d, parent)
{

}

/*!
    Destroys the object. Marker added to QChartView or QChart instances are owned by the
    instances and deleted when the instances are destroyed.
*/
QLineMarker::~QLineMarker()
{
    Q_D(QLineMarker);
    if (d->m_chart)
        d->m_chart->removeSeries(this);
}

/*!
    \reimp
*/
QAbstractSeries::SeriesType QtCharts::QLineMarker::type() const
{
    return QAbstractSeries::SeriesTypeLineMarker;
}

/*!
    Sets the marker position relative to the first attached axis which is pependicular
    to the marker's orientation.
 */
void QLineMarker::setPosition(qreal position)
{
    Q_D(QLineMarker);
    if (d->setPosition(position))
        emit positionChanged(d->m_position);
}

/*!
    Returns the marker position relative to the first attached axis which is pependicular
    to the marker's orientation.
 */
qreal QLineMarker::position() const
{
    Q_D(const QLineMarker);
    return d->m_position;
}

/*!
    Sets the marker orientation.
 */
void QLineMarker::setOrientation(Qt::Orientation orientation)
{
    Q_D(QLineMarker);
    d->setOrientation(orientation);

}

/*!
    Returns the marker orientation.
 */
Qt::Orientation QLineMarker::orientation() const
{
    Q_D(const QLineMarker);
    return d->m_orientation;
}

/*!
    Attaches the marker to the \a axis. If the \a axis orientation is identical to the marker's
    orientation then the marker will be parrallel to the \a axis. If not (the axis and the marker)
    pependicular then the marker will be drawn pependicular to the axis.
 */
bool QLineMarker::attachAxis(QAbstractAxis *axis)
{
    bool ret = QAbstractSeries::attachAxis(axis);
    Q_D(QLineMarker);
    d->axesUpdated();
    return ret;
}

/*!
    Sets the pen used for drawing the marker line on the chart to \a pen. If the pen is
    not defined, the pen from the chart theme is used.
    \sa QChart::setTheme()
*/
void QLineMarker::setPen(const QPen &pen)
{
    Q_D(QLineMarker);
    if (d->m_pen != pen) {
        bool emitColorChanged = d->m_pen.color() != pen.color();
        d->m_pen = pen;
        emit d->updated();
        if (emitColorChanged)
            emit colorChanged(pen.color());
        emit penChanged(pen);
    }
}

QPen QLineMarker::pen() const
{
    Q_D(const QLineMarker);
    if (d->m_pen == QChartPrivate::defaultPen())
        return QPen();
    else
        return d->m_pen;
}

/*!
    Sets the brush used for drawing the marker line  on the chart to \a brush. If the
    brush is not defined, the brush from the chart theme setting is used.
    \sa QChart::setTheme()
*/
void QLineMarker::setBrush(const QBrush &brush)
{
    Q_D(QLineMarker);
    if (d->m_brush != brush) {
        d->m_brush = brush;
        emit d->updated();
    }
}

QBrush QLineMarker::brush() const
{
    Q_D(const QLineMarker);
    if (d->m_brush == QChartPrivate::defaultBrush())
        return QBrush();
    else
        return d->m_brush;
}

void QLineMarker::setColor(const QColor &color)
{
    QPen p = pen();
    if (p.color() != color) {
        p.setColor(color);
        setPen(p);
    }
}

QColor QLineMarker::color() const
{
    return pen().color();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QtCharts::QLineMarkerPrivate::QLineMarkerPrivate(QLineMarker *q):
    QAbstractSeriesPrivate(q)
{

}

void QLineMarkerPrivate::initializeDomain()
{
    Q_Q(QLineMarker);
    auto parallelAxis = this->parallelAxis();
    if (parallelAxis) {
        if (m_orientation == Qt::Horizontal) {
            domain()->setRange(parallelAxis->min(), parallelAxis->max(), q->pen().width()/2.0, q->pen().width()/2.0);
        } else if (m_orientation == Qt::Vertical) {
            domain()->setRange(q->pen().width()/2.0, q->pen().width()/2.0, parallelAxis->min(), parallelAxis->max());
        }
    }
}

void QLineMarkerPrivate::initializeAxes()
{

}

void QLineMarkerPrivate::initializeTheme(int index, ChartTheme *theme, bool forced)
{
    Q_Q(QLineMarker);
    const QList<QColor> colors = theme->seriesColors();

    if (forced || QChartPrivate::defaultPen() == m_pen) {
        QPen pen;
        pen.setColor(colors.at(index % colors.size()));
        pen.setWidthF(2);
        q->setPen(pen);
    }
}

void QLineMarkerPrivate::initializeGraphics(QGraphicsItem *parent)
{
    Q_Q(QLineMarker);
    LineMarkerItem *line = new LineMarkerItem(q,parent);
    m_item.reset(line);
    QAbstractSeriesPrivate::initializeGraphics(parent);
}

void QLineMarkerPrivate::initializeAnimations(QChart::AnimationOptions options, int duration, QEasingCurve &curve)
{
    QAbstractSeriesPrivate::initializeAnimations(options, duration, curve);
}

QList<QLegendMarker *> QLineMarkerPrivate::createLegendMarkers(QLegend *legend)
{
    Q_UNUSED(legend)
    // TODO
    return QList<QLegendMarker*>();
}

QAbstractAxis::AxisType QLineMarkerPrivate::defaultAxisType(Qt::Orientation orientation) const
{
    Q_UNUSED(orientation);
    return QAbstractAxis::AxisTypeValue;
}

QAbstractAxis *QLineMarkerPrivate::createDefaultAxis(Qt::Orientation orientation) const
{
    Q_UNUSED(orientation);
    return new QValueAxis;
}

bool QLineMarkerPrivate::setPosition(qreal position)
{
    if (!qFuzzyCompare(m_position, position)) {
        m_position = position;
        emit updated();
        return true;
    }
    return false;
}

bool QLineMarkerPrivate::setOrientation(Qt::Orientation orientation)
{
    if (m_orientation != orientation) {
        m_orientation = orientation;
        emit updated();
        return true;
    }
    return false;
}

void QLineMarkerPrivate::axesUpdated()
{
    // TODO emit only if relevant axes changed
    emit updated();
}

QLineMarker *QLineMarkerPrivate::q_func()
{
    return static_cast<QLineMarker *>(q_ptr);
}

const QLineMarker *QLineMarkerPrivate::q_func() const
{
    return static_cast<const QLineMarker *>(q_ptr);
}

QValueAxis *QLineMarkerPrivate::parallelAxis()
{
    Q_Q(QLineMarker);
    for (auto axis : q->attachedAxes()) {
        if (axis->type() != QAbstractAxis::AxisTypeValue)
            continue;
        if (axis->orientation() == m_orientation)
            return static_cast<QValueAxis*>(axis);
    }
    return nullptr;
}

QT_CHARTS_END_NAMESPACE
