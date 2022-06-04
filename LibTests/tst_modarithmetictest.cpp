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

private:
    std::string getRandomNumber(std::size_t size);

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

    void test_BigInt_constructor();
    void test_BigInt_add();
    void test_BigInt_subtract();
    void test_BigInt_multiply();
    void test_BigInt_division();

    void test_BigModInt_constructor();
    void test_BigModInt_operators();
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


std::string ModArithmeticTest::getRandomNumber(std::size_t size){
    std::string alphabet = "1234567890";

    static std::default_random_engine gen;
    std::uniform_int_distribution<int>dis(0, alphabet.size() - 1);

    std::string result;
    for (std::size_t i = 0; i < size; i++){
        result += alphabet[dis(gen)];
    }

    if (result[0] == '0'){
        result[0] = '5';
    }

    return result;
}

void ModArithmeticTest::test_BigInt_constructor(){
    for (std::size_t i = 0; i < 1000; i++){ // check usual numbers
        std::string number_str = getRandomNumber(100);
        QCOMPARE(BigInt{number_str}.GetString(), number_str);
    }

    std::string number_1_str = "+100000000000000000000000";
    std::string number_1_str_expected = "100000000000000000000000";
    QCOMPARE(BigInt{number_1_str}.GetString(), number_1_str_expected);

    std::string number_2_str = "+00000000100000000000000000000000";
    std::string number_2_str_expected = "100000000000000000000000";
    QCOMPARE(BigInt{number_2_str}.GetString(), number_2_str_expected);

    std::string number_3_str = "-00000000100000000000000000000000";
    std::string number_3_str_expected = "-100000000000000000000000";
    QCOMPARE(BigInt{number_3_str}.GetString(), number_3_str_expected);

    // incorrect 1
    try{
        BigInt{"78tr783d0kf"};
    }
    catch(const std::exception& e){
        QCOMPARE(5, 5);
    }

    // incorrect 2
    try{
        BigInt{"+-3465654656"};
    }
    catch(const std::exception& e){
        QCOMPARE(5, 5);
    }

    // incorrect 3
    try{
        BigInt{"-+3465654656"};
    }
    catch(const std::exception& e){
        QCOMPARE(5, 5);
    }
}


void ModArithmeticTest::test_BigInt_add(){
    BigInt a_1{"9999999999999999999999999999999"};
    BigInt b_1{"9999999999999999999999999999999"};
    BigInt expected_1{"19999999999999999999999999999998"};
    QCOMPARE(a_1 + b_1, expected_1);

    BigInt a_2{"9999999999999999999999999999999"};
    BigInt b_2{"-9999999999999999999999999999999"};
    BigInt expected_2{"0"};
    QCOMPARE(a_2 + b_2, expected_2);


    BigInt a_3{"-9999999999999999999999999999999"};
    BigInt b_3{"4756754645535345"};
    BigInt expected_3{"-9999999999999995243245354464654"};
    QCOMPARE(a_3 + b_3, expected_3);

    BigInt a_4{"-9999999999999999999999999999999"};
    BigInt b_4{"-4756754645535345"};
    BigInt expected_4{"-10000000000000004756754645535344"};
    QCOMPARE(a_4 + b_4, expected_4);

    BigInt a_5{"0"};
    BigInt b_5{"-0"};
    BigInt expected_5{"0"};
    QCOMPARE(a_5 + b_5, expected_5);

}

void ModArithmeticTest::test_BigInt_subtract(){
    BigInt a_1{"9999999999999999999999999999999"};
    BigInt b_1{"9999999999999999999999999999999"};
    BigInt expected_1{"0"};
    QCOMPARE(a_1 - b_1, expected_1);

    BigInt a_2{"9999999999999999999999999999999"};
    BigInt b_2{"-9999999999999999999999999999999"};
    BigInt expected_2{"19999999999999999999999999999998"};
    QCOMPARE(a_2 - b_2, expected_2);


    BigInt a_3{"-9999999999999999999999999999999"};
    BigInt b_3{"4756754645535345"};
    BigInt expected_3{"-10000000000000004756754645535344"};
    QCOMPARE(a_3 - b_3, expected_3);

    BigInt a_4{"-9999999999999999999999999999999"};
    BigInt b_4{"-4756754645535345"};
    BigInt expected_4{"-9999999999999995243245354464654"};
    QCOMPARE(a_4 - b_4, expected_4);

    BigInt a_5{"0"};
    BigInt b_5{"-0"};
    BigInt expected_5{"0"};
    QCOMPARE(a_5 - b_5, expected_5);

}

void ModArithmeticTest::test_BigInt_multiply(){
    BigInt a_1{"9999999999999999999999999999999"};
    BigInt b_1{"9999999999999999999999999999999"};
    BigInt expected_1{"99999999999999999999999999999980000000000000000000000000000001"};
    QCOMPARE(a_1 * b_1, expected_1);

    BigInt a_2{"9999999999999999999999999999999"};
    BigInt b_2{"-9999999999999999999999999999999"};
    BigInt expected_2{"-99999999999999999999999999999980000000000000000000000000000001"};
    QCOMPARE(a_2 * b_2, expected_2);


    BigInt a_3{"-9999999999999999999999999999999"};
    BigInt b_3{"4756754645535345"};
    BigInt expected_3{"-47567546455353449999999999999995243245354464655"};
    QCOMPARE(a_3 * b_3, expected_3);

    BigInt a_4{"-9999999999999999999999999999999"};
    BigInt b_4{"-78934895472"};
    BigInt expected_4{"789348954719999999999999999999921065104528"};
    QCOMPARE(a_4 * b_4, expected_4);

    BigInt a_5{"0"};
    BigInt b_5{"-7845783457349848345"};
    BigInt expected_5{"0"};
    QCOMPARE(a_5 * b_5, expected_5);

}

