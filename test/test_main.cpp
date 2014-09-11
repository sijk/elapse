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

#include <QSettings>


int main(int argc, char** argv)
{
    Application app(argc, argv);
    app.setApplicationName("elapse-test-" + app.applicationName());
    app.setOrganizationName("test");

    QSettings::setPath(QSettings::defaultFormat(), QSettings::SystemScope,
                       app.applicationDirPath());
    QSettings::setPath(QSettings::defaultFormat(), QSettings::UserScope,
                       app.applicationDirPath());

    QSettings settings;
    for (auto key : settings.allKeys())
        settings.remove(key);

    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}

