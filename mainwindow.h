#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QImage>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QImage InputPic; // Input Picture
    QImage OutputPic; // Output Picture
    const QString None = tr("无图片"); // Text for No Output Picture
    const QString Note = tr("左上角文件-打开本地图片"); // Text for No Input Picture
    bool HaveResult; // does InputPic exist
    bool HaveInput; // does OutputPic exist

private slots:
    void OpenPic(); // Load a New Picture
    void SaveResult(); // Save the Output Picture
    void Analyze(); // Get Output Picture
    void Clear(); // Clear Input & Output Picture
};
#endif // MAINWINDOW_H
