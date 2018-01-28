using namespace std;
#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <fstream>
#include <cmath>

class Map   //������ ����������� ��� ������������
{
public:
    Map(int Position_X_, int Position_Y_)   //������� ��� ���������� ��� ����� ���� �� ���������� ��� ������������
    {
        setPosition_X(Position_X_);
        setPosition_Y(Position_Y_);
    }
    void setPosition_X(int Position_X_)     //������� ��� ��������� � ��� �����
    {
        Position_X = Position_X_;
    }
    void setPosition_Y(int Position_Y_)     //������� ��� ��������� � ��� �����
    {
        Position_Y = Position_Y_;
    }
    int getPosition_X()     //���� ��� ��������� � ��� �����
    {
        return Position_X;
    }
    int getPosition_Y()     //���� ��� ��������� � ��� �����
    {
        return Position_Y;
    }
protected:
    int Position_X, Position_Y;
};

class Ball; //Forward definitions
class Team;

class Player    //Abstract class --- �������-��������������
{
public:
    Player(string Name_, int Position_X_, int Position_Y_, int Jersey_Number_, int Movement_Line_, int Aim_Line_)   //������� ��� ��������������� ��� ������ ���� �� ���������� ��� ������������
    {
        setName(Name_);
        setPosition_X(Position_X_);
        setPosition_Y(Position_Y_);
        setJersey_Number(Jersey_Number_);
        setMovement_Line(Movement_Line_);
        setAim_Line(Aim_Line_);
    }
    void setName(string Name_)          //������� ��� �������� ��� ������
    {
        Name = Name_;
    }
    void setPosition_X(int Position_X_) //������� ��� ����� � ��� ������
    {
        Position_X = Position_X_;
    }
    void setPosition_Y(int Position_Y_) //������� ��� ����� � ��� ������
    {
        Position_Y = Position_Y_;
    }
    void setJersey_Number(int Jersey_Number_)   //������� ��� ������� ��� ������� ��� ������
    {
        Jersey_Number = Jersey_Number_;
    }
    void setMovement_Line(int Movement_Line_)   //������� ��� ������� ������� ��� ������
    {
        Movement_Line = Movement_Line_;
    }
    void setAim_Line(int Aim_Line_)     //������� ��� ������� ������ ��� ������
    {
        Aim_Line = Aim_Line_;
    }
    void setRed_Cards_Team1(int Red_Cards_Team1_)   //������� ��� ������� ��� �������� ������ ��� ������_�
    {
        Red_Cards_Team1 = Red_Cards_Team1_;
    }
    void setRed_Cards_Team2(int Red_Cards_Team2_)   //������� ��� ������� ��� �������� ������ ��� ������_�
    {
        Red_Cards_Team2 = Red_Cards_Team2_;
    }
    string getName()        //���� ��� �������� ��� ������
    {
        return Name;
    }
    int getPosition_X()     //���� ��� ����� � ��� ������
    {
        return Position_X;
    }
    int getPosition_Y()     //���� ��� ����� � ��� ������
    {
        return Position_Y;
    }
    int getJersey_Number()  //���� ��� ������� ��� ������� ��� ������
    {
        return Jersey_Number;
    }
    int getMovement_Line()  //���� ��� ������� ������� ��� ������
    {
        return Movement_Line;
    }
    int getAim_Line()       //���� ��� ������� ������ ��� ������
    {
        return Aim_Line;
    }
    int getRed_Cards_Team1()    //���� ��� ������� ��� �������� ������ ��� ������_�
    {
        return Red_Cards_Team1;
    }
    int getRed_Cards_Team2()    //���� ��� ������� ��� �������� ������ ��� ������_�
    {
        return Red_Cards_Team2;
    }
    virtual void movement(Map* map_)    //������� ����������� ��� ����� �������� � ����� ��� ������
    {
        int prob_movement = rand()%2;   //������ ������� ����������� �������� � �����
        if (prob_movement==1 && this->getPosition_X()!=map_->getPosition_X())   //������� ����� ����� ��� ����� ��� ���������� �����
            this->setPosition_X(this->getPosition_X()+1);       //���������� ����� ��� ������
        else if (prob_movement == 0 && this->getPosition_X() != 0)              //������� ����� ����� ��� ����� ��� ���������� �����
            this->setPosition_X(this->getPosition_X()-1);       //����������  ��� ������
    }
    //������� ����������� ��� ������ �� ��� ������ ����� ��� ������� ������, ������ � ������� ���� ��� �����
    virtual void transfer(Player* Current_Player, Ball* ball, list<Player*> &List_Object_Team1, list<Player*> &List_Object_Team2, Map* map_);
    //������� ������� ������� ��� �������������� �� ���� ����� - Pure Virtual
    virtual void special_Movement(Ball* ball, Player* Current_Player,list<Player*> &List_Object_Team1,list<Player*> &List_Object_Team2, Map* map_)=0;

    bool getTeam_of_Player(list<Player*> &List_Object_Team1)    //������� �� ���� ����� ������ � �������
    {   //�� ������ ���� ����� � ���� 0 - �� ������ ���� ����� � ���� 1
        bool found = !(find(List_Object_Team1.begin(), List_Object_Team1.end(), this) != List_Object_Team1.end());
        return found;
    }
    bool operator&&(Player *Current_Player) //����������� ��� ������� &&
    {//������� �� ���� ������ ���� ��� ��� ������ ������ ������� ������� ����� �������
       return       ((Current_Player->getPosition_X()==this->getPosition_X()-1) && (Current_Player->getPosition_Y()==this->getPosition_Y())//������� ��� ��������
                  || (Current_Player->getPosition_X()==this->getPosition_X()+1) && (Current_Player->getPosition_Y()==this->getPosition_Y())//������� ��� �����
                  || (Current_Player->getPosition_X()==this->getPosition_X()) && (Current_Player->getPosition_Y()==this->getPosition_Y()-1)//������� ��� ����
                  || (Current_Player->getPosition_X()==this->getPosition_X()) && (Current_Player->getPosition_Y()==this->getPosition_Y()+1)//������� ��� ����
                  || (Current_Player->getPosition_X()==this->getPosition_X()-1 && Current_Player->getPosition_Y()==this->getPosition_Y()-1)//��������� �������
                  || (Current_Player->getPosition_X()==this->getPosition_X()-1 && Current_Player->getPosition_Y()==this->getPosition_Y()+1)
                  || (Current_Player->getPosition_X()==this->getPosition_X()+1 && Current_Player->getPosition_Y()==this->getPosition_Y()+1)
                  || (Current_Player->getPosition_X()==this->getPosition_X()+1 && Current_Player->getPosition_Y()==this->getPosition_Y()-1));
    }
public:
    static int Red_Cards_Team1;     //�������� ��������� ��� ��� �� ����������� ��� ������
    static int Red_Cards_Team2;     //�������� ��������� ��� ��� �� ����������� ��� ������
private:
    string Name;
    int Position_X, Position_Y, Jersey_Number, Movement_Line, Aim_Line;
};
int Player :: Red_Cards_Team1 = 0;  //������������ ��� ����� ��� ��������� ����������
int Player :: Red_Cards_Team2 = 0;  //������������ ��� ����� ��� ��������� ����������

