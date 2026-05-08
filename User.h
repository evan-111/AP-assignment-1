#ifndef USER_H
#define USER_H
#include "Person.h"
#include <iomanip>

class User : public Person {
    private:
        double weight;
        double height;
        double bmi;
        std::string goal;
        int selectedMeals[10];
        int mealCountSelected;
        int selectedWorkouts[10];
        int workoutCountSelected;
        double totalBurnedCalories;
       
    //i divided some of the fucntion like this , cause i was so confuse which one is which
    public:
        User();
        void setUserInfo(std::string name,int age, char gender, float weight,float height,std::string goal);
        void calculateBMI();
        std::string getName(){return name; }
        double getBMI()const{return bmi;}
        double getWeight()const{return weight;}
        double getHeight()const{return height;}
        std::string getGoal()const{return goal;}

        void displayUserInfo();
        int minCalorie();
        
        void addSelectedMeal(int index);
        int getSelectedMealIndex(int index) { return selectedMeals[index]; }
        int getSelectedMealCount() { return mealCountSelected; }
        void deleteSelectedMeals();
        void viewSelectedMeals();
        int getTargetedCalories();

        int maxSafeCaloriesBurned();
        void addSelectedWorkout(int index);
        void deleteSelectedWorkouts();
        int getSelectedWorkoutCount(){return workoutCountSelected;}
        int getSelectedWorkoutIndex(int index);
        void addCaloriesBurned(double calories){totalBurnedCalories+=calories;}
        double getTotalBurnedCalories(){return totalBurnedCalories;}
        void setWeightAndBMI(double newWeight);

        friend void compareUsers(User &user1,User &user2);
        bool operator>(User &otherUser)const;
        bool operator<(User &otherUser)const;
        bool operator==(User &otherUser)const;
};
#endif