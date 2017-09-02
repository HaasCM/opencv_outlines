/*!
  \file image_widget.cpp
  \brief file to define ImageWidget
*/

#include "image_widget.h"

/*!
  \fn ImageWidget::ImageWidget(QWidget *parent)
  \brief Default constructor for ImageWidget
*/

ImageWidget::ImageWidget(QWidget *parent) :
QWidget(parent) {
  setupUi(this);
  QGraphicsScene *scene = new QGraphicsScene(this);
  imageView->setScene(scene);
}

/*!
  \fn ImageWidget::ImageWidget()
  \brief Default destructor for ImageWidget
*/

ImageWidget::~ImageWidget() {

}

/*!
  \fn void ImageWidget::setImage(const QPixmap &image)
  \brief sets the image in the scene
*/
void ImageWidget::setImage(const QPixmap &image) {
  onReset();
  imageView->scene()->addPixmap(image);
  resizeScene();
}

/*!
  \fn void ImageWidget::onReset()
  \brief handles the reset signal from the main window
*/
void ImageWidget::onReset() {
  imageView->scene()->clear();
  //resizeScene();
}

/*!
  \fn void ImageWidget::resizeEvent(QResizeEvent *event)
  \brief overrides the widgets event handler for resize events
*/
void ImageWidget::resizeEvent(QResizeEvent *event) {
  QWidget::resizeEvent(event);
  resizeScene();
}

/*!
  \fn void ImageWidget::resizeScene()
  \brief resizes the view's scene to perfectly match the view
*/
void ImageWidget::resizeScene() {
  imageView->fitInView(imageView->scene()->sceneRect(), Qt::KeepAspectRatio);
}

/*!
  \fn void ImageWidget::onCurrentChanged()
  \brief handles the changing of the tabs for resizing
*/
void ImageWidget::onCurrentChanged() {
  if(isVisible()) {
    resizeScene();
  }
}
