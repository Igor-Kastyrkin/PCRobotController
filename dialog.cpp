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

#include "dialog.h"

#include <QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QGridLayout>
#include <QtWidgets>

#include <QtSerialPort/QSerialPortInfo>

QT_USE_NAMESPACE


void Dialog::prepareMessage1(char cmd, long data, uint8_t length)
{
  char c1[22]="0";
  char c2[11] = "0000000000";
  dtStrOut.dt.command = cmd;
  c1[0]=cmd;
  ltoa(data,c2,10);
//  strcat(c2,"\r");
  strcat(c1,c2);
  dtStrOut.dt.data = data;
  setControlsEnabled(true);
  requestLineEdit->setText(tr(c1));
  setControlsEnabled(false);
  statusLabel->setText(tr("Статус: Включен, подключен к порту %1.")
                       .arg(serialPortComboBox->currentText()));
  thread.transaction(serialPortComboBox->currentText(),
                     waitResponseSpinBox->value(),
                     requestLineEdit->text());
//  dtStrOut.dt.CRC = crc_calc(dtStrOut.b, length);
//  MySerial->println((char*)dtStrOut.b); // Для отладки
}

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , transactionCount(0)
    , serialPortLabel(new QLabel(tr("Serial port:")))
    , serialPortComboBox(new QComboBox())
    , waitResponseLabel(new QLabel(tr("Ожидание отклика, мс:")))
    , waitResponseSpinBox(new QSpinBox())
    , requestLabel(new QLabel(tr("Запрос:")))
    , requestLineEdit(new QLineEdit(tr("00000000000")))
    , trafficLabel(new QLabel(tr("Нет соединения.")))
    , statusLabel(new QLabel(tr("Статус: Неактивен.")))
    , runButton(new QPushButton(tr("Старт")))
    , upButton(new QPushButton(tr("&Вперед")))
    , downButton(new QPushButton(tr("&Назад")))
    , leftButton(new QPushButton(tr("&Влево")))
    , rightButton(new QPushButton(tr("&Вправо")))
    , leftUpButton(new QPushButton(tr("&LeftUp")))
    , rightUpButton(new QPushButton(tr("&RightUp")))
    , stopButton(new QPushButton(tr("&Стоп")))
    , left10(new QPushButton(tr("&L10")))
    , left30(new QPushButton(tr("&L30")))
    , left45(new QPushButton(tr("&L45")))
    , right10(new QPushButton(tr("&R10")))
    , right30(new QPushButton(tr("&R30")))
    , right45(new QPushButton(tr("&R45")))
    , speedComboBox(new QComboBox())
    , SetSpeed(new QPushButton(tr("&Задать скорость")))
    , SetAccel(new QPushButton(tr("&Задать ускорение")))
    , accelComboBox(new QComboBox())
    , stepDepthComboBox(new QComboBox())
    , stepAngleComboBox(new QComboBox())
    , LlegFull(new QPushButton(tr("&Выдвинуть левую")))
    , RlegFull(new QPushButton(tr("&Выдвинуть правую")))
    , TlgRight(new QPushButton(tr("&Переместить ЦТ вправо")))
    , TlgLeft(new QPushButton(tr("&Переместить ЦТ влево")))
    , TlgCntr(new QPushButton(tr("&Переместить ЦТ в центр")))
    , SetStepAngle(new QPushButton(tr("&Задать угол шагов")))
    , SetStepDepth(new QPushButton(tr("&Задать глубину шагов")))
    , Calibration(new QPushButton(tr("&Калибровка")))


