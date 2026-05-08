#include "ProgressTracker.h"

ProgressTracker::ProgressTracker():previousWeight(0),previousBMI(0),currentWeight(0),currentBMI(0){}

std::string ProgressTracker::getDate() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buf[20];
    sprintf(buf, "%04d-%02d-%02d", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday);
    return std::string(buf);
}

void ProgressTracker::updateProgress(User &user, double newWeight) {
    previousWeight = user.getWeight();
    previousBMI = user.getBMI();

    currentWeight = newWeight;
    currentBMI = newWeight / (user.getHeight() * user.getHeight());

    user.setWeightAndBMI(newWeight);
    std::cout<<std::endl;
    std::cout << "\nProgress updated successfully"<<std::endl;

    std::string filename = "progress"+ user.getName() +".txt";
    std::ofstream file(filename.c_str(), std::ios::app);
    if (file.is_open()) {
        file << getDate() << " "
             << currentWeight << " "
             << currentBMI <<std::endl;
        file.close();
    } else {
        std::cout << "Unable to open progress file."<<std::endl;
    }
}



void ProgressTracker::displayProgress(User &user){
    std::cout << "------------- Progress Report -------------"<<std::endl;
    std::cout << "Previous Weight: " << previousWeight <<std::endl;;
    std::cout << "Current Weight : " << user.getWeight() <<std::endl;
    std::cout << "Previous BMI   : " << previousBMI <<std::endl;
    std::cout << "Current BMI    : " << user.getBMI() <<std::endl;

    double diff=currentWeight-previousWeight;
    if(diff>0)
        std::cout<<"You gained "<<diff<<" kg since last update."<<std::endl;
    else if(diff<0)
        std::cout<<"You lost "<<-diff<<" kg since last update."<<std::endl;
    else
        std::cout << "Your weight remained the same."<<std::endl;

    std::cout << "-------------------------------------------"<<std::endl;

    std::string goal = user.getGoal();
    if (goal == "lose"){
        std::cout << " Stay consistent with calorie control and regular workouts."<<std::endl;
    }
    else if(goal=="gain"){
        std::cout << " Keep increasing intake with balanced meals and strength training."<<std::endl;
    }
    else{
        std::cout<<" Keep maintaining your routine — great balance!"<<std::endl;
    }
}

void ProgressTracker::viewProgressHistory(User &user){
    std::string date;
    double weight, bmi;
    int count = 0;
    double totalWeight = 0, totalBMI = 0;

    std::string filename="progress_"+user.getName()+".txt";
    std::ifstream file(filename.c_str());
    if(!file.is_open()){
        std::cout<<"No progress history found for"<<user.getName()<<"."<<std::endl;
        return;
    }

    std::cout<<"========= " << user.getName() << "'s Progress History ========="<<std::endl;
    std::cout<<std::left<<std::setw(15)<<"Date"
             <<std::setw(12)<<"Weight"
             <<std::setw(10)<<"BMI"<<std::endl;
    std::cout<<std::endl;
    
    while (file >> date >> weight >> bmi) {
        std::cout << std::left
                  << std::setw(15) << date
                  << std::setw(12) << std::fixed << std::setprecision(1) << weight
                  << std::fixed << std::setprecision(2) << bmi <<std::endl;
        totalWeight += weight;
        totalBMI += bmi;
        count++;
    }
    std::cout << "-------------------------------------------"<<std::endl;
    file.close();
}