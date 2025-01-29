#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

class Job {
public:
    int id;
    std::string name;

    Job() : id(0), name("") {}  // Конструктор по умолчанию
    Job(int id, const std::string& name) : id(id), name(name) {}
};

class Position {
public:
    int id;
    std::string title;

    Position() : id(0), title("") {}  // Конструктор по умолчанию
    Position(int id, const std::string& title) : id(id), title(title) {}
};

class Person {
public:
    int id;
    std::string name;
    int jobId;
    int positionId;

    Person(int id, const std::string& name, int jobId, int positionId)
        : id(id), name(name), jobId(jobId), positionId(positionId) {}
};

class PersonsList {
private:
    std::vector<Person> persons;
    std::map<int, Job> jobs;
    std::map<int, Position> positions;

public:
    void addJob(const Job& job) {
        jobs[job.id] = job;
    }

    void addPosition(const Position& position) {
        positions[position.id] = position;
    }

    void addPerson(const Person& person) {
        persons.push_back(person);
    }

    static bool compareByJobName(const Person& a, const Person& b, const std::map<int, Job>& jobs) {
        return jobs.at(a.jobId).name < jobs.at(b.jobId).name;
    }

    void sortByJobName() {
        std::stable_sort(persons.begin(), persons.end(),
            [this](const Person& a, const Person& b) {
                return compareByJobName(a, b, jobs);
            });
    }

    void print() const {
        for (const auto& person : persons) {
            std::cout << "ID: " << person.id << ", Name: " << person.name
                      << ", Job: " << jobs.at(person.jobId).name
                      << ", Position: " << positions.at(person.positionId).title << std::endl;
        }
    }
};

int main() {
    PersonsList list;

    // Добавление мест работы
    list.addJob(Job(1, "Developer"));
    list.addJob(Job(2, "Manager"));

    // Добавление должностей
    list.addPosition(Position(1, "Senior Developer"));
    list.addPosition(Position(2, "Project Manager"));

    // Добавление работников
    list.addPerson(Person(1, "Alice", 1, 1));
    list.addPerson(Person(2, "Bob", 2, 2));
    list.addPerson(Person(3, "Charlie", 1, 1));

    // Сортировка по названию работы
    list.sortByJobName();

    // Вывод результатов
    list.print();

    return 0;
}
