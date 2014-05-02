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
    app.setApplicationName("elapse-test-" + qAppName());
    app.setOrganizationName("test");

    QSettings::setPath(QSettings::defaultFormat(), QSettings::SystemScope,
                       qApp->applicationDirPath());
    QSettings::setPath(QSettings::defaultFormat(), QSettings::UserScope,
                       qApp->applicationDirPath());

    QSettings settings;
    foreach (auto key, settings.allKeys())
        settings.remove(key);

    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}

