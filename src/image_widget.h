/*!
  \file image_widget.h
  \brief file to define ImageWidget
*/

#ifndef IMAGE_WIDGET_H
#define IMAGE_WIDGET_H

#include <QPixmap>
#include <QWidget>
#include "ui_image_widget_base.h"

class ImageWidget : public QWidget, private Ui::imageWidgetBase {
  Q_OBJECT

public:
  ImageWidget(QWidget *parent=nullptr);
  ~ImageWidget();

  void setImage(const QPixmap &image);
public slots:
  void onReset();
  void onCurrentChanged();

protected:
  void resizeEvent(QResizeEvent *event);
private:
  void resizeScene();
};

#endif //IMAGE_WIDGET_H
