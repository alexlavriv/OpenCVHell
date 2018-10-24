/**
 * @file HoughCircle_Demo.cpp
 * @brief Demo code for Hough Transform
 * @author OpenCV team
 */


//#include "restclient-cpp/restclient.h"
#include <iostream>
#include <string>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv_bridge;

namespace
{
    // windows and trackbars name
    const std::string windowName = "Hough Circle Detection Demo";
    const std::string cannyThresholdTrackbarName = "Canny threshold";
    const std::string accumulatorThresholdTrackbarName = "Accumulator Threshold";
    const std::string usage = "Usage : tutorial_HoughCircle_Demo <path_to_input_image>\n";
    string uri = "http://localhost:3000/";
    // initial and max values of the parameters of interests.
    const int cannyThresholdInitialValue = 75;
    const int accumulatorThresholdInitialValue = 75;
    const int maxAccumulatorThreshold = 200;
    const int maxCannyThreshold = 255;

    string intToHEX(int n)
    {
            string zero = "0";
            std::stringstream stream;
            stream << std::hex <<  n;
            std::string result( stream.str() );
            if (result.length() == 1){
              return zero.append(result);
            }
            return result;
    }
    void HoughDetection(const Mat& src_gray, const Mat& src_display, int cannyThreshold, int accumulatorThreshold)
    {
        // will hold the results of the detection
        std::vector<Vec3f> circles;
        // runs the actual detection
        HoughCircles( src_gray, circles, HOUGH_GRADIENT, 1, src_gray.rows/8, cannyThreshold, accumulatorThreshold, 0, 0 );

        // clone the colour, input image for displaying purposes
        Mat display = src_display.clone();
        for( size_t i = 0; i < circles.size(); i++ )
        {
            Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
            int radius = cvRound(circles[i][2]);

            int B = display.at<cv::Vec3b>(center)[0];
            int G = display.at<cv::Vec3b>(center)[1];
            int R = display.at<cv::Vec3b>(center)[2];

            string strRGB ="";
            strRGB.append(intToHEX(R));
            strRGB.append(intToHEX(G));
            strRGB.append(intToHEX(B));
            cout << strRGB << endl;
              string uriWithRGB = string(uri);
           //   RestClient::Response r = RestClient::get(uriWithRGB.append(strRGB));
            //  cout << r.body << endl;

             // size_t firstComma = r.body.find(",",0);
             // size_t secondComma = r.body.find(",", firstComma+1);
             // string colorName = r.body.substr(firstComma+2, secondComma - firstComma -3);
         
            // circle center
            circle( display, center, 3, Scalar(0,255,0), -1, 8, 0 );
            // circle outline
            circle( display, center, radius, Scalar(0,0,255), 3, 8, 0 );

            //    cv::putText(display, //target image
            // colorName, //text
            // center, //top-left position
            // cv::FONT_HERSHEY_DUPLEX,
            // 1.0,
            // CV_RGB(118, 185, 0), //font color
            // 2);
        }

        // shows the results
        imshow( windowName, display);
    }
}


int main(int argc, char** argv)
{

 

    Mat src, src_gray;

    // Read the image
    String imageName("colors.jpg"); // by default
    if (argc > 1)
    {
       imageName = argv[1];
    }
    src = imread( imageName, IMREAD_COLOR );

    if( src.empty() )
    {
        std::cerr<<"Invalid input image\n";
        std::cout<<usage;
        return -1;
    }

    // Convert it to gray
    cvtColor( src, src_gray, COLOR_BGR2GRAY );

    // Reduce the noise so we avoid false circle detection
    GaussianBlur( src_gray, src_gray, Size(9, 9), 2, 2 );

    //declare and initialize both parameters that are subjects to change
    int cannyThreshold = cannyThresholdInitialValue;
    int accumulatorThreshold = accumulatorThresholdInitialValue;

    // create the main window, and attach the trackbars
    namedWindow( windowName, WINDOW_AUTOSIZE );
            //runs the detection, and update the display
        HoughDetection(src_gray, src, 75, accumulatorThreshold);

   // infinite loop to display
    // and refresh the content of the output image
    // until the user presses q or Q
    char key = 0;
    while(key != 'q' && key != 'Q')
    {
        // those parameters cannot be =0
        // so we must check here


        // get user key
        key = (char)waitKey(10);
    }

    return 0;
}
