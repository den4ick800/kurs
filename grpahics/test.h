#ifndef TEST_H
#define TEST_H

#include <QObject>

class Test:public QObject
{
    Q_OBJECT
public:
    explicit Test(QObject *parent = 0);
private slots:
    void test_return_function();
    void test_object();
    void info_test();
    void test_ob();
};

#endif // TEST_H
