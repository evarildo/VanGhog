#include "hexstring.h"

HexString::HexString()
{

}

bool isHex(QString color){
    int length=color.length();
    if(length==3||length== 6){
        for(int i=0; i<length;i++){
            if(!isxdigit(color.at(i).toLatin1()))
                return false;
        }
        return true;
    }else{
        return false;
    }
}

void toVec3b(QString color){
    int length=color.length();
    bool status;
    QString out;
    if(length==3){
        for(int i=0;i<3;i++){
            status=false;
            out.clear();
            out.append(color.at(i)).append(color.at(i));
            uint val=out.toUInt(&status, 16);
            qDebug()<<val<<endl;
        }
    }else{
        for(int i=0;i<3;i++){
            status=false;
            out.clear();
            out.append(color.at(2*i)).append(color.at((2*i)+1));
            uint val=out.toUInt(&status, 16);
            qDebug()<<val<<endl;
        }
    }
}

