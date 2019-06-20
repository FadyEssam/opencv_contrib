// This file is part of OpenCV project.
// It is subject to the license terms in the LICENSE file found in the top-level directory
// of this distribution and at http://opencv.org/license.html.

#include "precomp.hpp"
namespace cv { namespace augment {

FlipHorizontal::FlipHorizontal() {}

void FlipHorizontal::image(InputArray _src, OutputArray _dst)
{
    cv::flip(_src, _dst, 1);
}

Point2f FlipHorizontal::point(const Point2f& src)
{
    return Point2f(srcImageCols - 1 - src.x, src.y);
}


FlipVertical::FlipVertical() {}

void FlipVertical::image(InputArray _src, OutputArray _dst)
{
    cv::flip(_src, _dst, 0);
}

Point2f FlipVertical::point(const Point2f& src)
{
    return Point2f(src.x, srcImageRows - 1 - src.y);
}

}}
