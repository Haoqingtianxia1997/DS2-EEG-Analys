#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent), ui(new Ui::MainWindow), pythonProcess(new QProcess(this))

{
    ui->setupUi(this);



    connect(ui->newAction, &QAction::triggered, this, &MainWindow::newActionSlot);
    connect(ui->openAction, &QAction::triggered, this, &MainWindow::openActionSlot);
    connect(ui->saveAction, &QAction::triggered, this, &MainWindow::saveActionSlot);

    connect(pythonProcess, &QProcess::errorOccurred, this, &MainWindow::onPythonScriptError);

    connect(pythonProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &MainWindow::onPythonScriptFinished);



    this->setWindowTitle("综合测试");


    this->setWindowIcon(QIcon("1704897787850.png"));

    pythonScriptPath = ui->lineEdit->text(); 


}

MainWindow::~MainWindow()
{
    delete ui;
}

//==================================================================================================================================================

void MainWindow::newActionSlot()
{
    ui->textEdit->clear();
    ui->lineEdit->clear();
    ui->lineEdit_a->clear();
    ui->lineEdit_b->clear();
    ui->lineEdit_c->clear();
    ui->lineEdit_d->clear();
    this->setWindowTitle("新建文本文档.txt");
}


void MainWindow::openActionSlot()
{
    QString fileName = QFileDialog::getOpenFileName(this, "选择一个文件",
                        QCoreApplication::applicationFilePath(), "*.py");

    if (fileName.isEmpty())
    {
        QMessageBox::warning(this, "警告", "请选择一个文件");
    }
    else
    {
        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::warning(this, "错误", "无法打开文件");
            return;
        }
        QByteArray ba = file.readAll(); 
        ui->textEdit->setText(QString(ba)); 
        file.close();
    }
}


void MainWindow::saveActionSlot()
{
    QString fileName = QFileDialog::getSaveFileName(this, "选择一个文件",
                        QCoreApplication::applicationFilePath(), "*.py");

    if (fileName.isEmpty())
    {
        QMessageBox::warning(this, "警告", "请选择一个文件");
    }
    else
    {
        QFile file(fileName);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) // 尝试以只写和文本模式打开文件
        {
            QMessageBox::warning(this, "错误", "无法打开文件");
            return;
        }
        QByteArray ba;
        ba.append(ui->textEdit->toPlainText());
        file.write(ba);
        file.close();

    }
}


//==================================================================================================================================================


void MainWindow::on_SelectButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "选择一个文件",
                        QCoreApplication::applicationFilePath(), "*.py");

    if (fileName.isEmpty())
    {
        QMessageBox::warning(this, "警告", "请选择一个文件");
    }
    else
    {
        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) 
        {
            QMessageBox::warning(this, "错误", "无法打开文件");
            return;
        }
        QByteArray ba = file.readAll(); 
        ui->textEdit->setText(QString(ba)); 
        ui->lineEdit->setText(fileName);
        file.close();
    }
}


void MainWindow::on_SaveButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "选择一个文件",
                        QCoreApplication::applicationFilePath(), "*.py");

    if (fileName.isEmpty())
    {
        QMessageBox::warning(this, "警告", "请选择一个文件");
    }
    else
    {
        QFile file(fileName);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) 
        {
            QMessageBox::warning(this, "错误", "无法打开文件");
            return;
        }
        QByteArray ba;
        ba.append(ui->textEdit->toPlainText());
        file.write(ba);
        file.close();

    }
}


void MainWindow::on_ExecuteButton_clicked()
{
    QString filePath = ui->lineEdit->text(); 

    if (!filePath.isEmpty())
    {
        
        QString pythonInterpreter = "py环境/venv/Scripts/python.exe";


        pythonProcess->start(pythonInterpreter, QStringList() << filePath);




    }
}

void MainWindow::on_ExitButton_clicked()
{
    this->close(); // 关闭窗口
}



