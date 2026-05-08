#ifndef DIERTPLAN_H
#define DIETPLAN_H

#include <iostream>
#include <string>
#include <iomanip>

class DietPlan{
    private:
        std::string mealType;
        std::string food;
        int calories;

    public:
        DietPlan();
        void setDietInfo(std::string mealType, std::string food, int calories);
        void displayDietPlan(int index);
        std::string getMealType(){return mealType;};
        int getCalories(){return calories;};
        std::string getFood(){return food;}
};



#endif