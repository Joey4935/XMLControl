#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QMainWindow>
#include "timer.hpp"
#include <QDomDocument>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_bntFilePath_clicked();

    void on_bntStart_clicked();

    void on_bntStop_clicked();

private:
   static void writeXML();


private:
    Ui::MainWindow *ui;

    QString m_filePath;

    double x;
    double y;
    double z;

    Timer m_ExecuteTimer;

    static MainWindow *m_pThis;
};
#endif // MAINWINDOW_H
