/*
 * Copyright (C) 2017  Luca Weiss <luca (at) z3ntu (dot) xyz>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "devicelistwidget.h"
#include "razerimagedownloader.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QIcon>

DeviceListWidget::DeviceListWidget(QWidget *parent, librazer::Device *device) : QWidget(parent)
{
    this->device = device;

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setMargin(2);

    // Add icon
    if(!device->getPngFilename().isEmpty()) {
        QString path = RazerImageDownloader::getDownloadPath() + device->getPngFilename();
        QPixmap scaled = createPixmapFromFile(path);
        imageLabel = new QLabel(this);
        imageLabel->setPixmap(scaled);
    } else {
        imageLabel = new QLabel("Downloading image...", this);
    }
    imageLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(imageLabel);

    QLabel *deviceName = new QLabel(device->getDeviceName(), this);
    deviceName->setWordWrap(true);
    deviceName->setAlignment(Qt::AlignCenter);

    layout->addWidget(deviceName);
}

QPixmap DeviceListWidget::createPixmapFromFile(QString &filename)
{
    QPixmap icon(filename);
    return icon.scaled(150, 75, Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

void DeviceListWidget::imageDownloaded(QString &filename)
{
    qDebug() << "DeviceListWidget: Received signal!" << filename;
    QPixmap scaled = createPixmapFromFile(filename);
    imageLabel->setPixmap(scaled);
}
