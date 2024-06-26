/*
 *  SPDX-FileCopyrightText: 2020 Dmitrii Utkin <loentar@gmail.com>
 *
 *  SPDX-License-Identifier: LGPL-2.1-only
 */

#ifndef RECORDER_EXPORT_CONFIG_H
#define RECORDER_EXPORT_CONFIG_H

#include <QString>
#include <QList>
#include "recorder_export_settings.h"


class KisConfig;
class QSize;

class RecorderExportConfig
{
public:
    RecorderExportConfig(bool readOnly);
    ~RecorderExportConfig();

    void loadConfiguration(RecorderExportSettings *settings, bool loadLockFps = true) const;

    int inputFps() const;
    void setInputFps(int value);

    int fps() const;
    void setFps(int value);

    bool resultPreview() const;
    void setResultPreview(bool value);

    void setFirstFrameSec(int value);
    int firstFrameSec() const;

    bool extendResult() const;
    void setExtendResult(bool value);

    void setLastFrameSec(int value);
    int lastFrameSec() const;

    bool resize() const;
    void setResize(bool value);

    QSize size() const;
    void setSize(const QSize &value);

    bool lockRatio() const;
    void setLockRatio(bool value);

    bool lockFps() const;
    void setLockFps(bool value);

    int profileIndex() const;
    void setProfileIndex(int value);

    QList<RecorderProfile> profiles() const;
    void setProfiles(const QList<RecorderProfile> &value);

    QList<RecorderProfile> defaultProfiles() const;

    QSet<int> editedProfilesIndexes() const;
    void setEditedProfilesIndexes(const QSet<int> &value);

    QString ffmpegPath() const;
    void setFfmpegPath(const QString &value);

    QString videoDirectory() const;
    void setVideoDirectory(const QString &value);

private:
    Q_DISABLE_COPY(RecorderExportConfig)
    mutable KisConfig *config;
};

bool operator==(const RecorderProfile &left, const RecorderProfile &right);
bool operator!=(const RecorderProfile &left, const RecorderProfile &right);

#endif // RECORDER_EXPORT_CONFIG_H
