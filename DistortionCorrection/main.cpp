#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <vector>
#include <QDebug>
using namespace std;
using namespace cv;
double divid =0.2;

Point2d upperLeft(764.11350209834291*divid, 621.9136455665207*divid);
Point2d upperRight(2624.4176420761373*divid, 519.85418332633435*divid);
Point2d lowerLeft(713.21758771346913*divid, 3639.7445176981314*divid);
Point2d lowerRight(2712.7031913854335*divid, 3671.4076277199497*divid);

Point2d upperLeftText(764.11350209834291*divid+45, 621.9136455665207*divid+95);
Point2d upperRightText(2624.4176420761373*divid-60, 519.85418332633435*divid+107);
Point2d lowerLeftText(713.21758771346913*divid+52, 3639.7445176981314*divid-240);
Point2d lowerRightText(2712.7031913854335*divid-60, 3671.4076277199497*divid-255);
int main()
{
    Mat img = imread("/home/hossein/QtWs/Distortion/ImageDistortion/DistortionCorrection/images/original2.png",CV_LOAD_IMAGE_COLOR);
    resize(img , img , Size() , divid , divid );
//    drawMarker(img , upperRightText , Scalar(0,0,255) , MARKER_CROSS , 20 , 3 , 8);
    line(img,upperLeft,upperRight,Scalar(0,0,255));
    line(img,upperLeft,lowerLeft,Scalar(0,0,255));
    line(img,lowerLeft,lowerRight,Scalar(0,0,255));
    line(img,lowerRight,upperRight,Scalar(0,0,255));

//    line(img,upperLeftText,upperRightText,Scalar(0,255,255));
//    line(img,upperLeftText,lowerLeftText,Scalar(0,255,255));
//    line(img,lowerLeftText,lowerRightText,Scalar(0,255,255));
//    line(img,lowerRightText,upperRightText,Scalar(0,255,255));
    vector<Point2f> src;
    src.push_back(upperLeftText);
    src.push_back(upperRightText);
    src.push_back(lowerLeftText);
    src.push_back(lowerRightText);
    // Somehow good
    //    src.push_back(lowerLeft);
    //    src.push_back(upperLeft);
    //    src.push_back(lowerRight);
    //    src.push_back(upperRight);

    vector<Point2f> dest;
    dest.push_back(Point2f(upperLeftText.x,upperLeftText.y));
    dest.push_back(Point2f(upperRightText.x+20,upperRightText.y));
    dest.push_back(Point2f(lowerLeftText.x,lowerLeftText.y));
    dest.push_back(Point2f(lowerRightText.x,lowerRightText.y));

    Mat persPective = getPerspectiveTransform(src , dest);
    Mat result = Mat(img.size(),img.type());
    warpPerspective(img  , result  , persPective, Size2f(img.cols,img.rows));



    imshow("Original image",img);
    imshow("Perspective transformed",result);
    imwrite("/home/hossein/Desktop/res.png",result);

    waitKey(0);

    return 0;
}

