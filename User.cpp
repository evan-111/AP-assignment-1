#include "User.h"

//i did my contructor like this becuase miss bridget told me a better way which is this
//but for the array i found a way how to initilize it to -1 like this meaning the array is empty the user havent pick diet.
User::User():weight(0),bmi(0),height(0),goal(""),mealCountSelected(0),workoutCountSelected(0),totalBurnedCalories(0.00){
    for(int i = 0; i < 10; i++) {
        selectedMeals[i] = -1; 
        selectedWorkouts[i]=-1;
    }
}

void User::calculateBMI() {
    bmi = weight / (height * height);    
}

void User::setUserInfo(std::string name,int age,char gender,float weight, float height,std::string goal){
    this->name=name;
    this->age=age;
    this->gender=gender;
    this->weight=weight;
    this->height=height;
    this->goal=goal;

    calculateBMI();
}

void User::displayUserInfo(){
    std::string healthyRange;
    
    if(bmi<18.5){
        healthyRange="Underweight";
    }
    else if(bmi>=18.5 && bmi<=24.9){
        healthyRange="Healthy Weight";
    }
    else if(bmi>=25.0 && bmi<=29.9){
        healthyRange="Overweight";
    }
    else{
        healthyRange="Obese";
    }

    std::cout<<"-----------------------"<<std::endl;
    std::cout<<"    User Information   "<<std::endl;
    std::cout<<"-----------------------"<<std::endl;
    std::cout<<"Name: "<<name<<std::endl;
    std::cout<<"Age: "<<age<<std::endl;
    std::cout<<"Gender: "<<gender<<std::endl;
    std::cout<<"weight: "<<weight<<"kg"<<std::endl;
    std::cout<<"height: "<<height<<"m"<<std::endl;
    std::cout<<"BMI: "<<bmi<<"("<<healthyRange<<")"<<std::endl;
    std::cout<<"goal: "<<goal<<std::endl;
    std::cout<<std::endl;    
}

int User::minCalorie(){
    if(gender=='F'){
        return 1200;
    }   
    return 1500;
}

void User::addSelectedMeal(int index) {
    if (mealCountSelected < 10) {
        selectedMeals[mealCountSelected] = index;
        mealCountSelected++;
    }
}

void User::deleteSelectedMeals() {
    mealCountSelected = 0;
    for(int i = 0; i < 10; i++) {
        selectedMeals[i] = -1;
    }
}

int User::getTargetedCalories() {
    if (goal == "lose")  return 1300;  
    if (goal == "maintain") return 2000;
    if (goal == "gain") return 2600;
    return 2000; 
}

int User::maxSafeCaloriesBurned(){
    if(gender=='F'){
        return 400;
    }
    return 500;
}

void User::addSelectedWorkout(int index){
    if (workoutCountSelected<10)
        selectedWorkouts[workoutCountSelected++]=index;
}

void User::deleteSelectedWorkouts(){
    for (int i=0;i<10;i++){
        selectedWorkouts[i]=-1;
    }
    workoutCountSelected=0;
    totalBurnedCalories=0;
    std::cout<<"workout plan deleted"<<std::endl;
}

int User::getSelectedWorkoutIndex(int i){
    if(i>=0 && i< workoutCountSelected)
        return selectedWorkouts[i];
    else
        return -1;
}

void User::setWeightAndBMI(double newWeight){
    weight=newWeight;
    bmi = weight / (height * height);
}

//friend function
void compareUsers( User &user1, User &user2){
    if (user1<user2){
        std::cout<<user1.getName()<<" has a lower BMI than "<<user2.getName()<<std::endl;
    }
    else if(user1>user2){
        std::cout<<user1.getName()<<" has a higher BMI than "<<user2.getName()<<std::endl;
    }
    else{
        std::cout<<"Both have the same BMI."<<std::endl;
    }
}

//operator overloading
bool User::operator>(User &otherUser)const {
    return bmi>otherUser.bmi;
}

bool User::operator<(User &otherUser)const {
    return bmi<otherUser.bmi;
}

bool User::operator==(User &otherUser)const {
    return bmi==otherUser.bmi;
}

