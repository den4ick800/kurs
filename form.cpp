#include "form.h"
#include "ui_form.h"
#include <iostream>
#include <fstream>
Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    model=new car;
}

Form::~Form()
{
    delete ui;
}

void Form::on_pushButton_clicked()
{
    number_of_passenger=ui->passenger_cars->value();
    number_of_trucks=ui->trucks->value();
   number_of_crossover=ui->crossover->value();
   QString trf=ui->traffic_lights->currentText();
   if(trf=="true"){
       traffic_lights=true;
   }
   else{
       traffic_lights=false;
   }
    //traffic_lights=ui->traffic_lights;
    std::ofstream out;
    out.open("/Users/den4ick800/Desktop/grpahics/modeling_information.txt");
    if(out.is_open()){
    out<<number_of_passenger<<std::endl;
    out<<number_of_crossover<<std::endl;
    out<<number_of_trucks<<std::endl;
    out<<traffic_lights<<std::endl;
    out.close();
    }
    model->show();
    this->close();
}

