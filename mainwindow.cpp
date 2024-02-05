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


    //信号与槽的链接
    connect(ui->newAction, &QAction::triggered, this, &MainWindow::newActionSlot);
    connect(ui->openAction, &QAction::triggered, this, &MainWindow::openActionSlot);
    connect(ui->saveAction, &QAction::triggered, this, &MainWindow::saveActionSlot);

    // 设置进程错误时的信号槽连接
    connect(pythonProcess, &QProcess::errorOccurred, this, &MainWindow::onPythonScriptError);
    // 设置 Python 脚本完成时的信号槽连接
    connect(pythonProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &MainWindow::onPythonScriptFinished);



    // 设置窗口标题
    this->setWindowTitle("综合测试");

    // 设置窗口图标
    this->setWindowIcon(QIcon("1704897787850.png"));

    //获取.py文件路径
    pythonScriptPath = ui->lineEdit->text(); // 请将此路径替换为实际路径


}

MainWindow::~MainWindow()
{
    delete ui;
}

//==================================================================================================================================================
//行为槽函数
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
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) // 尝试以只读和文本模式打开文件
        {
            QMessageBox::warning(this, "错误", "无法打开文件");
            return;
        }
        QByteArray ba = file.readAll(); // 读取文件的所有内容到字节数组中
        ui->textEdit->setText(QString(ba)); // 将字节数组的内容设置到文本编辑器中
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
//按钮槽函数

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
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) // 尝试以只读和文本模式打开文件
        {
            QMessageBox::warning(this, "错误", "无法打开文件");
            return;
        }
        QByteArray ba = file.readAll(); // 读取文件的所有内容到字节数组中
        ui->textEdit->setText(QString(ba)); // 将字节数组的内容设置到文本编辑器中
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


void MainWindow::on_ExecuteButton_clicked()
{
    QString filePath = ui->lineEdit->text();  // 有一个 QLineEdit 来输入文件路径

    if (!filePath.isEmpty())
    {
        //如果你有虚拟环境，指定虚拟环境中的 Python 解释器的完整路径
        QString pythonInterpreter = "py环境/venv/Scripts/python.exe";

        // 启动 Python 脚本
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
        QStringList values = output.split(' '); // 假设输出中的值由空格分隔

        // 确保values列表中有足够多的元素
        if(values.size() >= 4) {
            ui->lineEdit_a->setText(values.at(0));
            ui->lineEdit_b->setText(values.at(1));
            ui->lineEdit_c->setText(values.at(2));
            ui->lineEdit_d->setText(values.at(3));

//            //自适应版
//            ui->imagelabel1->setPixmap(QPixmap("图片/Channel_1.png"));
//            ui->imagelabel1->resize(ui->scrollArea->rect().size());
//            ui->scrollAreaWidgetContents->resize(ui->scrollArea->rect().size());
//            ui->imagelabel1->setScaledContents(true); // 如果需要，可以让图片自适应 QLabel 的大小

//            ui->imagelabel2->setPixmap(QPixmap("图片/Channel_2.png"));
//            ui->imagelabel2->resize(ui->scrollArea->rect().size());
//            ui->scrollAreaWidgetContents_3->resize(ui->scrollArea_2->rect().size());
//            ui->imagelabel2->setScaledContents(true); // 如果需要，可以让图片自适应 QLabel 的大小

            //无损版
            ui->imagelabel1->setPixmap(QPixmap("图片/Channel_1.png"));
            ui->imagelabel1->resize(QPixmap("图片/Channel_1.png").size());
            ui->scrollAreaWidgetContents->resize(ui->imagelabel1->rect().size());

            ui->imagelabel2->setPixmap(QPixmap("图片/Channel_2.png"));
            ui->imagelabel2->resize(QPixmap("图片/Channel_2.png").size());
            ui->scrollAreaWidgetContents_3->resize(ui->imagelabel2->rect().size());



        } else {
            // 错误处理: 输出不符合预期
            QMessageBox::warning(this, "Python Script Error", "Please check your .py file!");
        }
    }
}

//==================================================================================================================================================
//将python得到的图片展示到qt界面中



//==================================================================================================================================================
//检查进程
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
//图片展示
void MainWindow::on_comboBox_activated(int index)
{
//    //自适应版
//    ui->imagelabel1->resize(ui->scrollArea->rect().size());
//    ui->scrollAreaWidgetContents->resize(ui->scrollArea->rect().size());
//    ui->imagelabel1->setScaledContents(true); // 如果需要，可以让图片自适应 QLabel 的大小

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
//                ui->imagelabel1->clear(); // 如果没有匹配的选项，清除图片
//        }

    //无损版
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
//    //自适应版
//    ui->imagelabel2->resize(ui->scrollArea_2->rect().size());
//    ui->scrollAreaWidgetContents_3->resize(ui->scrollArea_2->rect().size());
//    ui->imagelabel2->setScaledContents(true); // 如果需要，可以让图片自适应 QLabel 的大小

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

    //无损版
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
                ui->imagelabel2->clear(); // 如果没有匹配的选项，清除图片

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

    QString folderPath = "图片"; // 设置要清空的文件夹路径
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

//    //自适应版
//    ui->imagelabel1->resize(ui->scrollArea->rect().size());
//    ui->scrollAreaWidgetContents->resize(ui->scrollArea->rect().size());
//    ui->imagelabel2->resize(ui->scrollArea_2->rect().size());
//    ui->scrollAreaWidgetContents_3->resize(ui->scrollArea_2->rect().size());

//    ui->imagelabel1->setScaledContents(true); // 如果需要，可以让图片自适应 QLabel 的大小
//    ui->imagelabel2->setScaledContents(true); // 如果需要，可以让图片自适应 QLabel 的大小

    //无损版
}
