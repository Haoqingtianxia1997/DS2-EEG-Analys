#include "mainwindow.h"
#include "ui_mainwindow.h"
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Seizure Scout");  //Set the window's title
    this->setWindowIcon(QIcon("./ds2_logo.png"));   //Set the window's logo

    ui->statusBar->setSizeGripEnabled(false);   //Disable window zoom

    statusLog = new QLabel("Ready.",this);  //Initialise status bar
    statusLog->setMinimumWidth(760);
    ui->statusBar->addWidget(statusLog);

    pro = new QProgressBar(this);   //Initialise progress bar
    ui->statusBar->addPermanentWidget(pro, 1);
    pro->setTextVisible(true);
    pro->setStyleSheet("QProgressBar { min-width: 300px; max-width: 300px; min-height: 10px; max-height: 10px; }");
    pro->setValue(0);

    Py_Initialize();    //Initialise the Python compiler
    PyRun_SimpleString("import sys");   //python compiler environment configuration
    PyRun_SimpleString("sys.argv = ['python.py']");
    PyRun_SimpleString("sys.path.append('F:/python380/')");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_selectPatientButton_clicked()
{
    qint32 count = pro->value();    //Reset progress bar
    count = 0;
    pro->setValue(count);
    statusLog->setText(QString::asprintf("Raw patient data being selected..."));    //Reset status bar
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this, tr("file"), "", tr("edf file(*.edf);;csv file(*.csv);;All file(*.*)"));
    //Select and get the file path
    if (!fileName.isNull())
    {
        QFile file(fileName);
        if(!file.open(QFile::ReadOnly|QFile::Text))
        {
            QMessageBox::warning(this, tr("Error"), tr("read file error:&1").arg(file.errorString()));
            return;
        }
        QTextStream in(&file);
        QApplication::setOverrideCursor(Qt::WaitCursor);
        ui->pt_fileName->setText(fileName.toUtf8());    //Display the selected file path
        statusLog->setText("<" + fileName + ">" + " is selected.");
        QApplication::restoreOverrideCursor();
    }
}

void MainWindow::on_icPatientButton_clicked()
{
    qint32 count = pro->value();    //Reset progress bar
    count = 0;
    pro->setValue(count);
    statusLog->setText(QString::asprintf("Start checking raw data..."));    //Reset status bar
    QString address = ui->pt_fileName->text();
    count = count +5;
    pro->setValue(count);
    PyObject* pModule = PyImport_ImportModule("load_data"); //External .py module pointer
    PyObject* pFunadd = PyObject_GetAttrString(pModule, "load_single_data");    //Pointer to functions within the external .py module
    count = count +5;
    pro->setValue(count);
    PyObject* args = PyTuple_New(1);    //Incoming parameters needed for Python functions
    PyObject* arg1 = Py_BuildValue("s", string(address.toLocal8Bit()).c_str());
    PyTuple_SetItem(args, 0, arg1);
    count = count +5;
    pro->setValue(count);
    PyObject* pyValue = PyEval_CallObject(pFunadd, args);   //Calling external Python functions and pass the return value
    count = count +50;
    pro->setValue(count);
    int ok, ch_num;
    char* d_size;
    float sf, data_len;
    char* rs;
    ok = PyArg_ParseTuple(pyValue, "isffs", &ch_num, &d_size, &sf, &data_len, &rs); //Receive the return value into a C++ type variable
    count = count +15;
    pro->setValue(count);
    PyGC_Collect(); //Free the memory that used by calls external .py modules

    QString freq = " Hz", t = " s";
    //Display the results
    if (ok) {
        ui->pt_check->setText("standard");
        ui->ch_number->setText(QString::number(ch_num));
        ui->measurement->setText("10-20 System");
        ui->data_size->setText(d_size);
        ui->s_f->setText(QString::number(sf, 'f', 2).append(freq));
        ui->time_total->setText(QString::number(data_len, 'f', 2).append(t));
        ui->re_sys->setText(rs);
    }
    count = count +20;
    pro->setValue(count);
    statusLog->setText(QString::asprintf("Check raw data successful."));
}

void MainWindow::on_selectModelButton_clicked()
{
    qint32 count = pro->value();    //Reset progress bar
    count = 0;
    pro->setValue(count);
    statusLog->setText(QString::asprintf("Model being selected..."));   //Reset status bar
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this, tr("file"), "", tr("pkl file(*.pkl);;All file(*.*)"));
    //Select and get the file path
    if (!fileName.isNull())
    {
        QFile file(fileName);
        if(!file.open(QFile::ReadOnly|QFile::Text))
        {
            QMessageBox::warning(this, tr("Error"), tr("read file error:&1").arg(file.errorString()));
            return;
        }
        QTextStream in(&file);
        QApplication::setOverrideCursor(Qt::WaitCursor);
        ui->model_fileName->setText(fileName.toUtf8()); //Display the selected file path
        statusLog->setText("<" + fileName + ">" + " is selected.");
        QApplication::restoreOverrideCursor();
    }
}

