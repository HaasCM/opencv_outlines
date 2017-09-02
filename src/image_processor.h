/*!
  \file image_processor.h
  \brief file to define ImageProcessor
*/

#ifndef IMAGE_PROCESSOR_H
#define IMAGE_PROCESSOR_H


#include <opencv2/imgproc/imgproc.hpp>
#include <QPixmap>
#include <QObject>

class ImageProcessor : public QObject{
  Q_OBJECT

public:
  ImageProcessor(QObject *parent = nullptr);
  ~ImageProcessor();

  static cv::Mat QPixmapToCvMat(const QPixmap &inImage);
  static QPixmap cvMatToQPixmap(const cv::Mat &inMatrix);

  QPixmap findContours(const QPixmap &pixmap) const;
  QPixmap findCorners(const QPixmap &pixmap) const;

protected:

private:

};

#endif //IMAGE_PROCESSOR_H
