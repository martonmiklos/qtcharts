/****************************************************************************
**
** Copyright (C) 2020 Miklos Marton <martonmiklosqdev@gmail.com>
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

#ifndef QLINEMARKER_H
#define QLINEMARKER_H

#include <QtCharts/QChartGlobal>
#include <QtCharts/QAbstractSeries>
#include <private/linemarkeritem_p.h>

QT_CHARTS_BEGIN_NAMESPACE

class QLineMarkerPrivate;

class Q_CHARTS_EXPORT QLineMarker : public QAbstractSeries
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
public:
    explicit QLineMarker(qreal position, Qt::Orientation orientation = Qt::Horizontal, QObject *parent = nullptr);
    explicit QLineMarker(QObject *parent = nullptr);
    ~QLineMarker();

    QAbstractSeries::SeriesType type() const override;

    void setPosition(qreal position);
    qreal position() const;

    void setOrientation(Qt::Orientation orientation);
    Qt::Orientation orientation() const;

    bool attachAxis(QAbstractAxis *axis) override;

    virtual void setPen(const QPen &pen);
    QPen pen() const;

    void setBrush(const QBrush &brush);
    QBrush brush() const;

    void setColor(const QColor &color);
    QColor color() const;

protected:
    QLineMarker(QLineMarkerPrivate &d, QObject *parent = nullptr);

Q_SIGNALS:
    void positionChanged(qreal position);
    void colorChanged(QColor color);
    void penChanged(const QPen &pen);

private:
    Q_DECLARE_PRIVATE(QLineMarker)
    Q_DISABLE_COPY(QLineMarker)
    friend class LineMarkerItem;
};

QT_CHARTS_END_NAMESPACE

#endif // QLINEMARKER_H
