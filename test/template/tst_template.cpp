#include <QtTest>

class TemplateTest : public QObject
{
    Q_OBJECT

private slots:
    void onePlusOne();
};


void TemplateTest::onePlusOne()
{
    QCOMPARE(1 + 1, 2);
}


QTEST_GUILESS_MAIN(TemplateTest)
#include "tst_template.moc"
