#include "serials.h"


Serials::Serials()
{

}

QString Serials::generateMachine(){
    QSysInfo info;
    QString str = QString(info.machineUniqueId())+QString(info.kernelType())+QString(info.machineHostName())+QString(info.buildCpuArchitecture());
    QByteArray hash = QCryptographicHash::hash(QByteArray::fromStdString(str.toStdString()), QCryptographicHash::Md5);
    return hash.toHex();
}

QString Serials::generateSecret(int ITERS){
    QString key;
    for (int i=0; i<ITERS; i++){
        key += QString::number(rand()-3000);
        key = QCryptographicHash::hash(QByteArray::fromStdString(key.toStdString()), QCryptographicHash::Sha3_512).toHex();
    }
    return key;
}

QString Serials::generateSerial(QString secret, QString machine, QString username){
    if (secret.isEmpty()||machine.isEmpty()||username.isEmpty()){
        return "";
    }
    QString key1,key2,key3,serial;

    short int itersA = rand() % 9; //A
    short int itersB = rand() % 9; //B
    short int itersC = rand() % 9; //C
    short int itersD = rand() % 9; //D
    short int i;

    key1 = QCryptographicHash::hash(QByteArray::fromStdString(secret.toStdString()), QCryptographicHash::Sha3_512).toHex();
    for (i=0; i<itersA;i++)
        key1 = QCryptographicHash::hash(QByteArray::fromStdString(key1.toStdString()), QCryptographicHash::Sha3_512).toHex();
    key2 = QCryptographicHash::hash(QByteArray::fromStdString(machine.toStdString()), QCryptographicHash::Sha3_512).toHex();
    for (i=0; i<itersB;i++)
        key2 = QCryptographicHash::hash(QByteArray::fromStdString(key2.toStdString()), QCryptographicHash::Sha3_512).toHex();
    key3 = QCryptographicHash::hash(QByteArray::fromStdString(username.toStdString()), QCryptographicHash::Sha3_512).toHex();
    for (i=0; i<itersC;i++)
        key3 = QCryptographicHash::hash(QByteArray::fromStdString(key3.toStdString()), QCryptographicHash::Sha3_512).toHex();

    serial = QCryptographicHash::hash(QByteArray::fromStdString(key1.toStdString()+key2.toStdString()+key3.toStdString()), QCryptographicHash::Sha3_512).toHex();
    for (i=0; i<itersD;i++)
        serial = QCryptographicHash::hash(QByteArray::fromStdString(serial.toStdString()), QCryptographicHash::Sha3_512).toHex();

    serial = QCryptographicHash::hash(QByteArray::fromStdString(serial.toStdString()), QCryptographicHash::Md5).toHex().toUpper();

    //qDebug() << "itersA: "<<itersA<<"; itersB: "<<itersB<<"; itersC: "<<itersC<<"; itersD: "<<itersD;
    //qDebug() << serial;

    //AXXX-BXXX-CXXX-DXXX-XXXX-XXXX-XXXX-XXXX
    //0    3    7    11

    serial.replace(0,1,QString::number(itersA)[0]);
    serial.replace(4,1,QString::number(itersB)[0]);
    serial.replace(8,1,QString::number(itersC)[0]);
    serial.replace(12,1,QString::number(itersD)[0]);


    serial.insert(4,'-');
    serial.insert(9,'-');
    serial.insert(14,'-');
    serial.insert(19,'-');
    serial.insert(24,'-');
    serial.insert(29,'-');
    serial.insert(34,'-');

    //qDebug() << serial;

    return serial;
}