void MainWindow::on_icModelButton_clicked()
{
    pro->setValue(0);   //Reset progress bar
    statusLog->setText(QString::asprintf("Start checking model..."));   //Reset status bar
    QString address = ui->model_fileName->text();
    pro->setValue(5);
    PyObject* pModule = PyImport_ImportModule("load_model");    //External .py module pointer
    PyObject* pFunadd = PyObject_GetAttrString(pModule, "load_singel_model");   //Pointer to functions within the external .py module
    pro->setValue(10);
    PyObject* args = PyTuple_New(1);    //Incoming parameters needed for Python functions
    PyObject* arg1 = Py_BuildValue("s", string(address.toLocal8Bit()).c_str());
    PyTuple_SetItem(args, 0, arg1);
    pro->setValue(15);
    PyObject* pyValue = PyEval_CallObject(pFunadd, args);   //Calling external Python functions and pass the return value
    pro->setValue(65);
    int ok, f_dim;
    char* core;
    char* l_dim, * subk1, * subk2, * subk3, * subk4, * subk5;
    ok = PyArg_ParseTuple(pyValue, "sissssss", &core, &f_dim, &l_dim, &subk1, &subk2, &subk3, &subk4, &subk5);  //Receive the return value into a C++ type variable
    pro->setValue(80);
    PyGC_Collect(); //Free the memory that used by calls external .py modules
    //Display the results
    if (ok) {
        ui->model_check->setText("standard");
        ui->model_k->setText(core);
        ui->feature_d->setText(QString::number(f_dim));
        ui->label_d->setText(l_dim);
        ui->label_k1->setText(subk1);
        ui->label_k2->setText(subk2);
        ui->label_k3->setText(subk3);
        ui->label_k4->setText(subk4);
        ui->label_k5->setText(subk5);
    }
    pro->setValue(100);
    statusLog->setText(QString::asprintf("Check model successful."));
}

void MainWindow::on_testButton_clicked()
{
    pro->setValue(0);   //Reset progress bar
    statusLog->setText(QString::asprintf("Start testing..."));  //Reset status bar
    QString address_d = ui->pt_fileName->text();
    QString address_m = ui->model_fileName->text();
    pro->setValue(5);
    PyObject* pModule = PyImport_ImportModule("predict");   //External .py module pointer
    PyObject* pFunadd = PyObject_GetAttrString(pModule, "epilepsy_detector");   //Pointer to functions within the external .py module
    pro->setValue(10);
    PyObject* args = PyTuple_New(1);    //Incoming parameters needed for Python functions
    PyObject* arg0 = Py_BuildValue("s", string(address_d.toLocal8Bit()).c_str());
    PyTuple_SetItem(args, 0, arg0);
    pro->setValue(15);
    PyObject* pyValue = PyEval_CallObject(pFunadd, args);   //Calling external Python functions and pass the return value
    pro->setValue(55);
    int ok, flag;
    float result_conf;
    char* result_seiz;
    ok = PyArg_ParseTuple(pyValue, "sfi", &result_seiz, &result_conf, &flag);   //Receive the return value into a C++ type variable
    pro->setValue(70);
    PyGC_Collect(); //Free the memory that used by calls external .py modules
    //Display the results
    if (ok) {
        ui->result->setText(result_seiz);
        if (flag){
            QPalette pal;
            pal.setColor(QPalette::Text, QColor("red"));
            ui->result->setPalette(pal);
        }
        ui->conf->setText(QString::number(result_conf, 'f', 3));
    }
    //Show psd topological map
    QString PSD_GM = "./cache/psd_gm.png";
    show_image_qLabel(PSD_GM, ui->label_psd_dm);
    pro->setValue(80);
    //Show time domain signals of two channels
    QString ch_sig_1 = "./cache/channel_1.png";
    show_image_scrollArea(ch_sig_1, ui->label_ch_up, ui->scrollArea_ch_up);
    QString ch_sig_2 = "./cache/channel_2.png";
    show_image_scrollArea(ch_sig_2, ui->label_ch_down, ui->scrollArea_ch_down);
    pro->setValue(90);
    //Show psd plot
    QString PSD_FM = "./cache/psd_fm.png";
    show_image_scrollArea(PSD_FM, ui->label_psd_fm, ui->scrollArea_psd_fm);
    pro->setValue(100);
    statusLog->setText(QString::asprintf("Test successful."));
}