{
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos)
        serialPortComboBox->addItem(info.portName());

    speedComboBox->addItem("0,1x");
    speedComboBox->addItem("0,3x");
    speedComboBox->addItem("1,0x");
    accelComboBox->addItem("0,1x");
    accelComboBox->addItem("0,3x");
    accelComboBox->addItem("1,0x");
    stepAngleComboBox->addItem(tr("10 град"));
    stepAngleComboBox->addItem(tr("20 град"));
    stepAngleComboBox->addItem(tr("30 град"));
    stepAngleComboBox->addItem(tr("45 град"));
    stepAngleComboBox->addItem(tr("60 град"));
    stepAngleComboBox->addItem(tr("70 град"));
    stepAngleComboBox->addItem(tr("80 град"));
    stepAngleComboBox->addItem(tr("90 град"));
    stepDepthComboBox->addItem(tr("15 мм"));
    stepDepthComboBox->addItem(tr("30 мм"));
    stepDepthComboBox->addItem(tr("45 мм"));
    stepDepthComboBox->addItem(tr("60 мм"));
    stepDepthComboBox->addItem(tr("80 мм"));
    stepDepthComboBox->addItem(tr("90 мм"));


//    left10->setFixedWidth(40);
//    left30->setFixedWidth(40);
//    left45->setFixedWidth(40);
//    stopButton->setPalette()

    waitResponseSpinBox->setRange(0, 10000);
    waitResponseSpinBox->setValue(1000);


//    spinBoxDir->setMinimum(-90);
//    spinBoxDir->setMaximum(90);
//    spinBoxDir->setSingleStep(15);
//    spinBoxDir->setValue(0);
/*
    mySliderDir->setRange(spinBoxDir->minimum(), spinBoxDir->maximum());
    mySliderDir->setSingleStep(15);
    mySliderDir->setTickPosition(QSlider::TicksBelow);
    mySliderDir->setTickInterval(15);
*/
//    connect(spinBoxDir, SIGNAL(valueChanged(int)), mySliderDir, SLOT(setValue(int)));
//    connect( mySliderDir, SIGNAL(valueChanged(int)),spinBoxDir, SLOT(setValue(int)));


    auto mainLayout = new QGridLayout;
    mainLayout->addWidget(serialPortLabel, 0, 0);
    mainLayout->addWidget(serialPortComboBox, 0, 1);
    mainLayout->addWidget(waitResponseLabel, 1, 0);
    mainLayout->addWidget(waitResponseSpinBox, 1, 1);
    mainLayout->addWidget(runButton, 0, 2, 2, 1);
    mainLayout->addWidget(requestLabel, 2, 0);
    mainLayout->addWidget(requestLineEdit, 2, 1, 1, 3);
    mainLayout->addWidget(trafficLabel, 3, 0, 1, 4);
    mainLayout->addWidget(statusLabel, 4, 0, 1, 5);
    mainLayout->addWidget(upButton, 5, 1+2);
    mainLayout->addWidget(downButton, 7, 1+2);
    mainLayout->addWidget(leftButton, 6, 0+2);
    mainLayout->addWidget(left10, 5, 0+2);
    mainLayout->addWidget(left30, 5, 0+1);
    mainLayout->addWidget(left45, 5, 0);
    mainLayout->addWidget(right10, 5, 2+2);
    mainLayout->addWidget(right30, 5, 2+3);
    mainLayout->addWidget(right45, 5, 2+4);
    mainLayout->addWidget(rightButton, 6, 2+2);
//    mainLayout->addWidget(leftUpButton, 5, 0+2);
//    mainLayout->addWidget(rightUpButton, 5, 2+2);
    mainLayout->addWidget(stopButton, 6, 1+2);