//==================================================================================================================================================
void MainWindow::onPythonScriptFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    Q_UNUSED(exitCode);
    Q_UNUSED(exitStatus);

    QProcess *process = qobject_cast<QProcess *>(sender());
    if (process)
    {
        QString output = process->readAllStandardOutput();
        QStringList values = output.split(' '); 
       
        if(values.size() >= 4) {
            ui->lineEdit_a->setText(values.at(0));
            ui->lineEdit_b->setText(values.at(1));
            ui->lineEdit_c->setText(values.at(2));
            ui->lineEdit_d->setText(values.at(3));

//  
//            ui->imagelabel1->setPixmap(QPixmap("图片/Channel_1.png"));
//            ui->imagelabel1->resize(ui->scrollArea->rect().size());
//            ui->scrollAreaWidgetContents->resize(ui->scrollArea->rect().size());
//            ui->imagelabel1->setScaledContents(true); 

//            ui->imagelabel2->setPixmap(QPixmap("图片/Channel_2.png"));
//            ui->imagelabel2->resize(ui->scrollArea->rect().size());
//            ui->scrollAreaWidgetContents_3->resize(ui->scrollArea_2->rect().size());
//            ui->imagelabel2->setScaledContents(true); 

          
            ui->imagelabel1->setPixmap(QPixmap("图片/Channel_1.png"));
            ui->imagelabel1->resize(QPixmap("图片/Channel_1.png").size());
            ui->scrollAreaWidgetContents->resize(ui->imagelabel1->rect().size());

            ui->imagelabel2->setPixmap(QPixmap("图片/Channel_2.png"));
            ui->imagelabel2->resize(QPixmap("图片/Channel_2.png").size());
            ui->scrollAreaWidgetContents_3->resize(ui->imagelabel2->rect().size());



        } else {
           
            QMessageBox::warning(this, "Python Script Error", "Please check your .py file!");
        }
    }
}

//==================================================================================================================================================




//==================================================================================================================================================

void MainWindow::onPythonScriptError(QProcess::ProcessError error)
{
    switch (error) {
        case QProcess::FailedToStart:
            QMessageBox::critical(this, "错误", "进程启动失败，可能是因为没有找到文件或权限不足。");
            break;
        case QProcess::Crashed:
            QMessageBox::critical(this, "错误", "进程崩溃了。");
            break;
        case QProcess::Timedout:
            QMessageBox::critical(this, "错误", "进程操作超时。");
            break;
        case QProcess::WriteError:
            QMessageBox::critical(this, "错误", "写入进程时发生错误。");
            break;
        case QProcess::ReadError:
            QMessageBox::critical(this, "错误", "从进程读取时发生错误。");
            break;
        case QProcess::UnknownError:
            QMessageBox::critical(this, "错误", "发生未知错误。");
            break;
    }
}

//==================================================================================================================================================

