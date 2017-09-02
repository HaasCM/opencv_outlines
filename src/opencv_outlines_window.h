/*!
  \file opencv_outlines_window.h
  \brief file to define OpenCVOutlinesWindow
*/

#ifndef OPENCV_OUTLINE_WINDOW_H
#define OPENCV_OUTLINE_WINDOW_H

#include "image_processor.h"

#include "ui_opencv_outlines_window_base.h"
#include <QMainWindow>
#include <QMap>
#include "image_widget.h"

class OpenCVOutlinesWindow :public QMainWindow, private Ui::OpenCVOutlinesWindowBase {
  Q_OBJECT

public:
  OpenCVOutlinesWindow(QWidget *parent=nullptr);
  ~OpenCVOutlinesWindow();

private:
  void tryToAddTab(const QString &tabTitle);

  QPixmap mSourceImage;
  ImageProcessor *mProcessor;
  QMap<QString, ImageWidget*> mImageWidgets;

private slots:
  void onLoadImage();
  void onLocateOutlines();
  void onLocateCorners();

};

#endif //OPENCV_OUTLINE_WINDOW_H
