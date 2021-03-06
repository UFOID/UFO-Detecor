#ifndef MAINWINDOW_H
#define MAINWINDOW_H
/*
 * UFO Detector | www.UFOID.net
 *
 * Copyright (C) 2016 UFOID
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "actualdetector.h"
#include "config.h"
#include "updateapplicationdialog.h"
#include "clickablelabel.h"
#include "videowidget.h"
#include "camera.h"
#include "settingsdialog.h"
#include "imageexplorer.h"
#include "videouploaderdialog.h"
#include "planechecker.h"
#include "datamanager.h"
#include <QMainWindow>
#include <QModelIndex>
#include <QDomDocument>
#include <QFile>
#include <QListWidgetItem>
#include <QMenu>
#include <iostream>
#include <QTime>
#include <opencv2/imgproc/imgproc.hpp>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>
#include <QDir>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMutex>
#include <QScrollBar>

using namespace cv;

namespace Ui {
class MainWindow;
}

class ActualDetector;

/**
 * @brief Main window of UFO Detector
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Camera* cameraPtr, Config* configPtr, DataManager* dataManager, QWidget* parent = 0);
    ~MainWindow();
    void addOutputText(QString msg);

    void setSignalsAndSlots(ActualDetector *actualDetector);

private:
    Ui::MainWindow *ui;
    SettingsDialog *m_settingsDialog;
    ActualDetector* m_actualDetector;
    DataManager* m_dataManager;
    UpdateApplicationDialog* m_updateApplicationDialog;
    std::atomic<bool> m_showCameraVideo;    ///< showing camera video
    std::atomic<bool> m_recordingVideo;     ///< recording video
    std::atomic<bool> m_lastMessageWasInfo; ///< last output message was an info message
    bool m_detecting;   ///< object detection is running
    int counterPositive_, counterNegative_, recordingCounter_;
    cv::Mat m_webcamFrame;
    Camera* m_camera;
    std::unique_ptr<std::thread> threadWebcam;
    cv::Size m_cameraViewResolution;    ///< frame size of camera view
    QImage m_cameraViewImage;           ///< image to be drawn in camera view
    QImage m_latestCameraViewVideoFrame;///< latest video frame
    QMutex m_cameraViewImageMutex;      ///< syncing camera view image
    QString m_detectionStatusStyleOn;   ///< detection status indicator style when detection on
    QString m_detectionStatusStyleOff;  ///< detection status indicator style when detection off
    PlaneChecker* m_planeChecker;

    Config* m_config;

    QString m_programVersion;
    QString m_classifierVersion;
    QNetworkAccessManager *m_networkAccessManager;

    void updateWebcamFrame();
    bool checkAndSetResolution(const int width, const int height);
    void adjustCameraViewFrameSize();    ///< fit camera frame into camera view

    /**
     * @brief Verify camera is working normally.
     *
     * @param width
     * @param height
     * @return
     */
    bool checkCamera(const int width, const int height);

    void on_stopButton_clicked();

    /**
     * @brief Remove all video related data: video list item, item from result data file, video, thumbnail
     * @param dateTime timestamp formatted as YYYY-MM-DD--hh-mm-ss
     */
    void removeVideo(QString dateTime);


signals:
    void elementWasRemoved();
    void updatePixmap(QImage img);

    /**
     * @brief Emitted when frame size of camera view has changed.
     * @param newSize new frame size
     */
    void cameraViewFrameSizeChanged(QSize newSize);

public slots:
    void onRecordingStarted();
    void onRecordingFinished();
    void on_progressBar_valueChanged(int value);
    void update_output_text(QString msg);
    void displayPixmap(QImage img);
    void addVideoToList(QString filename, QString dateTime, QString videoLength);

private slots:
    void on_startButton_clicked();
    void on_checkBoxDisplayWebcam_stateChanged(int arg1);
    void on_buttonClear_clicked();
    void on_sliderNoise_sliderMoved(int position);
    void on_settingsButton_clicked();
    void on_recordingTestButton_clicked();
    void onVideoPlayClicked();
    void onVideoDeleteClicked();
    void onVideoUploadClicked();

    /**
     * @brief Show context menu in video list.
     * @param pos
     *
     * @todo prevent right-click on VideoWidget small buttons to pop up context menu
     */
    void onVideoListContextMenuRequested(const QPoint& pos);

    void onDeleteSelectedVideosClicked();
    void setPositiveMessage();
    void setNegativeMessage();
    void setErrorReadingDetectionAreaFile();
    void on_aboutButton_clicked();

    void on_buttonImageExpl_clicked();
    void on_sliderThresh_sliderMoved(int position);
    void on_toolButtonNoise_clicked();
    void on_toolButtonThresh_clicked();

    void onNewApplicationVersionAvailable(QString newVersion, std::queue<QString> messageInXml);

protected:
    void showEvent(QShowEvent *event);
    void resizeEvent(QResizeEvent *event);
    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