void MainWindow::on_comboBox_activated(int index)
{
//
//    ui->imagelabel1->resize(ui->scrollArea->rect().size());
//    ui->scrollAreaWidgetContents->resize(ui->scrollArea->rect().size());
//    ui->imagelabel1->setScaledContents(true);
//    switch(index) {
//            case 0: // 对应 "chl1"
//                ui->imagelabel1->setPixmap(QPixmap("图片/Channel_1.png"));

//                break;
//            case 1: // 对应 "chl2"
//                ui->imagelabel1->setPixmap(QPixmap("图片/Channel_2.png"));

//                break;
//            case 2: // 对应 "chl3"
//                ui->imagelabel1->setPixmap(QPixmap("图片/Channel_3.png"));

//                break;
//            case 3: // 对应 "chl4"
//                ui->imagelabel1->setPixmap(QPixmap("图片/Channel_4.png"));

//                break;
//            case 4: // 对应 "chl5"
//                ui->imagelabel1->setPixmap(QPixmap("图片/Channel_5.png"));

//                break;
//            case 5: // 对应 "chl6"
//                ui->imagelabel1->setPixmap(QPixmap("图片/Channel_6.png"));

//                break;
//            case 6: // 对应 "chl7"
//                ui->imagelabel1->setPixmap(QPixmap("图片/Channel_7.png"));

//                break;
//            case 7: // 对应 "chl8"
//                ui->imagelabel1->setPixmap(QPixmap("图片/Channel_8.png"));

//                break;
//            case 8: // 对应 "chl9"
//                ui->imagelabel1->setPixmap(QPixmap("图片/Channel_9.png"));

//                break;
//            case 9: // 对应 "chl10"
//                ui->imagelabel1->setPixmap(QPixmap("图片/Channel_10.png"));

//                break;
//            case 10: // 对应 "chl11"
//                ui->imagelabel1->setPixmap(QPixmap("图片/Channel_11.png"));

//                break;
//            default:
//                ui->imagelabel1->clear(); 
//        }


    switch(index) {
            case 0: // 对应 "chl1"
                ui->imagelabel1->setPixmap(QPixmap("图片/Channel_1.png"));
                ui->imagelabel1->resize(QPixmap("图片/Channel_1.png").size());
                ui->scrollAreaWidgetContents->resize(ui->imagelabel1->rect().size());
                break;
            case 1: // 对应 "chl2"
                ui->imagelabel1->setPixmap(QPixmap("图片/Channel_2.png"));
                ui->imagelabel1->resize(QPixmap("图片/Channel_2.png").size());
                ui->scrollAreaWidgetContents->resize(ui->imagelabel1->rect().size());
                break;
            case 2: // 对应 "chl3"
                ui->imagelabel1->setPixmap(QPixmap("图片/Channel_3.png"));
                ui->imagelabel1->resize(QPixmap("图片/Channel_3.png").size());
                ui->scrollAreaWidgetContents->resize(ui->imagelabel1->rect().size());
                break;
            case 3: // 对应 "chl4"
                ui->imagelabel1->setPixmap(QPixmap("图片/Channel_4.png"));
                ui->imagelabel1->resize(QPixmap("图片/Channel_4.png").size());
                ui->scrollAreaWidgetContents->resize(ui->imagelabel1->rect().size());
                break;
            case 4: // 对应 "chl5"
                ui->imagelabel1->setPixmap(QPixmap("图片/Channel_5.png"));
                ui->imagelabel1->resize(QPixmap("图片/Channel_5.png").size());
                ui->scrollAreaWidgetContents->resize(ui->imagelabel1->rect().size());
                break;
            case 5: // 对应 "chl6"
                ui->imagelabel1->setPixmap(QPixmap("图片/Channel_6.png"));
                ui->imagelabel1->resize(QPixmap("图片/Channel_6.png").size());
                ui->scrollAreaWidgetContents->resize(ui->imagelabel1->rect().size());
                break;
            case 6: // 对应 "chl7"
                ui->imagelabel1->setPixmap(QPixmap("图片/Channel_7.png"));
                ui->imagelabel1->resize(QPixmap("图片/Channel_7.png").size());
                ui->scrollAreaWidgetContents->resize(ui->imagelabel1->rect().size());
                break;
            case 7: // 对应 "chl8"
                ui->imagelabel1->setPixmap(QPixmap("图片/Channel_8.png"));
                ui->imagelabel1->resize(QPixmap("图片/Channel_8.png").size());
                ui->scrollAreaWidgetContents->resize(ui->imagelabel1->rect().size());
                break;
            case 8: // 对应 "chl9"
                ui->imagelabel1->setPixmap(QPixmap("图片/Channel_9.png"));
                ui->imagelabel1->resize(QPixmap("图片/Channel_9.png").size());
                ui->scrollAreaWidgetContents->resize(ui->imagelabel1->rect().size());
                break;
            case 9: // 对应 "chl10"
                ui->imagelabel1->setPixmap(QPixmap("图片/Channel_10.png"));
                ui->imagelabel1->resize(QPixmap("图片/Channel_10.png").size());
                ui->scrollAreaWidgetContents->resize(ui->imagelabel1->rect().size());
                break;
            case 10: // 对应 "chl11"
                ui->imagelabel1->setPixmap(QPixmap("图片/Channel_11.png"));
                ui->imagelabel1->resize(QPixmap("图片/Channel_11.png").size());
                ui->scrollAreaWidgetContents->resize(ui->imagelabel1->rect().size());
                break;
            default:
                ui->imagelabel1->clear(); // 如果没有匹配的选项，清除图片
        }

}





