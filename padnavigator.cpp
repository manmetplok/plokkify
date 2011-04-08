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


#include "padnavigator.h"

#include <QtGui/QtGui>
#include <QtOpenGL/QtOpenGL>

PadNavigator::PadNavigator( QWidget *parent)
    : QGraphicsView(parent)
{
    QSize size(6,2);

    // Pad item
    this->pad = new FlippablePad(size);

    // Selection item
    RoundRectItem *selectionItem = new RoundRectItem(QRectF(-110, -110, 220, 220),
                                                     Qt::gray, pad);
    selectionItem->setZValue(0.5);

    // Selection animation
    QPropertyAnimation *smoothXSelection = new QPropertyAnimation(selectionItem, "x");
    QPropertyAnimation *smoothYSelection = new QPropertyAnimation(selectionItem, "y");
    smoothXSelection->setDuration(100);
    smoothYSelection->setDuration(100);
    smoothXSelection->setEasingCurve(QEasingCurve::InCurve);
    smoothYSelection->setEasingCurve(QEasingCurve::InCurve);

    // Build the state machine
    QStateMachine *stateMachine = new QStateMachine(this);

    QState *frontState = new QState(stateMachine);

    frontState->assignProperty(pad, "fill", false);

    frontState->assignProperty(selectionItem, "visible", true);

    stateMachine->addDefaultAnimation(smoothXSelection);
    stateMachine->addDefaultAnimation(smoothYSelection);
    stateMachine->setInitialState(frontState);

    // Create substates for each icon; store in temporary grid.
    int columns = size.width();
    int rows = size.height();
    QVector< QVector< QState * > > stateGrid;
    stateGrid.resize(rows);
    for (int y = 0; y < rows; ++y) {
        stateGrid[y].resize(columns);
        for (int x = 0; x < columns; ++x)
            stateGrid[y][x] = new QState(frontState);
    }
    frontState->setInitialState(stateGrid[0][0]);
    selectionItem->setPos(pad->iconAt(0, 0)->pos());

    // Enable key navigation using state transitions
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < columns; ++x) {
            QState *state = stateGrid[y][x];
            QKeyEventTransition *rightTransition = new QKeyEventTransition(this, QEvent::KeyPress,
                                                                           Qt::Key_Right, state);
            QKeyEventTransition *leftTransition = new QKeyEventTransition(this, QEvent::KeyPress,
                                                                          Qt::Key_Left, state);
            QKeyEventTransition *downTransition = new QKeyEventTransition(this, QEvent::KeyPress,
                                                                          Qt::Key_Down, state);
            QKeyEventTransition *upTransition = new QKeyEventTransition(this, QEvent::KeyPress,
                                                                        Qt::Key_Up, state);

            rightTransition->setTargetState(stateGrid[y][(x + 1) % columns]);
            leftTransition->setTargetState(stateGrid[y][((x - 1) + columns) % columns]);
            downTransition->setTargetState(stateGrid[(y + 1) % rows][x]);
            upTransition->setTargetState(stateGrid[((y - 1) + rows) % rows][x]);

            RoundRectItem *icon = pad->iconAt(x, y);

            state->assignProperty(selectionItem, "x", icon->x());
            state->assignProperty(selectionItem, "y", icon->y());

        }
    }
    // Scene
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->addItem(pad);
    scene->setSceneRect(scene->itemsBoundingRect());
    setScene(scene);

    // View
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setMinimumSize(50, 50);
    setCacheMode(CacheBackground);
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);

    stateMachine->start();

}

PadNavigator::~PadNavigator(){
    delete pad;
}

void PadNavigator::addAction(  QPixmap pixmap, int id){
    int row = id > 5 ? 1 : 0;
    int column = id > 5  ? id - 6 : id;
    this->pad->setIcon(pixmap ,column,row);
}

void PadNavigator::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
}