class Ball  //�����
{
public:
    Ball(int Ball_Position_X_, int Ball_Position_Y_, list<Player*> &List_Object_Team1,list<Player*> &List_Object_Team2) //������� ��� ��������������� ��� ������ ���� �� ���������� ��� ������������
    {
        setBall_Position_X(Ball_Position_X_);
        setBall_Position_Y(Ball_Position_Y_);
        setCurrent_Player(List_Object_Team1, List_Object_Team2);
    }
    void setBall_Position_X(int Ball_Position_X_)   //������� ��� ����� � ��� ������
    {
        Ball_Position_X = Ball_Position_X_;
    }
    void setBall_Position_Y(int Ball_Position_Y_)   //������� ��� ����� � ��� ������
    {
        Ball_Position_Y = Ball_Position_Y_;
    }
    void setCurrent_Player(list<Player*> &List_Object_Team1, list<Player*> &List_Object_Team2)  //������� ��� ������ ��� ���� ���� ������ ��� ��� �����
    {
        this->setEx_Player(Current_Player, List_Object_Team1, List_Object_Team2);   //������� ��� ����� ������ ������ ����� �� ������� ���� ������ �������
        bool flag = 0;
        list<Player*>::iterator p = List_Object_Team1.begin();
        while(p != List_Object_Team1.end())     //������� ��� �� ����� ��� ������ �
        {
            if (getBall_Position_X()==(*p)->getPosition_X() && getBall_Position_Y()==(*p)->getPosition_Y()) //������� �� ����������� �� ������������� ��� ������ �� ������� ������
            {
                Current_Player = (*p);  //�� ������� ���� ����� ������ ������
                flag = 1;
            }
            p++;
        }
        if (flag == 0)    //������ ������� ��� �� ����� ��� ������ �
        {
            list<Player*>::iterator p = List_Object_Team2.begin();
            while(p != List_Object_Team2.end())
            {
                if (getBall_Position_X()==(*p)->getPosition_X() && getBall_Position_Y()==(*p)->getPosition_Y()) //������� �� ����������� �� ������������� ��� ������ �� ������� ������
                {
                    Current_Player = (*p);  //�� ������� ���� ����� ������ ������
                    flag = 1;
                }
                p++;
            }
        }
        if (flag == 0) //�� ��� ������� ������� ��� �� ��� ���� ������ ��� ��� ����� ���� ���� NULL
        {
            Current_Player = NULL;
        }
    }
    void setEx_Player(Player* Current_Player, list<Player*> &List_Object_Team1, list<Player*> &List_Object_Team2)   //������� ��� ������������� ������ ������
    {
            list<Player*>::iterator findIter = find(List_Object_Team1.begin(), List_Object_Team1.end(), Current_Player);
            if (findIter != List_Object_Team1.end())    //������ ��� ������ ������ ���� ������ ������� ��� ������� ��� �� ����� ������ �������
                {
                    Ex_Player = (*findIter);
                }
            else
            {
                list<Player*>::iterator findIter = find(List_Object_Team2.begin(), List_Object_Team2.end(), Current_Player);
                Ex_Player = (*findIter);
            }
    }
    int getBall_Position_X()    //���� ��� ����� � ��� ������
    {
        return Ball_Position_X;
    }
    int getBall_Position_Y()    //���� ��� ����� � ��� ������
    {
        return Ball_Position_Y;
    }
    Player* getCurrent_Player() //���� ��� ������ ������
    {
        return Current_Player;
    }
    Player* getEx_Player()      //���� ��� ������������� ������ ������
    {
        return Ex_Player;
    }
    //������� �������� - �������������
    void assignment(Player* Player_, list<Player*> &List_Object_Team1, list<Player*> &List_Object_Team2, Team* Team1, Team* Team2); //������� ��� ������ ���� ������ ��� ������ �� ��������� �� ������ ���� ���� ��� ��� �����

    void assignment(list<Player*> &List_Object_Team1, list<Player*> &List_Object_Team2, Team* Team1, Team*  Team2, Map* map_)   //������� ��� ������ ���� ����������� ������, �� ��� ������� ��� ������ �������
    {
        if (Current_Player == NULL) //������� �� ������� ������ �������
        {
            float min_distance = sqrt(pow(map_->getPosition_X(),2)+pow(map_->getPosition_Y(),2)) + 1;   //������� ������� ��� ����� ����������� ��� �������� ��������� ������ 2 ������ ��� �����
            list<Player*>::iterator p = List_Object_Team1.begin();
            while(p != List_Object_Team1.end())     //������� ��� ���� ������� ��� ������ �
            {
                if (sqrt(pow((*p)->getPosition_X()-this->getBall_Position_X(),2)+pow((*p)->getPosition_Y()-this->getBall_Position_Y(),2)) < min_distance)   //�������� ��� ����������
                {
                    min_distance = sqrt(pow((*p)->getPosition_X()-this->getBall_Position_X(),2)+pow((*p)->getPosition_Y()-this->getBall_Position_Y(),2));   //������� ��� ���� ��������� ���������
                    temp = p;   //��������� ���������� ��� ����� ��� ������������ ��� �����
                }
                p++;
            }
            p = List_Object_Team2.begin();
            while(p != List_Object_Team2.end())     //������� ��� ���� ������� ��� ������ �
            {
                if (sqrt(pow((*p)->getPosition_X()-this->getBall_Position_X(),2)+pow((*p)->getPosition_Y()-this->getBall_Position_Y(),2)) < min_distance)   //�������� ��� ����������
                {
                    min_distance = sqrt(pow((*p)->getPosition_X()-this->getBall_Position_X(),2)+pow((*p)->getPosition_Y()-this->getBall_Position_Y(),2));   //������� ��� ���� ��������� ���������
                    temp = p;   //��������� ���������� ��� ����� ��� ������������ ��� �����
                }
                p++;
            }
            this->setBall_Position_X((*temp)->getPosition_X()); //������ ��� ����� � ��� ������ �� ���� ��� ������������ ������
            this->setBall_Position_Y((*temp)->getPosition_Y()); //������ ��� ����� � ��� ������ �� ���� ��� ������������ ������
            this->setCurrent_Player(List_Object_Team1, List_Object_Team2); //������� ��� ���� ������ ������
        }
    }
    bool operator&&(Player *Player_) //����������� ��� ������� &&
    {//������� �� � ����� ����� �������� (������ �������=NULL) ��� �� ��������� ����� ���� ���������� ������
       return  (this->getCurrent_Player()==NULL && (this->getBall_Position_X()==Player_->getPosition_X()-1 && this->getBall_Position_Y()==Player_->getPosition_Y())//������� ��������
                                        || (this->getBall_Position_X()==Player_->getPosition_X()+1 && this->getBall_Position_Y()==Player_->getPosition_Y())//������� �����
                                        || (this->getBall_Position_X()==Player_->getPosition_X() && this->getBall_Position_Y()==Player_->getPosition_Y()-1)//������� ����
                                        || (this->getBall_Position_X()==Player_->getPosition_X() && this->getBall_Position_Y()==Player_->getPosition_Y()+1)//������� ����
                                        || (this->getBall_Position_X()==Player_->getPosition_X()-1 && this->getBall_Position_Y()==Player_->getPosition_Y()-1)//��������� �������
                                        || (this->getBall_Position_X()==Player_->getPosition_X()-1 && this->getBall_Position_Y()==Player_->getPosition_Y()+1)
                                        || (this->getBall_Position_X()==Player_->getPosition_X()+1 && this->getBall_Position_Y()==Player_->getPosition_Y()+1)
                                        || (this->getBall_Position_X()==Player_->getPosition_X()+1 && this->getBall_Position_Y()==Player_->getPosition_Y()-1));
    }
private:
    int Ball_Position_X, Ball_Position_Y;
    list<Player*> List_Object;
    list<Player*>::iterator temp;
public:
    Player* Current_Player ;
    Player* Ex_Player;
};

