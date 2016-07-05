#include "image_processing.hpp"

cv::Mat ImageProcessorImpl::CvtColor(const cv::Mat &src, const cv::Rect &roi) {
	cv::Mat src_copy;
	src.copyTo(src_copy);
	cv::Mat src_copy_roi = src_copy(roi);
	cv::Mat dst_gray_roi;
	cvtColor(src_copy_roi, dst_gray_roi, CV_BGR2GRAY);

	std::vector<cv::Mat> channels;
	channels.push_back(dst_gray_roi);
	channels.push_back(dst_gray_roi);
	channels.push_back(dst_gray_roi);
	cv::Mat dst_roi;
	merge(channels, dst_roi);
	dst_roi.copyTo(src_copy_roi);
	return src_copy;
};
cv::Mat ImageProcessorImpl::Filter(const cv::Mat &src, const cv::Rect &roi,
	const int size) 
{
	cv::Mat src_copy;
	src.copyTo(src_copy);
	cv::Mat src_copy_roi = src_copy(roi);
	medianBlur(src_copy_roi, src_copy_roi,size);
	 
	return src_copy;
};
cv::Mat ImageProcessorImpl::DetectEdges(const cv::Mat &src, const cv::Rect &roi,
	const int filter_size, const int low_threshold,
	const int ratio, const int kernel_size) 
{
	
	cv::Mat src_roi = src(roi);
   cv::Mat src_gray_roi = CvtColor(src_roi, roi);
   cv::Mat gray_blurred;
   cv::blur(src_gray_roi, gray_blurred, cv::Size(3, 3));
   cv::Canny(gray_blurred, gray_blurred, 0, 50);
   cv::Mat dst;
   src.copyTo(dst);
   cv::Mat dst_roi = dst(roi);
   return dst;
};

cv::Mat ImageProcessorImpl::Pixelize(const cv::Mat &src, const cv::Rect &roi,
	const int divs) 
{
	cv::Mat src_copy;
	src.copyTo(src_copy);
	cv::Mat src_copy_roi = src_copy(roi);
	return src_copy;
};