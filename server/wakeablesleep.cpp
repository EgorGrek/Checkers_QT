#include "wakeablesleep.h"

WakeableSleep::WakeableSleep(QObject *parent) :
    QObject(parent){}

void WakeableSleep::sleep(quint32 milliseconds)
{
    mutex.lock();
    waitCondition.wait(&mutex, milliseconds);
    mutex.unlock();
}

void WakeableSleep::wake()
{
    mutex.lock();
    waitCondition.wakeAll();
    mutex.unlock();
}
