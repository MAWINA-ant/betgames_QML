TEMPLATE = app

QT += quick qml quickwidgets core gui network webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

SOURCES += main.cpp \
    appcore.cpp \
    abstractgameclass.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    appcore.h \
    abstractgameclass.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
    AndroidManifest.xml \
    gradle/wrapper/gradle-wrapper.jar \
    gradlew \
    res/values/libs.xml \
    build.gradle \
    gradle/wrapper/gradle-wrapper.properties \
    gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD





