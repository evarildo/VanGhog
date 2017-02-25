#include "hexstring.hpp"

HexString::HexString()
{
}

/**
 * @brief isHex
 * @param color
 * @return A boolean if the string is a valid 3d hex color with 8bits each or not
 */
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

/**
 * @brief toVec3b
 * @param color The QString of hex color
 * @return A vector of the calor recieved in the parameter
 * Is converts the hex color to a Vec3b of the OpenCV
 */
Vec3b toVec3b(QString color){
    int length=color.length();
    bool status;
    Vec3b out_vec;
    QString out;
    if(length==3){
        for(int i=0;i<3;i++){
            status=false;
            out.clear();
            out.append(color.at(i)).append(color.at(i));
            uint val=out.toUInt(&status, 16);
            qDebug()<<val<<endl;
            out_vec[2-i]=val;
        }
    }else{
        for(int i=0;i<3;i++){
            status=false;
            out.clear();
            out.append(color.at(2*i)).append(color.at((2*i)+1));
            uint val=out.toUInt(&status, 16);
            qDebug()<<val<<endl;
            out_vec[2-i]=val;
        }
    }
    return out_vec;
}

