#include "MainWindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    connect(m_ui->pushButton_refresh,   SIGNAL(clicked()), this, SLOT(refresh()));
    connect(m_ui->pushButton_open,      SIGNAL(clicked()), this, SLOT(open()));
    connect(m_ui->pushButton_close,     SIGNAL(clicked()), this, SLOT(close()));
    connect(m_ui->pushButton_send,      SIGNAL(clicked()), this, SLOT(send()));

    // 槽函数在主线程运行
    connect(&m_serialPort,              SIGNAL(accepted(QByteArray)), this, SLOT(accepted(QByteArray)));
    connect(&m_serialPort,              SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(error(QSerialPort::SerialPortError)));

    // 槽函数在串口工作线程运行（在本示例中不推荐使用这个，因为要操作GUI）
    QObject::connect(&m_serialPort, &JasonQt_SerialPort::accepted, this, &MainWindow::accepted, Qt::QueuedConnection);
    connect(&m_serialPort, &JasonQt_SerialPort::accepted, this, [&](QByteArray arr){

        qDebug() << __FUNCTION__ << arr << QThread::currentThreadId() ;
        this->accepted(arr);
    }, Qt::QueuedConnection);
//    connect(&m_serialPort,              SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(error(QSerialPort::SerialPortError)), Qt::DirectConnection);

    this->refresh();
}

MainWindow::~MainWindow(void)
{
    delete m_ui;
}

void MainWindow::refresh(void)
{
    m_ui->comboBox_availablePorts->clear();
    for(const auto &now: QSerialPortInfo::availablePorts())
    {
        m_ui->comboBox_availablePorts->addItem(now.portName());
    }

    m_ui->pushButton_open->setEnabled(m_ui->comboBox_availablePorts->count());
}

void MainWindow::open(void)
{
    if(m_serialPort.open(m_ui->comboBox_availablePorts->currentText(), m_ui->spinBox->value()))
    {
        m_ui->pushButton_open->setEnabled(false);
        m_ui->pushButton_close->setEnabled(true);
        m_ui->pushButton_refresh->setEnabled(false);
        m_ui->comboBox_availablePorts->setEnabled(false);
        m_ui->lineEdit_readySend->setEnabled(true);
        m_ui->pushButton_send->setEnabled(true);
    }
    else
    {
        QMessageBox::warning(this, "Open error", "Can open this serial port");
    }
}

void MainWindow::close(void)
{
    m_serialPort.close();

    m_ui->pushButton_open->setEnabled(true);
    m_ui->pushButton_close->setEnabled(false);
    m_ui->pushButton_refresh->setEnabled(true);
    m_ui->comboBox_availablePorts->setEnabled(true);
    m_ui->lineEdit_readySend->setEnabled(false);
    m_ui->pushButton_send->setEnabled(false);
}

void MainWindow::send(void)
{
    m_serialPort.send(m_ui->lineEdit_readySend->text().toLatin1());
    m_ui->textEdit_send->append(m_ui->lineEdit_readySend->text());
}

void MainWindow::accepted(const QByteArray data)
{
	qDebug() << __FUNCTION__ << data;
    m_ui->textEdit_accepted->append(QString(data));
}

void MainWindow::error(const QSerialPort::SerialPortError &error)
{
    QMessageBox::warning(this, "Serial error", QString("Serial error: %1").arg(error));
}
