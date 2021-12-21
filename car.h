#ifndef CAR_H
#define CAR_H

#include <QWidget>
#include <QImage>
#include <QRectF>
#include <QPainter>
#include <QGraphicsPixmapItem>
#include<QGraphicsView>
#include <thread>
#include <mutex>
#include <QTime>
#include <QTimer>
#include <chrono>
#include <fstream>
class Automobile{
private:
    std::string model_name;
    double mass;
    double reliability;
public:
    Automobile(){
        model_name="";
        mass=0;
        reliability=0;
    }
    Automobile(std::string& type){
        if(type=="passenger"){
            int c=rand()%3;
            if(c==1){
                model_name="Kia Rio";
                mass=1200;
                reliability=0.6;
            }
            if(c==2){
                model_name="Lada Vesta";
                mass=1300;
                reliability=0.3;
            }
            if(c==0){
                model_name="Mercedes C63";
                mass=1800;
                reliability=0.9;
            }
        }
        if(type=="crossover"){
            int c=rand()%3;
            if(c==1){
                model_name="Toyata RAV4";
                mass=1700;
                reliability=0.9;
            }
            if(c==2){
                model_name="Lada Niva";
                mass=1300;
                reliability=0.3;
            }
            if(c==0){
                model_name="Hyndai Creta";
                mass=1700;
                reliability=0.6;
            }
        }
        if(type=="truck"){
            int c=rand()%3;
            if(c==1){
                model_name="Mercedes-Benz Acorcs";
                mass=2700;
                reliability=0.9;
            }
            if(c==2){
                model_name="Kamaz";
                mass=2300;
                reliability=0.3;
            }
            if(c==0){
                model_name="Renault T";
                mass=2700;
                reliability=0.6;
            }
        }
    }
    std::string model_Name(){
        return model_name;
    }
    double Mass(){
        return mass;
    }
    double reliable(){
        return reliability;
    }
    bool operator!=(Automobile& rhs){
        if(model_name!=rhs.model_name){
            return true;
        }
        if(mass!=rhs.mass){
            return true;
        }
        if(reliability!=rhs.reliability){
            return true;
        }
        return false;
    }
     ~Automobile()=default;
};
class object  {
private:
    Automobile car;
    QGraphicsPixmapItem* model;
    std::pair<int,int> place;
    bool move;
    std::string var;
public:
    object(){
        car=Automobile();
        model=new QGraphicsPixmapItem;
        place=std::make_pair(0,0);
        move=false;
    }
    object(Automobile& a,QPixmap& b,std::pair<int,int>& c){
        car=a;
         model=new QGraphicsPixmapItem;
        model->setPixmap(b);
        place=c;
        move=false;
        if((place==std::make_pair(234,20)) || (place==std::make_pair(680,20)) || (place==std::make_pair(1130,20))){
            var="down";
        }
        if((place==std::make_pair(265,760)) || (place==std::make_pair(710,760)) ){
            var="up";
        }
        if((place==std::make_pair(20,270)) || (place==std::make_pair(20,645))){
            var="right";
        }
        if((place==std::make_pair(1240,244)) || (place==std::make_pair(1240,620))){
            var="left";
        }
    }
    bool operator==(object& rhs){
        if(car!=rhs.car){
            return false;
        }
        if(model!=rhs.model){
            return false;
        }
        if(move!=rhs.move){
            return false;
        }
        if(var!=rhs.var){
            return false;
        }
        if(place!=rhs.place){
            return false;
        }
        return true;
    }
    void show(int x,int y,QGraphicsScene *scene){
        scene->addItem(model);
        model->setPos(x,y);
    }
    void clear(){
        move=false;
        model->setOpacity(0);
    }
    void disappear(){
        model->setOpacity(0);
    }
    void appear(){
        model->setOpacity(1);
    }
    std::pair<int,int> coord(){
        return place;
    }
    void st(){
        move=true;
    }
    void change_direction_from_down(std::string& type){
        if(type=="right"){
            model_change(type);
            place.first+=50;
            place.second+=15;
            model->moveBy(50,15);
            model->setPos(place.first,place.second);
            var="right";
        }
        if(type=="left"){
            model_change(type);
            place.first-=76;
            place.second-=5;
            model->moveBy(-76,-5);
             model->setPos(place.first,place.second);
            var="left";
        }
        if(type=="up"){
            model_change(type);
            place.first+=30;
            place.second-=75;
            model->moveBy(30,-75);
             model->setPos(place.first,place.second);
            var="up";
        }
        if(type=="down"){
            place.second+=53;
            model->moveBy(0,53);
             model->setPos(place.first,place.second);
        }
    }
    void change_direction_from_up(std::string& type){
        if(type=="right"){
            model_change(type);
            place.first+=25;
            place.second-=25;
            model->moveBy(25,-25);
             model->setPos(place.first,place.second);
            var="right";
        }
        if(type=="left"){
            model_change(type);
            place.first-=75;
            place.second-=55;
            model->moveBy(-75,-55);
             model->setPos(place.first,place.second);
            var="left";

        }
        if(type=="up"){
            place.second-=25;
            model->moveBy(0,-25);
             model->setPos(place.first,place.second);

        }
        if(type=="down"){
            model_change(type);
            place.first-=30;
            place.second-=30;
            model->moveBy(-30,-30);
             model->setPos(place.first,place.second);
            var="down";
        }
    }
    void change_direction_from_right(std::string& type){
        if(type=="down"){
            model_change(type);
            place.first+=15;
            place.second+=25;
            model->moveBy(15,25);
             model->setPos(place.first,place.second);
            var="down";
        }
        if(type=="up"){
            model_change(type);
            place.first+=30;
            place.second-=25;
            model->moveBy(30,-25);
             model->setPos(place.first,place.second);
            var="up";
        }
        if(type=="right"){
            place.first+=50;
            model->moveBy(50,0);
             model->setPos(place.first,place.second);
        }
        if(type=="left"){
            model_change(type);
            place.first-=50;
            place.second-=25;
            model->moveBy(-50,-25);
             model->setPos(place.first,place.second);
            var="left";
        }
    }
    void change_direction_from_left(std::string& type){
        if(type=="left"){
            place.first-=50;
            model->moveBy(-50,0);
            model->setPos(place.first,place.second);
        }
        if(type=="up"){
            model_change(type);
            place.first-=35;
            place.second-=25;
            model->moveBy(-35,-25);
            model->setPos(place.first,place.second);
            var="up";
        }
        if(type=="down"){
            model_change(type);
            place.first-=65;
            place.second+=25;
            model->moveBy(-65,25);
            model->setPos(place.first,place.second);
            var="down";
        }
        if(type=="right"){
            model_change(type);
            place.first+=25;
            place.second+=25;
            model->moveBy(50,25);
            model->setPos(place.first,place.second);
            var="right";
        }
    }
    bool is_movable(){
        if(move){
            return true;
        }
        else
        {
            return false;
        }
    }
    std::string vr(){
        return var;
    }
    void moving(int x,int y){
        model->moveBy(x,y);
        place.first+=x;
        place.second+=y;
    }
    std::string dir(){
        return var;
    }
    Automobile avto(){
        return car;
    }