class Defender: public Player   //�������� ���������
{
public:
    Defender(string Name_,int Position_X_, int Position_Y_, int Jersey_Number_, int Movement_Line_, int Aim_Line_) : Player(Name_, Position_X_, Position_Y_, Jersey_Number_, Movement_Line_, Aim_Line_)
    {
        setYellow_Card(0);
    }
    void setYellow_Card(bool Yellow_Card_)  //������� �������� ������ ��� ���������
    {
        Yellow_Card = Yellow_Card_;
    }
    void setSteals(int Steals_) //������� ��� ��������� ���������� ����������
    {
        Steals = Steals_;
    }
    bool getYellow_Card()   //���� �������� ������ ��� ���������
    {
        return Yellow_Card;
    }
    int getSteals()     //���� ��� ��������� ���������� ����������
    {
        return Steals;
    }
    //���������� ��� ������� ������� �������, ���� �� ������� ��������� ������� ������� �� ������� ���� ���� �� ������� ���� ������ ��� ��� �����, ���� ������� ������� �����
    void special_Movement(Ball *ball, Player *Current_Player,list<Player*> &List_Object_Team1,list<Player*> &List_Object_Team2, Map* map_)
    {
        if (Current_Player != NULL) //������� �� ������� ������ �������
        {
            if (Current_Player->getTeam_of_Player(List_Object_Team1)!=this->getTeam_of_Player(List_Object_Team1))   //������� �� � ������ ������� ����� ���������
            {
                if (*this && Current_Player)  //����� ��� ������������� ������� && ��� ��� ������ ��� ���� ������
                {
                    int prob_get_ball = rand()%101; //������ ���������� ���������� ��� ������
                    int prob_yellow_card = rand()%101;  //������ ���������� ����� �������� ������
                    if (prob_get_ball <= 70)    //������� ��� ������
                    {
                        ball->setBall_Position_X(this->getPosition_X());    //������ ��� ����� � ��� ������
                        ball->setBall_Position_Y(this->getPosition_Y());    //������ ��� ����� � ��� ������
                        setSteals(getSteals()+1);   //������ ��� ���������� ���� 1
                    }
                    else if (prob_yellow_card <= 20)    //���� �������� ������
                    {
                        if (this->getYellow_Card() == 0)    //������� �� ���� ��� ������� �����
                            this->setYellow_Card(1);    //�� ��� ���� ��� ���� ������� ��� ������� �����
                        else if (this->getYellow_Card() == 1)   //�� ���� ��� ��� ������� ����� ���� ����������� ��� �� ��������
                        {
                            if (this->getTeam_of_Player(List_Object_Team1) == 0)    //������� �� ��������� � ��������� ���� ����� �
                            {
                                list<Player*>::iterator p = List_Object_Team1.begin();
                                p = find(List_Object_Team1.begin(), List_Object_Team1.end(), this); //������ ��� ����� ��� ��� ����� ��� ������� ��� ������ �
                                (*p)->setRed_Cards_Team1((*p)->getRed_Cards_Team1()+1); //������ ��� �������� ������ ���� 1 ��� ������ �
                                p = List_Object_Team1.erase(p); //�������� ��� ������������ ��� ��� �����
                                delete this;    //�������� ��� ������������
                            }
                            else
                            {
                                list<Player*>::iterator p = List_Object_Team2.begin();
                                p = find(List_Object_Team2.begin(), List_Object_Team2.end(), this); //������ ��� ����� ��� ��� ����� ��� ������� ��� ������ �
                                (*p)->setRed_Cards_Team2((*p)->getRed_Cards_Team2()+1); //������ ��� �������� ������ ���� 1 ��� ������ �
                                p = List_Object_Team2.erase(p); //�������� ��� ������������ ��� ��� �����
                                delete this;    //�������� ��� ������������
                            }
                        }
                    }
                }
            }
        }
    }
public:
    static int Steals;  //�������� �������� ����������
private:
    bool Yellow_Card;
};
 int Defender :: Steals = 0;    //������������ ��� �������� ���������� ����������

class Midfielder: public Player //�������� �����
{
public:
    Midfielder(string Name_,int Position_X_, int Position_Y_, int Jersey_Number_, int Movement_Line_, int Aim_Line_) : Player(Name_, Position_X_, Position_Y_, Jersey_Number_, Movement_Line_, Aim_Line_)
    {
        setYellow_Card(0);
    }
    void setYellow_Card(bool Yellow_Card_)  //������� �������� ������ ��� �����
    {
        Yellow_Card = Yellow_Card_;
    }
    void setSteals(int Steals_) //������� ��� ��������� ���������� ����������
    {
        Steals = Steals_;
    }
    bool getYellow_Card()   //���� �������� ������ ��� �����
    {
        return Yellow_Card;
    }
    int getSteals()     //���� ��� ��������� ���������� ����������
    {
        return Steals;
    }
    //���������� ��� ������� ������� �������, ���� �� ������� ��������� ������� ������� �� ������� ���� ���� �� ������� ���� ������ ��� ��� �����, ���� ������� ������� �����
    void special_Movement(Ball *ball, Player *Current_Player,list<Player*> &List_Object_Team1,list<Player*> &List_Object_Team2, Map* map_)
    {
        if (Current_Player != NULL) //������� �� ������� ������ �������
        {
            if (Current_Player->getTeam_of_Player(List_Object_Team1)!=this->getTeam_of_Player(List_Object_Team1))   //������� �� � ������ ������� ����� ���������
            {
                if (*this && Current_Player)  //����� ��� ������������� ������� && ��� ��� ������ ��� ���� ������
                {
                    int prob_get_ball = rand()%101; //������ ���������� ���������� ��� ������
                    int prob_yellow_card = rand()%101;  //������ ���������� ����� �������� ������
                    if (prob_get_ball <= 50)    //������� ��� ������
                    {
                        ball->setBall_Position_X(this->getPosition_X());    //������ ��� ����� � ��� ������
                        ball->setBall_Position_Y(this->getPosition_Y());    //������ ��� ����� � ��� ������
                        setSteals(getSteals()+1);   //������ ��� ���������� ���� 1
                    }
                    else if (prob_yellow_card <= 20)    //���� �������� ������
                    {
                        if (this->getYellow_Card() == 0)    //������� �� ���� ��� ������� �����
                            this->setYellow_Card(1);    //�� ��� ���� ��� ���� ������� ��� ������� �����
                        else if (this->getYellow_Card() == 1)   //�� ���� ��� ��� ������� ����� ���� ����������� ��� �� ��������
                        {
                            if (this->getTeam_of_Player(List_Object_Team1) == 0)    //������� �� ��������� � ��������� ���� ����� �
                            {
                                list<Player*>::iterator p = List_Object_Team1.begin();
                                p = find(List_Object_Team1.begin(), List_Object_Team1.end(), this); //������ ��� ����� ��� ��� ����� ��� ������� ��� ������ �
                                (*p)->setRed_Cards_Team1((*p)->getRed_Cards_Team1()+1); //������ ��� �������� ������ ���� 1 ��� ������ �
                                p = List_Object_Team1.erase(p); //�������� ��� ������������ ��� ��� �����
                                delete this;    //�������� ��� ������������
                            }
                            else
                            {
                                list<Player*>::iterator p = List_Object_Team2.begin();
                                p = find(List_Object_Team2.begin(), List_Object_Team2.end(), this); //������ ��� ����� ��� ��� ����� ��� ������� ��� ������ �
                                (*p)->setRed_Cards_Team2((*p)->getRed_Cards_Team2()+1); //������ ��� �������� ������ ���� 1 ��� ������ �
                                p = List_Object_Team2.erase(p); //�������� ��� ������������ ��� ��� �����
                                delete this;    //�������� ��� ������������
                            }
                        }
                    }
                }
            }
        }
    }
    //���������� ��� ������� ����������� ��� ������ ���� �� ���������� ���������� �� ��������� � ����� �� ������ ��� ���������� ���� �������� �����
    void transfer(Player* Current_Player, Ball* ball, list<Player*> &List_Object_Team1, list<Player*> &List_Object_Team2, Map* map_)
    {
        if (Current_Player != NULL) //������� �� ������� ������ �������
        {
            if (this->getName() == Current_Player->getName())   //������� �� �� ����������� ���� ����� � ������ �������
            {
                ball->setBall_Position_Y(this->getAim_Line());  //������� ��� ����� � ��� ������ ��� �� �� ������ ������ ��� �����
                int prob_of_Position_X = rand()%101;    //������ ���������� �� ������ � ����� �� ������ ��� ��������� ������
                if (prob_of_Position_X <= 50)
                    ball->setBall_Position_X(rand()%2+(map_->getPosition_X()/2));   //������� ��� ������ ������ �� ������ ��� ��������� ������
                else
                    ball->setBall_Position_X(rand()%(map_->getPosition_X()+1));     //������� ��� ������ ������ �� ����������� �����
                ball->setCurrent_Player(List_Object_Team1, List_Object_Team2);      //������� ��� ���� ������ ������
            }
        }
    }
public:
    static int Steals;  //�������� �������� ����������
private:
    bool Yellow_Card;
};
int Midfielder :: Steals = 0;   //������������ ��� �������� ���������� ����������

