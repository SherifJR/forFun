#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main()
{
    VideoCapture cam(0);
    if(!cam.isOpened())
    {
        cerr << "ERROR: Cannot open camera!" << endl;
        return EXIT_FAILURE;
    }
    cout << "Camera opened successfully!" << endl;

    cam.set(CAP_PROP_FRAME_WIDTH, 640);
    cam.set(CAP_PROP_FRAME_HEIGHT, 480);

    Scalar lowercolor(0, 0, 0);   
    Scalar uppercolor(180, 255, 80);

    Mat frame, hsv, mask;
    string window_name = "Object Detection";
    namedWindow(window_name);

    while(true)
    {
        cam >> frame;
        if(frame.empty())
        {
            cerr << "ERROR: No frames captured!" << endl;
            break;
        }

        flip(frame, frame, 1); 
        cvtColor(frame, hsv, COLOR_BGR2HSV);
        inRange(hsv, lowercolor, uppercolor, mask);

        GaussianBlur(mask, mask, Size(5,5), 0);
        erode(mask, mask, Mat(), Point(-1,-1), 1);
        dilate(mask, mask, Mat(), Point(-1,-1), 2);

        vector<vector<Point>> contours;
        findContours(mask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        if(!contours.empty())
        {
            double maxarea = 0;
            int maxidx = -1;
            for(int i=0; i<contours.size(); i++)
            {
                double area = contourArea(contours[i]);
                if(area > maxarea)
                {
                    maxarea = area;
                    maxidx = i;
                }
            }

            if(maxidx != -1 && maxarea > 500)
            {
                Rect box = boundingRect(contours[maxidx]);
                Scalar hudColor(0, 255, 0);

                rectangle(frame, box, hudColor, 2);

                int cx = box.x + box.width/2;
                int cy = box.y + box.height/2;

                line(frame, Point(cx-10, cy), Point(cx+10, cy), hudColor, 2);
                line(frame, Point(cx, cy-10), Point(cx, cy+10), hudColor, 2);

                string coords = "X:" + to_string(cx) + " Y:" + to_string(cy);
                putText(frame, "Target detected", Point(box.x, box.y-25), FONT_HERSHEY_SIMPLEX, 0.6, hudColor, 2);
                putText(frame, coords, Point(50, 50), FONT_HERSHEY_PLAIN, 1, hudColor, 1);
            }
        }
        else
        {
            putText(frame, "Scanning...", Point(50, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 2);
        }

        imshow(window_name, frame);

        char key = (char)waitKey(10);
        if(key == 27) break;
    }

    cam.release();
    destroyAllWindows();
    return 0;
}
