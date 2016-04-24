#include "config.h"

Config::Config(QObject *parent) : QObject(parent)
{
#if defined (Q_OS_WIN)
    m_videoEncoderLocation = QCoreApplication::applicationDirPath()+"/ffmpeg.exe";
#elif defined (Q_OS_LINUX) || defined (Q_OS_UNIX)
    /// @todo use which(1) to find if ffmpeg and avconv are present. Prefer avconv at least in *ubuntu.
    m_videoEncoderLocation = "/usr/bin/avconv";
#else
    m_videoEncoderLocation = "";
#endif
}

QString Config::videoEncoderLocation() {
    return m_videoEncoderLocation;
}

