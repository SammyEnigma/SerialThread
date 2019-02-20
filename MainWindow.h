#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Qt lib import
#include <QMainWindow>
#include <QMessageBox>

// JasonQt lib import
#include "JasonQt/JasonQt_SerialPort.h"

// UI imrtpo
#include "ui_MainWindow.h"

class MainWindow: public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *m_ui;
    JasonQt_SerialPort m_serialPort;

public:
    explicit MainWindow(QWidget *parent = NULL);

    ~MainWindow(void);

private slots:
    void refresh(void);

    void open(void);

    void close(void);

    void send(void);

    void accepted(const QByteArray data);

    void error(const QSerialPort::SerialPortError &error);
};

#endif // MAINWINDOW_H