class Forward: public Player    //�������� ����������
{
public:
    Forward(string Name_,int Position_X_, int Position_Y_, int Jersey_Number_, int Movement_Line_, int Aim_Line_) : Player(Name_, Position_X_, Position_Y_, Jersey_Number_, Movement_Line_, Aim_Line_)
    {

    }
    //���������� ��� ������� ������� �������, ���� �� � ����� ��������� �� ��������� ���, �� ������������ ���� 2 ������ �� �������� ���������� ��� ��� ����������� ��������
    void special_Movement(Ball *ball, Player *Current_Player, list<Player*> &List_Object_Team1, list<Player*> &List_Object_Team2, Map* map_)
    {
        if (Current_Player != NULL) //������� �� ������� ������ �������
        {
            if (Current_Player->getTeam_of_Player(List_Object_Team1) == this->getTeam_of_Player(List_Object_Team1)) //������� �� � ������ ������� ����� ����������
            {
                float min_distance = sqrt(pow(map_->getPosition_X(),2)+pow(map_->getPosition_Y(),2))+1;   //������� ������� ��� ����� ����������� ��� �������� ��������� ������ 2 ������ ��� �����
                int min_distance_X, min_distance_Y;
                if(Current_Player->getTeam_of_Player(List_Object_Team1) == 0) //������� �� ���� ����� ������ � ������ �������
                {
                    list<Player*>::iterator p = List_Object_Team2.begin();
                    while(p != List_Object_Team2.end()) //��������� ��� ��� ����������� �������� ���� ����� �
                    {
                        if (sqrt(pow((*p)->getPosition_X()-this->getPosition_X(),2)+pow((*p)->getPosition_Y()-this->getPosition_Y(),2)) < min_distance)   //�������� ��� ����������
                        {
                            min_distance = sqrt(pow((*p)->getPosition_X()-this->getPosition_X(),2)+pow((*p)->getPosition_Y()-this->getPosition_Y(),2)); //������� ��� ���� ��������� ���������
                            min_distance_X =(*p)->getPosition_X();
                            min_distance_Y =(*p)->getPosition_Y();
                        }
                        p++;
                    }
                    if (this->getPosition_X()+2 > map_->getPosition_X())    //������� �� � ���������� ���������� ��� ����� ��� ����� �
                        this->setPosition_X(getPosition_X()-2); //���� ���������� ���� 2 ������ �������� ��� ������
                    else if (0 > this->getPosition_X()-2)   //������� �� � ���������� �������� �� ��������� ����� ��� ����� �
                        this->setPosition_X(getPosition_X()+2); //���� ���������� ���� 2 ������ ����� ��� ������
                    //�� ��� ��������� ����� ����� � ����������, ���� ����������� ��� ��� ����������� ��������
                    else if (sqrt(pow(this->getPosition_X()+2-min_distance_X,2)+pow(this->getPosition_Y()-min_distance_Y,2)) < (sqrt(pow(this->getPosition_X()-2-min_distance_X,2)+pow(this->getPosition_Y()-min_distance_Y,2))))
                        this->setPosition_X(getPosition_X()-2);
                    else
                        this->setPosition_X(getPosition_X()+2);
                }
                else
                {
                    list<Player*>::iterator p = List_Object_Team1.begin();
                    while(p != List_Object_Team1.end()) //��������� ��� ��� ����������� �������� ���� ����� �
                    {
                        if (sqrt(pow((*p)->getPosition_X()-this->getPosition_X(),2)+pow((*p)->getPosition_Y()-this->getPosition_Y(),2)) < min_distance)      //�������� ��� ����������
                        {
                            min_distance = sqrt(pow((*p)->getPosition_X()-this->getPosition_X(),2)+pow((*p)->getPosition_Y()-this->getPosition_Y(),2)); //������� ��� ���� ��������� ���������
                            min_distance_X =(*p)->getPosition_X();
                            min_distance_Y =(*p)->getPosition_Y();
                        }
                        p++;
                    }
                    if (this->getPosition_X()+2 > map_->getPosition_X())    //������� �� � ���������� ���������� ��� ����� ��� ����� �
                        this->setPosition_X(getPosition_X()-2); //���� ���������� ���� 2 ������ �������� ��� ������
                    else if (0 > this->getPosition_X()-2)   //������� �� � ���������� �������� �� ��������� ����� ��� ����� �
                        this->setPosition_X(getPosition_X()+2); //���� ���������� ���� 2 ������ ����� ��� ������
                    //�� ��� ��������� ����� ����� � ����������, ���� ����������� ��� ��� ����������� ��������
                    else if (sqrt(pow(this->getPosition_X()+2-min_distance_X,2)+pow(this->getPosition_Y()-min_distance_Y,2)) < (sqrt(pow(this->getPosition_X()-2-min_distance_X,2)+pow(this->getPosition_Y()-min_distance_Y,2))))
                        this->setPosition_X(getPosition_X()-2);
                    else
                        this->setPosition_X(getPosition_X()+2);
                }
            }
        }
    }
    //���������� ��� ������� ����������� ��� ������ ���� �� ���������� ���������� �� ��������� � ����� �� ������ ��� ���������� ���� �������� �����
    void transfer(Player* Current_Player, Ball* ball, list<Player*> &List_Object_Team1, list<Player*> &List_Object_Team2, Map* map_)
    {
        if (Current_Player != NULL) //������� �� ������� ������ �������
        {
            if (this->getName() == Current_Player->getName())   //������� �� �� ����������� ���� ����� � ������ �������
            {
                ball->setBall_Position_Y(this->getAim_Line());  //������� ��� ����� � ��� ������ ��� �� �� ������ ������ ��� �����
                int prob_of_Position_X = rand()%101;    //������ ���������� �� ������ � ����� �� ������ ��� ��������� ������
                if (prob_of_Position_X <= 75)
                    ball->setBall_Position_X(rand()%2+(map_->getPosition_X()/2));   //������� ��� ������ ������ �� ������ ��� ��������� ������
                else
                    ball->setBall_Position_X(rand()%(map_->getPosition_X()+1));     //������� ��� ������ ������ �� ����������� �����
                ball->setCurrent_Player(List_Object_Team1, List_Object_Team2);      //������� ��� ���� ������ ������
            }
        }
    }
};

class Striker: public Forward   //�������� ����������-����������
{
public:
    Striker(string Name_,int Position_X_, int Position_Y_, int Jersey_Number_, int Movement_Line_, int Aim_Line_) : Forward(Name_, Position_X_, Position_Y_, Jersey_Number_, Movement_Line_, Aim_Line_)
    {
    }
    //���������� ��� ������� ����������� ��� ������ ���� �� ���������� ���������� �� ��������� � ����� �� ������ ��� ���������� ���� �������� �����
    void transfer(Player* Current_Player, Ball* ball, list<Player*> &List_Object_Team1, list<Player*> &List_Object_Team2, Map* map_)
    {
        if (Current_Player != NULL) //������� �� ������� ������ �������
        {
            if (this->getName() == Current_Player->getName())   //������� �� �� ����������� ���� ����� � ������ �������
            {
                ball->setBall_Position_Y(this->getAim_Line());  //������� ��� ����� � ��� ������ ��� �� �� ������ ������ ��� �����
                int prob_of_Position_X = rand()%101;    //������ ���������� �� ������ � ����� �� ������ ��� ��������� ������
                if (prob_of_Position_X <= 95)
                    ball->setBall_Position_X(rand()%2+(map_->getPosition_X()/2));   //������� ��� ������ ������ �� ������ ��� ��������� ������
                else
                    ball->setBall_Position_X(rand()%(map_->getPosition_X()+1));     //������� ��� ������ ������ �� ����������� �����
                ball->setCurrent_Player(List_Object_Team1, List_Object_Team2);      //������� ��� ���� ������ ������
            }
        }
    }
};
//������� ����������� ��� ������ �� ��� ������ ����� ��� ������� ������, ������ � ������� ���� ��� �����
void Player ::  transfer(Player* Current_Player, Ball* ball_, list<Player*> &List_Object_Team1, list<Player*> &List_Object_Team2, Map* map_)
{
    if (Current_Player != NULL) //������� �� ������� ������ �������
    {
        if (this->getName() == Current_Player->getName())   //������� �� �� ����������� ���� ����� � ������ �������
        {
            ball_->setBall_Position_Y(this->getAim_Line()); //������� ��� ����� � ��� ������ ��� �� �� ������ ������ ��� ������
            ball_->setBall_Position_X(rand()%(map_->getPosition_X()+1)); //������� ��� ������ ������ �� ����������� �����
            ball_->setCurrent_Player(List_Object_Team1, List_Object_Team2); //������� ��� ���� ������ ������
        }
    }
}

