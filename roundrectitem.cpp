/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#include "roundrectitem.h"

#include <QtGui/QtGui>

RoundRectItem::RoundRectItem(const QRectF &bounds,
                             const QColor &color,
                             QGraphicsItem *parent)
    : QGraphicsObject(parent),
      m_bounds(bounds)
{
    setCacheMode(ItemCoordinateCache);

    m_gradient.setStart(bounds.topLeft());
    m_gradient.setFinalStop(bounds.bottomRight());
    m_gradient.setColorAt(0, color);
    m_gradient.setColorAt(1, color.dark(200));
}

QRectF RoundRectItem::boundingRect() const
{
    return m_bounds.adjusted(0, 0, 2, 2);
}

void RoundRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                          QWidget *widget)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(m_gradient);

    painter->drawRect(m_bounds);

    if (!m_pix.isNull()) {
        painter->scale(1, 1);
        painter->drawPixmap((-m_pix.width() / 2)+20, (-m_pix.height() / 2)+20, m_pix);
    }

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QPixmap RoundRectItem::pixmap() const
{
    return m_pix;
}

void RoundRectItem::setPixmap(const QPixmap &pixmap)
{
    m_pix = pixmap;
    update();
}
