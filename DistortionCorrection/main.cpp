#include <distortcorrection.h>



int main()
{
    DistortCorrection distCor;

    /*
     * FIRST PHASE : PRE-PROCESSING
     * Load image by prefered scale
     * crope it based on user defined boundaries to just do process on ROI
     * convert cropped image to the grayscale and smooth the image by a low kernel size gaussian blure
     * do an adaptive threshold on the image
     */

    distCor.loadImage(distCor.imageAddress,0.2f);
    Mat croppedImage = distCor.cropImage(distCor.getOriginalImage(),distCor.userDefinedBound);
    Mat grayImag;
    cvtColor(croppedImage, grayImag,CV_RGB2GRAY);
    GaussianBlur(grayImag,grayImag,Size(5,5),0.1);
    Mat thresholdImage;
    adaptiveThreshold(grayImag,thresholdImage,255,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY_INV,35,25);
    imshow("Adaptive Threshold output",thresholdImage);

    /*
     * SECOND PHASE : TEXT ISOLATION
     * We wana eliminate Figures (if any) from our ROI
     */

    Mat isolatedImage = distCor.isolateTheTextBox(thresholdImage,200);
    //Mat isolatedImage2 = distCor.isolateTheTextBox(isolatedImage,100);

    int erodeSize=2;
    int dilateSize=2;

    Mat erodeElement = getStructuringElement( MORPH_RECT,
                                              Size( 2*erodeSize + 1, 2*erodeSize+1 ),
                                              Point( erodeSize, erodeSize ) );
    Mat dilateElement = getStructuringElement( MORPH_RECT,
                                               Size( 2*dilateSize + 1, 2*dilateSize+1 ),
                                               Point( dilateSize, dilateSize ) );
    for(int i=0;i<5;i++)
        dilate(isolatedImage , isolatedImage , dilateElement);

    for(int i=0;i<6;i++)
        erode( isolatedImage, isolatedImage, erodeElement );
    imshow("Display Image", isolatedImage);


    //Mat result = distCor.perspectiveTransformation(distCor.getOriginalImage(),distCor.src , distCor.dest);
    //imshow("Text bounding box perspective" , result);

    //imshow("Original Image",distCor.getOriginalImage());
    waitKey(0);
    return 0;
}