class Team //����� �����������
{
public:
    Team(string Team_Name_) //������� ��� ��������������� ��� ������ ���� ��� ���������� ��� ������������
    {
        setTeam_Name(Team_Name_);
        setMistakes(0);
        setPasses(0);
        setGoals(0);
        setMissed_Goals(0);
    }
    void setTeam_Name(string Team_Name_)    //������� �������� ��� ������
    {
        Team_Name = Team_Name_;
    }
    void setPlayer_List(Player *Player_)    //���� ������� �� ��� ����� ��� ����������� ������
    {
        List_Object.push_back(Player_);
    }
    void setMistakes(int Mistakes_)     //������� ����� ��� ������
    {
        Mistakes = Mistakes_;
    }
    void setPasses(int Passes_)     //������� ������ ��� ������
    {
        Passes = Passes_;
    }
    void setGoals(int Goals_)   //������� ��� ���� ��� ������
    {
        Goals = Goals_;
    }
    void setMissed_Goals(int Missed_Goals_) //������� ��� ������� ���� ��� ������
    {
        Missed_Goals = Missed_Goals_;
    }
    string getTeam_Name()   //���� �������� ��� ������
    {
        return Team_Name;
    }
    list<Player*> getPlayer_List()  //��� ��� ������ ��� ������� ��� ������
    {
        return List_Object;
    }
    int getMistakes()   //���� ��� ����� ��� ������
    {
        return Mistakes;
    }
    int getPasses()     //���� ��� ������ ��� ������
    {
        return Passes;
    }
    int getGoals()  //���� ��� ���� ��� ������
    {
        return Goals;
    }
    int getMissed_Goals()   //���� ��� ������� ���� ��� ������
    {
        return Missed_Goals;
    }
    //������� ��� ��������� ���� ������� ��� ������ ��� ��� ��� ������ ������� �� ������ ����� ��� ����������� �������� ���
    int action(list<Player*> &List_Object_Team1, list<Player*> &List_Object_Team2, Player* Current_Player, Player* Ex_Player, Ball* ball, Team* Team1, Team* Team2, Map* map_, int flag)
    {
        int counter1 = 0, counter2 = 0; //�������� ��� ������� ��� ������
        if (flag == 0)  //������� ��� ���� ����� ������� �� ����������� �� ����������� �������
        {
            counter1=list_elements(List_Object_Team1);  //�������� ������� ��� ������ �
            list<Player*>::iterator p = List_Object_Team1.begin();
            while(p != List_Object_Team1.end()) //�������� ��� ������� ��� ��� ����� �
            {
                int prob_action = rand()%101;   //������ ���������� ��������� �������
                if (prob_action < 35)   //35% ���������� ��������� ��� ������� �������
                {
                    (*p)->movement(map_);   //����� ������� �������
                    ball->assignment((*p), List_Object_Team1, List_Object_Team2, Team1, Team2); //����� ��� ������� �������� ���� �� ������ � ������� �� ����� ��� ����� ���� ������ ���
                   // cout<<"I AM "<<(*p)->getName()<<" AND CALLED MOVEMENT"<<endl;
                }
                else if (prob_action < 70)  //35% ���������� ��������� ��� ������� ���������
                {
                    (*p)->transfer(Current_Player, ball, List_Object_Team1, List_Object_Team2, map_);   //����� ������� ���������
                    ball->assignment((*p), List_Object_Team1, List_Object_Team2, Team1, Team2); //����� ��� ������� �������� ���� �� ������ � ������� �� ����� ��� ����� ���� ������ ���
                    //cout<<"I AM "<<(*p)->getName()<<" AND CALLED TRANSFER"<<endl;
                }
                else
                {
                    (*p)->special_Movement(ball, Current_Player, List_Object_Team1, List_Object_Team2, map_);   //����� ������� ������� �������
                    ball->assignment((*p), List_Object_Team1, List_Object_Team2, Team1, Team2); //����� ��� ������� �������� ���� �� ������ � ������� �� ����� ��� ����� ���� ������ ���
                    counter2 = list_elements(List_Object_Team1);  //�������� ��� ������ �, ���� ��� �������� ��� ������� ������� �������
                    if (counter2 < counter1) break; //������� �� ������� ������� ���������� ��� ��� �����������
                    if (counter2 == 0)  //������� �� � ����� � ������ ����� �������
                    {
                        throw "No more players left for Team A!";   //Throw exception
                    }
                   // cout<<"I AM "<<(*p)->getName()<<" AND CALLED SPECIAL_MOV"<<endl;
                }
                p++;
            }
        }
        else
        {
            counter1 = list_elements(List_Object_Team2);    //�������� ������� ��� ������ �
            list<Player*>::iterator p = List_Object_Team2.begin();
            while(p != List_Object_Team2.end()) //�������� ��� ������� ��� ��� ����� �
            {
                int prob_action = rand()%101;   //������ ���������� ��������� �������
                if (prob_action < 35)   //35% ���������� ��������� ��� ������� �������
                {
                    (*p)->movement(map_);   //����� ������� �������
                    ball->assignment((*p), List_Object_Team1, List_Object_Team2, Team1, Team2); //����� ��� ������� �������� ���� �� ������ � ������� �� ����� ��� ����� ���� ������ ���
                    //cout<<"I AM "<<(*p)->getName()<<" AND CALLED MOVEMENT"<<endl;
                }
                else if (prob_action < 70)  //35% ���������� ��������� ��� ������� ���������
                {
                    (*p)->transfer(Current_Player, ball, List_Object_Team1, List_Object_Team2,map_);    //����� ������� ���������
                    ball->assignment((*p), List_Object_Team1, List_Object_Team2, Team1, Team2); //����� ��� ������� �������� ���� �� ������ � ������� �� ����� ��� ����� ���� ������ ���
                   // cout<<"I AM "<<(*p)->getName()<<" AND CALLED TRANSFER"<<endl;
                }
                else
                {
                    (*p)->special_Movement(ball, Current_Player, List_Object_Team1, List_Object_Team2, map_);   //����� ������� ������� �������
                    ball->assignment((*p), List_Object_Team1, List_Object_Team2, Team1, Team2); //����� ��� ������� �������� ���� �� ������ � ������� �� ����� ��� ����� ���� ������ ���
                    counter2 = list_elements(List_Object_Team2);   //�������� ��� ������ �, ���� ��� �������� ��� ������� ������� �������
                    if (counter2 < counter1) break; //������� �� ������� ������� ���������� ��� ��� �����������
                    if (counter2 == 0)  //������� �� � ����� � ������ ����� �������
                    {
                        throw "No more players left for Team B!";   //Throw exception
                    }
                    //cout<<"I AM "<<(*p)->getName()<<" AND CALLED SPECIAL_MOV"<<endl;
                }
                p++;
            }
        }
    }
    //������� �������� ��� ������������ ��� �������� ��� �����
    int list_elements(list<Player*> &List_Object_Team)
    {
        list<Player*>::iterator p = List_Object_Team.begin();
        int counter = 0;    //������������ ��� �������
        while(p != List_Object_Team.end())
        {
            counter++;  //������ ���� ��� ��� ���� ����������� ��� ��������� ��� �����
            p++;
        }
        return counter;
    }
    //����������� ��� ������� <<
    friend ostream &operator<<(ostream&, const Team &);
private:
    string Team_Name;
    int Mistakes, Passes, Goals, Missed_Goals;
    list<Player*> List_Object;

};

