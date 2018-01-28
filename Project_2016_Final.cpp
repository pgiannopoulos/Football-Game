using namespace std;
#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <fstream>
#include <cmath>

class Map   //Χάρτης μετακίνησης των αντικειμένων
{
public:
    Map(int Position_X_, int Position_Y_)   //Ορισμός των διαστάσεων του χάρτη κατά τη δημιουργία του αντικειμένου
    {
        setPosition_X(Position_X_);
        setPosition_Y(Position_Y_);
    }
    void setPosition_X(int Position_X_)     //Ορισμός της διάστασης Χ του χάρτη
    {
        Position_X = Position_X_;
    }
    void setPosition_Y(int Position_Y_)     //Ορισμός της διάστασης Υ του χάρτη
    {
        Position_Y = Position_Y_;
    }
    int getPosition_X()     //Λήψη της διάστασης Χ του χάρτη
    {
        return Position_X;
    }
    int getPosition_Y()     //Λήψη της διάστασης Υ του χάρτη
    {
        return Position_Y;
    }
protected:
    int Position_X, Position_Y;
};

class Ball; //Forward definitions
class Team;

class Player    //Abstract class --- Παίχτης-Ποδοσφαιριστής
{
public:
    Player(string Name_, int Position_X_, int Position_Y_, int Jersey_Number_, int Movement_Line_, int Aim_Line_)   //Ορισμός των χαρακτηριστικών του παίχτη κατά τη δημιουργία του αντικειμένου
    {
        setName(Name_);
        setPosition_X(Position_X_);
        setPosition_Y(Position_Y_);
        setJersey_Number(Jersey_Number_);
        setMovement_Line(Movement_Line_);
        setAim_Line(Aim_Line_);
    }
    void setName(string Name_)          //Ορισμός του ονόματος του παίχτη
    {
        Name = Name_;
    }
    void setPosition_X(int Position_X_) //Ορισμός της θέσης Χ του παίχτη
    {
        Position_X = Position_X_;
    }
    void setPosition_Y(int Position_Y_) //Ορισμός της θέσης Υ του παίχτη
    {
        Position_Y = Position_Y_;
    }
    void setJersey_Number(int Jersey_Number_)   //Ορισμός του αριθμού της φανέλας του παίχτη
    {
        Jersey_Number = Jersey_Number_;
    }
    void setMovement_Line(int Movement_Line_)   //Ορισμός της γραμμής κίνησης του παίχτη
    {
        Movement_Line = Movement_Line_;
    }
    void setAim_Line(int Aim_Line_)     //Ορισμός της γραμμής στόχου του παίχτη
    {
        Aim_Line = Aim_Line_;
    }
    void setRed_Cards_Team1(int Red_Cards_Team1_)   //Ορισμός του αριθμού των κόκκινων καρτών της Ομάδας_Α
    {
        Red_Cards_Team1 = Red_Cards_Team1_;
    }
    void setRed_Cards_Team2(int Red_Cards_Team2_)   //Ορισμός του αριθμού των κόκκινων καρτών της Ομάδας_Β
    {
        Red_Cards_Team2 = Red_Cards_Team2_;
    }
    string getName()        //Λήψη του ονόματος του παίχτη
    {
        return Name;
    }
    int getPosition_X()     //Λήψη της θέσης Χ του παίχτη
    {
        return Position_X;
    }
    int getPosition_Y()     //Λήψη της θέσης Υ του παίχτη
    {
        return Position_Y;
    }
    int getJersey_Number()  //Λήψη του αριθμού της φανέλας του παίχτη
    {
        return Jersey_Number;
    }
    int getMovement_Line()  //Λήψη της γραμμής κίνησης του παίχτη
    {
        return Movement_Line;
    }
    int getAim_Line()       //Λήψη της γραμμής στόχου του παίχτη
    {
        return Aim_Line;
    }
    int getRed_Cards_Team1()    //Λήψη του αριθμού των κόκκινων καρτών της Ομάδας_Α
    {
        return Red_Cards_Team1;
    }
    int getRed_Cards_Team2()    //Λήψη του αριθμού των κόκκινων καρτών της Ομάδας_Β
    {
        return Red_Cards_Team2;
    }
    virtual void movement(Map* map_)    //Μέθοδος μετακίνησης μία θέσης αριστερά ή δεξιά του παίχτη
    {
        int prob_movement = rand()%2;   //Τυχαία επιλογή μετακίνησης αριστερά ή δεξιά
        if (prob_movement==1 && this->getPosition_X()!=map_->getPosition_X())   //Έλεγχος εντός ορίων του χάρτη για μετακίνηση δεξιά
            this->setPosition_X(this->getPosition_X()+1);       //Μετακίνηση δεξιά του παίχτη
        else if (prob_movement == 0 && this->getPosition_X() != 0)              //Έλεγχος εντός ορίων του χάρτη για μετακίνηση δεξιά
            this->setPosition_X(this->getPosition_X()-1);       //Μετακίνηση  του παίχτη
    }
    //Μέθοδος μεταβίβασης της μπάλας σε μια τυχαία στήλη της γραμμής στόχου, εφόσον ο παίχτης έχει την μπάλα
    virtual void transfer(Player* Current_Player, Ball* ball, list<Player*> &List_Object_Team1, list<Player*> &List_Object_Team2, Map* map_);
    //Μέθοδος ειδικής κίνησης που υπερκαλύπτεται σε κάθε κλάση - Pure Virtual
    virtual void special_Movement(Ball* ball, Player* Current_Player,list<Player*> &List_Object_Team1,list<Player*> &List_Object_Team2, Map* map_)=0;

    bool getTeam_of_Player(list<Player*> &List_Object_Team1)    //Έλεγχος σε ποια ομάδα ανήκει ο παίχτης
    {   //Αν ανήκει στην ομάδα Α τότε 0 - Αν ανήκει στην ομάδα Β τότε 1
        bool found = !(find(List_Object_Team1.begin(), List_Object_Team1.end(), this) != List_Object_Team1.end());
        return found;
    }
    bool operator&&(Player *Current_Player) //Υπερφόρτωση του τελεστή &&
    {//Έλεγχος αν στις θέσεις γύρω από τον τρέχων παίχτη υπάρχει κάποιος άλλος παίχτης
       return       ((Current_Player->getPosition_X()==this->getPosition_X()-1) && (Current_Player->getPosition_Y()==this->getPosition_Y())//Έλεγχος για αριστερά
                  || (Current_Player->getPosition_X()==this->getPosition_X()+1) && (Current_Player->getPosition_Y()==this->getPosition_Y())//Έλεγχος για δεξιά
                  || (Current_Player->getPosition_X()==this->getPosition_X()) && (Current_Player->getPosition_Y()==this->getPosition_Y()-1)//Έλεγχος για κάτω
                  || (Current_Player->getPosition_X()==this->getPosition_X()) && (Current_Player->getPosition_Y()==this->getPosition_Y()+1)//Έλεγχος για πάνω
                  || (Current_Player->getPosition_X()==this->getPosition_X()-1 && Current_Player->getPosition_Y()==this->getPosition_Y()-1)//Διαγώνιος έλεγχος
                  || (Current_Player->getPosition_X()==this->getPosition_X()-1 && Current_Player->getPosition_Y()==this->getPosition_Y()+1)
                  || (Current_Player->getPosition_X()==this->getPosition_X()+1 && Current_Player->getPosition_Y()==this->getPosition_Y()+1)
                  || (Current_Player->getPosition_X()==this->getPosition_X()+1 && Current_Player->getPosition_Y()==this->getPosition_Y()-1));
    }
public:
    static int Red_Cards_Team1;     //Καθολική μεταβλητή για όλα τα αντικείμενα της κλάσης
    static int Red_Cards_Team2;     //Καθολική μεταβλητή για όλα τα αντικείμενα της κλάσης
private:
    string Name;
    int Position_X, Position_Y, Jersey_Number, Movement_Line, Aim_Line;
};
int Player :: Red_Cards_Team1 = 0;  //Αρχικοποίηση της τιμής της καθολικής μεταβλητής
int Player :: Red_Cards_Team2 = 0;  //Αρχικοποίηση της τιμής της καθολικής μεταβλητής

