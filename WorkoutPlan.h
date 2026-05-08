#ifndef WORKOUTPLAN_H
#define WORKOUTPLAN_H


#include <iostream>
#include <string>
#include <iomanip>

class WorkoutPlan{
    private:
        std::string activity;
        int intensivityLevel;
        int caloriesBurnPerMinute;

    public:
        WorkoutPlan();
        void setWorkoutPlan(std::string activity, int intensitivityLevel,int caloriesBurnPerMinute);
        void displayWorkoutExercises(int index);
        std::string getActivity(){return activity;}
        int getIntensitivityLevel(){return intensivityLevel;}
        int getCaloriesBurnPerMinute(){return caloriesBurnPerMinute;}
        
};


#endif