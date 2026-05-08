#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>


class Person{
    protected:
        std::string name;
        int age;
        char gender;
        
    public:
        Person();
        Person(std::string Name, int age, char gender);


};

#endif