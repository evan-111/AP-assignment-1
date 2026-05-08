#include "DietPlan.h"

DietPlan::DietPlan():mealType(""),food(""),calories(0){}

void DietPlan::setDietInfo(std::string mealType,std::string food,int calories){
    this->mealType=mealType;
    this->food=food;
    this->calories=calories;
}

void DietPlan::displayDietPlan(int index){
    std::cout<<std::left<<index<<". "
             <<std::setw(12)<<mealType
             <<" | "<<std::setw(25)<<food
             <<" | "<<calories<<" calories"<<std::endl;
}