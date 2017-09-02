#include "opencv_outlines_window.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  OpenCVOutlinesWindow window;
  window.show();

  return a.exec();
}