////������� �������� ��� ������ ���� ������ ��� ������ �� ��������� �� ������ ���� ���� ��� ��� �����
void Ball :: assignment(Player *Player_, list<Player*> &List_Object_Team1, list<Player*> &List_Object_Team2, Team *Team1, Team *Team2)
{
    if (*this && Player_)   //����� ��� �������������� ������� ��� ������ �� � ����� ����� �������� (������ �������=NULL) ��� �� ��������� ����� ���� ���������� ������
    {
        this->setBall_Position_X(Player_->getPosition_X()); //���� �� ���� � ��� ������ ��� �� ��� ���� � ��� ������
        this->setBall_Position_Y(Player_->getPosition_Y()); //���� �� ���� � ��� ������ ��� �� ��� ���� � ��� ������
        this->setCurrent_Player(List_Object_Team1, List_Object_Team2);  //������� ��� ���� ������ ������
        if (this->getEx_Player()->getTeam_of_Player(List_Object_Team1) == Player_->getTeam_of_Player(List_Object_Team1))    //������� �� � ����� ������ ������� ��� � ���� ������ ������� ������� ���� ����� �
            Team1->setPasses(Team1->getPasses()+1); //������ ��� ������ ������ ��� ������ � ���� 1
        else if (this->getEx_Player()->getTeam_of_Player(List_Object_Team2) == Player_->getTeam_of_Player(List_Object_Team2))   //������� �� � ����� ������ ������� ��� � ���� ������ ������� ������� ���� ����� �
            Team2->setPasses(Team2->getPasses()+1); //������ ��� ������ ������ ��� ������ � ���� 1
        else    //������ � ���������� ����� ����������
        {
            if (this->getEx_Player()->getTeam_of_Player(List_Object_Team1) == 0)    //'������� �� ���� ����� ������ � ����� ������ �������
                Team1->setMistakes(Team1->getMistakes()+1); //������ ��� ������ ����� ��� ������ � ���� 1
            else
                Team2->setMistakes(Team2->getMistakes()+1); //������ ��� ������ ����� ��� ������ � ���� 1
        }
    }
}
//����������� ������� << ��� ��� �������� ����������� ��� ����������� ������
ostream &operator<<( ostream &output,  Team *team )
    {
        output  <<"Goals: "<<team->getGoals()<<endl //�������� ��� ������� ��� ���� ��� ������
                <<"Missed Goals: "<<team->getMissed_Goals()<<endl   //�������� ��� ������� ��� ������� ���� ��� ������
                <<"Passes: "<<team->getPasses()<<endl   //�������� ��� ������� ��� ������ ��� ������
                <<"Mistakes: "<<team->getMistakes()<<endl;  //�������� ��� ������� ��� ����� ��� ������
       return output;

    }

class Game  //��������
{
public:
    friend ostream &operator<<( ostream&, const Team & );   //����������� ������� << ��� ��� �������� ����������� ��� ����������� ������
    Game(list<Player*> &List_Object_Team1, list<Player*> &List_Object_Team2, Player* Current_Player, Player* Ex_Player, Ball* ball) //������� ��� ��������������� ��� ���������� ���� ��� ���������� ��� ������������
    {
        setRounds(0);
    }
    void setRounds(int rounds_)  //������� ��� ������� ��� ����� ��� ����������
    {
        rounds = rounds_;
    }
    int getRounds() //���� ��� ������� ��� ����� ��� ����������
    {
        return rounds;
    }
    //������� runTurn � ����� ������ ��� action ��� ���� ��� ��� ��� ������ �� ������ �����
    void runTurn(list<Player*> &List_Object_Team1, list<Player*> &List_Object_Team2, Team* Team1, Team* Team2, Player* Current_Player, Player* Ex_Player, Ball* ball, Map* map_)
    {
        int prob_team_action=rand()%101;    //������ ���������� �������� ������
        if (prob_team_action < 50)  //50% ���������� �������� ��� ������ �
        {
            Team1->action(List_Object_Team1, List_Object_Team2, Current_Player, Ex_Player, ball, Team1, Team2, map_, 0);    //�������� ��� action ����� ��� ��� ����� �
            Team2->action(List_Object_Team1, List_Object_Team2, Current_Player, Ex_Player, ball, Team1, Team2, map_, 1);    //�������� ��� action ��� ��� ����� �
        }
        else    //50% ���������� �������� ��� ������ �
        {
            Team2->action(List_Object_Team1, List_Object_Team2, Current_Player, Ex_Player, ball, Team1, Team2, map_, 1);    //�������� ��� action ����� ��� ��� ����� �
            Team1->action(List_Object_Team1, List_Object_Team2, Current_Player, Ex_Player, ball, Team1, Team2, map_, 0);    //�������� ��� action ��� ��� ����� �
        }
        this->setRounds(getRounds()+1); //������ ��� ������ ��� ���������� ���� 1
        //������� �� � ���� ��� ������ ��������� ���� ��������� ���� ������ ��� �����, ���� ������� �� ��������� ���� ��� ��� ����� �
        if   ((ball->getBall_Position_X()==map_->getPosition_X()/2&&ball->getBall_Position_Y()==0) || (ball->getBall_Position_X()==map_->getPosition_X()/2+1&&ball->getBall_Position_Y()==0))
        {
            int prob_goal = rand()%101; //������ ���������� �� ��������� ����
            if (prob_goal < 50) //50% ���������� �� ��������� ����
            {
                Team2->setGoals(Team2->getGoals()+1);   //������ �� ���� ��� ������ � ���� 1
                ball->setBall_Position_X(map_->getPosition_X()/2);  //���� �� ���� � ��� ������ ���� ������ ��� ����
                ball->setBall_Position_Y(map_->getPosition_Y()/2);  //���� �� ���� � ��� ������ ���� ������ ��� ����
            }
            else    //��� ���������� ����
                Team2->setMissed_Goals(Team2->getMissed_Goals()+1); //������ ��� ������ ��� ������� ���� ���� 1
        }
        //������� �� � ���� ��� ������ ��������� ���� ��������� ���� ������ ��� �����, ���� ������� �� ��������� ���� ��� ��� ����� �
        else if ((ball->getBall_Position_X()==map_->getPosition_X()/2 && ball->getBall_Position_Y()==map_->getPosition_Y())||(ball->getBall_Position_X()==map_->getPosition_X()/2+1 && ball->getBall_Position_Y()==map_->getPosition_Y()))
        {
            int prob_goal = rand()%101; //������ ���������� �� ��������� ����
            if (prob_goal < 50) //50% ���������� �� ��������� ����
            {
                Team1->setGoals(Team1->getGoals()+1);   //������ �� ���� ��� ������ � ���� 1
                ball->setBall_Position_X(map_->getPosition_X()/2);  //���� �� ���� � ��� ������ ���� ������ ��� ����
                ball->setBall_Position_Y(map_->getPosition_Y()/2);  //���� �� ���� � ��� ������ ���� ������ ��� ����
            }
            else    //��� ���������� ����
                 Team1->setMissed_Goals(Team1->getMissed_Goals()+1);    //������ ��� ������ ��� ������� ���� ���� 1
        }
        else    //� ����� ��� ��������� ���� ��������� ������
        {
            ball->assignment(List_Object_Team1, List_Object_Team2, Team1, Team2, map_); //������� ��� ������ ���� ����������� ������
        }
    }
    //������� ����� ������������� ��� ����� ������������ �� ����� ����������
    void map_visualisation(list<Player*> &List_Object_Team1, list<Player*> &List_Object_Team2, Ball* ball, Map* map_)
    {
        cout<<"Map Visualisation:"<<endl;
        int map[map_->getPosition_X()+2][map_->getPosition_Y()+2];  //���������� ������������ ������ ��� ��� �������� ��� �����
        for (int j=0; j < map_->getPosition_Y()+2; j++) //������������ ��� ������ �� ������ ���������� �� ���� ����
        {
            for (int i=0; i < map_->getPosition_X()+2; i++)
            {
                map[i][j]=' ';
            }
        }
        for (int i=0; i < map_->getPosition_X()+1; i++) //������� ��� ������������� � ��� �����
            map[i+1][0] = i;
        for (int i=0; i < map_->getPosition_Y()+1; i++) //������� ��� ������������� � ��� �����
            map[0][i+1] = i;
        list<Player*>::iterator p = List_Object_Team1.begin();
        while(p != List_Object_Team1.end()) //������� ��� ������� ��� ������ � �� �� ������� #
        {
            map[(*p)->getPosition_X()+1][(*p)->getPosition_Y()+1] = '#';
            p++;
        }
        p = List_Object_Team2.begin();
        while(p != List_Object_Team2.end()) //������� ��� ������� ��� ������ � �� �� ������� $
        {
            map[(*p)->getPosition_X()+1][(*p)->getPosition_Y()+1] = '$';
            p++;
        }
        map[ball->getBall_Position_X()+1][ball->getBall_Position_Y()+1] = '@';  //������� ��� ������ �� �� ������� @
        cout<<" ";
        for (int j=0; j < map_->getPosition_Y()+2; j++)     //�������� ��� �����, ���� ��� ������������ ������
        {
            for (int i=0; i < map_->getPosition_X()+2; i++)
            {
                if(!(i==0 && j==0)) //�������� ���� ����� ��� ������� (0,0)
                {
                    if(i!=0)    //�������� ���� ����� ������ ��� ������
                        cout<<" ";
                    if (i==0 || j==0)
                        printf("%d", map[i][j]);    //�������� ��� ������������� ��� �����
                    else
                        printf("%c", map[i][j]);    //�������� ��� ������� ���������� ��� ������������ ���� ��� �����
                }
            }
            cout<<endl;
        }
        cout<<endl;
    }
    //������� ��������� ������� ����������� ��� ����������� ��� �����
    void general_info()
    {
        cout<<"General Info:"<<endl;
        cout<<"Steals: "<<Defender::Steals+Midfielder::Steals<<endl;    //�������� ��� ��������� ������� ����������
        cout<<"Rounds: "<<this->getRounds()<<endl;  //�������� ��� ������� ��� ����� ��� ����������
        cout<<endl;
    }
    //������� ��������� ����������� ��� ���� ������
    void team_statistics(Team* Team1, Team* Team2)
    {
        cout<<"Team 1 Statistics:"<<endl;
        cout<<Team1;    //����� ��� �������������� ������� ��� ��� ����� � <<
        cout<<"Red Cards: "<<Player::Red_Cards_Team1<<endl; //�������� ��� ������� ��� �������� ������ ��� ������ �
        cout<<"Team 2 Statistics:"<<endl;
        cout<<Team2;    //����� ��� �������������� ������� ��� ��� ����� � <<
        cout<<"Red Cards: "<<Player::Red_Cards_Team2<<endl; //�������� ��� ������� ��� �������� ������ ��� ������ �
        cout<<endl;
    }
    //������� ��������� ��� ����������� ��� ������� ��� ���� ������ ��� �� �������� ����
    void player_info(list<Player*> &List_Object_Team1, list<Player*> &List_Object_Team2)
    {
        bool Yellow_Card;   //�� ���� ������� ����� � ����������� �������
        cout<<"Team 1 Players: "<<endl;
        cout<<"Pos_X Pos_Y Move_Line Aim_Line Jersey_Num Yellow_Card Name    "<<endl;
        list<Player*>::iterator p = List_Object_Team1.begin();
        while(p != List_Object_Team1.end()) //�������� ��� ��������� ��� ���� ������� ��� ������ �
        {
            if (dynamic_cast<Defender*>(*p)==NULL && dynamic_cast<Midfielder*>(*p)==NULL) //������� �� � ������� ��� ����� ���� ��������� ���� �����
                Yellow_Card = 0;    //�� ��� ����� ���� ��� ���� ������� ������� �����
            else if(dynamic_cast<Midfielder*>(*p) == NULL)   //�� ������ ���� � ������� �� ��� ���������
                Yellow_Card = dynamic_cast<Defender*>(*p)->getYellow_Card();    //���� ��� ������� �������� ������ ��� ���������
            else    //������ �� ��� �����
                Yellow_Card = dynamic_cast<Midfielder*>(*p)->getYellow_Card();  //���� ��� ������� �������� ������ ��� �����
            //�������� ��� ����������� ��� ��������� ��� ������� ��� ������ �
            cout<<"  "<<(*p)->getPosition_X()<<"     "<<(*p)->getPosition_Y()<<"       "<<(*p)->getMovement_Line()<<"        "<<(*p)->getAim_Line()<<"         "<<(*p)->getJersey_Number()<<"           "<<Yellow_Card<<"      "<<(*p)->getName()<<endl;
            p++;
        }
        cout<<"Team 2 Players: "<<endl;
        cout<<"Pos_X Pos_Y Move_Line Aim_Line Jersey_Num Yellow_Card Name    "<<endl;
        p = List_Object_Team2.begin();
        while(p != List_Object_Team2.end()) //�������� ��� ��������� ��� ���� ������� ��� ������ �
        {
            if (dynamic_cast<Defender*>(*p)==NULL && dynamic_cast<Midfielder*>(*p)==NULL) //������� �� � ������� ��� ����� ���� ��������� ���� �����
                Yellow_Card = 0;    //�� ��� ����� ���� ��� ���� ������� ������� �����
            else if (dynamic_cast<Midfielder*>(*p) == NULL)  //�� ������ ���� � ������� �� ��� ���������
                Yellow_Card = dynamic_cast<Defender*>(*p)->getYellow_Card();    //���� ��� ������� �������� ������ ��� ���������
            else    //������ �� ��� �����
                Yellow_Card = dynamic_cast<Midfielder*>(*p)->getYellow_Card();  //���� ��� ������� �������� ������ ��� �����
            //�������� ��� ����������� ��� ��������� ��� ������� ��� ������ �
            cout<<"  "<<(*p)->getPosition_X()<<"     "<<(*p)->getPosition_Y()<<"       "<<(*p)->getMovement_Line()<<"        "<<(*p)->getAim_Line()<<"         "<<(*p)->getJersey_Number()<<"           "<<Yellow_Card<<"      "<<(*p)->getName()<<endl;
            p++;
        }
    }
private:
    int rounds;
};

