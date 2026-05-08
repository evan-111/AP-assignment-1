#include "WorkoutPlan.h"

WorkoutPlan::WorkoutPlan():activity(""),intensivityLevel(0),caloriesBurnPerMinute(0){}


void WorkoutPlan::setWorkoutPlan(std::string activity, int intensitivityLevel,int caloriesBurnPerMinute){
    this->activity=activity;
    this->intensivityLevel=intensitivityLevel;
    this->caloriesBurnPerMinute=caloriesBurnPerMinute;
}

void WorkoutPlan::displayWorkoutExercises(int index){
    std::cout<<std::left<<std::setw(3)<<index<<". "
             <<std::setw(18)<<activity
             <<" | intensivity level= "<<std::setw(3)<<intensivityLevel
             <<" | "<<std::setw(3)<<caloriesBurnPerMinute<<" calories burn/min"<<std::endl;
}