//    mainLayout->addWidget(spinBoxDir,8,0);
//    mainLayout->addWidget(mySliderDir,9,0);
    mainLayout->addWidget(speedComboBox, 8, 0);
    mainLayout->addWidget(SetSpeed, 8, 1);
    mainLayout->addWidget(accelComboBox, 9, 0);
    mainLayout->addWidget(stepDepthComboBox, 10, 0);
    mainLayout->addWidget(stepAngleComboBox, 11, 0);
    mainLayout->addWidget(SetAccel, 9, 1);
    mainLayout->addWidget(LlegFull, 9, 2);
    mainLayout->addWidget(RlegFull, 9, 4);
    mainLayout->addWidget(TlgRight, 8, 4);
    mainLayout->addWidget(TlgCntr, 8, 3);
    mainLayout->addWidget(TlgLeft, 8, 2);
    mainLayout->addWidget(SetStepAngle, 11, 1);
    mainLayout->addWidget(SetStepDepth, 10, 1);
    mainLayout->addWidget(Calibration, 8, 5);

    setLayout(mainLayout);

    setWindowTitle(tr("Канал наведения объекта"));
    serialPortComboBox->setFocus();

    connect(runButton, &QPushButton::clicked, this, &Dialog::transaction);
    connect(upButton,  &QPushButton::clicked, this, &Dialog::bUp);
    connect(stopButton,  &QPushButton::clicked, this, &Dialog::bStop);
    connect(leftButton,  &QPushButton::clicked, this, &Dialog::bLeft);
    connect(rightButton,  &QPushButton::clicked, this, &Dialog::bRight);
    connect(downButton,  &QPushButton::clicked, this, &Dialog::bBack);
    connect(left10,  &QPushButton::clicked, this, &Dialog::bL10);
    connect(left30,  &QPushButton::clicked, this, &Dialog::bL30);
    connect(left45,  &QPushButton::clicked, this, &Dialog::bL45);
    connect(right10,  &QPushButton::clicked, this, &Dialog::bR10);
    connect(right30,  &QPushButton::clicked, this, &Dialog::bR30);
    connect(right45,  &QPushButton::clicked, this, &Dialog::bR45);
    connect(SetSpeed,  &QPushButton::clicked, this, &Dialog::bSetSpeed);
    connect(SetAccel,  &QPushButton::clicked, this, &Dialog::bSetAccel);
    connect(LlegFull,  &QPushButton::clicked, this, &Dialog::bLlegFull);
    connect(RlegFull,  &QPushButton::clicked, this, &Dialog::bRlegFull);

    connect(TlgRight,  &QPushButton::clicked, this, &Dialog::bTlgRight);
    connect(TlgCntr,  &QPushButton::clicked, this, &Dialog::bTlgCntr);
    connect(TlgLeft,  &QPushButton::clicked, this, &Dialog::bTlgLeft);
    connect(SetStepAngle,  &QPushButton::clicked, this, &Dialog::bSetStepAngle);
    connect(SetStepDepth,  &QPushButton::clicked, this, &Dialog::bSetStepDepth);
    connect(Calibration,  &QPushButton::clicked, this, &Dialog::bCalibration);

    //connect(speedComboBox, static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::highlighted)), [=](const QString &text){ /* ... */ });
    connect(&thread, &MasterThread::response, this, &Dialog::showResponse);
    connect(&thread, &MasterThread::error, this, &Dialog::processError);
    connect(&thread, &MasterThread::timeout, this, &Dialog::processTimeout);
}

void Dialog::transaction()
{
    setControlsEnabled(false);
    statusLabel->setText(tr("Статус: Включен, подключен к порту %1.")
                         .arg(serialPortComboBox->currentText()));
    thread.transaction(serialPortComboBox->currentText(),
                       waitResponseSpinBox->value(),
                       requestLineEdit->text());
}

void Dialog::bUp()
{

    prepareMessage1('K',14L/*967*/,0);

}

void Dialog::bStop()
{
    prepareMessage1('K',10/*967*/,0);
}
void Dialog::bLeft()
{
    prepareMessage1('K',11L/*967*/,0);
}