class Data  //�������� �������
{
public:
    Data()  //Default constructor
    {
    }
    void setList_Object_Team1(list<Player*> List_Object_Team1_) //������� ��� ������ ������� ��� ������ �
    {
        List_Object_Team1 = List_Object_Team1_;
    }
    void setList_Object_Team2(list<Player*> List_Object_Team2_) //������� ��� ������ ������� ��� ������ �
    {
        List_Object_Team2 = List_Object_Team2_;
    }
    void setTeam_A(Team* team_A_)   //������� ��� ������ �
    {
        team_A = team_A_;
    }
    void setTeam_B(Team* team_B_)   //������� ��� ������ �
    {
        team_B = team_B_;
    }
    list<Player*> &getList_Object_Team1()   //���� ��� ������ ������� ��� ������ �
    {
        return List_Object_Team1;
    }
    list<Player*> &getList_Object_Team2()   //���� ��� ������ ������� ��� ������ �
    {
        return List_Object_Team2;
    }
    Team* getTeam_A()   //���� ��� ������ �
    {
        return team_A;
    }
    Team* getTeam_B()   //���� ��� ������ �
    {
        return team_B;
    }
    int data_initialization(Map *map_)  //������� ��������� ��� ��������� ���� �������
    {
        ifstream input("data.txt"); //�������� ��������� ���� ��� ������� data.txt ��� ��������� ��� ���� path �� �� ����������
        if(!input.is_open())    //������ ������� ��� ��� ������ ������� ��� �������
        {
            cout<<"Please create the input data file named as 'data.txt'"<<endl;
            return 0;   //����������� ��� ������������
        }
        int team_Counter = 0;   //�������� ������� ��� ������ ��� ���� ������������
        string team_Names[2];   //������� ����������� ��� �������� ��� ������
        Team *team_A, *team_B;  //����������� ������ � ��� �
        string team_Name, player_Type, player_Name; int pos_X, pos_Y, jersey_Num, movement_Line, aim_Line;  //�������������� �������
        while (input >> team_Name >> player_Type >> player_Name >> pos_X >> pos_Y >> jersey_Num >> movement_Line >> aim_Line)
        {
            //������� ���� �� ����������� ����� �� ���������� ���� ��� ���� ��� �����
            if (pos_X > map_->getPosition_X() || pos_Y > map_->getPosition_Y() || movement_Line > map_->getPosition_Y() || aim_Line > map_->getPosition_Y()
                || pos_X < 0 || pos_Y < 0 || movement_Line < 0 || aim_Line < 0)
            {
                cout<<"Player's values exceed the map dimensions!"<<endl;
                return 0;   //����������� ��� ������������
            }
            if (pos_Y != movement_Line) //� ���� � ��� ������ ����� ��� � ������ ������� ��� ������ �� �����������
            {
                cout<<"Player's position_Y must be same as his movement line!"<<endl;
                return 0;   //����������� ��� ������������
            }

            if (team_Counter == 0)  //������� �� ��� ���� ������������ ����� �����
            {
                team_A = new Team(team_Name);   //���� ����������� � ���������� ����
                team_Names[0] = team_Name;
                team_Counter = 1;   //������ ��� ������� ���� 1, ������ ������������� ��� �����
            }
            else if(team_Counter == 1 && team_Names[0]!=team_Name)  //������� �� � ������� ����� ��� �� ������������ ��� ���������� �� ��� �����
            {
                team_B = new Team(team_Name);   //���� ����������� � ���������� �������� ������
                team_Names[1] = team_Name;
                team_Counter = 2;   //������ ��� ������� ���� 1, ������ ������������� ��� ����� �����
            }
            if (team_Counter==2 && team_Names[0]!=team_Name && team_Names[1]!=team_Name)    //������� �� ������������� �������� ��� 2 ������
            {
                cout<< "Error! Maximum number of teams reached!" <<endl;
                return 0;   //����������� ��� ������������
            }
            if(team_Names[0] == team_Name)  //������� ��� ��������������� ��� ������� ��� ������ �
            {
                //������� ��� ����� ��� ������ ��� �� ������������
                if (player_Type == "Defender")
                {
                    team_A->setPlayer_List(new Defender(player_Name, pos_X, pos_Y, jersey_Num, movement_Line, aim_Line));
                }
                else if (player_Type == "Midfielder")
                {
                    team_A->setPlayer_List(new Midfielder(player_Name, pos_X, pos_Y, jersey_Num, movement_Line, aim_Line));
                }
                else if (player_Type == "Forward")
                {
                    team_A->setPlayer_List(new Forward(player_Name, pos_X, pos_Y, jersey_Num, movement_Line, aim_Line));
                }
                else if (player_Type == "Striker")
                {
                    team_A->setPlayer_List(new Striker(player_Name, pos_X, pos_Y, jersey_Num, movement_Line, aim_Line));
                }
                else
                {
                    cout<<"Not a valid Player Type!" << endl;
                    return 0;   //����������� ��� ������������
                }
            }
            else if(team_Names[1] == team_Name) //������� ��� ��������������� ��� ������� ��� ������ �
            {
                //������� ��� ����� ��� ������ ��� �� ������������
                if (player_Type == "Defender")
                {
                    team_B->setPlayer_List(new Defender(player_Name, pos_X, pos_Y, jersey_Num, movement_Line, aim_Line));
                }
                else if (player_Type == "Midfielder")
                {
                    team_A->setPlayer_List(new Midfielder(player_Name, pos_X, pos_Y, jersey_Num, movement_Line, aim_Line));
                }
                else if (player_Type == "Forward")
                {
                    team_B->setPlayer_List(new Forward(player_Name, pos_X, pos_Y, jersey_Num, movement_Line, aim_Line));
                }
                else if (player_Type == "Striker")
                {
                    team_A->setPlayer_List(new Striker(player_Name, pos_X, pos_Y, jersey_Num, movement_Line, aim_Line));
                }
                else
                {
                    cout<<"Not a valid Player Type!" << endl;
                    return 0;   //����������� ��� ������������
                }
            }
        }
        list<Player*> List_Object_Team1 = team_A->getPlayer_List(); //���� ��� ������ ��� ������� ��� ������ �
        list<Player*> List_Object_Team2 = team_B->getPlayer_List(); //���� ��� ������ ��� ������� ��� ������ �
        //������� ���� �� ����������� ���� ���� ������� �� ���� ������
        if (player_List_Validation(List_Object_Team1, List_Object_Team2)==0 || player_List_Validation(List_Object_Team2, List_Object_Team1)==0)
            return 0;   //����������� ��� ������������
        this->setList_Object_Team1(List_Object_Team1);  //������� ��� ������ ������� ��� ������ �
        this->setList_Object_Team2(List_Object_Team2);  //������� ��� ������ ������� ��� ������ �
        this->setTeam_A(team_A);    //������� ��� ������ �
        this->setTeam_B(team_B);    //������� ��� ������ �
    }
    //������� ������� ����������� ��� �������, ���� �� ����������� ���� ���� ������� �� ���� ������
    int player_List_Validation(list<Player*> List_Object_Team1, list<Player*> List_Object_Team2)
    {
        int Movement_Line;  //������ ������
        list<Player*>::iterator p1 = List_Object_Team1.begin();
        while(p1 != List_Object_Team1.end())    //������� ��� ���� ������ ��� ������ �, �� ���������� � ������ ������� ��� �� ������� ����� ������
        {
            Movement_Line = (*p1)->getMovement_Line();
            int counter = 0;    //�������� ��� ������� ��� ����� ��� ���� ������ ������� �� ��� ���������� ������
            list<Player*>::iterator p2 = List_Object_Team1.begin();
            while(p2 != List_Object_Team1.end())    //������� ������ �� ����� ���� ������� ��� ������ �
            {
                if (Movement_Line == (*p2)->getMovement_Line()) //������� �� ����������� �� ������� ������� ����
                    counter++;  //���� ������ ��� ������� ���� 1
                p2++;
            }
            list<Player*>::iterator p3 = List_Object_Team2.begin();
            while(p3 != List_Object_Team2.end())    //������� ��� �������� �� ����� ���� ������� ��� ������ �
            {
                if (Movement_Line == (*p3)->getMovement_Line()) //������� �� ����������� �� ������� ������� ����
                    counter++;  //���� ������ ��� ������� ���� 1
                p3++;
            }
            if (counter > 1)    //��� �� ����� ������ ������ � ��������=1, ����� ��������� ���� � ����������� ������� �� ��� ����� ���
            {
                cout<<"Only one player is permitted per line!"<<endl;
                return 0;   //����������� ������������
            }
            p1++;
        }
    }
private:
    list<Player*> List_Object_Team1;
    list<Player*> List_Object_Team2;
    Team *team_A;
    Team *team_B;
};

