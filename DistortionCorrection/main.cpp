#include <distortcorrection.h>



int main()
{
    DistortCorrection distCor;
    distCor.loadImage(distCor.imageAddress,0.2f);
    Mat result = distCor.perspectiveTransformation(distCor.getOriginalImage(),distCor.src , distCor.dest);

    imshow("Original Image",distCor.getOriginalImage());
    imshow("Text bounding box perspective" , result);
    waitKey(0);
    return 0;
}

