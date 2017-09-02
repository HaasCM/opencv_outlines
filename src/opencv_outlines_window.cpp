/*!
  \file opencv_outlines_window.cpp
  \brief file to define OpenCVOutlinesWindow
*/

#include <QDir>
#include <QFileDialog>
#include <QPixmap>

#include "opencv_outlines_window.h"

/*!
  \fn OpenCVOutlinesWindow::OpenCVOutlinesWindow(QWidget *parent)
  \brief Default constructor for OpenCVOutlinesWindow
*/
OpenCVOutlinesWindow::OpenCVOutlinesWindow(QWidget *parent) :
QMainWindow(parent) {
setupUi(this);
mProcessor = new ImageProcessor(this);

//remove all image tabs
imageTabs->removeTab(1);
imageTabs->removeTab(0);

connect(actionLoad, &QAction::triggered,
       this, &OpenCVOutlinesWindow::onLoadImage);
connect(actionOutlines, &QAction::triggered,
        this, &OpenCVOutlinesWindow::onLocateOutlines);
connect(actionCorners, &QAction::triggered,
        this, &OpenCVOutlinesWindow::onLocateCorners);
}

/*!
  \fn OpenCVOutlinesWindow::OpenCVOutlinesWindow()
  \brief Default destructor for OpenCVOutlinesWindow
*/
OpenCVOutlinesWindow::~OpenCVOutlinesWindow() {
}


/*!
  \fn void OpenCVOutlinesWindow::onLoadImage()
  \brief handles the signal from the load action
*/
void OpenCVOutlinesWindow::onLoadImage() {
  const QString title = "Source";
  tryToAddTab(title);
  const QString picturePath = QFileDialog::getOpenFileName(this, "Import Image",
                                                           QDir::homePath(),
                                                           "Images (*.jpeg *.png *.jpg)");
  mSourceImage.load(picturePath);

  mImageWidgets[title]->setImage(mSourceImage);
}

/*!
  \fn void OpenCVOutlinesWindow::onLocateOutlines()
  \brief handles the triggered signal from locating the outlines
*/
void OpenCVOutlinesWindow::onLocateOutlines() {
  const QString title = "Contours";
  tryToAddTab(title);
  if(!mSourceImage.isNull()) {
    QPixmap contours = mProcessor->findContours(mSourceImage);
    mImageWidgets[title]->setImage(contours);
  }
}

/*!
  \fn void OpenCVOutlinesWindow::onLocateCorners()
  \brief handles the triggered signal from locating the corners
*/
void OpenCVOutlinesWindow::onLocateCorners() {
  const QString title = "Corners";
  tryToAddTab(title);
  if(!mSourceImage.isNull()) {
    QPixmap corners = mProcessor->findCorners(mSourceImage);
    mImageWidgets[title]->setImage(corners);
  }
}

/*!
  \fn void OpenCVOutlinesWindow::tryToAddTab(const QString &tabTitle)
  \brief attempts to add a tab to the imagesTab widget
*/
void OpenCVOutlinesWindow::tryToAddTab(const QString &tabTitle) {
  if(!mImageWidgets.contains(tabTitle)) {
    mImageWidgets[tabTitle] = new ImageWidget(this);
    imageTabs->addTab(mImageWidgets[tabTitle], tabTitle);
    connect(actionLoad, &QAction::triggered,
            mImageWidgets[tabTitle], &ImageWidget::onReset);
    connect(actionReset, &QAction::triggered,
            mImageWidgets[tabTitle], &ImageWidget::onReset);
    connect(imageTabs, &QTabWidget::currentChanged,
            mImageWidgets[tabTitle], &ImageWidget::onCurrentChanged);
  }
}


