#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QFileDialog>
#include <QMessageBox>

/* default111 means debug mode */
#define default111

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    HaveResult = false;
    HaveInput = false;

    ui->pushButton->setDisabled(true); // set Analyse Button disabled

    /* setup toolBar */
    ui->toolBar->setMovable(false);
    ui->toolBar->setIconSize(QSize(30, 30));

    QAction *OpenAction = new QAction(tr("&打开本地图片"), this);
    OpenAction->setIcon(QIcon(":/src/folder-open.svg"));
    ui->toolBar->addAction(OpenAction);

    ui->toolBar->addSeparator();

    QAction *SaveAction = new QAction(tr("&保存输出结果"), this);
    SaveAction->setIcon(QIcon(":/src/download.svg"));
    ui->toolBar->addAction(SaveAction);

    ui->toolBar->addSeparator();

    QAction *AnalyzeAction = new QAction(tr("&分析"), this);
    AnalyzeAction->setIcon(QIcon(":/src/clockwise.svg"));
    ui->toolBar->addAction(AnalyzeAction);

    ui->toolBar->addSeparator();

    QAction *ClearAction = new QAction(tr("&关闭当前图片"), this);
    ClearAction->setIcon(QIcon(":/src/trash.svg"));
    ui->toolBar->addAction(ClearAction);

    /* connect MenuBar Actions to slots */
    connect(ui->action, SIGNAL(triggered()), this, SLOT(OpenPic()));
    connect(ui->action_2, SIGNAL(triggered()), this, SLOT(SaveResult()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(Analyze()));
    connect(ui->action_3, SIGNAL(triggered()), this, SLOT(Analyze()));
    connect(ui->action_4, SIGNAL(triggered()), this, SLOT(Clear()));

    /* connect ToolBar actions to slots */
    connect(OpenAction, SIGNAL(triggered()), this, SLOT(OpenPic()));
    connect(SaveAction, SIGNAL(triggered()), this, SLOT(SaveResult()));
    connect(AnalyzeAction, SIGNAL(triggered()), this, SLOT(Analyze()));
    connect(ClearAction, SIGNAL(triggered()), this, SLOT(Clear()));
}
/* Load Picture from local to InputPic and Show */
void MainWindow::OpenPic()
{
    QString NewPicPath = QFileDialog::getOpenFileName(this,
        tr("打开"), "", "Image (*.jpg *.png *.bmp)");
    if(!NewPicPath.isEmpty())
    {
        InputPic.load(NewPicPath);
        InputPic = InputPic.scaled(ui->label_4->size(), Qt::KeepAspectRatio,
                Qt::SmoothTransformation); // set picture addapted to label size with fixed ratio
        ui->label_4->resize(InputPic.size());
        ui->label_2->resize(InputPic.size());
        ui->label_4->setPixmap(QPixmap::fromImage(InputPic));
        ui->label_2->clear();
        ui->label_2->setText(None);
        HaveResult = false;
        HaveInput = true;
        ui->pushButton->setEnabled(true);
    }
    else {
        QMessageBox::critical(this, tr("错误提示"), tr("打开文件失败！"));
    }
}
/* save OutputPic to local */
void MainWindow::SaveResult()
{
    if(!HaveResult)
    {
        QMessageBox::information(this, tr("提示"), tr("当前无结果！"));
        return;
    }
    QString FileName = QFileDialog::getSaveFileName(this,
        tr("保存"), "Result.jpg", "Image (*.jpg *.png *.bmp)");
    if(FileName.length() > 0)
    {
        OutputPic.save(FileName);
    }
    else
    {
        QMessageBox::critical(this, tr("错误提示"), tr("保存文件失败！"));
    }
}
/* Get OutputPic */
void MainWindow::Analyze()
{
    if(!HaveInput)
    {
        QMessageBox::information(this, tr("提示"), tr("请打开一张图片！"));
        return;
    }
#ifdef default111
    // debug: let OutputPic = InputPic
    OutputPic = InputPic.copy();
#else
    // do whatever you want
    ;
#endif
    if(OutputPic.isNull()) // no Output
    {
        QMessageBox::critical(this, tr("错误提示"), tr("分析失败！"));
        return;
    }
    OutputPic = OutputPic.scaled(ui->label_4->size(), Qt::KeepAspectRatio,
            Qt::SmoothTransformation);
    ui->label_2->resize(OutputPic.size());
    ui->label_2->setPixmap(QPixmap::fromImage(OutputPic));
    HaveResult = true;
}
void MainWindow::Clear()
{
    if(!HaveInput)
    {
        QMessageBox::information(this, tr("提示"), tr("当前无图片！"));
        return;
    }
    ui->label_4->clear();
    ui->label_4->setText(Note);
    ui->label_2->clear();
    ui->label_2->setText(None);
    HaveResult = false;
    HaveInput = false;
    ui->pushButton->setDisabled(true);
}
MainWindow::~MainWindow()
{
    delete ui;
}