class Ball  //Μπάλα
{
public:
    Ball(int Ball_Position_X_, int Ball_Position_Y_, list<Player*> &List_Object_Team1,list<Player*> &List_Object_Team2) //Ορισμός των χαρακτηριστικών της μπάλας κατά τη δημιουργία του αντικειμένου
    {
        setBall_Position_X(Ball_Position_X_);
        setBall_Position_Y(Ball_Position_Y_);
        setCurrent_Player(List_Object_Team1, List_Object_Team2);
    }
    void setBall_Position_X(int Ball_Position_X_)   //Ορισμός της θέσης Χ της μπάλας
    {
        Ball_Position_X = Ball_Position_X_;
    }
    void setBall_Position_Y(int Ball_Position_Y_)   //Ορισμός της θέσης Υ της μπάλας
    {
        Ball_Position_Y = Ball_Position_Y_;
    }
    void setCurrent_Player(list<Player*> &List_Object_Team1, list<Player*> &List_Object_Team2)  //Ορισμός του παίχτη που έχει στην κατοχή του την μπάλα
    {
        this->setEx_Player(Current_Player, List_Object_Team1, List_Object_Team2);   //Ορισμός του πρώην τρέχων παίχτη καθώς θα οριστεί νέος τρέχων παίχτης
        bool flag = 0;
        list<Player*>::iterator p = List_Object_Team1.begin();
        while(p != List_Object_Team1.end())     //Έλεγχος για τη λίστα της ομάδας Α
        {
            if (getBall_Position_X()==(*p)->getPosition_X() && getBall_Position_Y()==(*p)->getPosition_Y()) //Έλεγχος αν ταυτίζονται οι συντεταγμένες της μπάλας με κάποιου παίχτη
            {
                Current_Player = (*p);  //Αν βρέθηκε τότε όρισε τρέχων παίχτη
                flag = 1;
            }
            p++;
        }
        if (flag == 0)    //Αλλιώς έλεγχος για τη λίστα της ομάδας Β
        {
            list<Player*>::iterator p = List_Object_Team2.begin();
            while(p != List_Object_Team2.end())
            {
                if (getBall_Position_X()==(*p)->getPosition_X() && getBall_Position_Y()==(*p)->getPosition_Y()) //Έλεγχος αν ταυτίζονται οι συντεταγμένες της μπάλας με κάποιου παίχτη
                {
                    Current_Player = (*p);  //Αν βρέθηκε τότε όρισε τρέχων παίχτη
                    flag = 1;
                }
                p++;
            }
        }
        if (flag == 0) //Αν δεν βρέθηκε παίχτης που να χει στην κατοχή του την μπάλα τότε θέσε NULL
        {
            Current_Player = NULL;
        }
    }
    void setEx_Player(Player* Current_Player, list<Player*> &List_Object_Team1, list<Player*> &List_Object_Team2)   //Ορισμός του προτελευταίου τρέχων παίχτη
    {
            list<Player*>::iterator findIter = find(List_Object_Team1.begin(), List_Object_Team1.end(), Current_Player);
            if (findIter != List_Object_Team1.end())    //Εύρεση του τρέχων παίχτη στις λίστες παιχτών και ορισμός του ως πρώηγ τρέχων παίχτης
                {
                    Ex_Player = (*findIter);
                }
            else
            {
                list<Player*>::iterator findIter = find(List_Object_Team2.begin(), List_Object_Team2.end(), Current_Player);
                Ex_Player = (*findIter);
            }
    }
    int getBall_Position_X()    //Λήψη της θέσης Χ της μπάλας
    {
        return Ball_Position_X;
    }
    int getBall_Position_Y()    //Λήψη της θέσης Υ της μπάλας
    {
        return Ball_Position_Y;
    }
    Player* getCurrent_Player() //Λήψη του τρέχων παίχτη
    {
        return Current_Player;
    }
    Player* getEx_Player()      //Λήψη του προτελευταίου τρέχων παίχτη
    {
        return Ex_Player;
    }
    //Μέθοδοι ανάθεσης - Πολυμορφισμός
    void assignment(Player* Player_, list<Player*> &List_Object_Team1, list<Player*> &List_Object_Team2, Team* Team1, Team* Team2); //Ανάθεση της μπάλας στον παίχτη που δόθηκε αν βρίσκεται σε κάποια θέση γύρω από την μπάλα

