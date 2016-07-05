#include <iostream>
#include <string>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "image_processing.hpp"
using namespace std;
using namespace cv;
const char* kAbout =
"This is an empty application that can be treated as a template for your "
"own doing-something-cool applications.";

const char* kOptions =
"{ @image         | <none> | image to process            }"
"{ gray           |        | convert ROI to gray scale   }"
"{ median         |        | apply median filter for ROI }"
"{ edges          |        | detect edges in ROI         }"
"{ pix            |        | pixelize ROI                }"
"{ h ? help usage |        | print help message          }";
struct MouseCallbackState {
	bool is_selection_started;
	bool is_selection_finished;
	Point point_first;
	Point point_second;
};
void OnMouse(int event, int x, int y, int flags, void* userdata)
{

	if (event == EVENT_LBUTTONDOWN)
	{
		((MouseCallbackState*)userdata)->is_selection_started = true;
		((MouseCallbackState*)userdata)->is_selection_finished = false;
		((MouseCallbackState*)userdata)->point_first = Point(x, y);
		cout << "Left button of the mouse is down - position (" << x << ", " << y << ")" << endl;
	}
	if (event == EVENT_LBUTTONUP)
	{
		((MouseCallbackState*)userdata)->is_selection_started = false;
		((MouseCallbackState*)userdata)->is_selection_finished = true;
		((MouseCallbackState*)userdata)->point_second = Point(x, y);
		cout << "Left button of the mouse is up - position (" << x << ", " << y << ")" << endl;
	}
	if (event == EVENT_MOUSEMOVE && ((MouseCallbackState*)userdata)->is_selection_finished == false)
	{
		((MouseCallbackState*)userdata)->point_second = Point(x, y);
	}
}

int main(int argc, const char** argv) {

	CommandLineParser parser(argc, argv, kOptions);
	parser.about(kAbout);
	MouseCallbackState *MouseClick = new MouseCallbackState();

	if (parser.get<bool>("help")) {
		parser.printMessage();
		return 0;
	}
	


	Mat img1 = imread("pic1.JPG"), img2, roimat;

	if (img1.empty())
	{
		cout << "Error loading the image" << endl;
		return -1;
	}
	namedWindow("Window1", 1);
	setMouseCallback("Window1", OnMouse, (void*)MouseClick);

	imshow("Window1", img1);
	waitKey(25);
	while (!MouseClick->is_selection_finished)
		waitKey(25);
	ImageProcessorImpl ipi;

	Rect roi(MouseClick->point_first, MouseClick->point_second);
	//img2 = ipi.CvtColor(img1, roi);
	
	img2 = ipi.Filter(img1, roi,9);
	namedWindow("Window2", 1);
	imshow("Window2", img2);
	
	waitKey(0);

	return 0;
}
