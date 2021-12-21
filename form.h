#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <car.h>
namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Form *ui;
    car *model;
    int number_of_passenger=0;
    int number_of_trucks=0;
    int number_of_crossover=0;
    bool traffic_lights;
    int number_of_lines=0;
};

#endif // FORM_H
