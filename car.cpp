#include "car.h"
#include "ui_car.h"
#include <QPainter>
#include <QPixmap>
#include <fstream>
#include <string>
#include <thread>
#include <vector>
#include<QPixmap>
#include<QGraphicsScene>
#include <iostream>
#include <QGraphicsPixmapItem>
#include <cstdlib>
car::car(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::car)
{
    srand(time(NULL));
    ui->setupUi(this);
    this->resize(1600,800);
    this->resize(1280,800);
    scene = new QGraphicsScene;
     QPixmap image =  QPixmap(("/Users/den4ick800/Desktop/grpahics/oie_nfr6CCmJOZ5X.jpg"));
     ui->graphicsView->resize(1280,800);
    ui->graphicsView->setSceneRect(0,0,1280,800);
    scene->addPixmap(image);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
    redlight=new QGraphicsPixmapItem;
    greenlight=new QGraphicsPixmapItem;
    redlight->setPixmap(QPixmap("/Users/den4ick800/Desktop/grpahics/red.jpg"));
    greenlight->setPixmap(QPixmap("/Users/den4ick800/Desktop/grpahics/green.jpg"));
    scene->addItem(redlight);
    redlight->setPos(353,-3);
    scene->addItem(greenlight);
    greenlight->setPos(353,-3);
    redlight->setOpacity(0);
    greenlight->setOpacity(0);


}

car::~car()
{
    delete ui;
    delete graphicsview;
    delete scene;
    delete tmr;
    delete tmr_1;
    delete redlight;
    delete greenlight;
}

void car::on_pushButton_clicked()
{
    std::ifstream in("/Users/den4ick800/Desktop/grpahics/modeling_information.txt");
    std::vector<int> info=info_create(in);
    in.close();
    std::string type="passenger";
    places=place_create();
    for(unsigned int i=0;i<info[0];++i){
        Automobile a(type);
        std::pair<int,int> b=places[i];
        QPixmap c=pixmap_create(a,b);
        object cv(a,c,b);
        ob.push_back(cv);
    }
    type="crossover";
    for(unsigned int i=0;i<info[1];++i){
        Automobile a(type);
        std::pair<int,int> b=places[i+info[0]];
        QPixmap c=pixmap_create(a,b);
        object cv(a,c,b);
        ob.push_back(cv);
    }
    type="truck";
    for(unsigned int i=0;i<info[2];++i){
        Automobile a(type);
        std::pair<int,int> b=places[i+info[0]+info[1]];
        QPixmap c=pixmap_create(a,b);
        object cv(a,c,b);
        ob.push_back(cv);
    }
    places.resize(ob.size());
    for(unsigned int i=0;i<ob.size();++i){
        ob[i].show(ob[i].coord().first,ob[i].coord().second,scene);
    }
    for(unsigned int i=0;i<ob.size();++i){
        ob[i].st();
    }
   tmr = new QTimer(this);
   tmr->setInterval(15);
    connect(tmr, SIGNAL(timeout()), this, SLOT(update_picture()));
    tmr->start();
    if (info[3]==1){
    tmr_1=new QTimer(this);
    tmr_1->setInterval(10000);
    connect(tmr_1, SIGNAL(timeout()), this, SLOT(add_road()));
    tmr_1->start();
    trf=false;
}



}