void MainWindow::on_comboBox_2_activated(int index)
{
//   
//    ui->imagelabel2->resize(ui->scrollArea_2->rect().size());
//    ui->scrollAreaWidgetContents_3->resize(ui->scrollArea_2->rect().size());
//    ui->imagelabel2->setScaledContents(true); 
//    switch(index) {
//        case 0: // 对应 "chl1"
//            ui->imagelabel2->setPixmap(QPixmap("图片/Channel_2.png"));

//            break;
//        case 1: // 对应 "chl2"
//            ui->imagelabel2->setPixmap(QPixmap("图片/Channel_1.png"));

//            break;
//        case 2: // 对应 "chl3"
//            ui->imagelabel2->setPixmap(QPixmap("图片/Channel_3.png"));

//            break;
//        case 3: // 对应 "chl4"
//            ui->imagelabel2->setPixmap(QPixmap("图片/Channel_4.png"));

//            break;
//        case 4: // 对应 "chl5"
//            ui->imagelabel2->setPixmap(QPixmap("图片/Channel_5.png"));

//            break;
//        case 5: // 对应 "chl6"
//            ui->imagelabel2->setPixmap(QPixmap("图片/Channel_6.png"));

//            break;
//        case 6: // 对应 "chl7"
//            ui->imagelabel2->setPixmap(QPixmap("图片/Channel_7.png"));

//            break;
//        case 7: // 对应 "chl8"
//            ui->imagelabel2->setPixmap(QPixmap("图片/Channel_8.png"));

//            break;
//        case 8: // 对应 "chl9"
//            ui->imagelabel2->setPixmap(QPixmap("图片/Channel_9.png"));

//            break;
//        case 9: // 对应 "chl10"
//            ui->imagelabel2->setPixmap(QPixmap("图片/Channel_10.png"));

//            break;
//        case 10: // 对应 "chl11"
//            ui->imagelabel2->setPixmap(QPixmap("图片/Channel_11.png"));

//            break;
//            default:
//                ui->imagelabel2->clear(); // 如果没有匹配的选项，清除图片
//        }

   
    switch(index) {
            case 0: // 对应 "chl1"
                ui->imagelabel2->setPixmap(QPixmap("图片/Channel_2.png"));
                ui->imagelabel2->resize(QPixmap("图片/Channel_2.png").size());
                ui->scrollAreaWidgetContents->resize(ui->imagelabel1->rect().size());
                break;
            case 1: // 对应 "chl2"
                ui->imagelabel2->setPixmap(QPixmap("图片/Channel_1.png"));
                ui->imagelabel2->resize(QPixmap("图片/Channel_1.png").size());
                ui->scrollAreaWidgetContents->resize(ui->imagelabel1->rect().size());
                break;
            case 2: // 对应 "chl3"
                ui->imagelabel2->setPixmap(QPixmap("图片/Channel_3.png"));
                ui->imagelabel2->resize(QPixmap("图片/Channel_3.png").size());
                ui->scrollAreaWidgetContents->resize(ui->imagelabel1->rect().size());
                break;
            case 3: // 对应 "chl4"
                ui->imagelabel2->setPixmap(QPixmap("图片/Channel_4.png"));
                ui->imagelabel2->resize(QPixmap("图片/Channel_4.png").size());
                ui->scrollAreaWidgetContents->resize(ui->imagelabel1->rect().size());
                break;
            case 4: // 对应 "chl5"
                ui->imagelabel2->setPixmap(QPixmap("图片/Channel_5.png"));
                ui->imagelabel2->resize(QPixmap("图片/Channel_5.png").size());
                ui->scrollAreaWidgetContents->resize(ui->imagelabel1->rect().size());
                break;
            case 5: // 对应 "chl6"
                ui->imagelabel2->setPixmap(QPixmap("图片/Channel_6.png"));
                ui->imagelabel2->resize(QPixmap("图片/Channel_6.png").size());
                ui->scrollAreaWidgetContents->resize(ui->imagelabel1->rect().size());
                break;
            case 6: // 对应 "chl7"
                ui->imagelabel2->setPixmap(QPixmap("图片/Channel_7.png"));
                ui->imagelabel2->resize(QPixmap("图片/Channel_7.png").size());
                ui->scrollAreaWidgetContents->resize(ui->imagelabel1->rect().size());
                break;
            case 7: // 对应 "chl8"
                ui->imagelabel2->setPixmap(QPixmap("图片/Channel_8.png"));
                ui->imagelabel2->resize(QPixmap("图片/Channel_8.png").size());
                ui->scrollAreaWidgetContents->resize(ui->imagelabel1->rect().size());
                break;
            case 8: // 对应 "chl9"
                ui->imagelabel2->setPixmap(QPixmap("图片/Channel_9.png"));
                ui->imagelabel2->resize(QPixmap("图片/Channel_9.png").size());
                ui->scrollAreaWidgetContents->resize(ui->imagelabel1->rect().size());
                break;
            case 9: // 对应 "chl10"
                ui->imagelabel2->setPixmap(QPixmap("图片/Channel_10.png"));
                ui->imagelabel2->resize(QPixmap("图片/Channel_10.png").size());
                ui->scrollAreaWidgetContents->resize(ui->imagelabel1->rect().size());
                break;
            case 10: // 对应 "chl11"
                ui->imagelabel2->setPixmap(QPixmap("图片/Channel_11.png"));
                ui->imagelabel2->resize(QPixmap("图片/Channel_11.png").size());
                ui->scrollAreaWidgetContents->resize(ui->imagelabel1->rect().size());
                break;
            default:
                ui->imagelabel2->clear(); 

            }

}


