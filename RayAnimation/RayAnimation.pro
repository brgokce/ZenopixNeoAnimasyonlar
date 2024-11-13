QT       += core gui concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    buttoneventclass.cpp \
    channellabel.cpp \
    colorwheelwidget.cpp \
    core.cpp \
    hsbcolorwheel.cpp \
    labelclass.cpp \
    main.cpp \
    mainwindow.cpp \
    rayanimthread.cpp

HEADERS += \
    buttoneventclass.h \
    channellabel.h \
    colorwheelwidget.h \
    core.h \
    hsbcolorwheel.h \
    labelclass.h \
    mainwindow.h \
    rayanimthread.h

FORMS += \
    mainwindow.ui

INCLUDEPATH +=C:\Users\ASUS\Desktop\OPENCV2\opencv\build\install\include

LIBS += -L"C:\Users\ASUS\Desktop\OPENCV2\opencv\build\install\x64\mingw\bin" \
libopencv_aruco480 \
libopencv_aruco480 \
libopencv_bgsegm480 \
libopencv_bioinspired480 \
libopencv_calib3d480 \
libopencv_ccalib480 \
libopencv_core480 \
libopencv_cvv480 \
libopencv_datasets480 \
libopencv_dnn_objdetect480 \
libopencv_dnn480 \
libopencv_dpm480 \
libopencv_face480 \
libopencv_features2d480 \
libopencv_flann480 \
libopencv_fuzzy480 \
libopencv_hfs480 \
libopencv_highgui480 \
libopencv_img_hash480 \
libopencv_imgcodecs480 \
libopencv_imgproc480 \
libopencv_line_descriptor480 \
libopencv_ml480 \
libopencv_objdetect480 \
libopencv_optflow480 \
libopencv_phase_unwrapping480 \
libopencv_photo480 \
libopencv_plot480 \
libopencv_reg480 \
libopencv_rgbd480 \
libopencv_saliency480 \
libopencv_shape480 \
libopencv_stereo480 \
libopencv_stitching480 \
libopencv_structured_light480 \
libopencv_superres480 \
libopencv_surface_matching480 \
libopencv_text480 \
libopencv_tracking480 \
libopencv_video480 \
libopencv_videoio480 \
libopencv_videostab480 \
libopencv_xfeatures2d480 \
libopencv_ximgproc480 \
libopencv_xobjdetect480 \
libopencv_xphoto480


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
