#include "multiscale/core/Multiscale.hpp"
#include "multiscale/analysis/spatial/factory/RectangularMatFactory.hpp"

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace multiscale::analysis;
using namespace std;

// Main function

int main() {
    RectangularMatFactory factory;

    Mat image = factory.createFromViewerImage("data/test/rectangular.png");

    namedWindow("Test", WINDOW_NORMAL);
    imshow("Test", image);

    cout << "Maximum colour bar intensity: "
         << factory.maxColourBarIntensityFromViewerImage("data/test/rectangular.png")
         << endl;

    waitKey(0);

    return multiscale::EXEC_SUCCESS_CODE;
}