main()  //�������� ��� ����������
{
    int ball_same_position=0;   //�������� ��� �� ������ ������ ���� ������� ���� � �����
    Map *map_ = new Map(5,8);   //�������� ��� ���������� ��� ����� [0,x] [0,y]
    Data *data = new Data();    //�������� ��� ��������� ���� ��� �������
    if (data->data_initialization(map_)==0) //������� ����������� ��� ��������� �������
        return 0;   //����������� ������������
    //���������� ���� ������������ ������, �� ������� ������������� �� ������ ��� �����
    Ball *b = new Ball(map_->getPosition_X()/2,map_->getPosition_Y()/2, data->getList_Object_Team1(), data->getList_Object_Team2());
    int ball_Position_X = b->getBall_Position_X();  //���� ��� ��������� ����� � ��� ������
    int ball_Position_Y = b->getBall_Position_Y();  //���� ��� ��������� ����� � ��� ������
    //���������� ���� ������������ ����������
    Game *game = new Game(data->getList_Object_Team1(), data->getList_Object_Team2(),  b->Current_Player, b->Ex_Player, b);

    int iterations = 0; //�������� ��� �������� �����������
    //�������� ��� ������������ ����� �� ��������� � ������������ ������� ���� � �� ���������� � ����������� ������� �����������
    while (data->getTeam_A()->getGoals()<700 && data->getTeam_B()->getGoals()<700 && iterations<1000)
    {
        //�������� ��� ����������� ������� ��� ������ ���������� ��� ��� ����������� ���
        game->runTurn(data->getList_Object_Team1(), data->getList_Object_Team2(), data->getTeam_A(), data->getTeam_B(), b->getCurrent_Player(), b->getEx_Player(), b, map_);
        game->map_visualisation(data->getList_Object_Team1(), data->getList_Object_Team2(), b, map_);
        game->general_info();
        game->team_statistics(data->getTeam_A(),data->getTeam_B());
        game->player_info(data->getList_Object_Team1(), data->getList_Object_Team2());
        if (b->getBall_Position_X()== ball_Position_X && b->getBall_Position_Y()==ball_Position_Y)  //������� �� ��������� � ����� ���� ���� ����
            ball_same_position += 1;    //������ ��� ������� ���� 1
        else
        {
            ball_same_position=0;   //��������� ��� �������, ����� ������ ���� � �����
            ball_Position_X = b->getBall_Position_X();  //������� ��� ���� ����� � ��� ������
            ball_Position_Y = b->getBall_Position_Y();  //������� ��� ���� ����� � ��� ������
        }
        if (ball_same_position == 5)    //������� �� ��������� � ����� ���� ���� ���� ��� 5 ������
            b->assignment(data->getList_Object_Team1(), data->getList_Object_Team2(), data->getTeam_A(), data->getTeam_B(), map_); //������� ��� ������ ���� ����������� ������, �� ��� ������� ��� ������ �������

        iterations += 1;    //������ ��� ������� ���� ��� ��� ����� ��� ���� �����
    }
    return 0;   //����������� ������������
}

