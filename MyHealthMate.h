#ifndef MYHEALTHMATE_H
#define MYHEALTHMATE_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "User.h"
#include "DietPlan.h"
#include "WorkoutPlan.h"
#include "ProgressTracker.h"

class MyHealthMate{
    private :
        User users[50];
        DietPlan meals[50];
        WorkoutPlan workouts[50];

        int userCount;
        int mealCount;
        int workoutCount;

    public:
        MyHealthMate();
        void loadFiles();
        void start();
        int findUserWithName(std::string name);
        void userSession(User &user);
        void dietSession(User &user);
        void ChooseDiet(User &user);
        void autoChooseDiet(User &user);
        void viewDietPlan(User &user);
        void showDietMenu();
        int findMealIndex(DietPlan meal);
        void workoutSession(User &user);
        void showWorkoutMenu();
        void chooseWorkout(User &user);
        void viewWorkoutPlan(User &user);
        void progressSession(User &user);
        void compareTwoUsersSession();

        

    
};


#endif