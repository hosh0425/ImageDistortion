#ifndef DISTORTCORRECTION_H
#define DISTORTCORRECTION_H

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <vector>
#include <QDebug>

using namespace std;
using namespace cv;
class DistortCorrection
{
public:
    DistortCorrection();
    String imageAddress = "/home/hossein/QtWs/Distortion/ImageDistortion/DistortionCorrection/images/original2.png";
    void loadImage(String imagePath , float scale);
    Mat perspectiveTransformation(Mat img , vector<Point2f> src , vector<Point2f> dest);
    Mat drawRectangle(Mat img , vector<Point2f>points,Scalar color = Scalar(0,0,255));
    // The src points must be detected by our rectangleFit algorithm
    vector<Point2f> src;
    // The dest points must be detected based on src points
    vector<Point2f> dest;
    Mat getOriginalImage(){return originalImage;}
private:
    // This is resizing scale. If 0<scale<1 will decrease the size and if scale>1 will increase the size
    float scale =0.2f;


    //These for points are choosen by user. I do not use these in this version still.
    Point2f upperLeft = Point2f(764.11350209834291f*scale, 621.9136455665207f*scale);
    Point2f upperRight = Point2f(2624.4176420761373f*scale, 519.85418332633435f*scale);
    Point2f lowerLeft = Point2f(713.21758771346913f*scale, 3639.7445176981314f*scale);
    Point2f lowerRight= Point2f(2712.7031913854335f*scale, 3671.4076277199497f*scale);

    //These for points are groundturuth for text bounding box which I have to find them
    Point2f upperLeftText= Point2f(764.11350209834291f*scale+45, 621.9136455665207f*scale+95);
    Point2f upperRightText= Point2f(2624.4176420761373f*scale-60, 519.85418332633435f*scale+107);
    Point2f lowerLeftText= Point2f(713.21758771346913f*scale+52, 3639.7445176981314f*scale-240);
    Point2f lowerRightText = Point2f(2712.7031913854335f*scale-60, 3671.4076277199497f*scale-255);


    Mat originalImage;

};

#endif // DISTORTCORRECTION_H
