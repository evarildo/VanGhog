#ifndef HEXSTRING_H
#define HEXSTRING_H
#include <QString>
#include <cctype>
#include <QDebug>

bool isHex(QString color);
void toVec3b(QString color);

class HexString
{
public:
    HexString();
};

#endif // HEXSTRING_H