void Dialog::bRight()
{
    prepareMessage1('K',12L/*967*/,0);
}
void Dialog::bBack()
{
    prepareMessage1('K',13L,0);
}
void Dialog::bL10()
{
    prepareMessage1('L',10L,0);
}
void Dialog::bL30()
{
    prepareMessage1('L',30L,0);
}
void Dialog::bL45()
{
    prepareMessage1('L',45L,0);
}
void Dialog::bR10()
{
    prepareMessage1('R',10L,0);
}
void Dialog::bR30()
{
    prepareMessage1('R',30L,0);
}
void Dialog::bR45()
{
    prepareMessage1('R',45L,0);
}
void Dialog::bSetSpeed()
{
    int i = speedComboBox->currentIndex();
    switch (i) {
    case 0:
        prepareMessage1('S',0L,0);
    break;
    case 1:
        prepareMessage1('S',1L,0);
    break;
    case 2:
        prepareMessage1('S',2L,0);
    break;
    }
}
void Dialog::bSetAccel()
{
    int i = accelComboBox->currentIndex();
    switch (i) {
    case 0:
        prepareMessage1('A',0L,0);
    break;
    case 1:
        prepareMessage1('A',1L,0);
    break;
    case 2:
        prepareMessage1('A',2L,0);
    break;
    }
}

void Dialog::bLlegFull()
{
    prepareMessage1('K',15L,0);
}

void Dialog::bRlegFull()
{
    prepareMessage1('K',16L,0);
}

void Dialog::bTlgRight()
{
    prepareMessage1('K',17L,0);
}

void Dialog::bTlgCntr()
{
    prepareMessage1('K',18L,0);
}

void Dialog::bTlgLeft()
{
    prepareMessage1('K',19L,0);
}

void Dialog::bSetStepAngle()
{
    int i = stepAngleComboBox->currentIndex();
    switch (i) {
    case 0:
        prepareMessage1('K',20L,0);
    break;
    case 1:
        prepareMessage1('K',21L,0);
    break;
    case 2:
        prepareMessage1('K',22L,0);
    break;
    case 3:
        prepareMessage1('K',23L,0);
    break;
    case 4:
        prepareMessage1('K',24L,0);
    break;
    case 5:
        prepareMessage1('K',25L,0);
    break;
    case 6:
        prepareMessage1('K',26L,0);
    break;
    case 7:
        prepareMessage1('K',27L,0);
    break;
    }
}

void Dialog::bSetStepDepth()
{
    int i = stepDepthComboBox->currentIndex();
    switch (i) {
    case 0:
        prepareMessage1('K',28L,0);
    break;
    case 1:
        prepareMessage1('K',29L,0);
    break;
    case 2:
        prepareMessage1('K',30L,0);
    break;
    case 3:
        prepareMessage1('K',31L,0);
    break;
    case 4:
        prepareMessage1('K',32L,0);
    break;
    case 5:
        prepareMessage1('K',33L,0);
    break;
  }
}

void Dialog::bCalibration()
{
    prepareMessage1('K',34L,0);
}

void Dialog::showResponse(const QString &s)
{
    setControlsEnabled(true);
    trafficLabel->setText(tr("Обмен, transaction #%1:"
                             "\n\r-request: %2"
                             "\n\r-response: %3")
                          .arg(++transactionCount).arg(requestLineEdit->text()).arg(s));
}

void Dialog::processError(const QString &s)
{
    setControlsEnabled(true);
    statusLabel->setText(tr("Статус: выключен, %1.").arg(s));
    trafficLabel->setText(tr("Нет обмена."));
}

void Dialog::processTimeout(const QString &s)
{
    setControlsEnabled(true);
    statusLabel->setText(tr("Статус: Включен, %1.").arg(s));
    trafficLabel->setText(tr("Нет обмена."));
}

void Dialog::setControlsEnabled(bool enable)
{
    //thisPort.setBaudRate(SettingsPort.baudRate)
    runButton->setEnabled(enable);
    serialPortComboBox->setEnabled(enable);
    waitResponseSpinBox->setEnabled(enable);
    requestLineEdit->setEnabled(enable);
}
