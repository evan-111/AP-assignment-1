# MyHealthMate – Advanced Programming Assignment

A C++ console-based health and fitness tracking application. Users can manage profiles, plan diets (manually or via a greedy auto-generator), select workouts, and track weight/BMI progress over time.

## Features

- **User Profiles** – Create and manage personal info (name, age, gender, weight, height) with automatic BMI calculation and health range classification.
- **Diet Planning** – Browse available meals and manually build a daily diet, or use the auto-generator to produce a goal-aligned plan with calorie targeting.
- **Workout Planning** – Browse workouts with intensity levels and calorie burn rates, with a safety cap on daily burn.
- **Progress Tracking** – Log weight and BMI over time; view history from file-based records.
- **BMI Comparison** – Compare BMI between two users using operator overloading and a friend function.

## Educational Concepts Demonstrated

- Classes and inheritance (`Person` → `User`)
- File I/O with `fstream`
- Operator overloading (`>`, `<`, `==`)
- Friend functions
- Greedy algorithm for auto-diet generation
- Multi-file project organisation with header/source separation

## Building

Compile with any C++11-compliant compiler:

```bash
g++ -std=c++11 -o MyHealthMate \
    main.cpp \
    MyHealthMate.cpp \
    User.cpp \
    Person.cpp \
    DietPlan.cpp \
    WorkoutPlan.cpp \
    ProgressTracker.cpp
```

## Running

Ensure the data files (`userInfo.txt`, `dietPlans.txt`, `workoutPlans.txt`) are in the same directory as the executable, then run:

```bash
./MyHealthMate
```

Type a user's name (capitalised, e.g. `Alice`) to log in, or `Exit` to quit. Follow the interactive menus to browse meals, workouts, and track progress.

## Data File Formats

**userInfo.txt**
```
<Name> <Age> <F/M> <Weight(kg)> <Height(m)> <lose|maintain|gain>
```

**dietPlans.txt**
```
<MealType>,<FoodDescription>,<Calories>
```

**workoutPlans.txt**
```
<Activity>,<IntensityLevel>,<CaloriesBurnPerMinute>
```

## Notes

- Built as part of the **Advanced Programming** course (Semester 2, Year 2).
- The assignment restricted the use of STL containers – all data is stored in raw fixed-size arrays (max 50 users, meals, workouts).
- There is no authentication beyond name lookup, and diet/workout selections are not persisted between sessions.
