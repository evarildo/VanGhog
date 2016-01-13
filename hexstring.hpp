#ifndef HEXSTRING_H
#define HEXSTRING_H
#include <QString>
#include <cctype>
#include <QDebug>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

bool isHex(QString color);
Vec3b toVec3b(QString color);

class HexString
{
public:
    HexString();
};

#endif // HEXSTRING_H
