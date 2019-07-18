// This file is part of OpenCV project.
// It is subject to the license terms in the LICENSE file found in the top-level directory
// of this distribution and at http://opencv.org/license.html.


#ifndef OPENCV_AUGMENT_AVERAGEBLUR_HPP
#define OPENCV_AUGMENT_AVERAGEBLUR_HPP
#include <opencv2/augment/transform.hpp>

namespace cv { namespace augment {

class CV_EXPORTS_W AverageBlur : public Transform
{
public:
    /* @brief Constructor to initialize the average blur transformation with a range of kernel sizes
       @param minKernelSize the min size of average blur kernel
       @param maxKernelSize the max size of average blur kernel
    */
    CV_WRAP AverageBlur(Size minKernelSize, Size maxKernelSize,const std::vector<int>& borderTypes = std::vector<int>());

    /* @brief Constructor to initialize the average blur transformation with a specific kernel size
       @param kernelSize the size of average blur kernel
    */
    CV_WRAP AverageBlur(Size kernelSize, int borderType = BORDER_DEFAULT);

    /* @brief Apply the gaussian blue to a single image
        @param src Input image to be blurred
        @param dst Output (blurred) image
    */
    CV_WRAP virtual void image(InputArray src, OutputArray dst) override;

    /* @brief choose an random kernel size and sigma from the specified ranges to apply in next transformations
    */
    void virtual init(const Mat&) override;

private :
    Size minKernelSize;
    Size maxKernelSize;
    Size kernelSize;
    bool sameXY;
    std::vector<int> borderTypes;
    int borderType;

};

}} //namespace cv::augment

#endif
