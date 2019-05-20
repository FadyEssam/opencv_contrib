// This file is part of OpenCV project.
// It is subject to the license terms in the LICENSE file found in the top-level directory
// of this distribution and at http://opencv.org/license.html.


#include "precomp.hpp"
#include <iostream>
namespace cv {
namespace augment {

    Transform::Transform() {}

    Transform::~Transform() {}
                
    void Transform::image(InputArray _src, OutputArray _dst)
    {
        _src.copyTo(_dst);
    }

    Point2f Transform::point(InputArray,const Point2f& src)
    {
        return src;
    }

    Scalar Transform::rectangle(InputArray image,const Scalar& src)
    {
        float x1 = src[0],
            y1 = src[1],
            x2 = src[2],
            y2 = src[3];

        Point2f tl(x1, y1);
        Point2f bl(x1, y2);
        Point2f tr(x2, y1);
        Point2f br(x2, y2);

        Point2f tl_transformed = this->point(image, tl);
        Point2f bl_transformed = this->point(image, bl);
        Point2f tr_transformed = this->point(image, tr);
        Point2f br_transformed = this->point(image, br);

        float x1_transformed = std::min({ tl_transformed.x, bl_transformed.x, tr_transformed.x, br_transformed.x });
        float y1_transformed = std::min({ tl_transformed.y, bl_transformed.y, tr_transformed.y, br_transformed.y });
        float x2_transformed = std::max({ tl_transformed.x, bl_transformed.x, tr_transformed.x, br_transformed.x });
        float y2_transformed = std::max({ tl_transformed.y, bl_transformed.y, tr_transformed.y, br_transformed.y });

        Scalar output_box({ x1_transformed ,y1_transformed ,x2_transformed ,y2_transformed });
        return output_box;
    }

    void Transform::points(InputArray image, InputArray _src, OutputArray _dst)
    {
        Mat src = _src.getMat();
        CV_Assert(src.cols == 2);
        
        //making sure input matrix is float
        int type = src.type();
        uchar depth = type & CV_MAT_DEPTH_MASK;
        if (depth != CV_32F)
        {
            src.convertTo(src, CV_32F);
        }

        _dst.create(src.size(), CV_32F);
        Mat dst = _dst.getMat();

        for (size_t i = 0; i < src.rows; i++)
        {
            Mat src_row = src.row(i);
            Point2f src_point = Point2f(src_row.at<float>(0), src_row.at<float>(1));
            Point2f dst_point = this->point(image, src_point);
            dst.at<float>(i,0) = dst_point.x;
            dst.at<float>(i,1) = dst_point.y;
        }

    }

    void Transform::rectangles(InputArray image, InputArray _src, OutputArray _dst)
    {
        Mat src = _src.getMat();
        CV_Assert(src.cols == 4);

        //making sure input matrix is float
        int type = src.type();
        uchar depth = type & CV_MAT_DEPTH_MASK;
        if (depth != CV_32F)
        {
            src.convertTo(src, CV_32F);
        }

        _dst.create(src.size(), CV_32F);
        Mat dst = _dst.getMat();

        for (size_t i = 0; i < src.rows; i++)
        {
            Mat src_row = src.row(i);
            Scalar src_rect = Scalar(src_row.at<float>(0), src_row.at<float>(1), src_row.at<float>(2), src_row.at<float>(3));
            Scalar dst_rect = this->rectangle(image, src_rect);
            dst.at<float>(i, 0) = dst_rect[0];
            dst.at<float>(i, 1) = dst_rect[1];
            dst.at<float>(i, 2) = dst_rect[2];
            dst.at<float>(i, 3) = dst_rect[3];
        }

    }

    std::vector<Mat> Transform::polygons(InputArray image, std::vector<Mat> src)
    {
        std::vector<Mat> dst(src.size());

        for (size_t i = 0; i < src.size(); i++)
        {
            Mat src_row = src[i];
            Mat dst_row;
            this->points(image, src_row, dst_row);
            dst[i] = dst_row;
        }

        return dst;
    }    

}
}
