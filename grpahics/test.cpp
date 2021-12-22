#include "test.h"
#include <QTest>
#include <car.h>
Test::Test(QObject* parent):
    QObject(parent)
{

}
void  Test::test_return_function(){
    Automobile a;
    QCOMPARE(a.Mass(),0);
    QCOMPARE(a.model_Name(),"A");
    QCOMPARE(a.reliable(),0);
}
void Test::test_object(){
 Automobile a;
 object b;
 QCOMPARE(b.coord(),std::make_pair(0,0));


}
void Test::info_test(){
    std::vector<std::pair<int,int>> a=place_create();
     QCOMPARE(a[0],std::make_pair(234,20));
       QCOMPARE(a[1],std::make_pair(680,20));
       QCOMPARE(a[2],std::make_pair(1130,20));
       QCOMPARE(a[3],std::make_pair(265,760));
       QCOMPARE(a[4],std::make_pair(710,760));
       QCOMPARE(a[5],std::make_pair(20,270));
        QCOMPARE(a[6],std::make_pair(20,645));
         QCOMPARE(a[7],std::make_pair(1240,244));
          QCOMPARE(a[8],std::make_pair(1240,620));



}
void Test::test_ob(){
    object b;
    b.st();
    QCOMPARE(b.mv(),true);
    b.stop();
    QCOMPARE(b.mv(),false);
}