bool Serials::validSerial(QString serial, QString secret, QString machine, QString username){
    if (serial.isEmpty()||secret.isEmpty()||machine.isEmpty()||username.isEmpty()){
        return false;
    }
    QStringList parts = serial.split("-");
    QString key1,key2,key3,Rserial;

    short int itersA = charToInt(parts[0][0].toLatin1()); //A
    short int itersB = charToInt(parts[1][0].toLatin1()); //B
    short int itersC = charToInt(parts[2][0].toLatin1()); //C
    short int itersD = charToInt(parts[3][0].toLatin1()); //D
    short int i;

    key1 = QCryptographicHash::hash(QByteArray::fromStdString(secret.toStdString()), QCryptographicHash::Sha3_512).toHex();
    for (i=0; i<itersA;i++)
        key1 = QCryptographicHash::hash(QByteArray::fromStdString(key1.toStdString()), QCryptographicHash::Sha3_512).toHex();
    key2 = QCryptographicHash::hash(QByteArray::fromStdString(machine.toStdString()), QCryptographicHash::Sha3_512).toHex();
    for (i=0; i<itersB;i++)
        key2 = QCryptographicHash::hash(QByteArray::fromStdString(key2.toStdString()), QCryptographicHash::Sha3_512).toHex();
    key3 = QCryptographicHash::hash(QByteArray::fromStdString(username.toStdString()), QCryptographicHash::Sha3_512).toHex();
    for (i=0; i<itersC;i++)
        key3 = QCryptographicHash::hash(QByteArray::fromStdString(key3.toStdString()), QCryptographicHash::Sha3_512).toHex();

    Rserial = QCryptographicHash::hash(QByteArray::fromStdString(key1.toStdString()+key2.toStdString()+key3.toStdString()), QCryptographicHash::Sha3_512).toHex();
    for (i=0; i<itersD;i++)
        Rserial = QCryptographicHash::hash(QByteArray::fromStdString(Rserial.toStdString()), QCryptographicHash::Sha3_512).toHex();

    Rserial = QCryptographicHash::hash(QByteArray::fromStdString(Rserial.toStdString()), QCryptographicHash::Md5).toHex().toUpper();

    //qDebug() << "itersA: "<<itersA<<"; itersB: "<<itersB<<"; itersC: "<<itersC<<"; itersD: "<<itersD;
    //qDebug() << serial;

    //AXXX-BXXX-CXXX-DXXX-XXXX-XXXX-XXXX-XXXX
    //0    3    7    11

    Rserial.replace(0,1,QString::number(itersA)[0]);
    Rserial.replace(4,1,QString::number(itersB)[0]);
    Rserial.replace(8,1,QString::number(itersC)[0]);
    Rserial.replace(12,1,QString::number(itersD)[0]);


    Rserial.insert(4,'-');
    Rserial.insert(9,'-');
    Rserial.insert(14,'-');
    Rserial.insert(19,'-');
    Rserial.insert(24,'-');
    Rserial.insert(29,'-');
    Rserial.insert(34,'-');

    //qDebug() << serial;
    //qDebug() << Rserial;
    //qDebug() << (serial.compare(Rserial));

    return  (serial.compare(Rserial)==0);
}

short int Serials::charToInt(char a){
    switch (a) {
        case '0': return 0;
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;
    }
    return 0;
}

QStringList Serials::hashs(QString string){
    QStringList list;
    list.append(QCryptographicHash::hash(QByteArray::fromStdString(string.toStdString()), QCryptographicHash::Md4         ).toHex());
    list.append(QCryptographicHash::hash(QByteArray::fromStdString(string.toStdString()), QCryptographicHash::Md5         ).toHex());
    list.append(QCryptographicHash::hash(QByteArray::fromStdString(string.toStdString()), QCryptographicHash::Sha1        ).toHex());
    list.append(QCryptographicHash::hash(QByteArray::fromStdString(string.toStdString()), QCryptographicHash::Sha224      ).toHex());
    list.append(QCryptographicHash::hash(QByteArray::fromStdString(string.toStdString()), QCryptographicHash::Sha256      ).toHex());
    list.append(QCryptographicHash::hash(QByteArray::fromStdString(string.toStdString()), QCryptographicHash::Sha384      ).toHex());
    list.append(QCryptographicHash::hash(QByteArray::fromStdString(string.toStdString()), QCryptographicHash::Sha512      ).toHex());
    list.append(QCryptographicHash::hash(QByteArray::fromStdString(string.toStdString()), QCryptographicHash::Keccak_224  ).toHex());
    list.append(QCryptographicHash::hash(QByteArray::fromStdString(string.toStdString()), QCryptographicHash::Keccak_256  ).toHex());
    list.append(QCryptographicHash::hash(QByteArray::fromStdString(string.toStdString()), QCryptographicHash::Keccak_384  ).toHex());
    list.append(QCryptographicHash::hash(QByteArray::fromStdString(string.toStdString()), QCryptographicHash::Keccak_512  ).toHex());
    list.append(QCryptographicHash::hash(QByteArray::fromStdString(string.toStdString()), QCryptographicHash::RealSha3_224).toHex());
    list.append(QCryptographicHash::hash(QByteArray::fromStdString(string.toStdString()), QCryptographicHash::RealSha3_256).toHex());
    list.append(QCryptographicHash::hash(QByteArray::fromStdString(string.toStdString()), QCryptographicHash::RealSha3_384).toHex());
    list.append(QCryptographicHash::hash(QByteArray::fromStdString(string.toStdString()), QCryptographicHash::RealSha3_512).toHex());
    return list;
}
