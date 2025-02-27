/****************************************************************************
**
** Copyright (C) 2012 Denis Shienkov <denis.shienkov@gmail.com>
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtSerialPort module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
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
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
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
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

#include "masterthread.h"

QT_BEGIN_NAMESPACE

class QLabel;
class QLineEdit;
class QSpinBox;
class QPushButton;
class QComboBox;
class QSlider;

QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    union unionDtStr {
#pragma pack(push, 1)
      struct Data {
  //      uint8_t dev;
        char command;
        long data;
 //       char CRC;
      } dt;
      char b[5];
#pragma pack(pop)
    }dtStrOut;
    void prepareMessage1(char cmd, long data, uint8_t length);

signals:
    void valueChanged(int value);

private slots:
    void transaction();
    void showResponse(const QString &s);
    void processError(const QString &s);
    void processTimeout(const QString &s);
    void bUp();
    void bStop();
    void bLeft();
    void bRight();
    void bL10();
    void bL30();
    void bL45();
    void bBack();
    void bR10();
    void bR30();
    void bR45();
    void bSetSpeed();
    void bSetAccel();
    void bLlegFull();
    void bRlegFull();
    void bTlgRight();
    void bTlgLeft();
    void bTlgCntr();
    void bSetStepAngle();
    void bSetStepDepth();
    void bCalibration();


private:
    void setControlsEnabled(bool enable);

private:
    int transactionCount;
    QLabel *serialPortLabel;
    QComboBox *serialPortComboBox;
    QLabel *waitResponseLabel;
    QSpinBox *waitResponseSpinBox;
    QLabel *requestLabel;
    QLineEdit *requestLineEdit;
    QLabel *trafficLabel;
    QLabel *statusLabel;
    QPushButton *runButton;
    QPushButton *upButton;
    QPushButton *downButton;
    QPushButton *leftButton;
    QPushButton *leftUpButton;
    QPushButton *rightUpButton;
    QPushButton *rightButton;
    QPushButton *stopButton;
    QPushButton *right10;
    QPushButton *right30;
    QPushButton *right45;
    QPushButton *left10;
    QPushButton *left30;
    QPushButton *left45;
    QSpinBox *spinBoxDir;
    QSlider  *mySliderDir;
    QComboBox *speedComboBox;
    QPushButton *SetSpeed;
    QPushButton *SetAccel;
    QComboBox *accelComboBox;
    QComboBox *stepDepthComboBox;
    QComboBox *stepAngleComboBox;
    QPushButton *LlegFull;
    QPushButton *RlegFull;
    QPushButton *TlgRight;
    QPushButton *TlgLeft;
    QPushButton *TlgCntr;
    QPushButton *SetStepAngle;
    QPushButton *SetStepDepth;
    QPushButton *Calibration;

    MasterThread thread;
};

#endif // DIALOG_H
