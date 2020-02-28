#include "face_detection.hpp"

int main(int argc, char *argv[])
{
    FLAGS_alsologtostderr = true;
    ::google::InitGoogleLogging(argv[0]);
    cv::Mat img = cv::imread("naassom-azevedo-cropped.jpg");
    cv::imshow("Found faces", face_detection(img));
    cv::waitKey();
}
