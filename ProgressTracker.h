#ifndef PROGRESSTRACKER_H
#define PROGRESSTRACKER_H

#include "User.h"
#include <ctime>
#include <fstream>

class ProgressTracker{
    private:
        double previousWeight;
        double previousBMI;
        double currentWeight;
        double currentBMI;

    public:
        ProgressTracker();
        void updateProgress(User &user,double newWeight);
        void displayProgress(User &user);
        std::string getDate();
        void viewProgressHistory(User &user);

};

#endif