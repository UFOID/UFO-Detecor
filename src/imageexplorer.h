/**
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

#ifndef IMAGEEXPLORER_H
#define IMAGEEXPLORER_H

#include <QDialog>
#include <QModelIndex>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include <stack>


namespace Ui {
class ImageExplorer;
}

class ImageExplorer : public QDialog
{
    Q_OBJECT

public:
    explicit ImageExplorer(QWidget *parent = 0);
    ~ImageExplorer();

private:
    QString mainDir;
    QString currentDir;
    QString folderName;
    std::stack<QString> fileList;
    QNetworkAccessManager* manager;

private slots:
    void on_buttonClear_clicked();
    void on_buttonUpload_clicked();
    void displayFolder(QModelIndex index);
    void on_buttonBack_clicked();
    void uploadFinish(QNetworkReply *r);
    void uploadError(QNetworkReply::NetworkError state);
    void openedPHP();
    void on_commandLinkButton_clicked();

private:
    Ui::ImageExplorer *ui;
};

#endif // IMAGEEXPLORER_H
