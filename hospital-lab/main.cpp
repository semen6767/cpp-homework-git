#include <iostream>
#include <string>
#include <vector>
#include <utility>

enum class Department {
    Therapy,     
    Surgery,     
    Cardiology,  
    Unknown
};

enum class PatientState {
    InQueue,     
    InTreatment, 
    Discharged   
};

std::string departmentToString(Department d);
std::string stateToString(PatientState s);

std::string departmentToString(Department d) {
    switch (d) {
        case Department::Therapy:    return "Терапия";
        case Department::Surgery:    return "Хирургия";
        case Department::Cardiology: return "Кардиология";
        default:                     return "Неизвестно";
    }
}

std::string stateToString(PatientState s) {
    switch (s) {
        case PatientState::InQueue:     return "В очереди";
        case PatientState::InTreatment: return "Лечится";
        case PatientState::Discharged:  return "Выписан";
        default:                        return "Неизвестно";
    }
}

class Patient {
private:
    std::string name;
    int age;
    Department department;
    PatientState state;

public:
    Patient(std::string name, int age, Department dept)
        : name(std::move(name)), age(age), department(dept), state(PatientState::InQueue) {}

    std::string getName() const { return name; }
    int getAge() const { return age; }
    Department getDepartment() const { return department; }
    PatientState getState() const { return state; }

    void setAge(int age) {
        if (age > 0) {
            this->age = age;
        } else {
            std::cerr << "Ошибка: возраст должен быть больше 0!" << std::endl;
        }
    }

    void setState(PatientState s) {
        state = s;
    }

    virtual std::string getDescription() const {
        return "Пациент: " + name + 
               ", возраст: " + std::to_string(age) + 
               ", отделение: " + departmentToString(department) + 
               ", состояние: " + stateToString(state);
    }

    virtual ~Patient() = default;
};

class ChildPatient : public Patient {
private:
    std::string parentName;

public:
    ChildPatient(std::string name, int age, Department dept, std::string parentName)
        : Patient(std::move(name), age, dept), parentName(std::move(parentName)) {}

    std::string getDescription() const override {
        return "Ребёнок: " + getName() + 
               ", возраст: " + std::to_string(getAge()) + 
               ", отделение: " + departmentToString(getDepartment()) + 
               ", состояние: " + stateToString(getState()) + 
               ", родитель: " + parentName;
    }
};

int main() {
    Patient adult("Иван Петров", 35, Department::Surgery);
    ChildPatient child("Маша Иванова", 8, Department::Therapy, "Ольга Иванова");

    std::cout << adult.getDescription() << std::endl;
    std::cout << child.getDescription() << std::endl;

    adult.setState(PatientState::InTreatment);

    std::cout << adult.getDescription() << std::endl;

    return 0;
}