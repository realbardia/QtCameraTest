#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVideoWidget>
#include <QCamera>
#include <QCameraInfo>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_listWidget_currentRowChanged(int currentRow);
    void on_resolutions_activated(int index);

private:
    Ui::MainWindow *ui;
    QVideoWidget *mVideo;
    QCamera *mCamera = nullptr;

    QList<QCameraInfo> mCameras;
};
#endif // MAINWINDOW_H