void car::update_picture(){
    std::mutex mut;
    std::pair<int,int> s;
    for (unsigned int i=0;i<ob.size();++i){
        int k=0;
        if(ob[i].is_movable()){

            //up
            if(ob[i].vr()=="up"){
                if(ob[i].coord().second>670){
                    ob[i].moving(0,-1);
                     s=ob[i].coord();
                    places_update(s,i);
                }
                if((ob[i].coord().second<670) && (ob[i].coord().second>300)){
                    ob[i].moving(0,-1);
                     s=ob[i].coord();
                    places_update(s,i);
                }
                if((ob[i].coord().second<300) && (ob[i].coord().second>20)){
                   ob[i].moving(0,-1);
                    s=ob[i].coord();
                   places_update(s,i);
                }

                if((ob[i].coord().second==670) || (ob[i].coord().second==300) || (ob[i].coord().second==20)){
                   std::string a=choose_direction(ob[i]);
                    ob[i].change_direction_from_up(a);
                     s=ob[i].coord();
                    places_update(s,i);
                    ++k;

                }



                }




//down

            if(ob[i].vr()=="down"){

        if((ob[i].coord().second<253)){
            ob[i].moving(0,1);
             s=ob[i].coord();
            places_update(s,i);
        }
        if((ob[i].coord().second>253) && (ob[i].coord().second<630)){
            ob[i].moving(0,1);
             s=ob[i].coord();
            places_update(s,i);
        }
        if((ob[i].coord().second>632) && (ob[i].coord().second<770)){
             ob[i].moving(0,1);
              s=ob[i].coord();
             places_update(s,i);
        }

        if((ob[i].coord().second==253) || (ob[i].coord().second==630) || (ob[i].coord().second==770)){
            if(k==0){
            std::string a=choose_direction(ob[i]);
            ob[i].change_direction_from_down(a);
             s=ob[i].coord();
            places_update(s,i);
            ++k;

}
        }


        }




//right
            if(ob[i].vr()=="right"){
                if(ob[i].coord().first<227){
                    ob[i].moving(1,0);
                     s=ob[i].coord();
                    places_update(s,i);
                }
                if((ob[i].coord().first>227) && (ob[i].coord().first<680)){
                    if((ob[i].coord().first>310) && (ob[i].coord().first<413)){
                            ob[i].disappear();
                }
                    else{
                        ob[i].appear();
                    }
                        ob[i].moving(1,0);
                         s=ob[i].coord();
                        places_update(s,i);
            }
                if((ob[i].coord().first>680) && (ob[i].coord().first<1125)){
                    ob[i].moving(1,0);
                     s=ob[i].coord();
                    places_update(s,i);
                }
                if((ob[i].coord().first>1125) && (ob[i].coord().first<1250)){
                    ob[i].moving(1,0);
                     s=ob[i].coord();
                    places_update(s,i);
                }
                if((ob[i].coord().first==227) || (ob[i].coord().first==680) || (ob[i].coord().first==1125) || (ob[i].coord().first==1250)){
                    if(k==0){
                    std::string a=choose_direction(ob[i]);
                    ob[i].change_direction_from_right(a);
                     s=ob[i].coord();
                    places_update(s,i);
                    ++k;
                    }
            }



                }

//left
            if(ob[i].vr()=="left"){
                if(ob[i].coord().first>1214){
                    ob[i].moving(-1,0);
                     s=ob[i].coord();
                    places_update(s,i);
                }
                if((ob[i].coord().first<1214) && (ob[i].coord().first>745)){
                    ob[i].moving(-1,0);
                     s=ob[i].coord();
                    places_update(s,i);
                }
                if((ob[i].coord().first<745) && (ob[i].coord().first>304)){
                    if((ob[i].coord().first>310) && (ob[i].coord().first<413)){
                            ob[i].disappear();
                }
                    else{
                        ob[i].appear();
                    }
                    ob[i].moving(-1,0);
                     s=ob[i].coord();
                    places_update(s,i);
                }
                if((ob[i].coord().first<304) && (ob[i].coord().first>20)){
                    ob[i].moving(-1,0);
                     s=ob[i].coord();
                    places_update(s,i);
                }
                if((ob[i].coord().first==1214) ||(ob[i].coord().first==745) || (ob[i].coord().first==304 ) || (ob[i].coord().first==20)){
                    if(k==0){
                    std::string a=choose_direction(ob[i]);
                    ob[i].change_direction_from_left(a);
                     s=ob[i].coord();
                    places_update(s,i);
                    ++k;
                }
                }


            }
            for (unsigned int j=0;j<places.size();++j){
                if( ((places[j]==s) && (i!=j)) ||  ((fabs(places[j].first-s.first)<30) && (fabs(places[j].second-s.second)<30) && (i!=j) )){

                    accident(ob[i],ob[j]);

                }
            }

}
    }
    }



