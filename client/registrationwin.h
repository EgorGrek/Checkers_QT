#ifndef REGISTRATIONWIN_H
#define REGISTRATIONWIN_H

#include <QDialog>
#include <QtWidgets>

class RegistrationWin : public QDialog
{
    Q_OBJECT
public:
    explicit RegistrationWin(QDialog *parent = nullptr);
    void reject() override;
signals:
    void registrationWinClosed();

public slots:
};

#endif // REGISTRATIONWIN_H