    void model_change(std::string a){
        //down
        if(a=="down"){
    if(car.model_Name()=="Kia Rio"){
        model->setPixmap( QPixmap("/Users/den4ick800/Desktop/grpahics/Kia Rio down.png"));
    }
    if(car.model_Name()=="Lada Vesta"){
        model->setPixmap( QPixmap("/Users/den4ick800/Desktop/grpahics/Lada Vesta down.png"));
    }
    if(car.model_Name()=="Mercedes C63"){
        model->setPixmap( QPixmap("/Users/den4ick800/Desktop/grpahics/Mercedes C63 down.png"));
    }
    if(car.model_Name()=="Toyata RAV4"){
        model->setPixmap( QPixmap("/Users/den4ick800/Desktop/grpahics/Toyata RAV4 down.png"));
    }
    if(car.model_Name()=="Lada Niva"){
       model->setPixmap( QPixmap("/Users/den4ick800/Desktop/grpahics/Lada Niva down.png"));
    }
    if(car.model_Name()=="Hyndai Creta"){
        model->setPixmap( QPixmap("/Users/den4ick800/Desktop/grpahics/Hyndai Creta down.png"));
    }
    if(car.model_Name()=="Mercedes-Benz Acorcs"){
        model->setPixmap( QPixmap("/Users/den4ick800/Desktop/grpahics/Mercedes-Benz Acorcs down.png"));
    }
    if(car.model_Name()=="Kamaz"){
        model->setPixmap( QPixmap("/Users/den4ick800/Desktop/grpahics/Kamaz down.png"));
    }
    if(car.model_Name()=="Renault T"){
       model->setPixmap( QPixmap("/Users/den4ick800/Desktop/grpahics/Renault T down.png"));
    }
        }

        //up
       if(a=="up") {
           if(car.model_Name()=="Kia Rio"){
               model->setPixmap( QPixmap("/Users/den4ick800/Desktop/grpahics/Kia Rio up.png"));
           }
           if(car.model_Name()=="Lada Vesta"){
               model->setPixmap( QPixmap("/Users/den4ick800/Desktop/grpahics/Lada Vesta up.png"));
           }
           if(car.model_Name()=="Mercedes C63"){
              model->setPixmap( QPixmap("/Users/den4ick800/Desktop/grpahics/Mercedes C63 up.png"));
           }
           if(car.model_Name()=="Toyata RAV4"){
              model->setPixmap( QPixmap("/Users/den4ick800/Desktop/grpahics/Toyata RAV4 up.png"));
           }
           if(car.model_Name()=="Lada Niva"){
               model->setPixmap( QPixmap("/Users/den4ick800/Desktop/grpahics/Lada Niva up.png"));
           }
           if(car.model_Name()=="Hyndai Creta"){
              model->setPixmap( QPixmap("/Users/den4ick800/Desktop/grpahics/Hyndai Creta up.png"));
           }
           if(car.model_Name()=="Mercedes-Benz Acorcs"){
               model->setPixmap( QPixmap("/Users/den4ick800/Desktop/grpahics/Mercedes-Benz Acorcs up.png"));
           }
           if(car.model_Name()=="Kamaz"){
               model->setPixmap( QPixmap("/Users/den4ick800/Desktop/grpahics/Kamaz up.png"));
           }
           if(car.model_Name()=="Renault T"){
               model->setPixmap( QPixmap("/Users/den4ick800/Desktop/grpahics/Renault T up.png"));
           }
       }

       //right
       if(a=="right"){
           if(car.model_Name()=="Kia Rio"){
               model->setPixmap( QPixmap("/Users/den4ick800/Desktop/grpahics/Kia Rio right.png"));
           }
           if(car.model_Name()=="Lada Vesta"){
             model->setPixmap( QPixmap("/Users/den4ick800/Desktop/grpahics/Lada Vesta right.png"));
           }
           if(car.model_Name()=="Mercedes C63"){
               model->setPixmap( QPixmap("/Users/den4ick800/Desktop/grpahics/Mercedes C63 right.png"));
           }
           if(car.model_Name()=="Toyata RAV4"){
              model->setPixmap( QPixmap("/Users/den4ick800/Desktop/grpahics/Toyata RAV4 right.png"));
           }
           if(car.model_Name()=="Lada Niva"){
               model->setPixmap( QPixmap("/Users/den4ick800/Desktop/grpahics/Lada Niva right.png"));
           }
           if(car.model_Name()=="Hyndai Creta"){
               model->setPixmap( QPixmap("/Users/den4ick800/Desktop/grpahics/Hyndai Creta right.png"));
           }
           if(car.model_Name()=="Mercedes-Benz Acorcs"){
              model->setPixmap( QPixmap("/Users/den4ick800/Desktop/grpahics/Mercedes-Benz Acorcs right.png"));
           }
           if(car.model_Name()=="Kamaz"){
              model->setPixmap( QPixmap("/Users/den4ick800/Desktop/grpahics/Kamaz right.png"));
           }
           if(car.model_Name()=="Renault T"){
              model->setPixmap( QPixmap("/Users/den4ick800/Desktop/grpahics/Renault T right.png"));
           }
       }
       //left
       if(a=="left"){
           if(car.model_Name()=="Kia Rio"){
               model->setPixmap( QPixmap("/Users/den4ick800/Desktop/grpahics/Kia Rio left.png"));
           }
           if(car.model_Name()=="Lada Vesta"){
               model->setPixmap( QPixmap("/Users/den4ick800/Desktop/grpahics/Lada Vesta left.png"));
           }
           if(car.model_Name()=="Mercedes C63"){
              model->setPixmap( QPixmap("/Users/den4ick800/Desktop/grpahics/Mercedes C63 left.png"));
           }
           if(car.model_Name()=="Toyata RAV4"){
              model->setPixmap(  QPixmap("/Users/den4ick800/Desktop/grpahics/Toyata RAV4 left.png"));
           }
           if(car.model_Name()=="Lada Niva"){
              model->setPixmap( QPixmap("/Users/den4ick800/Desktop/grpahics/Lada Niva left.png"));
           }
           if(car.model_Name()=="Hyndai Creta"){
              model->setPixmap( QPixmap("/Users/den4ick800/Desktop/grpahics/Hyndai Creta left.png"));
           }
           if(car.model_Name()=="Mercedes-Benz Acorcs"){
               model->setPixmap( QPixmap("/Users/den4ick800/Desktop/grpahics/Mercedes-Benz Acorcs left.png"));
           }
           if(car.model_Name()=="Kamaz"){
               model->setPixmap( QPixmap("/Users/den4ick800/Desktop/grpahics/Kamaz left.png"));
           }
           if(car.model_Name()=="Renault T"){
               model->setPixmap( QPixmap("/Users/den4ick800/Desktop/grpahics/Renault T left.png"));
           }
       }
    }
void stop(){
    if(move==true){
        move=false;
    }
    else{
        move=true;
    }
}

    ~object()=default;

};
namespace Ui {
class car;
}

class car : public QWidget
{
    Q_OBJECT

public:
    explicit car(QWidget *parent = nullptr);
    ~car();

private slots:
    void on_pushButton_clicked();
    void update_picture();
    void add_road();
    void delete_from_moving(object& a,object&b);
    void places_update(std::pair<int,int>& a,unsigned int& b);
    void accident(object& a,object& b);
private:
    Ui::car *ui;
    QPixmap model;
    QGraphicsView *graphicsview;
    QGraphicsScene *scene;
    std::vector<object> ob;
    QTimer *tmr;
    QTimer *tmr_1;
    bool trf;
    QGraphicsPixmapItem* redlight;
    QGraphicsPixmapItem* greenlight;
    std::vector<std::pair<int,int>> places;
    std::ofstream out;

};


inline QPixmap pixmap_create(Automobile& a,std::pair<int,int>& b);
inline std::vector<int> info_create(std::ifstream &in);

inline std::vector<std::pair<int,int>> place_create();
inline std::string choose_direction(object& a);
inline bool is_main_spawn(object& a);
inline void car_destroy(Automobile a,Automobile b,std::ofstream &out);

#endif // CAR_H
