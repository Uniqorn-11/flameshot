#pragma once

#include <QString>
#include <QTextStream>

/**
 * @brief A class that allows you to log events to where they need to go.
 */
class AbstractLogger
{
public:
    enum Target
    {
        Notification = 0x01,
        Stderr = 0x02,
        LogFile = 0x08,
        String = 0x10,
        Default = Notification | LogFile | Stderr,
    };

    enum Channel
    {
        Info,
        Warning,
        Error
    };

    AbstractLogger(Channel channel = Info, int targets = Default);
    AbstractLogger(QString& str,
                   Channel channel,
                   int additionalTargets = String);
    ~AbstractLogger();

    // Convenience functions
    static AbstractLogger info(int targets = Default);
    static AbstractLogger warning(int targets = Default);
    static AbstractLogger error(int targets = Default);

    AbstractLogger& sendMessage(QString msg, Channel channel);
    AbstractLogger& operator<<(QString msg);
    AbstractLogger& addOutputString(QString& str);
    AbstractLogger& attachNotificationPath(QString path);
    AbstractLogger& enableMessageHeader(bool enable);

private:
    QString messageHeader(Channel type, Target channel);

    int m_targets;
    Channel m_defaultChannel;
    QList<QTextStream*> m_textStreams;
    QString m_notificationPath;
    bool m_enableMessageHeader = true;
};