//==================================================================================================================================================
//clear

void MainWindow::on_clearButton_clicked()
{
    ui->comboBox->setCurrentIndex(0);
    ui->comboBox_2->setCurrentIndex(0);
    ui->imagelabel1->clear();
    ui->imagelabel2->clear();
    ui->textEdit->clear();
    ui->lineEdit->clear();
    ui->lineEdit_a->clear();
    ui->lineEdit_b->clear();
    ui->lineEdit_c->clear();
    ui->lineEdit_d->clear();

    QString folderPath = "图片"; 
    QDir dir(folderPath);

    dir.setFilter(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    QFileInfoList fileList = dir.entryInfoList();

    foreach (QFileInfo fileInfo, fileList) {
        if (fileInfo.isDir()) {
            QDir subDir(fileInfo.absoluteFilePath());
            subDir.removeRecursively();
        } else {
            QFile file(fileInfo.absoluteFilePath());
            file.remove();
        }
    }
}

//==================================================================================================================================================
void MainWindow::resizeEvent(QResizeEvent *event)
{

    QRect re= this->rect();
    int w=re.width();
    int h=re.height();
    ui->groupBox_4->setGeometry(5, 5, (w-20)/2, h*0.95);
    ui->groupBox_5->setGeometry(w/2+5, 5, (w-20)/2, h*0.95);


    ui->imagelabel1->setMargin(5);
    ui->imagelabel2->setMargin(5);


//    ui->imagelabel1->resize(ui->scrollArea->rect().size());
//    ui->scrollAreaWidgetContents->resize(ui->scrollArea->rect().size());
//    ui->imagelabel2->resize(ui->scrollArea_2->rect().size());
//    ui->scrollAreaWidgetContents_3->resize(ui->scrollArea_2->rect().size());

//    ui->imagelabel1->setScaledContents(true); 
//    ui->imagelabel2->setScaledContents(true); 

}
