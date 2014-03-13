#include <gmock/gmock.h>
#include <gtest/gtest.h>

#ifdef QT_GUI_LIB
#include <QApplication>
#else
#include <QCoreApplication>
#endif

int main(int argc, char** argv) {
#ifdef QT_GUI_LIB
    QApplication app(argc, argv);
#else
    QCoreApplication app(argc, argv);
#endif
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}

