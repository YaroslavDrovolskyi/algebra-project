#include <QtTest>
#include <QCoreApplication>

// add necessary includes here
#include "BigModInt.h"
#include "Polynomial.h"

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

    void test_gcdExt();
    void test_inverse();
    void test_bigmodint_div();
    void test_polynomial_plus();
    void test_polynomial_minus();
    void test_polynomial_mult();
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

void ModArithmeticTest::test_gcdExt()
{
    //k=2 and f=7 it must return x=-3 and y=1;
    BigInt k("2"),f("7"),x,y;
    gcdExtended(k,f,&x,&y);
    QVERIFY(x==-3 && y==1);
    //k=2 and f=6 it must return x=1 and y=0;
    f={"6"};
    gcdExtended(k,f,&x,&y);
    QVERIFY(x==1 && y==0);
}

void ModArithmeticTest::test_inverse()
{
    //modulo inverse of 2 and 7 is 4
    BigInt x, y;
    BigInt anum("2"),amod("7");
    gcdExtended(anum, amod, &x, &y);
    BigInt result_number;
    while(x<0){
        x = x + amod;
    }
    result_number = (x % amod + amod) % amod;
    QVERIFY(x==4);
}

void ModArithmeticTest::test_bigmodint_div()
{
    // modulo inverse of 5 is 3. than 2*3 mod 7 equals 6
    BigInt x, y;
    BigInt anum("2"), amod("7"), bnum("5"), bmod("7");
    gcdExtended(bnum, bmod, &x, &y);
    BigInt cnum;
    while(x<0){
        x = x + bmod;
    }
    cnum = (x % bmod + bmod) % bmod;
    BigInt result_number = (anum * cnum) % amod;
    QVERIFY(result_number==6);
}

void ModArithmeticTest::test_polynomial_plus()
{
    std::vector<BigInt> pol = {5,8,3,7,2};
    Polynomial poly(pol,7);

    std::vector<BigInt> pol2 = {2,2,3,1,7};
    Polynomial poly2(pol2,7);

    Polynomial result = poly+poly2;
    std::vector<BigModInt> res = {{0,7},{3,7},{6,7},{1,7},{2,7}};
    QVERIFY(result.getPolynomial()==res);

    pol = {5,18,3,7,9};
    poly = {pol,7};

    pol2 = {2,9,3,1};
    poly2 = {pol2,7};

    result = poly+poly2;
    res = {{0,7},{6,7},{6,7},{1,7},{2,7}};
    QVERIFY(result.getPolynomial()==res);


    pol = {2,9,3,1};
    poly = {pol,7};

    pol2 = {5,18,3,7,9};
    poly2 = {pol2,7};

    result = poly+poly2;
    res = {{0,7},{6,7},{6,7},{1,7},{2,7}};
    QVERIFY(result.getPolynomial()==res);
}

void ModArithmeticTest::test_polynomial_minus()
{
    std::vector<BigInt> pol = {5,8,3,7,2};
    Polynomial poly(pol,7);

    std::vector<BigInt> pol2 = {2,2,3,1,7};
    Polynomial poly2(pol2,7);

    Polynomial result = poly-poly2;
    std::vector<BigModInt> res = {{3,7},{6,7},{0,7},{6,7},{2,7}};
    QVERIFY(result.getPolynomial()==res);

    pol = {5,18,3,7,9};
    poly = {pol,7};

    pol2 = {2,9,3,1};
    poly2 = {pol2,7};

    result = poly-poly2;
    res = {{3,7},{2,7},{0,7},{6,7},{2,7}};
    QVERIFY(result.getPolynomial()==res);


    pol = {2,9,3,1};
    poly = {pol,7};

    pol2 = {5,18,3,7,9};
    poly2 = {pol2,7};

    result = poly-poly2;
    res = {{4,7},{5,7},{0,7},{1,7},{5,7}};
    QVERIFY(result.getPolynomial()==res);
}

void ModArithmeticTest::test_polynomial_mult()
{
    std::vector<BigInt> pol = {5,8,3,7,2};
    Polynomial poly(pol,7);

    std::vector<BigInt> pol2 = {2,2,3,1,7};
    Polynomial poly2(pol2,7);

    Polynomial result = poly*poly2;
    std::vector<BigModInt> res = {{3,7},{5,7},{2,7},{0,7},{0,7},{0,7},{6,7},{2,7}};
    QVERIFY(result.getPolynomial()==res);
}

QTEST_MAIN(ModArithmeticTest)

#include "tst_modarithmetictest.moc"
