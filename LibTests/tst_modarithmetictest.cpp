#include <QtTest>
#include <QCoreApplication>

// add necessary includes here
#include "BigModInt.h"

class ModArithmeticTest : public QObject
{
    Q_OBJECT

public:
    ModArithmeticTest();
    ~ModArithmeticTest();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

ModArithmeticTest::ModArithmeticTest()
{

}

ModArithmeticTest::~ModArithmeticTest()
{

}

void ModArithmeticTest::initTestCase()
{

}

void ModArithmeticTest::cleanupTestCase()
{

}

void ModArithmeticTest::test_case1()
{
    BigModInt a({"2345"}, {"2332"});
    QVERIFY(true);
}

QTEST_MAIN(ModArithmeticTest)

#include "tst_modarithmetictest.moc"
