#include <gmock/gmock.h>
#include <gtest/gtest.h>

#if defined(QT_WIDGETS_LIB)
#  include <QApplication>
#  define Application QApplication
#elif defined(QT_GUI_LIB)
#  include <QGuiApplication>
#  define Application QGuiApplication
#else
#  include <QCoreApplication>
#  define Application QCoreApplication
#endif

int main(int argc, char** argv)
{
    Application app(argc, argv);
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}