    void assignment(list<Player*> &List_Object_Team1, list<Player*> &List_Object_Team2, Team* Team1, Team*  Team2, Map* map_)   //Ανάθεση της μπάλας στον κοντινότερο παίχτη, αν δεν υπάρχει ήδη τρέχων παίχτης
    {
        if (Current_Player == NULL) //Έλεγχος αν υπάρχει τρέχων παίχτης
        {
            float min_distance = sqrt(pow(map_->getPosition_X(),2)+pow(map_->getPosition_Y(),2)) + 1;   //Αρχικός ορισμός μια τιμής μεγαλύτερης της μέγιστης απόστασης μεταξύ 2 θέσεων στο χάρτη
            list<Player*>::iterator p = List_Object_Team1.begin();
            while(p != List_Object_Team1.end())     //Έλεγχος για τους παίχτες της ομάδας Α
            {
                if (sqrt(pow((*p)->getPosition_X()-this->getBall_Position_X(),2)+pow((*p)->getPosition_Y()-this->getBall_Position_Y(),2)) < min_distance)   //Σύγκριση των αποστάσεων
                {
                    min_distance = sqrt(pow((*p)->getPosition_X()-this->getBall_Position_X(),2)+pow((*p)->getPosition_Y()-this->getBall_Position_Y(),2));   //Ορισμός της νέας ελάχιστης απόστασης
                    temp = p;   //Προσωρινή αποθήκευση της θέσης του αντικειμένου στη λίστα
                }
                p++;
            }
            p = List_Object_Team2.begin();
            while(p != List_Object_Team2.end())     //Έλεγχος για τους παίχτες της ομάδας Α
            {
                if (sqrt(pow((*p)->getPosition_X()-this->getBall_Position_X(),2)+pow((*p)->getPosition_Y()-this->getBall_Position_Y(),2)) < min_distance)   //Σύγκριση των αποστάσεων
                {
                    min_distance = sqrt(pow((*p)->getPosition_X()-this->getBall_Position_X(),2)+pow((*p)->getPosition_Y()-this->getBall_Position_Y(),2));   //Ορισμός της νέας ελάχιστης απόστασης
                    temp = p;   //Προσωρινή αποθήκευση της θέσης του αντικειμένου στη λίστα
                }
                p++;
            }
            this->setBall_Position_X((*temp)->getPosition_X()); //Αλλαγή της θέσης Χ της μπάλας σε αυτή του κοντινότερου παίχτη
            this->setBall_Position_Y((*temp)->getPosition_Y()); //Αλλαγή της θέσης Υ της μπάλας σε αυτή του κοντινότερου παίχτη
            this->setCurrent_Player(List_Object_Team1, List_Object_Team2); //Ορισμός του νέου τρέχων παίχτη
        }
    }
    bool operator&&(Player *Player_) //Υπερφόρτωση του τελεστή &&
    {//Έλεγχος αν η μπάλα είναι ελεύθερη (Τρέχων παίχτης=NULL) και αν βρίσκεται δίπλα στον αντίστοιχο παίχτη
       return  (this->getCurrent_Player()==NULL && (this->getBall_Position_X()==Player_->getPosition_X()-1 && this->getBall_Position_Y()==Player_->getPosition_Y())//Έλεγχος αριστερά
                                        || (this->getBall_Position_X()==Player_->getPosition_X()+1 && this->getBall_Position_Y()==Player_->getPosition_Y())//Έλεγχος δεξιά
                                        || (this->getBall_Position_X()==Player_->getPosition_X() && this->getBall_Position_Y()==Player_->getPosition_Y()-1)//Έλεγχος κάτω
                                        || (this->getBall_Position_X()==Player_->getPosition_X() && this->getBall_Position_Y()==Player_->getPosition_Y()+1)//Έλεγχος πάνω
                                        || (this->getBall_Position_X()==Player_->getPosition_X()-1 && this->getBall_Position_Y()==Player_->getPosition_Y()-1)//Διαγώνιος έλεγχος
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

class Defender: public Player   //Υποκλάση Αμυντικός
{
public:
    Defender(string Name_,int Position_X_, int Position_Y_, int Jersey_Number_, int Movement_Line_, int Aim_Line_) : Player(Name_, Position_X_, Position_Y_, Jersey_Number_, Movement_Line_, Aim_Line_)
    {
        setYellow_Card(0);
    }
    void setYellow_Card(bool Yellow_Card_)  //Ορισμός κίτρινης κάρτας του αμυντικού
    {
        Yellow_Card = Yellow_Card_;
    }
    void setSteals(int Steals_) //Ορισμός της καθολικής μεταβλητής κλεψιμάτων
    {
        Steals = Steals_;
    }
    bool getYellow_Card()   //Λήψη κίτρινης κάρτας του αμυντικού
    {
        return Yellow_Card;
    }
    int getSteals()     //Λήψη της καθολικής μεταβλητής κλεψιμάτων
    {
        return Steals;
    }
    //Υπερκάλυψη της μεθόδου ειδικής κίνησης, ώστε αν υπάρχει αντίπαλος τρλεχων παίχτης σε διπλανή θέση είτε να παίρνει στην κατοχή του την μπάλα, είτε δέχεται κίτρινη κάρτα
    void special_Movement(Ball *ball, Player *Current_Player,list<Player*> &List_Object_Team1,list<Player*> &List_Object_Team2, Map* map_)
    {
        if (Current_Player != NULL) //Έλεγχος αν υπάρχει τρέχων παίχτης
        {
            if (Current_Player->getTeam_of_Player(List_Object_Team1)!=this->getTeam_of_Player(List_Object_Team1))   //Έλεγχος αν ο τρέχων παίχτης είναι αντίπαλος
            {
                if (*this && Current_Player)  //Χρήση του υπερκαλυμένου τελεστή && για τον έλεγχο των γύρω θέσεων
                {
                    int prob_get_ball = rand()%101; //Τυχαία πιθανότητα κλεψίματος της μπάλας
                    int prob_yellow_card = rand()%101;  //Τυχαία πιθανότητα λήψης κίτρινης κάρτας
                    if (prob_get_ball <= 70)    //Κλέψιμο της μπάλας
                    {
                        ball->setBall_Position_X(this->getPosition_X());    //Αλλαγή της θέσης Χ της μπάλας
                        ball->setBall_Position_Y(this->getPosition_Y());    //Αλλαγή της θέσης Υ της μπάλας
                        setSteals(getSteals()+1);   //Αύξηση των κλεψιμάτων κατά 1
                    }
                    else if (prob_yellow_card <= 20)    //Λήψη κίτρινης κάρτας
                    {
                        if (this->getYellow_Card() == 0)    //Έλεγχος αν έχει ήδη κίτρινη κάρτα
                            this->setYellow_Card(1);    //Αν δεν έχει ήδη τότε παίρνει μία κίτρινη κάρτα
                        else if (this->getYellow_Card() == 1)   //Αν έχει ήδη μία κίτρινη κάρτα τότε αποβάλλεται από το παιχνίδι
                        {
                            if (this->getTeam_of_Player(List_Object_Team1) == 0)    //Έλεγχος αν βρίσκεται ο αμυντικός στην ομάδα Α
                            {
                                list<Player*>::iterator p = List_Object_Team1.begin();
                                p = find(List_Object_Team1.begin(), List_Object_Team1.end(), this); //Εύρεση της θέσης του στη λίστα των παιχτών της ομάδας Α
                                (*p)->setRed_Cards_Team1((*p)->getRed_Cards_Team1()+1); //Αύξηση των κόκκινων καρτών κατά 1 της ομάδας Α
                                p = List_Object_Team1.erase(p); //Διαγραφή του αντικειμένου από την λίστα
                                delete this;    //Διαγραφή του αντικειμένου
                            }
                            else
                            {
                                list<Player*>::iterator p = List_Object_Team2.begin();
                                p = find(List_Object_Team2.begin(), List_Object_Team2.end(), this); //Εύρεση της θέσης του στη λίστα των παιχτών της ομάδας Β
                                (*p)->setRed_Cards_Team2((*p)->getRed_Cards_Team2()+1); //Αύξηση των κόκκινων καρτών κατά 1 της ομάδας Β
                                p = List_Object_Team2.erase(p); //Διαγραφή του αντικειμένου από την λίστα
                                delete this;    //Διαγραφή του αντικειμένου
                            }
                        }
                    }
                }
            }
        }
    }
public:
    static int Steals;  //Καθολική μεταβήτή κλεψιμάτων
private:
    bool Yellow_Card;
};
 int Defender :: Steals = 0;    //Αρχικοποίηση της καθολική μεταβλητής κλεψιμάτων

class Midfielder: public Player //Υποκλάση Μέσος
{
public:
    Midfielder(string Name_,int Position_X_, int Position_Y_, int Jersey_Number_, int Movement_Line_, int Aim_Line_) : Player(Name_, Position_X_, Position_Y_, Jersey_Number_, Movement_Line_, Aim_Line_)
    {
        setYellow_Card(0);
    }
    void setYellow_Card(bool Yellow_Card_)  //Ορισμός κίτρινης κάρτας του μέσου
    {
        Yellow_Card = Yellow_Card_;
    }
    void setSteals(int Steals_) //Ορισμός της καθολικής μεταβλητής κλεψιμάτων
    {
        Steals = Steals_;
    }
    bool getYellow_Card()   //Λήψη κίτρινης κάρτας του μέσου
    {
        return Yellow_Card;
    }
    int getSteals()     //Λήψη της καθολικής μεταβλητής κλεψιμάτων
    {
        return Steals;
    }
    //Υπερκάλυψη της μεθόδου ειδικής κίνησης, ώστε αν υπάρχει αντίπαλος τρλεχων παίχτης σε διπλανή θέση είτε να παίρνει στην κατοχή του την μπάλα, είτε δέχεται κίτρινη κάρτα
    void special_Movement(Ball *ball, Player *Current_Player,list<Player*> &List_Object_Team1,list<Player*> &List_Object_Team2, Map* map_)
    {
        if (Current_Player != NULL) //Έλεγχος αν υπάρχει τρέχων παίχτης
        {
            if (Current_Player->getTeam_of_Player(List_Object_Team1)!=this->getTeam_of_Player(List_Object_Team1))   //Έλεγχος αν ο τρέχων παίχτης είναι αντίπαλος
            {
                if (*this && Current_Player)  //Χρήση του υπερκαλυμένου τελεστή && για τον έλεγχο των γύρω θέσεων
                {
                    int prob_get_ball = rand()%101; //Τυχαία πιθανότητα κλεψίματος της μπάλας
                    int prob_yellow_card = rand()%101;  //Τυχαία πιθανότητα λήψης κίτρινης κάρτας
                    if (prob_get_ball <= 50)    //Κλέψιμο της μπάλας
                    {
                        ball->setBall_Position_X(this->getPosition_X());    //Αλλαγή της θέσης Χ της μπάλας
                        ball->setBall_Position_Y(this->getPosition_Y());    //Αλλαγή της θέσης Υ της μπάλας
                        setSteals(getSteals()+1);   //Αύξηση των κλεψιμάτων κατά 1
                    }
                    else if (prob_yellow_card <= 20)    //Λήψη κίτρινης κάρτας
                    {
                        if (this->getYellow_Card() == 0)    //Έλεγχος αν έχει ήδη κίτρινη κάρτα
                            this->setYellow_Card(1);    //Αν δεν έχει ήδη τότε παίρνει μία κίτρινη κάρτα
                        else if (this->getYellow_Card() == 1)   //Αν έχει ήδη μία κίτρινη κάρτα τότε αποβάλλεται από το παιχνίδι
                        {
                            if (this->getTeam_of_Player(List_Object_Team1) == 0)    //Έλεγχος αν βρίσκεται ο αμυντικός στην ομάδα Α
                            {
                                list<Player*>::iterator p = List_Object_Team1.begin();
                                p = find(List_Object_Team1.begin(), List_Object_Team1.end(), this); //Εύρεση της θέσης του στη λίστα των παιχτών της ομάδας Α
                                (*p)->setRed_Cards_Team1((*p)->getRed_Cards_Team1()+1); //Αύξηση των κόκκινων καρτών κατά 1 της ομάδας Α
                                p = List_Object_Team1.erase(p); //Διαγραφή του αντικειμένου από την λίστα
                                delete this;    //Διαγραφή του αντικειμένου
                            }
                            else
                            {
                                list<Player*>::iterator p = List_Object_Team2.begin();
                                p = find(List_Object_Team2.begin(), List_Object_Team2.end(), this); //Εύρεση της θέσης του στη λίστα των παιχτών της ομάδας Β
                                (*p)->setRed_Cards_Team2((*p)->getRed_Cards_Team2()+1); //Αύξηση των κόκκινων καρτών κατά 1 της ομάδας Β
                                p = List_Object_Team2.erase(p); //Διαγραφή του αντικειμένου από την λίστα
                                delete this;    //Διαγραφή του αντικειμένου
                            }
                        }
                    }
                }
            }
        }
    }
    //Υπερκάλυψη της μεθόδου μεταβίβασης της μπάλας ώστε με μεγαλύτερη πιθανότητα να στέλνεται η μπάλα σε θέσεις που βρίσκονται στην κεντρική στήλη
    void transfer(Player* Current_Player, Ball* ball, list<Player*> &List_Object_Team1, list<Player*> &List_Object_Team2, Map* map_)
    {
        if (Current_Player != NULL) //Έλεγχος αν υπάρχει τρέχων παίχτης
        {
            if (this->getName() == Current_Player->getName())   //Έλεγχος αν το στιγμιότυπο αυτό είναι ο τρέχων παίχτης
            {
                ball->setBall_Position_Y(this->getAim_Line());  //Ορισμός της θέσης Υ της μπάλας ίση με τη γραμμή στόχου του μέσου
                int prob_of_Position_X = rand()%101;    //Τυχαία πιθανότητα να σταλεί η μπάλα σε θέσεις της κεντρικής στήλης
                if (prob_of_Position_X <= 50)
                    ball->setBall_Position_X(rand()%2+(map_->getPosition_X()/2));   //Ορισμός της μπάλας τυχαία σε θέσεις της κεντρικής στήλης
                else
                    ball->setBall_Position_X(rand()%(map_->getPosition_X()+1));     //Ορισμός της μπάλας τυχαία σε οποιαδήποτε στήλη
                ball->setCurrent_Player(List_Object_Team1, List_Object_Team2);      //Ορισμός του νέου τρέχων παίχτη
            }
        }
    }
public:
    static int Steals;  //Καθολική μεταβήτή κλεψιμάτων
private:
    bool Yellow_Card;
};
int Midfielder :: Steals = 0;   //Αρχικοποίηση της καθολική μεταβλητής κλεψιμάτων

class Forward: public Player    //Υποκλάση Επιθετικός
{
public:
    Forward(string Name_,int Position_X_, int Position_Y_, int Jersey_Number_, int Movement_Line_, int Aim_Line_) : Player(Name_, Position_X_, Position_Y_, Jersey_Number_, Movement_Line_, Aim_Line_)
    {

    }
    //Υπερκάλυψη της μεθόδου ειδικής κίνησης, ώστε αν η μπάλα βρίσκεται σε συμπαίκτη του, να μετακινείται κατά 2 θέσεις σε αντίθετη κατεύθυνση από τον κοντινότερο αντίπαλο
    void special_Movement(Ball *ball, Player *Current_Player, list<Player*> &List_Object_Team1, list<Player*> &List_Object_Team2, Map* map_)
    {
        if (Current_Player != NULL) //Έλεγχος αν υπάρχει τρέχων παίχτης
        {
            if (Current_Player->getTeam_of_Player(List_Object_Team1) == this->getTeam_of_Player(List_Object_Team1)) //Έλεγχος αν ο τρέχων παίχτης είναι συμπαίχτης
            {
                float min_distance = sqrt(pow(map_->getPosition_X(),2)+pow(map_->getPosition_Y(),2))+1;   //Αρχικός ορισμός μια τιμής μεγαλύτερης της μέγιστης απόστασης μεταξύ 2 θέσεων στο χάρτη
                int min_distance_X, min_distance_Y;
                if(Current_Player->getTeam_of_Player(List_Object_Team1) == 0) //Έλεγχος σε ποια ομάδα ανήκει ο τρέχων παίχτης
                {
                    list<Player*>::iterator p = List_Object_Team2.begin();
                    while(p != List_Object_Team2.end()) //Αναζήτηση για τον κοντινότερο αντίπαλο στην ομάδα Β
                    {
                        if (sqrt(pow((*p)->getPosition_X()-this->getPosition_X(),2)+pow((*p)->getPosition_Y()-this->getPosition_Y(),2)) < min_distance)   //Σύγκριση των αποστάσεων
                        {
                            min_distance = sqrt(pow((*p)->getPosition_X()-this->getPosition_X(),2)+pow((*p)->getPosition_Y()-this->getPosition_Y(),2)); //Ορισμός της νέας ελάχιστης απόστασης
                            min_distance_X =(*p)->getPosition_X();
                            min_distance_Y =(*p)->getPosition_Y();
                        }
                        p++;
                    }
                    if (this->getPosition_X()+2 > map_->getPosition_X())    //Έλεγχος αν η μετακίνηση υπερβαίνει τις τιμές του άξονα Χ
                        this->setPosition_X(getPosition_X()-2); //Τότε μετακίνησε κατα 2 θέσεις αριστερά τον παίχτη
                    else if (0 > this->getPosition_X()-2)   //Έλεγχος αν η μετακίνηση οδηγήσει σε αρνητικές τιμές του άξονα Χ
                        this->setPosition_X(getPosition_X()+2); //Τότε μετακίνησε κατα 2 θέσεις δεξιά τον παίχτη
                    //Αν δεν προκύπτει εκτός ορίων η μετακίνηση, τότε απομάκρυνση από τον κοντινότερο αντίπαλο
                    else if (sqrt(pow(this->getPosition_X()+2-min_distance_X,2)+pow(this->getPosition_Y()-min_distance_Y,2)) < (sqrt(pow(this->getPosition_X()-2-min_distance_X,2)+pow(this->getPosition_Y()-min_distance_Y,2))))
                        this->setPosition_X(getPosition_X()-2);
                    else
                        this->setPosition_X(getPosition_X()+2);
                }
                else
                {
                    list<Player*>::iterator p = List_Object_Team1.begin();
                    while(p != List_Object_Team1.end()) //Αναζήτηση για τον κοντινότερο αντίπαλο στην ομάδα Α
                    {
                        if (sqrt(pow((*p)->getPosition_X()-this->getPosition_X(),2)+pow((*p)->getPosition_Y()-this->getPosition_Y(),2)) < min_distance)      //Σύγκριση των αποστάσεων
                        {
                            min_distance = sqrt(pow((*p)->getPosition_X()-this->getPosition_X(),2)+pow((*p)->getPosition_Y()-this->getPosition_Y(),2)); //Ορισμός της νέας ελάχιστης απόστασης
                            min_distance_X =(*p)->getPosition_X();
                            min_distance_Y =(*p)->getPosition_Y();
                        }
                        p++;
                    }
                    if (this->getPosition_X()+2 > map_->getPosition_X())    //Έλεγχος αν η μετακίνηση υπερβαίνει τις τιμές του άξονα Χ
                        this->setPosition_X(getPosition_X()-2); //Τότε μετακίνησε κατα 2 θέσεις αριστερά τον παίχτη
                    else if (0 > this->getPosition_X()-2)   //Έλεγχος αν η μετακίνηση οδηγήσει σε αρνητικές τιμές του άξονα Χ
                        this->setPosition_X(getPosition_X()+2); //Τότε μετακίνησε κατα 2 θέσεις δεξιά τον παίχτη
                    //Αν δεν προκύπτει εκτός ορίων η μετακίνηση, τότε απομάκρυνση από τον κοντινότερο αντίπαλο
                    else if (sqrt(pow(this->getPosition_X()+2-min_distance_X,2)+pow(this->getPosition_Y()-min_distance_Y,2)) < (sqrt(pow(this->getPosition_X()-2-min_distance_X,2)+pow(this->getPosition_Y()-min_distance_Y,2))))
                        this->setPosition_X(getPosition_X()-2);
                    else
                        this->setPosition_X(getPosition_X()+2);
                }
            }
        }
    }
    //Υπερκάλυψη της μεθόδου μεταβίβασης της μπάλας ώστε με μεγαλύτερη πιθανότητα να στέλνεται η μπάλα σε θέσεις που βρίσκονται στην κεντρική στήλη
    void transfer(Player* Current_Player, Ball* ball, list<Player*> &List_Object_Team1, list<Player*> &List_Object_Team2, Map* map_)
    {
        if (Current_Player != NULL) //Έλεγχος αν υπάρχει τρέχων παίχτης
        {
            if (this->getName() == Current_Player->getName())   //Έλεγχος αν το στιγμιότυπο αυτό είναι ο τρέχων παίχτης
            {
                ball->setBall_Position_Y(this->getAim_Line());  //Ορισμός της θέσης Υ της μπάλας ίση με τη γραμμή στόχου του μέσου
                int prob_of_Position_X = rand()%101;    //Τυχαία πιθανότητα να σταλεί η μπάλα σε θέσεις της κεντρικής στήλης
                if (prob_of_Position_X <= 75)
                    ball->setBall_Position_X(rand()%2+(map_->getPosition_X()/2));   //Ορισμός της μπάλας τυχαία σε θέσεις της κεντρικής στήλης
                else
                    ball->setBall_Position_X(rand()%(map_->getPosition_X()+1));     //Ορισμός της μπάλας τυχαία σε οποιαδήποτε στήλη
                ball->setCurrent_Player(List_Object_Team1, List_Object_Team2);      //Ορισμός του νέου τρέχων παίχτη
            }
        }
    }
};

class Striker: public Forward   //Υποκλάση Εκτελεστής-Επιθετικός
{
public:
    Striker(string Name_,int Position_X_, int Position_Y_, int Jersey_Number_, int Movement_Line_, int Aim_Line_) : Forward(Name_, Position_X_, Position_Y_, Jersey_Number_, Movement_Line_, Aim_Line_)
    {
    }
    //Υπερκάλυψη της μεθόδου μεταβίβασης της μπάλας ώστε με μεγαλύτερη πιθανότητα να στέλνεται η μπάλα σε θέσεις που βρίσκονται στην κεντρική στήλη
    void transfer(Player* Current_Player, Ball* ball, list<Player*> &List_Object_Team1, list<Player*> &List_Object_Team2, Map* map_)
    {
        if (Current_Player != NULL) //Έλεγχος αν υπάρχει τρέχων παίχτης
        {
            if (this->getName() == Current_Player->getName())   //Έλεγχος αν το στιγμιότυπο αυτό είναι ο τρέχων παίχτης
            {
                ball->setBall_Position_Y(this->getAim_Line());  //Ορισμός της θέσης Υ της μπάλας ίση με τη γραμμή στόχου του μέσου
                int prob_of_Position_X = rand()%101;    //Τυχαία πιθανότητα να σταλεί η μπάλα σε θέσεις της κεντρικής στήλης
                if (prob_of_Position_X <= 95)
                    ball->setBall_Position_X(rand()%2+(map_->getPosition_X()/2));   //Ορισμός της μπάλας τυχαία σε θέσεις της κεντρικής στήλης
                else
                    ball->setBall_Position_X(rand()%(map_->getPosition_X()+1));     //Ορισμός της μπάλας τυχαία σε οποιαδήποτε στήλη
                ball->setCurrent_Player(List_Object_Team1, List_Object_Team2);      //Ορισμός του νέου τρέχων παίχτη
            }
        }
    }
};
//Μέθοδος μεταβίβασης της μπάλας σε μια τυχαία στήλη της γραμμής στόχου, εφόσον ο παίχτης έχει την μπάλα
void Player ::  transfer(Player* Current_Player, Ball* ball_, list<Player*> &List_Object_Team1, list<Player*> &List_Object_Team2, Map* map_)
{
    if (Current_Player != NULL) //Έλεγχος αν υπάρχει τρέχων παίχτης
    {
        if (this->getName() == Current_Player->getName())   //Έλεγχος αν το στιγμιότυπο αυτό είναι ο τρέχων παίχτης
        {
            ball_->setBall_Position_Y(this->getAim_Line()); //Ορισμός της θέσης Υ της μπάλας ίση με τη γραμμή στόχου του παίχτη
            ball_->setBall_Position_X(rand()%(map_->getPosition_X()+1)); //Ορισμός της μπάλας τυχαία σε οποιαδήποτε στήλη
            ball_->setCurrent_Player(List_Object_Team1, List_Object_Team2); //Ορισμός του νέου τρέχων παίχτη
        }
    }
}

class Team //Ομάδα ποδοσφαίρου
{
public:
    Team(string Team_Name_) //Ορισμός των χαρακτηριστικών της ομάδας κατά την δημιουργία του αντικειμένου
    {
        setTeam_Name(Team_Name_);
        setMistakes(0);
        setPasses(0);
        setGoals(0);
        setMissed_Goals(0);
    }
    void setTeam_Name(string Team_Name_)    //Ορισμός ονόματος της ομάδας
    {
        Team_Name = Team_Name_;
    }
    void setPlayer_List(Player *Player_)    //Θέσε παίχτες σε μία λίστα της αντίστοιχης ομάδας
    {
        List_Object.push_back(Player_);
    }
    void setMistakes(int Mistakes_)     //Ορισμός λαθών της ομάδας
    {
        Mistakes = Mistakes_;
    }
    void setPasses(int Passes_)     //Ορισμός πασσών της ομάδας
    {
        Passes = Passes_;
    }
    void setGoals(int Goals_)   //Ορισμός των γκολ της ομάδας
    {
        Goals = Goals_;
    }
    void setMissed_Goals(int Missed_Goals_) //Ορισμός των χαμένων γκολ της ομάδας
    {
        Missed_Goals = Missed_Goals_;
    }
    string getTeam_Name()   //Λήψη ονόματος της ομάδας
    {
        return Team_Name;
    }
    list<Player*> getPlayer_List()  //ήψη της λίστας των παιχτών της ομάδας
    {
        return List_Object;
    }
    int getMistakes()   //Λήψη των λαθών της ομάδας
    {
        return Mistakes;
    }
    int getPasses()     //Λήψη των πασσών της ομάδας
    {
        return Passes;
    }
    int getGoals()  //Λήψη των γκολ της ομάδας
    {
        return Goals;
    }
    int getMissed_Goals()   //Λήψη των χαμένων γκολ της ομάδας
    {
        return Missed_Goals;
    }
    //Μέθοδος που διατρέχει τους παίχτες της ομάδας και για τον καθένα εκτελεί με τυχαίο τρόπο τις αντίστοιχες μεθόδους του
    int action(list<Player*> &List_Object_Team1, list<Player*> &List_Object_Team2, Player* Current_Player, Player* Ex_Player, Ball* ball, Team* Team1, Team* Team2, Map* map_, int flag)
    {
        int counter1 = 0, counter2 = 0; //Μετρητές των παιχτών της ομάδας
        if (flag == 0)  //Έλεγχος για ποια ομάδα παιχτών θα εκτελεστούν οι αντίστοιχοι μέθοδοι
        {
            counter1=list_elements(List_Object_Team1);  //Μετρητής παιχτών της ομάδας Α
            list<Player*>::iterator p = List_Object_Team1.begin();
            while(p != List_Object_Team1.end()) //Εκτέλεση των μεθόδων για την ομάδα Α
            {
                int prob_action = rand()%101;   //Τυχαία πιθανότητα εκτέλεσης μεθόδου
                if (prob_action < 35)   //35% πιθανότητα εκτέλεσης της μεθόδου κίνησης
                {
                    (*p)->movement(map_);   //Κλήση μεθόδου κίνησης
                    ball->assignment((*p), List_Object_Team1, List_Object_Team2, Team1, Team2); //Κλήση της μεθόδου ανάθεσης ώστε αν μπορεί ο παίχτης να πάρει την μπάλα στην κατοχή του
                   // cout<<"I AM "<<(*p)->getName()<<" AND CALLED MOVEMENT"<<endl;
                }
                else if (prob_action < 70)  //35% πιθανότητα εκτέλεσης της μεθόδου μεταφοράς
                {
                    (*p)->transfer(Current_Player, ball, List_Object_Team1, List_Object_Team2, map_);   //Κλήση μεθόδου μεταφοράς
                    ball->assignment((*p), List_Object_Team1, List_Object_Team2, Team1, Team2); //Κλήση της μεθόδου ανάθεσης ώστε αν μπορεί ο παίχτης να πάρει την μπάλα στην κατοχή του
                    //cout<<"I AM "<<(*p)->getName()<<" AND CALLED TRANSFER"<<endl;
                }
                else
                {
                    (*p)->special_Movement(ball, Current_Player, List_Object_Team1, List_Object_Team2, map_);   //Κλήση μεθόδου ειδικής κίνησης
                    ball->assignment((*p), List_Object_Team1, List_Object_Team2, Team1, Team2); //Κλήση της μεθόδου ανάθεσης ώστε αν μπορεί ο παίχτης να πάρει την μπάλα στην κατοχή του
                    counter2 = list_elements(List_Object_Team1);  //Μετρητής της ομάδας Α, μετά την εκτέλεση της μεθόδου ειδικής κίνησης
                    if (counter2 < counter1) break; //Έλεγχος αν κάποιος παίχτης αφαιρέθηκε από την προσομοίωση
                    if (counter2 == 0)  //Έλεγχος αν η ομάδα Α έμεινε χωρίς παίχτες
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
            counter1 = list_elements(List_Object_Team2);    //Μετρητής παιχτών της ομάδας Β
            list<Player*>::iterator p = List_Object_Team2.begin();
            while(p != List_Object_Team2.end()) //Εκτέλεση των μεθόδων για την ομάδα Β
            {
                int prob_action = rand()%101;   //Τυχαία πιθανότητα εκτέλεσης μεθόδου
                if (prob_action < 35)   //35% πιθανότητα εκτέλεσης της μεθόδου κίνησης
                {
                    (*p)->movement(map_);   //Κλήση μεθόδου κίνησης
                    ball->assignment((*p), List_Object_Team1, List_Object_Team2, Team1, Team2); //Κλήση της μεθόδου ανάθεσης ώστε αν μπορεί ο παίχτης να πάρει την μπάλα στην κατοχή του
                    //cout<<"I AM "<<(*p)->getName()<<" AND CALLED MOVEMENT"<<endl;
                }
                else if (prob_action < 70)  //35% πιθανότητα εκτέλεσης της μεθόδου μεταφοράς
                {
                    (*p)->transfer(Current_Player, ball, List_Object_Team1, List_Object_Team2,map_);    //Κλήση μεθόδου μεταφοράς
                    ball->assignment((*p), List_Object_Team1, List_Object_Team2, Team1, Team2); //Κλήση της μεθόδου ανάθεσης ώστε αν μπορεί ο παίχτης να πάρει την μπάλα στην κατοχή του
                   // cout<<"I AM "<<(*p)->getName()<<" AND CALLED TRANSFER"<<endl;
                }
                else
                {
                    (*p)->special_Movement(ball, Current_Player, List_Object_Team1, List_Object_Team2, map_);   //Κλήση μεθόδου ειδικής κίνησης
                    ball->assignment((*p), List_Object_Team1, List_Object_Team2, Team1, Team2); //Κλήση της μεθόδου ανάθεσης ώστε αν μπορεί ο παίχτης να πάρει την μπάλα στην κατοχή του
                    counter2 = list_elements(List_Object_Team2);   //Μετρητής της ομάδας Β, μετά την εκτέλεση της μεθόδου ειδικής κίνησης
                    if (counter2 < counter1) break; //Έλεγχος αν κάποιος παίχτης αφαιρέθηκε από την προσομοίωση
                    if (counter2 == 0)  //Έλεγχος αν η ομάδα Α έμεινε χωρίς παίχτες
                    {
                        throw "No more players left for Team B!";   //Throw exception
                    }
                    //cout<<"I AM "<<(*p)->getName()<<" AND CALLED SPECIAL_MOV"<<endl;
                }
                p++;
            }
        }
    }
    //Μέθοδος μέτρησης των αντικειμένων που περιέχει μία λίστα
    int list_elements(list<Player*> &List_Object_Team)
    {
        list<Player*>::iterator p = List_Object_Team.begin();
        int counter = 0;    //Αρχικοποίηση του μετρητή
        while(p != List_Object_Team.end())
        {
            counter++;  //Αύξηση κατά ένα για κάθε αντικείμενο που προσπερνά στη λίστα
            p++;
        }
        return counter;
    }
    //Υπερφόρτωση του τελεστή <<
    friend ostream &operator<<(ostream&, const Team &);
private:
    string Team_Name;
    int Mistakes, Passes, Goals, Missed_Goals;
    list<Player*> List_Object;

};

////Μέθοδος ανάθεσης της μπάλας στον παίχτη που δόθηκε αν βρίσκεται σε κάποια θέση γύρω από την μπάλα
void Ball :: assignment(Player *Player_, list<Player*> &List_Object_Team1, list<Player*> &List_Object_Team2, Team *Team1, Team *Team2)
{
    if (*this && Player_)   //Χρήση του υπερφορτωμένου τελεστή για έλεγχο αν η μπάλα είναι ελεύθερη (Τρέχων παίχτης=NULL) και αν βρίσκεται δίπλα στον αντίστοιχο παίχτη
    {
        this->setBall_Position_X(Player_->getPosition_X()); //Θέσε τη θέση Χ της μπάλας ίση με την θέση Χ του παίχτη
        this->setBall_Position_Y(Player_->getPosition_Y()); //Θέσε τη θέση Υ της μπάλας ίση με την θέση Υ του παίχτη
        this->setCurrent_Player(List_Object_Team1, List_Object_Team2);  //Ορισμός του νέου τρέχων παίχτη
        if (this->getEx_Player()->getTeam_of_Player(List_Object_Team1) == Player_->getTeam_of_Player(List_Object_Team1))    //Έλεγχος αν ο πρώην τρέχων παίχτης και ο νέος τρέχων παίχτης ανήκουν στην ομάδα Α
            Team1->setPasses(Team1->getPasses()+1); //Αύξησε τον αριθμό πασσών της ομάδας Α κατά 1
        else if (this->getEx_Player()->getTeam_of_Player(List_Object_Team2) == Player_->getTeam_of_Player(List_Object_Team2))   //Έλεγχος αν ο πρώην τρέχων παίχτης και ο νέος τρέχων παίχτης ανήκουν στην ομάδα Β
            Team2->setPasses(Team2->getPasses()+1); //Αύξησε τον αριθμό πασσών της ομάδας Β κατά 1
        else    //Αλλιώς η μεταβίβαση είναι ανεπιτυχής
        {
            if (this->getEx_Player()->getTeam_of_Player(List_Object_Team1) == 0)    //'Ελεγχος σε ποια ομάδα ανήκει ο πρώην τρέχων παίχτης
                Team1->setMistakes(Team1->getMistakes()+1); //Αύξησε τον αριθμό λαθών της ομάδας Α κατά 1
            else
                Team2->setMistakes(Team2->getMistakes()+1); //Αύξησε τον αριθμό λαθών της ομάδας Β κατά 1
        }
    }
}
//Υπερφόρτωση τελεστή << για την εμφάνιση στατιστικών της αντίστοιχης ομάδας
ostream &operator<<( ostream &output,  Team *team )
    {
        output  <<"Goals: "<<team->getGoals()<<endl //Εμφάνιση του αριθμού των γκολ της ομάδας
                <<"Missed Goals: "<<team->getMissed_Goals()<<endl   //Εμφάνιση του αριθμού των χαμένων γκολ της ομάδας
                <<"Passes: "<<team->getPasses()<<endl   //Εμφάνιση του αριθμού των πασσών της ομάδας
                <<"Mistakes: "<<team->getMistakes()<<endl;  //Εμφάνιση του αριθμού των λαθών της ομάδας
       return output;

    }

class Game  //Παιχνίδι
{
public:
    friend ostream &operator<<( ostream&, const Team & );   //Υπερφόρτωση τελεστή << για την εμφάνιση στατιστικών της αντίστοιχης ομάδας
    Game(list<Player*> &List_Object_Team1, list<Player*> &List_Object_Team2, Player* Current_Player, Player* Ex_Player, Ball* ball) //Ορισμός των χαρακτηριστικών του παιχνιδιού κατά την δημιουργία του αντικειμένου
    {
        setRounds(0);
    }
    void setRounds(int rounds_)  //Ορισμός του αριθμού των γύρων του παιχνιδιού
    {
        rounds = rounds_;
    }
    int getRounds() //Λήψη του αριθμού των γύρων του παιχνιδιού
    {
        return rounds;
    }
    //Μέθοδος runTurn η οποία τρέχει την action για κάθε μία από τις ομάδες με τυχαία σειρά
    void runTurn(list<Player*> &List_Object_Team1, list<Player*> &List_Object_Team2, Team* Team1, Team* Team2, Player* Current_Player, Player* Ex_Player, Ball* ball, Map* map_)
    {
        int prob_team_action=rand()%101;    //Τυχαία πιθανότητα επιλογής ομάδας
        if (prob_team_action < 50)  //50% πιθανότητα επιλογής της ομάδας Α
        {
            Team1->action(List_Object_Team1, List_Object_Team2, Current_Player, Ex_Player, ball, Team1, Team2, map_, 0);    //Εκτέλεση της action πρώτα για την ομάδα Α
            Team2->action(List_Object_Team1, List_Object_Team2, Current_Player, Ex_Player, ball, Team1, Team2, map_, 1);    //Εκτέλεση της action για την ομάδα Β
        }
        else    //50% πιθανότητα επιλογής της ομάδας Β
        {
            Team2->action(List_Object_Team1, List_Object_Team2, Current_Player, Ex_Player, ball, Team1, Team2, map_, 1);    //Εκτέλεση της action πρώτα για την ομάδα Β
            Team1->action(List_Object_Team1, List_Object_Team2, Current_Player, Ex_Player, ball, Team1, Team2, map_, 0);    //Εκτέλεση της action για την ομάδα Α
        }
        this->setRounds(getRounds()+1); //Αύξησε του γύρους του παιχνιδιού κατά 1
        //Έλεγχος αν η θέση της μπάλας βρίσκεται στις κεντρικές πάνω στήλες του χάρτη, ώστε πιθανώς να σημειωθεί γκολ για την ομάδα Β
        if   ((ball->getBall_Position_X()==map_->getPosition_X()/2&&ball->getBall_Position_Y()==0) || (ball->getBall_Position_X()==map_->getPosition_X()/2+1&&ball->getBall_Position_Y()==0))
        {
            int prob_goal = rand()%101; //Τυχαία πιθανότητα να σημειωθεί γκολ
            if (prob_goal < 50) //50% πιθανότητα να σημειωθεί γκολ
            {
                Team2->setGoals(Team2->getGoals()+1);   //Αύξησε τα γκολ της ομάδας Β κατά 1
                ball->setBall_Position_X(map_->getPosition_X()/2);  //Θέσε τη θεση Χ της μπάλας στην αρχική της θέση
                ball->setBall_Position_Y(map_->getPosition_Y()/2);  //Θέσε τη θεση Υ της μπάλας στην αρχική της θέση
            }
            else    //Δεν σημειώθηκε γκολ
                Team2->setMissed_Goals(Team2->getMissed_Goals()+1); //Αύξησε τον αριθμό των χαμένων γκολ κατά 1
        }
        //Έλεγχος αν η θέση της μπάλας βρίσκεται στις κεντρικές κάτω στήλες του χάρτη, ώστε πιθανώς να σημειωθεί γκολ για την ομάδα Α
        else if ((ball->getBall_Position_X()==map_->getPosition_X()/2 && ball->getBall_Position_Y()==map_->getPosition_Y())||(ball->getBall_Position_X()==map_->getPosition_X()/2+1 && ball->getBall_Position_Y()==map_->getPosition_Y()))
        {
            int prob_goal = rand()%101; //Τυχαία πιθανότητα να σημειωθεί γκολ
            if (prob_goal < 50) //50% πιθανότητα να σημειωθεί γκολ
            {
                Team1->setGoals(Team1->getGoals()+1);   //Αύξησε τα γκολ της ομάδας Β κατά 1
                ball->setBall_Position_X(map_->getPosition_X()/2);  //Θέσε τη θεση Χ της μπάλας στην αρχική της θέση
                ball->setBall_Position_Y(map_->getPosition_Y()/2);  //Θέσε τη θεση Υ της μπάλας στην αρχική της θέση
            }
            else    //Δεν σημειώθηκε γκολ
                 Team1->setMissed_Goals(Team1->getMissed_Goals()+1);    //Αύξησε τον αριθμό των χαμένων γκολ κατά 1
        }
        else    //Η μπάλα δεν βρίσκεται στις κεντρικές στήλες
        {
            ball->assignment(List_Object_Team1, List_Object_Team2, Team1, Team2, map_); //Ανάθεση της μπάλας στον κοντινότερο παίχτη
        }
    }
    //Μέθοδος απλής αναπαράστασης του χάρτη προσομοιώσης με χρήση χαρακτήρων
    void map_visualisation(list<Player*> &List_Object_Team1, list<Player*> &List_Object_Team2, Ball* ball, Map* map_)
    {
        cout<<"Map Visualisation:"<<endl;
        int map[map_->getPosition_X()+2][map_->getPosition_Y()+2];  //Δημιουργία δισδιάστατου πίνακα για την εμφάνιση του χάρτη
        for (int j=0; j < map_->getPosition_Y()+2; j++) //Αρχικοποίηση του πίνακα με κενούς χαρακτήρες σε κάθε κελί
        {
            for (int i=0; i < map_->getPosition_X()+2; i++)
            {
                map[i][j]=' ';
            }
        }
        for (int i=0; i < map_->getPosition_X()+1; i++) //Ορισμός των συντεταγμένων Χ του χάρτη
            map[i+1][0] = i;
        for (int i=0; i < map_->getPosition_Y()+1; i++) //Ορισμός των συντεταγμένων Υ του χάρτη
            map[0][i+1] = i;
        list<Player*>::iterator p = List_Object_Team1.begin();
        while(p != List_Object_Team1.end()) //Ορισμός των παιχτών της ομάδας Α με το σύμβολο #
        {
            map[(*p)->getPosition_X()+1][(*p)->getPosition_Y()+1] = '#';
            p++;
        }
        p = List_Object_Team2.begin();
        while(p != List_Object_Team2.end()) //Ορισμός των παιχτών της ομάδας Α με το σύμβολο $
        {
            map[(*p)->getPosition_X()+1][(*p)->getPosition_Y()+1] = '$';
            p++;
        }
        map[ball->getBall_Position_X()+1][ball->getBall_Position_Y()+1] = '@';  //Ορισμός της μπάλας με το σύμβολο @
        cout<<" ";
        for (int j=0; j < map_->getPosition_Y()+2; j++)     //Εμφάνιση του χάρτη, μέσω του διαδιάστατου πίνακα
        {
            for (int i=0; i < map_->getPosition_X()+2; i++)
            {
                if(!(i==0 && j==0)) //Εκτύπωση όλων εκτός του σημείου (0,0)
                {
                    if(i!=0)    //Εμφάνιση ενός κενού μεταξύ των στηλών
                        cout<<" ";
                    if (i==0 || j==0)
                        printf("%d", map[i][j]);    //Εμφάνιση των συντεταγμένων του χάρτη
                    else
                        printf("%c", map[i][j]);    //Εμφάνιση των ειδικών χαρακτήρων των αντικείμενων πάνω στο χάρτη
                }
            }
            cout<<endl;
        }
        cout<<endl;
    }
    //Μέθοδος εμφάνισης γενικών πληροφοριών και στατιστικών του αγώνα
    void general_info()
    {
        cout<<"General Info:"<<endl;
        cout<<"Steals: "<<Defender::Steals+Midfielder::Steals<<endl;    //Εμφάνιση του συνολικού αριθμού κλεψιμάτων
        cout<<"Rounds: "<<this->getRounds()<<endl;  //Εμφάνιση του αριθμού των γύρων του παιχνιδιού
        cout<<endl;
    }
    //Μέθοδος εμφάνισης στατιστικών της κάθε ομάδας
    void team_statistics(Team* Team1, Team* Team2)
    {
        cout<<"Team 1 Statistics:"<<endl;
        cout<<Team1;    //Χρήση του υπερφορτωμένου τελεστή για την ομάδα Α <<
        cout<<"Red Cards: "<<Player::Red_Cards_Team1<<endl; //Εμφάνιση του αριθμού των κόκκινων καρτών της ομάδας Α
        cout<<"Team 2 Statistics:"<<endl;
        cout<<Team2;    //Χρήση του υπερφορτωμένου τελεστή για την ομάδα Β <<
        cout<<"Red Cards: "<<Player::Red_Cards_Team2<<endl; //Εμφάνιση του αριθμού των κόκκινων καρτών της ομάδας Β
        cout<<endl;
    }
    //Μέθοδος εμφάνισης των στατιστικών των παιχτών της κάθε ομάδας και τα στοιχεία τους
    void player_info(list<Player*> &List_Object_Team1, list<Player*> &List_Object_Team2)
    {
        bool Yellow_Card;   //Αν έχει κίτρινη κάρτα ο αντίστοιχος παίχτης
        cout<<"Team 1 Players: "<<endl;
        cout<<"Pos_X Pos_Y Move_Line Aim_Line Jersey_Num Yellow_Card Name    "<<endl;
        list<Player*>::iterator p = List_Object_Team1.begin();
        while(p != List_Object_Team1.end()) //Εμφάνιση των στοιχείων για τους παίχτες της ομάδας Α
        {
            if (dynamic_cast<Defender*>(*p)==NULL && dynamic_cast<Midfielder*>(*p)==NULL) //Έλεγχος αν ο παίχτης δεν είναι ούτε αμυντικός ούτε μέσος
                Yellow_Card = 0;    //Αν δεν είναι τότε δεν έχει σίγουρα κίτρινη κάρτα
            else if(dynamic_cast<Midfielder*>(*p) == NULL)   //Αν ισχύει τότε ο παίχτης θα ναι αμυντικός
                Yellow_Card = dynamic_cast<Defender*>(*p)->getYellow_Card();    //Λήψη του αριθμού κίτρινων καρτών του αμυντικού
            else    //Αλλιώς θα ναι μέσος
                Yellow_Card = dynamic_cast<Midfielder*>(*p)->getYellow_Card();  //Λήψη του αριθμού κίτρινων καρτών του μέσου
            //Εμφάνιση των στατιστικών και στοιχείων των παιχτών της ομάδας Α
            cout<<"  "<<(*p)->getPosition_X()<<"     "<<(*p)->getPosition_Y()<<"       "<<(*p)->getMovement_Line()<<"        "<<(*p)->getAim_Line()<<"         "<<(*p)->getJersey_Number()<<"           "<<Yellow_Card<<"      "<<(*p)->getName()<<endl;
            p++;
        }
        cout<<"Team 2 Players: "<<endl;
        cout<<"Pos_X Pos_Y Move_Line Aim_Line Jersey_Num Yellow_Card Name    "<<endl;
        p = List_Object_Team2.begin();
        while(p != List_Object_Team2.end()) //Εμφάνιση των στοιχείων για τους παίχτες της ομάδας Β
        {
            if (dynamic_cast<Defender*>(*p)==NULL && dynamic_cast<Midfielder*>(*p)==NULL) //Έλεγχος αν ο παίχτης δεν είναι ούτε αμυντικός ούτε μέσος
                Yellow_Card = 0;    //Αν δεν είναι τότε δεν έχει σίγουρα κίτρινη κάρτα
            else if (dynamic_cast<Midfielder*>(*p) == NULL)  //Αν ισχύει τότε ο παίχτης θα ναι αμυντικός
                Yellow_Card = dynamic_cast<Defender*>(*p)->getYellow_Card();    //Λήψη του αριθμού κίτρινων καρτών του αμυντικού
            else    //Αλλιώς θα ναι μέσος
                Yellow_Card = dynamic_cast<Midfielder*>(*p)->getYellow_Card();  //Λήψη του αριθμού κίτρινων καρτών του μέσου
            //Εμφάνιση των στατιστικών και στοιχείων των παιχτών της ομάδας Β
            cout<<"  "<<(*p)->getPosition_X()<<"     "<<(*p)->getPosition_Y()<<"       "<<(*p)->getMovement_Line()<<"        "<<(*p)->getAim_Line()<<"         "<<(*p)->getJersey_Number()<<"           "<<Yellow_Card<<"      "<<(*p)->getName()<<endl;
            p++;
        }
    }
private:
    int rounds;
};

class Data  //Δεδομένα εισόδου
{
public:
    Data()  //Default constructor
    {
    }
    void setList_Object_Team1(list<Player*> List_Object_Team1_) //Ορισμός της λίστας παιχτών της ομάδας Α
    {
        List_Object_Team1 = List_Object_Team1_;
    }
    void setList_Object_Team2(list<Player*> List_Object_Team2_) //Ορισμός της λίστας παιχτών της ομάδας Α
    {
        List_Object_Team2 = List_Object_Team2_;
    }
    void setTeam_A(Team* team_A_)   //Ορισμός της ομάδας Α
    {
        team_A = team_A_;
    }
    void setTeam_B(Team* team_B_)   //Ορισμός της ομάδας Β
    {
        team_B = team_B_;
    }
    list<Player*> &getList_Object_Team1()   //Λήψη της λίστας παιχτών της ομάδας Α
    {
        return List_Object_Team1;
    }
    list<Player*> &getList_Object_Team2()   //Λήψη της λίστας παιχτών της ομάδας Β
    {
        return List_Object_Team2;
    }
    Team* getTeam_A()   //Λήψη της ομάδας Α
    {
        return team_A;
    }
    Team* getTeam_B()   //Λήψη της ομάδας Β
    {
        return team_B;
    }
    int data_initialization(Map *map_)  //Μέθοδος εισαγωγής των δεδομένων μέσω αρχείου
    {
        ifstream input("data.txt"); //Εισαγωγή δεδομένων μέσω του αρχείου data.txt που βρίσκεται στο ίδιο path με το εκτελέσιμο
        if(!input.is_open())    //Έμεσος έλεγχος για τον έλεγχο ύπαρξης του αρχείου
        {
            cout<<"Please create the input data file named as 'data.txt'"<<endl;
            return 0;   //Τερματισμός του προγράμματος
        }
        int team_Counter = 0;   //Μετρητής αριθμού των ομάδων που χουν δημιουργηθεί
        string team_Names[2];   //Πίνακας αποθήκευσης των ονομάτων των ομάδων
        Team *team_A, *team_B;  //Αντικείμενα ομάδας Α και Β
        string team_Name, player_Type, player_Name; int pos_X, pos_Y, jersey_Num, movement_Line, aim_Line;  //Χαρακτηριστικά παιχτών
        while (input >> team_Name >> player_Type >> player_Name >> pos_X >> pos_Y >> jersey_Num >> movement_Line >> aim_Line)
        {
            //Έλεγχος ώστε οι εισαγόμενες τιμές να βρίσκονται μέσα στα όρια του χάρτη
            if (pos_X > map_->getPosition_X() || pos_Y > map_->getPosition_Y() || movement_Line > map_->getPosition_Y() || aim_Line > map_->getPosition_Y()
                || pos_X < 0 || pos_Y < 0 || movement_Line < 0 || aim_Line < 0)
            {
                cout<<"Player's values exceed the map dimensions!"<<endl;
                return 0;   //Τερματισμός του προγράμματος
            }
            if (pos_Y != movement_Line) //Η θέση Υ του παίχτη καθώς και η γραμμή κίνησής του πρέπει να ταυτίζονται
            {
                cout<<"Player's position_Y must be same as his movement line!"<<endl;
                return 0;   //Τερματισμός του προγράμματος
            }

            if (team_Counter == 0)  //Έλεγχος αν δεν έχει δημιουργηθεί καμία ομάδα
            {
                team_A = new Team(team_Name);   //Τότε επιτρέπεται η δημιουργία μιας
                team_Names[0] = team_Name;
                team_Counter = 1;   //Αύξηση του μετρητή κατά 1, εφόσον δημιουργήθηκε μία ομάδα
            }
            else if(team_Counter == 1 && team_Names[0]!=team_Name)  //Έλεγχος αν η δεύτερη ομάδα που θα δημιουργηθεί δεν ταυτίζεται με την πρώτη
            {
                team_B = new Team(team_Name);   //Τότε επιτρέπεται η δημιουργία δεύτερης ομάδας
                team_Names[1] = team_Name;
                team_Counter = 2;   //Αύξηση του μετρητή κατά 1, εφόσον δημιουργήθηκε μία ακόμη ομάδα
            }
            if (team_Counter==2 && team_Names[0]!=team_Name && team_Names[1]!=team_Name)    //Έλεγχος αν δημιουργηθούν παραπάνω από 2 ομάδες
            {
                cout<< "Error! Maximum number of teams reached!" <<endl;
                return 0;   //Τερματισμός του προγράμματος
            }
            if(team_Names[0] == team_Name)  //Ορισμός των χαρακτηριστικών των παιχτών της ομάδας Α
            {
                //Έλεγχος του τύπου του παίχτη που θα δημιουργηθεί
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
                    return 0;   //Τερματισμός του προγράμματος
                }
            }
            else if(team_Names[1] == team_Name) //Ορισμός των χαρακτηριστικών των παιχτών της ομάδας Β
            {
                //Έλεγχος του τύπου του παίχτη που θα δημιουργηθεί
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
                    return 0;   //Τερματισμός του προγράμματος
                }
            }
        }
        list<Player*> List_Object_Team1 = team_A->getPlayer_List(); //Λήψη της λίστας των παιχτών της ομάδας Α
        list<Player*> List_Object_Team2 = team_B->getPlayer_List(); //Λήψη της λίστας των παιχτών της ομάδας Β
        //Έλεγχος ώστε να επιτρέπεται μόνο ένας παίχτης σε κάθε γραμμή
        if (player_List_Validation(List_Object_Team1, List_Object_Team2)==0 || player_List_Validation(List_Object_Team2, List_Object_Team1)==0)
            return 0;   //Τερματισμός του προγράμματος
        this->setList_Object_Team1(List_Object_Team1);  //Ορισμός της λίστας παιχτών της ομάδας Α
        this->setList_Object_Team2(List_Object_Team2);  //Ορισμός της λίστας παιχτών της ομάδας Β
        this->setTeam_A(team_A);    //Ορισμός της ομάδας Α
        this->setTeam_B(team_B);    //Ορισμός της ομάδας Β
    }
    //Μέθοδος ελέγχου εγκυρότητας των παιχτών, ώστε να επιτρέπεται μόνο ένας παίχτης σε κάθε γραμμή
    int player_List_Validation(list<Player*> List_Object_Team1, list<Player*> List_Object_Team2)
    {
        int Movement_Line;  //Γραμμή κίνσης
        list<Player*>::iterator p1 = List_Object_Team1.begin();
        while(p1 != List_Object_Team1.end())    //Έλεγχος για κάθε παίχτη της ομάδας Α, αν ταυτίζεται η γραμμή κίνησής του με κάποιον άλλον παίχτη
        {
            Movement_Line = (*p1)->getMovement_Line();
            int counter = 0;    //Μετρητής των παιχτών που έχουν την ίδια γραμμή κίνησης με τον αντίστοιχο παίχτη
            list<Player*>::iterator p2 = List_Object_Team1.begin();
            while(p2 != List_Object_Team1.end())    //Έλεγχος αρχικά με όλους τους παίχτες της ομάδας Α
            {
                if (Movement_Line == (*p2)->getMovement_Line()) //Έλεγχος αν ταυτίζονται οι γραμμές κίνησής τους
                    counter++;  //Τότε αύξησε τον μετρητή κατά 1
                p2++;
            }
            list<Player*>::iterator p3 = List_Object_Team2.begin();
            while(p3 != List_Object_Team2.end())    //Έλεγχος στη συνέχεια με όλους τους παίχτες της ομάδας Β
            {
                if (Movement_Line == (*p3)->getMovement_Line()) //Έλεγχος αν ταυτίζονται οι γραμμές κίνησής τους
                    counter++;  //Τότε αύξησε τον μετρητή κατά 1
                p3++;
            }
            if (counter > 1)    //Για να είναι έγκυρο πρέπει ο μετρητής=1, καθώς μετριέται μόνο ο αντίστοιχος παίχτης με τον εαυτό του
            {
                cout<<"Only one player is permitted per line!"<<endl;
                return 0;   //Τερματισμός προγράμματος
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

main()  //Εκτέλεση του παιχνιδιού
{
    int ball_same_position=0;   //Μετρητής για το πόσους γύρους έχει σταθερή θέση η μπάλα
    Map *map_ = new Map(5,8);   //Εισαγωγή των διαστάσεων του χάρτη [0,x] [0,y]
    Data *data = new Data();    //Εισαγωγή των δεδομένων μέσω του αρχείου
    if (data->data_initialization(map_)==0) //Έλεγχος εγκυρότητας των δεδομένων εισόδου
        return 0;   //Τερματισμός προγράμματος
    //Δημιουργία ενός αντικειμένου μπάλας, με αρχικές συντεταγμένες το κέντρο του χάρτη
    Ball *b = new Ball(map_->getPosition_X()/2,map_->getPosition_Y()/2, data->getList_Object_Team1(), data->getList_Object_Team2());
    int ball_Position_X = b->getBall_Position_X();  //Λήψη της τρέχουσας θέσης Χ της μπάλας
    int ball_Position_Y = b->getBall_Position_Y();  //Λήψη της τρέχουσας θέσης Υ της μπάλας
    //Δημιουργία ενός αντικειμένου παιχνιδιού
    Game *game = new Game(data->getList_Object_Team1(), data->getList_Object_Team2(),  b->Current_Player, b->Ex_Player, b);

    int iterations = 0; //Μετρητής του αριμθμού επαναλήψεων
    //Εκτέλεση του προγράμματος μέχρι να σημειωθεί ο απαιτούμενος αριθμός γκολ ή να εκτελεστεί ο αντίστοιχος αριθμός επαναλήψεων
    while (data->getTeam_A()->getGoals()<700 && data->getTeam_B()->getGoals()<700 && iterations<1000)
    {
        //Εκτέλεση των αντίστοιχων μεθόδων της κλάσης παιχνιδιού για την προσομοίωσή του
        game->runTurn(data->getList_Object_Team1(), data->getList_Object_Team2(), data->getTeam_A(), data->getTeam_B(), b->getCurrent_Player(), b->getEx_Player(), b, map_);
        game->map_visualisation(data->getList_Object_Team1(), data->getList_Object_Team2(), b, map_);
        game->general_info();
        game->team_statistics(data->getTeam_A(),data->getTeam_B());
        game->player_info(data->getList_Object_Team1(), data->getList_Object_Team2());
        if (b->getBall_Position_X()== ball_Position_X && b->getBall_Position_Y()==ball_Position_Y)  //Έλεγχος αν παραμένει η μπάλα στην ίδια θέση
            ball_same_position += 1;    //Αύξηση του μετρητή κατά 1
        else
        {
            ball_same_position=0;   //Επαναφορά του μετρητή, καθώς άλλαξε θέση η μπάλα
            ball_Position_X = b->getBall_Position_X();  //Ορισμός της νέας θέσης Χ της μπάλας
            ball_Position_Y = b->getBall_Position_Y();  //Ορισμός της νέας θέσης Υ της μπάλας
        }
        if (ball_same_position == 5)    //Έλεγχος αν βρίσκεται η μπάλα στην ίδια θέση για 5 γύρους
            b->assignment(data->getList_Object_Team1(), data->getList_Object_Team2(), data->getTeam_A(), data->getTeam_B(), map_); //Ανάθεση της μπάλας στον κοντινότερο παίχτη, αν δεν υπάρχει ήδη τρέχων παίχτης

        iterations += 1;    //Αύξηση του μετρητή κατά ένα στο τέλος του κάθε γύρου
    }
    return 0;   //Τερματισμός προγράμματος
}

