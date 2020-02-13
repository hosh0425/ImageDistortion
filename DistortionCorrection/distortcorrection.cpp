#include "distortcorrection.h"

DistortCorrection::DistortCorrection()
{
    src.push_back(upperLeftText);
    src.push_back(upperRightText);
    src.push_back(lowerLeftText);
    src.push_back(lowerRightText);

    dest.push_back(upperLeftText);
    dest.push_back(Point2f(upperRightText.x+20,upperRightText.y));
    dest.push_back(lowerLeftText);
    dest.push_back(lowerRightText);
}

void DistortCorrection::loadImage(String imagePath , float scale){
    originalImage = imread(imagePath,CV_LOAD_IMAGE_COLOR);
    resize(originalImage , originalImage , Size() , static_cast<double>(scale) , static_cast<double>(scale));
}

Mat DistortCorrection::perspectiveTransformation(Mat img, vector<Point2f> src, vector<Point2f> dest)
{
    Mat persPective = getPerspectiveTransform(src , dest);
    Mat result = Mat(img.size(),img.type());
    warpPerspective(img  , result  , persPective, Size2f(img.cols,img.rows));
    return result;
}

Mat DistortCorrection::drawRectangle(Mat img, vector<Point2f> points , Scalar color)
{
    line(img, points[0],points[1],color);
    line(img, points[0],points[2],color);
    line(img, points[1],points[3],color);
    line(img, points[2],points[3],color);
    return img;
}
