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

    userDefinedBound.push_back(upperLeft);
    userDefinedBound.push_back(upperRight);
    userDefinedBound.push_back(lowerLeft);
    userDefinedBound.push_back(lowerRight);

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

Mat DistortCorrection::cropImage(Mat img, vector<Point2f> cropBound)
{
    return img(Rect(cropBound[0],cropBound[3]));
}

// I have used this gitlab https://gist.github.com/JinpengLI/2cf814fe25222c645dd04e04be4de5a6 code
Mat DistortCorrection::isolateTheTextBox(Mat thresholdedImage,int removeComponnentsBySizeLessThan)
{

    Mat labels;
    Mat stats;
    Mat centroids;
    cv::connectedComponentsWithStats(thresholdedImage, labels, stats, centroids);

    Mat temp;
    thresholdedImage.copyTo(temp);
    for(int i=0; i<stats.rows; i++)
    {
        int x = stats.at<int>(Point(0, i));
        int y = stats.at<int>(Point(1, i));
        int w = stats.at<int>(Point(2, i));
        int h = stats.at<int>(Point(3, i));

        //if a rectangle size is less than 80 we will fill it by a color as background
        Scalar color(0,0,0);
        Rect rect(x,y,w,h);
        if(w*h<removeComponnentsBySizeLessThan)
            cv::rectangle(temp, rect, color,CV_FILLED);
    }

    Mat res(temp.size() , temp.type());
    bitwise_xor(temp , thresholdedImage , res);
    return res;
}
