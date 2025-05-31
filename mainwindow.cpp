#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QCameraViewfinderSettings>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mCameras = QCameraInfo::availableCameras();
    for (const auto &cam: mCameras)
        ui->listWidget->addItem(cam.description() + " " + cam.deviceName());

    mVideo = new QVideoWidget(this);

    ui->verticalLayout->addWidget(mVideo);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_listWidget_currentRowChanged(int row)
{
    if (mCamera)
    {
        mCamera->stop();
        delete mCamera;
        mCamera = nullptr;
    }

    row--;
    if (row < 0 || row >= mCameras.count())
        return;

    const auto cam = mCameras.at(row);


    mCamera = new QCamera(cam, this);
    mCamera->setViewfinder(mVideo);
    mCamera->setCaptureMode(QCamera::CaptureViewfinder);
    mCamera->exposure()->setExposureMode(QCameraExposure::ExposureAuto);
    mCamera->imageProcessing()->setWhiteBalanceMode(QCameraImageProcessing::WhiteBalanceAuto);

    connect(mCamera, &QCamera::statusChanged, this, [this](QCamera::Status status){
        if (status == QCamera::Status::LoadedStatus)
        {
            const auto resolutions = mCamera->supportedViewfinderResolutions();
            ui->resolutions->clear();

            if (resolutions.isEmpty())
            {
                mCamera->start();
                return;
            }

            int index = resolutions.size()-1;
            for (const auto &res: resolutions)
            {
                ui->resolutions->addItem(QStringLiteral("%1x%2").arg(res.width()).arg(res.height()), res);
                if (res.height() <= 800)
                    index = ui->resolutions->count()-1;
            }

            ui->resolutions->setCurrentIndex(index);
            on_resolutions_activated(index);
        }
    });

    mCamera->load();

}

void MainWindow::on_resolutions_activated(int index)
{
    mCamera->stop();
    auto settings = mCamera->viewfinderSettings();
    if (index < 0)
        settings.setResolution(800, 600);
    else
    {
        const auto size = ui->resolutions->currentData();
        settings.setResolution(size.toSize());
    }
    mCamera->setViewfinderSettings(settings);
    mCamera->start();
}

