#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QDomDocument>
#include <QFileDialog>

MainWindow *MainWindow::m_pThis = NULL;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    m_pThis = this;

    m_filePath = "D:/ActionData_01.xml";
    ui->setupUi(this);

    ui->editModelID->setText("10001");
    ui->editType->setText("2");
    ui->editTargetID->setText("1");
    ui->editTargetType->setText("1");

    ui->lineEdit->setText(m_filePath);

    //����="116.4795518"
    //γ��="39.9397301378"
    //�߳�="11.2894053692"
    x = 116.4795518;
    y = 39.9397301378;
    z = 11.2894053692;

    ui->edit_01->setText(QString::number(x,'f',10));
    ui->edit_02->setText(QString::number(y,'f',10));
    ui->edit_03->setText(QString::number(z,'f',10));


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_bntFilePath_clicked()
{
    m_filePath = QFileDialog::getOpenFileName(this);
    ui->lineEdit->setText(m_filePath);

}

void MainWindow::on_bntStart_clicked()
{

    m_ExecuteTimer.start(2000, std::bind(writeXML));	//�����һ��

}

void MainWindow::on_bntStop_clicked()
{
    m_ExecuteTimer.stop();
}

void MainWindow::writeXML()
{
    QDomDocument doc;
    // �ļ�ͷ
    QDomProcessingInstruction instruction = doc.createProcessingInstruction("xml", "xml version=\"1.0\" encoding=\"gb2312\" standalone=\"yes\" ");
    doc.appendChild(instruction);

    // ���һ���ڵ� (ѧ������)
    QDomElement studentsElement = doc.createElement("actions");
    // ���ѧ�����ϵ�����

    doc.appendChild(studentsElement);

    // ���ѧ��1
    QDomElement actions1 = doc.createElement("action");


    // �����Ϣ
    QDomElement id1 = doc.createElement("model_ID");
    QDomText idText1 = doc.createTextNode(m_pThis->ui->editModelID->text());

    id1.appendChild(idText1);
    actions1.appendChild(id1);

    QDomElement id2 = doc.createElement("type");
    QDomText idText2 = doc.createTextNode(m_pThis-> ui->editType->text());
    id2.appendChild(idText2);
    actions1.appendChild(id2);

    QDomElement id3 = doc.createElement("target_type");
    QDomText idText3 = doc.createTextNode(m_pThis->ui->editTargetType->text());
    id3.appendChild(idText3);
    actions1.appendChild(id3);


    QDomElement id4 = doc.createElement("target_ID");
    QDomText idText4 = doc.createTextNode(m_pThis->ui->editTargetID->text());
    id4.appendChild(idText4);
    actions1.appendChild(id4);


    QDomElement id5 = doc.createElement(QStringLiteral("���Ƶ��б�"));
    //QDomAttr
    id5.setAttribute(QStringLiteral("���Ƶ����"),"1");


    //��ȡ
    m_pThis->x = m_pThis->ui->edit_01->text().toDouble();
    m_pThis->y = m_pThis->ui->edit_02->text().toDouble();
    m_pThis->z = m_pThis->ui->edit_03->text().toDouble();

    m_pThis->x+=0.01;
    m_pThis->y+=0.01;
    m_pThis->z+=0.01;

    m_pThis->ui->edit_01->setText(QString::number(m_pThis->x,'f',10));
    m_pThis->ui->edit_02->setText(QString::number(m_pThis->y,'f',10));
    m_pThis->ui->edit_03->setText(QString::number(m_pThis->z,'f',10));

    QDomElement id5_1 = doc.createElement(QStringLiteral("���Ƶ�1"));
    id5_1.setAttribute(QStringLiteral("����"),  QString::number(m_pThis->x,'f',10) );
    id5_1.setAttribute(QStringLiteral("γ��"),  QString::number(m_pThis->y,'f',10) );
    id5_1.setAttribute(QStringLiteral("�߳�"),  QString::number(m_pThis->z,'f',10) );

    id5.appendChild(id5_1);

    actions1.appendChild(id5);

    studentsElement.appendChild(actions1);
    // �ļ�·��

    QFile file(m_pThis->m_filePath);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        return;
    }
    QTextStream out(&file);
    // ÿ��һ����ǰ��������ո�
    out.setCodec("GB2312");
    doc.save(out,QDomNode::EncodingFromDocument);
    file.close();
}
