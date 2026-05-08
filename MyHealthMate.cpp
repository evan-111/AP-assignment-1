#include "MyHealthMate.h"

MyHealthMate::MyHealthMate(): userCount(0),mealCount(0),workoutCount(0){}

void MyHealthMate::loadFiles(){
    std::ifstream userFile("userInfo.txt");
    std::ifstream mealFile("dietPlans.txt");
    std::ifstream workoutFile("workoutPlans.txt");

    std::string text;

    while(getline(userFile,text)){
        std::stringstream ss(text);
        std::string name;
        std::string gender;
        std::string goal;
        int age;
        float weight;
        float height;
        
        ss >> name >> age >> gender >> weight >> height >> goal;

        users[userCount].setUserInfo(name, age, gender[0], weight, height, goal);
        userCount++;
    }

    while(getline(mealFile,text)){
        std::stringstream ss(text);
        std::string mealType;
        std::string food;
        int calories;

        getline(ss,mealType,',');
        getline(ss,food,',');
        ss>>calories;

        meals[mealCount].setDietInfo(mealType,food,calories);   
        mealCount++; 
    }

    while(getline(workoutFile,text)){
        std::stringstream ss(text);
        std::string activity;
        int intensitivityLevel;
        int caloriesBurnPerMinute;

        getline(ss,activity,',');
        ss>>intensitivityLevel;
        ss.ignore(1, ',');
        ss>>caloriesBurnPerMinute;

        workouts[workoutCount].setWorkoutPlan(activity,intensitivityLevel,caloriesBurnPerMinute);
        workoutCount++;
    }

    userFile.close();
    mealFile.close();
    workoutFile.close();

    std::cout<<"files loaded"<<std::endl;
}

int MyHealthMate::findUserWithName(std::string name) {
    for (int i = 0; i < userCount; i++) {
        if (users[i].getName() == name) {
            return i;
        }
    }
    return -1;
}

void MyHealthMate::ChooseDiet(User &user){
    int choice;
    int totalCalories=0;
    int numOfMealTime;

    std::cout<<"please enter the number of meal you want to eat:";
    std::cin>>numOfMealTime;
    std::cout<<std::endl;

    for(int i=0;i<numOfMealTime;i++){
        std::cout<<"please select your meals for your diet plan"<<std::endl;
        std::cout<<"enter meal index based on index of diet plan menu:";
        std::cin>>choice;

        if(choice<0 || choice >=mealCount){
            std::cout<<"invalid index, please try again.";
            i--;
            continue;
        }

        totalCalories+=meals[choice].getCalories();
        user.addSelectedMeal(choice);
        std::cout<<meals[choice].getMealType()<<" is added ";
    }

    std::cout<<" | Total calories= "<<totalCalories<<" kcal"<<std::endl;

    int minCalorie=user.minCalorie();

    if(totalCalories<minCalorie){
        std::cout<<"Your calorie intake is below safe threshold (min calorie ="<<minCalorie<<")"<<std::endl;
        std::cout<<"please add more food to gain balance diet"<<std::endl;
    }
    else if(totalCalories>minCalorie+500){
        std::cout<<"Your calorie intake is above safe threshold (min calorie ="<<minCalorie<<")"<<std::endl;
        std::cout<<"please remove some food to gain balance diet"<<std::endl;
    }
    else{
        std::cout<<"Your calorie intake is in safe threshold"<<std::endl;
    }
}

int MyHealthMate::findMealIndex(DietPlan meal){
    for(int i=0;i<mealCount;i++){
        if(meals[i].getMealType() == meal.getMealType() &&
           meals[i].getFood() == meal.getFood() &&
           meals[i].getCalories() == meal.getCalories())
            return i;
    }
    return 0;
}