void car::add_road(){
    if(trf==false){
    for (unsigned int i=0;i<ob.size();++i){
        ob[i].stop();
    }
   redlight->setOpacity(1);
   greenlight->setOpacity(0);
    trf=true;
    }
    else{
        trf=false;
        for (unsigned int i=0;i<ob.size();++i){
            ob[i].stop();
        }
        redlight->setOpacity(0);
        greenlight->setOpacity(1);
    }
}


inline QPixmap pixmap_create(Automobile& a,std::pair<int,int>& b){
    //down
    if((b==std::make_pair(234,20)) || (b==std::make_pair(680,20)) || (b==std::make_pair(1130,20))){
if(a.model_Name()=="Kia Rio"){
    return QPixmap("/Users/den4ick800/Desktop/grpahics/Kia Rio down.png");
}
if(a.model_Name()=="Lada Vesta"){
    return QPixmap("/Users/den4ick800/Desktop/grpahics/Lada Vesta down.png");
}
if(a.model_Name()=="Mercedes C63"){
    return QPixmap("/Users/den4ick800/Desktop/grpahics/Mercedes C63 down.png");
}
if(a.model_Name()=="Toyata RAV4"){
    return QPixmap("/Users/den4ick800/Desktop/grpahics/Toyata RAV4 down.png");
}
if(a.model_Name()=="Lada Niva"){
    return QPixmap("/Users/den4ick800/Desktop/grpahics/Lada Niva down.png");
}
if(a.model_Name()=="Hyndai Creta"){
    return QPixmap("/Users/den4ick800/Desktop/grpahics/Hyndai Creta down.png");
}
if(a.model_Name()=="Mercedes-Benz Acorcs"){
    return QPixmap("/Users/den4ick800/Desktop/grpahics/Mercedes-Benz Acorcs down.png");
}
if(a.model_Name()=="Kamaz"){
    return QPixmap("/Users/den4ick800/Desktop/grpahics/Kamaz down.png");
}
if(a.model_Name()=="Renault T"){
    return QPixmap("/Users/den4ick800/Desktop/grpahics/Renault T down.png");
}
    }

    //up
   if((b==std::make_pair(265,760)) || (b==std::make_pair(710,760)) ){
       if(a.model_Name()=="Kia Rio"){
           return QPixmap("/Users/den4ick800/Desktop/grpahics/Kia Rio up.png");
       }
       if(a.model_Name()=="Lada Vesta"){
           return QPixmap("/Users/den4ick800/Desktop/grpahics/Lada Vesta up.png");
       }
       if(a.model_Name()=="Mercedes C63"){
           return QPixmap("/Users/den4ick800/Desktop/grpahics/Mercedes C63 up.png");
       }
       if(a.model_Name()=="Toyata RAV4"){
           return QPixmap("/Users/den4ick800/Desktop/grpahics/Toyata RAV4 up.png");
       }
       if(a.model_Name()=="Lada Niva"){
           return QPixmap("/Users/den4ick800/Desktop/grpahics/Lada Niva up.png");
       }
       if(a.model_Name()=="Hyndai Creta"){
           return QPixmap("/Users/den4ick800/Desktop/grpahics/Hyndai Creta up.png");
       }
       if(a.model_Name()=="Mercedes-Benz Acorcs"){
           return QPixmap("/Users/den4ick800/Desktop/grpahics/Mercedes-Benz Acorcs up.png");
       }
       if(a.model_Name()=="Kamaz"){
           return QPixmap("/Users/den4ick800/Desktop/grpahics/Kamaz up.png");
       }
       if(a.model_Name()=="Renault T"){
           return QPixmap("/Users/den4ick800/Desktop/grpahics/Renault T up.png");
       }
   }

   //right
   if((b==std::make_pair(20,270)) || (b==std::make_pair(20,645))){
       if(a.model_Name()=="Kia Rio"){
           return QPixmap("/Users/den4ick800/Desktop/grpahics/Kia Rio right.png");
       }
       if(a.model_Name()=="Lada Vesta"){
           return QPixmap("/Users/den4ick800/Desktop/grpahics/Lada Vesta right.png");
       }
       if(a.model_Name()=="Mercedes C63"){
           return QPixmap("/Users/den4ick800/Desktop/grpahics/Mercedes C63 right.png");
       }
       if(a.model_Name()=="Toyata RAV4"){
           return QPixmap("/Users/den4ick800/Desktop/grpahics/Toyata RAV4 right.png");
       }
       if(a.model_Name()=="Lada Niva"){
           return QPixmap("/Users/den4ick800/Desktop/grpahics/Lada Niva right.png");
       }
       if(a.model_Name()=="Hyndai Creta"){
           return QPixmap("/Users/den4ick800/Desktop/grpahics/Hyndai Creta right.png");
       }
       if(a.model_Name()=="Mercedes-Benz Acorcs"){
           return QPixmap("/Users/den4ick800/Desktop/grpahics/Mercedes-Benz Acorcs right.png");
       }
       if(a.model_Name()=="Kamaz"){
           return QPixmap("/Users/den4ick800/Desktop/grpahics/Kamaz right.png");
       }
       if(a.model_Name()=="Renault T"){
           return QPixmap("/Users/den4ick800/Desktop/grpahics/Renault T right.png");
       }
   }
   //left
   if((b==std::make_pair(1240,244)) || (b==std::make_pair(1240,620))){
       if(a.model_Name()=="Kia Rio"){
           return QPixmap("/Users/den4ick800/Desktop/grpahics/Kia Rio left.png");
       }
       if(a.model_Name()=="Lada Vesta"){
           return QPixmap("/Users/den4ick800/Desktop/grpahics/Lada Vesta left.png");
       }
       if(a.model_Name()=="Mercedes C63"){
           return QPixmap("/Users/den4ick800/Desktop/grpahics/Mercedes C63 left.png");
       }
       if(a.model_Name()=="Toyata RAV4"){
           return QPixmap("/Users/den4ick800/Desktop/grpahics/Toyata RAV4 left.png");
       }
       if(a.model_Name()=="Lada Niva"){
           return QPixmap("/Users/den4ick800/Desktop/grpahics/Lada Niva left.png");
       }
       if(a.model_Name()=="Hyndai Creta"){
           return QPixmap("/Users/den4ick800/Desktop/grpahics/Hyndai Creta left.png");
       }
       if(a.model_Name()=="Mercedes-Benz Acorcs"){
           return QPixmap("/Users/den4ick800/Desktop/grpahics/Mercedes-Benz Acorcs left.png");
       }
       if(a.model_Name()=="Kamaz"){
           return QPixmap("/Users/den4ick800/Desktop/grpahics/Kamaz left.png");
       }
       if(a.model_Name()=="Renault T"){
           return QPixmap("/Users/den4ick800/Desktop/grpahics/Renault T left.png");
       }
   }
}
//информация о количестве машин
inline std::vector<int> info_create(std::ifstream &in){
    std::string line;
    getline(in,line);
    int number_of_passenger=atoi(line.c_str());
    getline(in,line);
    int number_of_crossover=atoi(line.c_str());
    getline(in,line);
    int number_of_trucks=atoi(line.c_str());
     getline(in,line);
     int traffic_lights=atoi(line.c_str());
     std::vector <int> info;
     info.push_back(number_of_passenger);
     info.push_back((number_of_crossover));
     info.push_back(number_of_trucks);
     info.push_back(traffic_lights);
     return info;
}
//моделирование аварии
void car::accident(object& a,object& b){
    car_destroy(a.avto(),b.avto(),out);
    a.clear();
    b.clear();
    QGraphicsPixmapItem *boom=new QGraphicsPixmapItem;
    boom->setPixmap(QPixmap("/Users/den4ick800/Downloads/acident.png"));
    scene->addItem(boom);
    boom->setPos(a.coord().first,a.coord().second);
    boom->setOpacity(0.6);
    delete_from_moving(a,b);
}
//изначальный спавн автомобилей
inline std::vector<std::pair<int,int>> place_create(){
    std::pair<int,int> pair_1=std::make_pair(234,20);
    std::pair<int,int> pair_2=std::make_pair(680,20);
    std::pair<int,int> pair_3=std::make_pair(1130,20);
    std::pair<int,int> pair_4=std::make_pair(265,760);
    std::pair<int,int> pair_5=std::make_pair(710,760);
    std::pair<int,int> pair_6=std::make_pair(20,270);
    std::pair<int,int> pair_7=std::make_pair(20,645);
    std::pair<int,int> pair_8=std::make_pair(1240,244);
    std::pair<int,int> pair_9=std::make_pair(1240,620);
    std::vector<std::pair<int,int>> places;
    places.push_back(pair_1);
    places.push_back(pair_2);
    places.push_back(pair_3);
    places.push_back(pair_4);
    places.push_back(pair_5);
    places.push_back(pair_6);
    places.push_back(pair_7);
    places.push_back(pair_8);
    places.push_back(pair_9);
    return places;
}
inline std::string choose_direction(object& a){
    std::string direction;
    if(((abs(a.coord().first-1148))<100) && ((abs(a.coord().second-620))<100)){
        int c=rand()%3;

            if(c==0){
                return std::string("up");
            }
            if(c==1){
                return std::string("left");
            }
            if(c==2){
                return std::string("right");
            }

    }
    if(is_main_spawn(a)){
        if(a.dir()=="up"){
            return std::string("down");
        }
        if(a.dir()=="down"){
            return std::string("up");
        }
        if(a.dir()=="right"){
            return std::string ("left");
        }
        if(a.dir()=="left"){
            return std::string("right");
        }
    }
     int c=rand()%4;
     if(c==0){
         return std::string("up");
     }
     if(c==1){
         return std::string("left");
     }
     if(c==2){
         return std::string("right");
     }
     if(c==3){
         return std::string("down");
     }

}
inline bool is_main_spawn(object& a){

        if ((a.coord().second>730) || (a.coord().second<50) || (a.coord().first<40) || (a.coord().first>1150)  ){
            return true;
        }

    return false;
}
void car::delete_from_moving(object& a,object&b){
    std::vector<object> ob_2;
    std::vector<std::pair<int,int>> places_2;
    object aa=a;
    object bb=b;
    for (unsigned int i=0;i<ob.size();++i){
        if((ob[i]==aa) ){

            for(unsigned int j=0;j<ob.size();++j){
                if(j!=i){
                    ob_2.push_back(ob[j]);
                    places_2.push_back(places[j]);
                }
            }
            ob.resize(0);
            places.resize(0);
            for(unsigned int j=0;j<ob_2.size();++j){
                ob.push_back(ob_2[j]);
                places.push_back(places_2[j]);

            }

        }
    }
    ob_2.resize(0);
    places_2.resize(0);
    for (unsigned int i=0;i<ob.size();++i){
        if((ob[i]==bb) ){

            for(unsigned int j=0;j<ob.size();++j){
                if(j!=i){
                    ob_2.push_back(ob[j]);
                    places_2.push_back(places[j]);
                }
            }
            ob.resize(0);
            places.resize(0);
            for(unsigned int j=0;j<ob_2.size();++j){
                ob.push_back(ob_2[j]);
                places.push_back(places_2[j]);

            }

        }
    }
}
void car::places_update(std::pair<int,int>& a,unsigned int& b){
    places[b]=a;
}
inline void car_destroy(Automobile a,Automobile  b,std::ofstream &out){
    out.open("/Users/den4ick800/Desktop/grpahics/accidents.txt");
    double luck=double(rand()) / (double) RAND_MAX ;
    out<<"Car accident:"<<std::endl;
    out<<"Automobiles:"<<std::endl;
    out<<"1)"<<a.model_Name()<<std::endl;
    if(a.reliable()>luck){
        out<<"Fortunately was not broken"<<std::endl;
    }
    else{
        double percent=b.Mass()/a.Mass();
        double p=50*percent;
        out<<"Unfortunately suffered by"<<p<<"percent"<<std::endl;
    }
    out<<"2)"<<b.model_Name()<<std::endl;
    if(b.reliable()>luck){
        out<<"Fortunately was not broken"<<std::endl;
    }
    else{
        double percent=a.Mass()/b.Mass();
        double p=50*percent;
        out<<"Unfortunately suffered by"<<p<<"percent"<<std::endl;
    }
out.close();
}

