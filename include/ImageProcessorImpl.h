#pragma once
#include "image_processing.hpp"
using namespace cv;
class ImageProcessorImpl : public ImageProcessor
{
public:
	virtual Mat CvtColor(const Mat &src, const Rect &roi);
	virtual Mat Filter(const Mat &src, const Rect &roi,const int size);
	virtual Mat DetectEdges(const Mat &src, const Rect &roi,
		const int filter_size, const int low_threshold,
		const int ratio, const int kernel_size);
	
	virtual Mat Pixelize(const Mat &src, const Rect &roi,const int divs);
};