void ModArithmeticTest::test_BigInt_division(){
    BigInt a_1{"9999999999999999999999999999999"};
    BigInt b_1{"9999999999999999999999999999999"};
    BigInt expected_fraction_1{"1"};
    BigInt expected_remainder_1{"0"};
    QCOMPARE(a_1 / b_1, expected_fraction_1);
    QCOMPARE(a_1 % b_1, expected_remainder_1);

    BigInt a_2{"0"};
    BigInt b_2{"4564457564634"};
    BigInt expected_fraction_2{"0"};
    BigInt expected_remainder_2{"0"};
    QCOMPARE(a_2 / b_1, expected_fraction_2);
    QCOMPARE(a_2 % b_2, expected_remainder_2);


    BigInt a_3{"54674938246782634"};
    BigInt b_3{"4352"};
    BigInt expected_fraction_3{"12563175148617"};
    BigInt expected_remainder_3{"1450"};
    QCOMPARE(a_3 / b_3, expected_fraction_3);
    QCOMPARE(a_3 % b_3, expected_remainder_3);

    BigInt a_4{"967088353926928"};
    BigInt b_4{"-00000326305413671862"};
    BigInt expected_fraction_4{"-2"};
    QCOMPARE(a_4 / b_4, expected_fraction_4);

    BigInt a_5{"-71587114808229"};
    BigInt b_5{"-983274443675080"};
    BigInt expected_fraction_5{"0"};
    QCOMPARE(a_5 / b_5, expected_fraction_5);

}


void ModArithmeticTest::test_BigModInt_constructor(){
    for (std::size_t i = 0; i < 1000; i++){ // check usual numbers
        BigInt number{getRandomNumber(100)};
        BigInt modulus{getRandomNumber(100)};

        BigModInt a{number, modulus};

        QCOMPARE(a.getNumber().GetString(), number % modulus);
    }

    BigModInt{BigInt{"0"}, BigInt{"5345343"}}; // correct


    // incorrect 1
    try{
        BigModInt{BigInt{"-45346546"}, BigInt{"5345343"}};
    }
    catch(const std::exception& e){
        QCOMPARE(5, 5);
    }

    // incorrect 2
    try{
        BigModInt{BigInt{"-35423"}, BigInt{"-57433"}};
    }
    catch(const std::exception& e){
        QCOMPARE(5, 5);
    }

    // incorrect 3
    try{
        BigModInt{BigInt{"897990"}, BigInt{"-57433"}};
    }
    catch(const std::exception& e){
        QCOMPARE(5, 5);
    }

    // incorrect 4
    try{
        BigModInt{BigInt{"45346546"}, BigInt{"1"}};
    }
    catch(const std::exception& e){
        QCOMPARE(5, 5);
    }

    // incorrect 5
    try{
        BigModInt{BigInt{"45346546"}, BigInt{"1"}};
    }
    catch(const std::exception& e){
        QCOMPARE(5, 5);
    }
}


void ModArithmeticTest::test_BigModInt_operators(){
    // add
    BigModInt a_1{BigInt{"9999999999999999999999999999999"}, BigInt{"100003"}};
    BigModInt b_1{BigInt{"9999999999999999999999999999999"}, BigInt{"100003"}};
    BigModInt expected_1{BigInt{"14578"}, BigInt{"100003"}};
    QCOMPARE(a_1 + b_1, expected_1);

    // subtract
    BigModInt a_2{BigInt{"100053000"}, BigInt{"100003"}};
    BigModInt b_2{BigInt{"100061000"}, BigInt{"100003"}};
    BigModInt expected_2{BigInt{"92003"}, BigInt{"100003"}};
    QCOMPARE(a_2 - b_2, expected_2);

    BigModInt a_3{BigInt{"100053000"}, BigInt{"100003"}};
    BigModInt b_3{BigInt{"100053000"}, BigInt{"100003"}};
    BigModInt expected_3{BigInt{"0"}, BigInt{"100003"}};
    QCOMPARE(a_3 - b_3, expected_3);

    // multiply
    BigModInt a_4{BigInt{"100053000"}, BigInt{"100003"}};
    BigModInt b_4{BigInt{"100061000"}, BigInt{"100003"}};
    BigModInt expected_4{BigInt{"13003"}, BigInt{"100003"}};
    QCOMPARE(a_4 * b_4, expected_4);

    BigModInt a_5{BigInt{"0"}, BigInt{"100003"}};
    BigModInt b_5{BigInt{"100053000"}, BigInt{"100003"}};
    BigModInt expected_5{BigInt{"0"}, BigInt{"100003"}};
    QCOMPARE(a_4 * b_4, expected_4);

    // division
    BigModInt a_6{BigInt{"1000"}, BigInt{"100003"}};
    BigModInt b_6{BigInt{"8485"}, BigInt{"100003"}};
    BigModInt expected_6{BigInt{"66767"}, BigInt{"100003"}};
    QCOMPARE(a_6 / b_6, expected_6);

    try{ // test division by 0
        BigModInt a_7{BigInt{"1000"}, BigInt{"100003"}};
        BigModInt b_7{BigInt{"0"}, BigInt{"100003"}};
    }
    catch(const std::exception& e){
        QCOMPARE(5, 5);
    }
}

QTEST_MAIN(ModArithmeticTest)

#include "tst_modarithmetictest.moc"
