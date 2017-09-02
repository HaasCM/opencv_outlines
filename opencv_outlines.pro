#
# The qmake include used for OpenCV Outlines, to include common
# functionality and build layout.
#
#

# Configure Options
CONFIG += debug_and_release c++11

CONFIG += warn_on console
macx: CONFIG -= app_bundle
QT += network widgets
DEFINES += QT_MESSAGELOGCONTEXT # Required by message_router for context info

OPENCV_ROOT = $${PWD}
SRC = $${OPENCV_ROOT}/src

DESTDIR = $${OPENCV_ROOT}/bin

HEADERS += \
           $${SRC}/opencv_outlines_window.h \
    src/image_processor.h \
    src/image_widget.h

SOURCES += \
           $${SRC}/main.cpp \
           $${SRC}/opencv_outlines_window.cpp \
    src/image_processor.cpp \
    src/image_widget.cpp

FORMS += \
         $${SRC}/opencv_outlines_window_base.ui \
    src/image_widget_base.ui

# Temporary Destinations
OBJECTS_DIR = "$${OPENCV_OUTLINES}/tmp/obj"
MOC_DIR = "$${OPENCV_OUTLINES}/tmp/moc"
UI_DIR = "$${OPENCV_OUTLINES}/tmp/uic"
RCC_DIR = "$${OPENCV_OUTLINES}/tmp/rcc"

LIBS += -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy -lopencv_flann
