/*!
  \file image_processor.cpp
  \brief file to define ImageProcessor
*/

#include "image_processor.h"

/*!
  \fn ImageProcessor::ImageProcessor(QObject *parent)
  \brief Default constructor for ImageProcessor
*/

ImageProcessor::ImageProcessor(QObject *parent) :
QObject(parent){
}

/*!
  \fn ImageProcessor::ImageProcessor()
  \brief Default destructor for ImageProcessor
*/

ImageProcessor::~ImageProcessor() {

}

/*!
  \fn cv::Mat ImageProcessor::QPixmapToCvMat(const QPixmap &inImage) const
  \brief converts a QPixmap to a matrix from openCV
*/
cv::Mat ImageProcessor::QPixmapToCvMat(const QPixmap &inImage) {
  QImage image = inImage.toImage();
  switch(image.format()) {
    case QImage::Format_ARGB32:
    case QImage::Format_ARGB32_Premultiplied:

      // for simplicity of this tutorial I am just cloning the returned matrix
      // because RGB32 and RGB888 algorithms require cloning so I want to keep
      // the same behavior across all conversions

      return cv::Mat(image.height(), image.width(),
                    CV_8UC4,
                    const_cast<uchar*>(image.bits()),
                    static_cast<size_t>(image.bytesPerLine())).clone();

    case QImage::Format_RGB32:
    case QImage::Format_RGB888:

      image = image.convertToFormat(QImage::Format_RGB888).rgbSwapped();

      return cv::Mat(image.height(), image.width(),
                    CV_8UC3,
                    const_cast<uchar*>(image.bits()),
                    static_cast<size_t>(image.bytesPerLine())).clone();

    case QImage::Format_Indexed8:

      return cv::Mat(image.height(), image.width(),
                    CV_8UC1,
                    const_cast<uchar*>(image.bits()),
                    static_cast<size_t>(image.bytesPerLine())).clone();

    default:
      return cv::Mat();
      break;
  }

}

/*!
  \fn QPixmap ImageProcessor::cvMatToQPixmap(const cv::Mat &inMatrix)
  \brief converts from an OpenCV matrix to a QPixmap
*/
QPixmap ImageProcessor::cvMatToQPixmap(const cv::Mat &inMatrix) {
  return QPixmap::fromImage(QImage((unsigned char*) inMatrix.data,
                                   inMatrix.cols,
                                   inMatrix.rows,
                                   QImage::Format_RGB888));
}

/*!
  \fn QPixmap ImageProcessor::findContours(const QPixmap &pixmap) const
  \brief finds the contours of the pixmap coming in
  \returns A QPixmap with the contours highlighted
*/
QPixmap ImageProcessor::findContours(const QPixmap &pixmap) const {
  cv::Mat sourceImage = QPixmapToCvMat(pixmap);
  cv::Mat grayedImage;

  //convert color to grayed image
  cv::cvtColor(sourceImage, grayedImage, cv::COLOR_BGR2GRAY);
  //blur the image
  // source, dest,
  cv::blur(grayedImage, grayedImage, cv::Size(3,3));

  const int threshold = 100; // threshold for hysteresis procedure
  cv::Mat cannyEdgeDetect;

  cv::Canny(grayedImage, cannyEdgeDetect, threshold, threshold*2);
  // locate the contours of the canny image and map the points
  cv::vector<cv::vector<cv::Point>> contours;
  cv::vector<cv::Vec4i> heirarchy;
  cv::findContours(cannyEdgeDetect, contours, heirarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point(0,0));

  // draw the contours on an image
  cv::Mat contourImage = cv::Mat::zeros(cannyEdgeDetect.size(), CV_8UC3);

  cv::RNG rng(12345);
  for(size_t i = 0; i < contours.size(); i++) {
    cv::Scalar color = cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
    cv::drawContours(contourImage, contours, (int)i, color, 2, 8, heirarchy, 0);
  }
  return cvMatToQPixmap(contourImage);
}

/*!
  \fn QPixmap ImageProcessor::findCorners(const QPixmap &pixmap) const
  \brief deploys a Harris corner detection algorithm on the pixmap
*/
QPixmap ImageProcessor::findCorners(const QPixmap &pixmap) const {
  cv::Mat sourceImage = QPixmapToCvMat(pixmap);
  cv::Mat grayedImage;

  //convert color to grayed image
  cv::cvtColor(sourceImage, grayedImage, cv::COLOR_BGR2GRAY);

  //detection parameters
  int blockSize = 2;
  int apetureSize = 3;
  double k = 0.04;
  cv::Mat destImage = cv::Mat::zeros(sourceImage.size(), CV_32FC1);

  cornerHarris(grayedImage, destImage, blockSize, apetureSize, k, cv::BORDER_DEFAULT);

  //normalize the image
  cv::Mat destImageNorm, destImageNormAndScaled;

  cv::normalize(destImage, destImageNorm, 0 , 255, cv::NORM_MINMAX, CV_32FC1, cv::Mat());
  convertScaleAbs(destImageNorm, destImageNormAndScaled);

  const int threshold = 200;
  for(int j = 0; j < destImageNorm.rows; j++) {
    for(int i = 0; i < destImageNorm.cols; i++) {
      if((int) destImageNorm.at<float>(j,i) > threshold) {
        // draw circle if it exceeds the threshold
        circle(destImageNormAndScaled, cv::Point(i,j), 5, cv::Scalar(0), 2, 8, 0);
      }
    }
  }
  return cvMatToQPixmap(destImageNormAndScaled);
}
