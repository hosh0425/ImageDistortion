#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <vector>
using namespace std;
using namespace cv;


/*
 * I have just tried it for getting some idea maybe, but now seems it doesn't help
 * About destination points I have just set them approximately, to get more accurate results some calculations need based on src points
 * If you wanna test this fnction copy all of this source file to the main and change the dePerspectiveTransform to main() :))
 */
void  doPerspectiveTransform()
{
    Point upperLeft(120,295);
    Point upperRight(405,245);
    Point lowerLeft(115,770);
    Point lowerRight(405,810);

    Mat img = imread("/home/hossein/QtWs/Distortion/ImageDistortion/DistortionCorrection/images/boundary.png",CV_LOAD_IMAGE_COLOR);
    resize(img , img , Size() , 0.5 , 0.5 );
    //drawMarker(img , lowerRight , Scalar(0,0,255) , MARKER_CROSS , 20 , 3 , 8);
    vector<Point2f> src;
    src.push_back(upperLeft);
    src.push_back(upperRight);
    src.push_back(lowerLeft);
    src.push_back(lowerRight);

    vector<Point2f> dest;
    dest.push_back(Point2f(0,0));
    dest.push_back(Point2f(300*1.3,0));
    dest.push_back(Point2f(0,500*1.3));
    dest.push_back(Point2f(300*1.3,500*1.3));

    Mat persPective = getPerspectiveTransform(src , dest);
    Mat result = Mat(img.size(),img.type());
    warpPerspective(img  , result  , persPective, Size2f(300*1.3,500*1.3));
    imshow("Original image",img);
    imshow("Perspective transformed",result);
    waitKey(0);
}