void MyHealthMate::autoChooseDiet(User &user){
    int numOfMealTime;
    int totalCalories=0;
    std::cout<<"please enter the number of you want to eat:";
    std::cin>>numOfMealTime;

    DietPlan breakfasts[10], lunches[10], dinners[10], snacks[10];
    int bCount = 0, lCount = 0, dCount = 0, sCount = 0;

    int caloriesNeeded=user.getTargetedCalories();

    DietPlan sortedMeals[50];
    for(int i=0;i<mealCount;i++){
        sortedMeals[i]=meals[i];
    }

    user.deleteSelectedMeals();//to clear the selected meals before

    //at first i was going to use swap for swapping of the sortedMels,
    //then i realise i cannot use STL , god dammit luckily i remember cannot use STL
    //while sorting the depending on goals
    if(user.getGoal()=="lose"){
        for(int i=0;i<mealCount;i++){
            for(int j=1+i;j<mealCount;j++){
                 bool condition;
                 if(user.getGoal() == "lose"){
                    condition = (sortedMeals[j].getCalories() < sortedMeals[i].getCalories());
                 }
                 else{
                    condition = (sortedMeals[j].getCalories() > sortedMeals[i].getCalories());
                 }
                if (condition) {
                    DietPlan temp = meals[i];
                    meals[i] = meals[j];
                    meals[j] = temp;
                }
            }
        }
    }

    /*i addedd a rule saying saying that the automated diet planner must choose  breakfast,lunch and dinner for the if they chose 3 meals
    but the current configuration will get breakfsat with the user input 1 for numofMealsTime and lunch if 2*/
    //and also the current configuration will keep adding snacks if the user chose alot of meals,
    //for example if the user input 5 meals per day the last two meal is snacks.
    for(int i=0;i<mealCount;i++){
    if(sortedMeals[i].getMealType() == "Breakfast") breakfasts[bCount++] = sortedMeals[i];
    else if(sortedMeals[i].getMealType() == "Lunch") lunches[lCount++] = sortedMeals[i];
    else if(sortedMeals[i].getMealType() == "Dinner") dinners[dCount++] = sortedMeals[i];
    else snacks[sCount++] = sortedMeals[i];
    }
    std::cout<<std::endl;
    std::cout<<"--------------------automated diet plan---------------------"<<std::endl;
    
    int mealAdded = 0;

    if(numOfMealTime >= 1 && bCount > 0){
        std::cout<<"Meal 1: "; breakfasts[0].displayDietPlan(0);
        user.addSelectedMeal( findMealIndex(breakfasts[0]) );
        totalCalories += breakfasts[0].getCalories();
        caloriesNeeded -= breakfasts[0].getCalories();
        mealAdded++;
    }

    if(numOfMealTime >= 2 && lCount > 0){
        std::cout<<"Meal 2: "; lunches[0].displayDietPlan(1);
        user.addSelectedMeal( findMealIndex(lunches[0]) );
        totalCalories += lunches[0].getCalories();
        caloriesNeeded -= lunches[0].getCalories();
        mealAdded++;
    }

    if(numOfMealTime >= 3 && dCount > 0){
        std::cout<<"Meal 3: "; dinners[0].displayDietPlan(2);
        user.addSelectedMeal( findMealIndex(dinners[0]) );
        totalCalories += dinners[0].getCalories();
        caloriesNeeded -= dinners[0].getCalories();
        mealAdded++;
    }

    //this is the greedy algorithm i used to auto make the diet depending on goals
    //i added the algorithm to an existing function since the previous want was not working.
    for(int i=mealAdded;i<numOfMealTime;i++){
        int bestIndex=-1;
        int bestDiff=99999;

         for (int j=0;j<mealCount;j++){
            int c=meals[j].getCalories();
            int diff=abs((caloriesNeeded/(numOfMealTime-i))-c);

            if (diff<bestDiff){
                bestDiff=diff;
                bestIndex=j;
            }
        }
        std::cout<<"Meal "<<(i+1)<<": ";
        sortedMeals[bestIndex].displayDietPlan(i);
        user.addSelectedMeal(bestIndex);
        totalCalories+=sortedMeals[i].getCalories();
        caloriesNeeded -= meals[bestIndex].getCalories();
    }

    std::cout<<std::endl;
    std::cout<<"Total calories= "<<totalCalories<<" kcal"<<std::endl;

    int minCalorie=user.minCalorie();

    if(totalCalories<minCalorie){
        std::cout<<"Your calorie intake is below safe threshold (min calorie ="<<minCalorie<<")"<<std::endl;
        std::cout<<"please add more eating session for more meals to allow me to auto plan"<<std::endl;
    }
    else if(totalCalories>minCalorie+500){
        std::cout<<"Your calorie intake is above safe threshold (min calorie ="<<minCalorie<<")"<<std::endl;
        std::cout<<"please remove some eating session for less meal to allow me to auto plan"<<std::endl;
    }
    else{
        std::cout<<"Your calorie intake is in safe threshold"<<std::endl;
    }
    std::cout<<std::endl;
}


void MyHealthMate::viewDietPlan(User &user){
    if(user.getSelectedMealCount()==0){
        std::cout<<"You havent select meals yet"<<std::endl;
    }
    else{
        std::cout<<"selected diet plan:"<<std::endl;
        for(int i=0;i<user.getSelectedMealCount();i++){
            int index=user.getSelectedMealIndex(i);
            meals[index].displayDietPlan(i);
        }
    }
}

