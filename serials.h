#ifndef SERIALS_H
#define SERIALS_H
#include <QString>
#include <QSysInfo>
#include <QStringList>
#include <QCryptographicHash>


class Serials
{
public:
    Serials();
    static QString generateSecret(int ITERS = 50);
    static QString generatePublic();
    static QString generateMachine();
    static QString generateSerial(QString,QString,QString);
    static bool validSerial(QString,QString,QString,QString);
    static QStringList hashs(QString);
protected:
    static short int charToInt(char a);
};

#endif // SERIALS_H