void MainWindow::on_exportButton_clicked()
{
    pro->setValue(0);   //Reset progress bar
    statusLog->setText(QString::asprintf("Start exporting..."));    //Reset status bar
    QString address_d = ui->pt_fileName->text();
    QString seiz_result = ui->result->text();
    QString confidence = ui->conf->text();
    pro->setValue(5);
    PyObject* pModule = PyImport_ImportModule("export");    //External .py module pointer
    PyObject* pFunadd = PyObject_GetAttrString(pModule, "save_result_csv"); //Pointer to functions within the external .py module
    pro->setValue(15);
    PyObject* args = PyTuple_New(3);    //Incoming parameters needed for Python functions
    PyObject* arg0 = Py_BuildValue("s", string(seiz_result.toLocal8Bit()).c_str());
    PyObject* arg1 = Py_BuildValue("f", confidence.toFloat());
    PyObject* arg2 = Py_BuildValue("s", string(address_d.toLocal8Bit()).c_str());
    PyTuple_SetItem(args, 0, arg0);
    PyTuple_SetItem(args, 1, arg1);
    PyTuple_SetItem(args, 2, arg2);
    pro->setValue(60);
    PyObject* pyValue = PyEval_CallObject(pFunadd, args);   //Hier is no return value
    pro->setValue(100);
    statusLog->setText(QString::asprintf("Export successful."));
}

void MainWindow::on_comboBox_up_activated(int index)
{
    QString ch_sig = "./cache/channel_1.png";
    //Use the drop-down menus to select signal images for different channels
    switch (index) {
        case 0:
            ch_sig = "./cache/channel_1.png";
            break;
        case 1:
            ch_sig = "./cache/channel_2.png";
            break;
        case 2:
            ch_sig = "./cache/channel_3.png";
            break;
        case 3:
            ch_sig = "./cache/channel_4.png";
            break;
        case 4:
            ch_sig = "./cache/channel_5.png";
            break;
        case 5:
            ch_sig = "./cache/channel_6.png";
            break;
        case 6:
            ch_sig = "./cache/channel_7.png";
            break;
        case 7:
            ch_sig = "./cache/channel_8.png";
            break;
        case 8:
            ch_sig = "./cache/channel_9.png";
            break;
        default:
            break;
    }
    show_image_scrollArea(ch_sig, ui->label_ch_up, ui->scrollArea_ch_up);
}

void MainWindow::on_comboBox_down_activated(int index)
{
    QString ch_sig = "./cache/channel_2.png";
    //Use the drop-down menus to select signal images for different channels
    switch (index) {
        case 0:
            ch_sig = "./cache/channel_2.png";
            break;
        case 1:
            ch_sig = "./cache/channel_1.png";
            break;
        case 2:
            ch_sig = "./cache/channel_3.png";
            break;
        case 3:
            ch_sig = "./cache/channel_4.png";
            break;
        case 4:
            ch_sig = "./cache/channel_5.png";
            break;
        case 5:
            ch_sig = "./cache/channel_6.png";
            break;
        case 6:
            ch_sig = "./cache/channel_7.png";
            break;
        case 7:
            ch_sig = "./cache/channel_8.png";
            break;
        case 8:
            ch_sig = "./cache/channel_9.png";
            break;
        default:
            break;
    }
    show_image_scrollArea(ch_sig, ui->label_ch_down, ui->scrollArea_ch_down);
}

void MainWindow::on_pushButton_clear_clicked()
{
    //Clear all content on the page
    ui->pt_fileName->clear();
    ui->pt_check->clear();
    ui->ch_number->clear();
    ui->measurement->clear();
    ui->data_size->clear();
    ui->time_total->clear();
    ui->s_f->clear();
    ui->re_sys->clear();
    ui->model_fileName->clear();
    ui->model_check->clear();
    ui->model_k->clear();
    ui->label_k1->clear();
    ui->label_k2->clear();
    ui->label_k3->clear();
    ui->label_k4->clear();
    ui->label_k5->clear();
    ui->feature_d->clear();
    ui->label_d->clear();
    ui->result->clear();
    ui->conf->clear();
    ui->label_psd_dm->clear();
    ui->label_ch_up->clear();
    ui->label_ch_down->clear();
    ui->label_psd_fm->clear();

    ui->comboBox_up->setCurrentIndex(0);
    ui->comboBox_down->setCurrentIndex(0);
}

void show_image_scrollArea(QString path, QLabel* label_show, QScrollArea* scra_show)
{
    //Display images in QscrollArea
    QImage* this_img = new QImage;
    this_img->load(path);
    label_show->setPixmap(QPixmap::fromImage(*this_img));
    label_show->adjustSize();
    scra_show->setWidget(label_show);
}

void show_image_qLabel(QString path, QLabel* label_show)
{
    //Display images in Qlabel
    QImage* this_img = new QImage, * this_img_scal = new QImage;
    this_img->load(path);
    int qlabel_width = label_show->size().width();
    int qlabel_height = label_show->size().height();
    * this_img_scal = this_img->scaled(qlabel_width, qlabel_height, Qt::IgnoreAspectRatio);
    label_show->setPixmap(QPixmap::fromImage(* this_img_scal));
}