//at first i did not think of writing this function, but then i also dont to
//repeat the below code in the diet session menu.
void MyHealthMate::showDietMenu(){
    std::cout<<"-------------------Diet Plan Menu-----------------------";
    std::cout<<std::endl;
    for(int i=0;i<mealCount;i++){
        meals[i].displayDietPlan(i);
    }
    std::cout<<"-------------------------------------------------------";
    std::cout<<std::endl;
}


void MyHealthMate::dietSession(User &user ){
    int choice;
    std::cout<<std::endl;
    std::cout<<"You have entered into the diet session"<<std::endl;
    do{
        std::cout<<"Please enter your choice"<<std::endl;
        std::cout<<"1. view diet menu"<<std::endl;
        std::cout<<"2. edit diet plan"<<std::endl;
        std::cout<<"3. auto generate diet plan"<<std::endl;
        std::cout<<"4. view diet plan"<<std::endl;
        std::cout<<"5. delete diet plan"<<std::endl;
        std::cout<<"6. exit"<<std::endl;
        std::cout<<"please enter choice to continue(1,2,3,4,5,6): ";
        std::cin>>choice;
        std::cout<<std::endl;

        switch(choice){
            case 1:
                showDietMenu();
                break;
            case 2:
                showDietMenu();
                ChooseDiet(user);
                break;
            case 3:
                autoChooseDiet(user);
                break;
            case 4:
                viewDietPlan(user);
                break;
            case 5:
                user.deleteSelectedMeals();
                std::cout<<"diet plan is deleted"<<std::endl;
                break;
            case 6:
                return;
            default:
                std::cout<<"invalid choice, please try again."<<std::endl;
        }
    }while(choice!=6);

}

void MyHealthMate::showWorkoutMenu(){
    std::cout<<"-------------------Diet Plan Menu-----------------------";
    std::cout<<std::endl;
    for(int i=0;i<workoutCount;i++){
        workouts[i].displayWorkoutExercises(i);
    }
    std::cout<<"-------------------------------------------------------";
    std::cout<<std::endl;
}

void MyHealthMate::chooseWorkout(User &user) {
    int choice;
    int numOfWorkoutTime;
    int workoutDuration;
    double caloriesBurned = 0;
    double totalCaloriesBurned = 0;
    double safeCaloriesBurn = user.maxSafeCaloriesBurned();

    std::cout<<"Please enter the amount of workout sessions per day you want: ";
    std::cin>>numOfWorkoutTime;
    std::cout<<std::endl;
    user.deleteSelectedWorkouts();

    for (int i=0;i<numOfWorkoutTime;i++){
        std::cout<<std::endl;
        std::cout<<"Please enter the workout index to choose (0,1,2,...): ";
        std::cin>>choice;
        std::cout<<std::endl;
        if (choice<0 || choice>=workoutCount) {
            std::cout<<"Invalid choice, try again."<<std::endl;
            i--;
            continue;
        }
        std::cout<<std::endl;    
        std::cout<<"Enter workout duration (minutes): ";
        std::cin>>workoutDuration;
        caloriesBurned=workoutDuration*workouts[choice].getCaloriesBurnPerMinute();
        if (totalCaloriesBurned+caloriesBurned>safeCaloriesBurn) {
            std::cout<<"This workout exceeds your safe daily burn limit!"<<std::endl;
            std::cout<< "You can only burn "<<(safeCaloriesBurn-totalCaloriesBurned)<< " more calories today."<<std::endl;
            break;
        }

        totalCaloriesBurned+=caloriesBurned;
        user.addSelectedWorkout(choice);
        user.addCaloriesBurned(caloriesBurned);

        std::cout << workouts[choice].getActivity()<<" added. Burned "<<caloriesBurned<<" cal"<<std::endl;
    }

    std::cout<<"Total calories burned: "<<totalCaloriesBurned<<" cal"<<std::endl;
    if (totalCaloriesBurned>0){
        std::cout<<"Workout plan saved."<<std::endl;
    }
    else{
        std::cout<<"Workout plan not saved."<<std::endl;
    }
}

void MyHealthMate::viewWorkoutPlan(User &user){
    if (user.getSelectedWorkoutCount()==0){
        std::cout<<"No workouts selected yet."<<std::endl;
        return;
    }
    std::cout<<"--------- Your Workout Plan ---------"<<std::endl;
    for (int i=0;i<user.getSelectedWorkoutCount();i++){
        int index = user.getSelectedWorkoutIndex(i);
        workouts[index].displayWorkoutExercises(i);
    }
    std::cout<<"Total calories burned: "<<user.getTotalBurnedCalories()<<" cal"<<std::endl;
    std::cout<<"------------------------------------"<<std::endl;
}

