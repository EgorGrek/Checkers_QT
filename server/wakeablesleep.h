#ifndef WAKEABLESLEEP_H
#define WAKEABLESLEEP_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>

class WakeableSleep : public QObject
{
    Q_OBJECT
public:
    explicit WakeableSleep(QObject *parent = nullptr);
    /**
     * @brief Euthanize current stream in milliseconds - milliseconds.
     * @param milliseconds Time to sleep.
     */
    void sleep(quint32 milliseconds);
    /**
     * @brief wake Wake up the target thread from another thread.
     */
    void wake();
private:
    QMutex mutex;
    QWaitCondition waitCondition;
};

#endif // WAKEABLESLEEP_H