void MyHealthMate::workoutSession(User &user){
    int choice;
    std::cout<<std::endl;
    std::cout<<"You have entered into the workout session"<<std::endl;
    do{
        std::cout<<"Please enter your choice"<<std::endl;
        std::cout<<"1. view workout menu"<<std::endl;
        std::cout<<"2. edit workout plan"<<std::endl;
        std::cout<<"3. view workout plan"<<std::endl;
        std::cout<<"4. delete workout plan"<<std::endl;
        std::cout<<"5. exit"<<std::endl;
        std::cout<<"please enter choice to continue(1,2,3,4,5): ";
        std::cin>>choice;
        std::cout<<std::endl;
        
        switch(choice){
            case 1:
                showWorkoutMenu();
                break;
            case 2:
                showWorkoutMenu();
                chooseWorkout(user);
                break;
            case 3:
                viewWorkoutPlan(user);
                break;
            case 4:
                user.deleteSelectedWorkouts();
                break;
            case 5:
                return;
            default:
                std::cout<<"invalid choice, please try again."<<std::endl;
        }
    }while(choice!=6);
}

void MyHealthMate::progressSession(User &user){
    int choice;
    double newWeight;
    std::cout<<"please enter your choice:"<<std::endl;
    std::cout<<"1. update progress"<<std::endl;
    std::cout<<"2. view progress history"<<std::endl;
    std::cout<<"Please enter your chioce(1,2):";
    std::cin>>choice;
    
    ProgressTracker tracker;
    if(choice==1){
        std::cout<<"please enter your new weight: ";
        std::cin>>newWeight;
        tracker.updateProgress(user, newWeight);
        tracker.displayProgress(user);
    }
    else if(choice==2){
        tracker.viewProgressHistory(user);
    }
    else{
        std::cout<<"invalid choice"<<std::endl;
    }
   
}

/*i added this comppare user function to so that i acomplish the friend fucntion
requiremnt*/
void MyHealthMate::compareTwoUsersSession(){
    std::string name1, name2;

    std::cout<<"you have entered into the comparing page"<<std::endl;
    std::cout<<"Enter first user's name: (first letter must be uppercase):";
    std::cin>>name1;
    std::cout<<"Enter second user's name: (first letter must be uppercase):";
    std::cin>>name2;

    int index1=findUserWithName(name1);
    int index2=findUserWithName(name2);

    if (index1==-1 || index2==-1){
        std::cout<<"One or both users not found."<<std::endl;
        return;
    }

    compareUsers(users[index1], users[index2]);
    std::cout<<std::endl;
}

void MyHealthMate::userSession(User &user){
    int choice;
    std::cout<<std::endl;
    do{
        std::cout<<"please enter a number to continue"<<std::endl;
        std::cout<<"1. view personal info"<<std::endl;
        std::cout<<"2. view diet page"<<std::endl;
        std::cout<<"3. view workout page"<<std::endl;
        std::cout<<"4. view progress page"<<std::endl;
        std::cout<<"5. compare two users"<<std::endl;
        std::cout<<"6. logout"<<std::endl;
        std::cout<<"enter choice:";
        std::cin>>choice;
        std::cout<<std::endl;

        switch(choice){
            case 1 : 
                user.displayUserInfo();
                break;
            case 2 :
                dietSession(user);
                break;
            case 3 :
                workoutSession(user);
                break;
            case 4 :
                progressSession(user);
                break;
            case 5 :
                 compareTwoUsersSession(); 
                 break;
            case 6 : 
                std::cout<<"log out"<<std::endl;
                break;
            default:
                std::cout<<"invalid choice"<<std::endl;
        }

    }while(choice != 6);
}

void MyHealthMate::start(){
    std::string name;

    while(true){
        std::cout<<std::endl;
        std::cout<<"-------------------------"<<std::endl;
        std::cout<<"welcome to My HealthMate "<<std::endl;
        std::cout<<"-------------------------"<<std::endl;
        std::cout<<"please enter your name (or type Exit to uit the system)"<<std::endl;
        std::cout<<"first letter must be uppercase:";
        std::cin>>name;
        std::cout<<std::endl;

        if(name=="Exit"){
            std::cout<<"have a nice day"<<std::endl;
            break;
        }

        int place = findUserWithName(name);

        if(place==-1){
            std::cout<<"User is not in the list, please try again to continue";
        }
        else{
            std::cout<<"user found! welcome, "<<users[place].getName()<< std::endl;
            userSession(users[place]);
        }

        
    }

}





