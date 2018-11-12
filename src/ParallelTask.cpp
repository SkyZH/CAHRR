//
// Created by Alex Chi on 2018/11/12.
//

#include "ParallelTask.h"

bool ParallelTask::initialize() {
    bool result = true;
    for (std::vector <Task*> ::const_iterator iter = this->tasks.begin(); iter != this->tasks.end(); iter++) {
        result = result && (*iter)->initialize();
    }
    return result;
}

bool ParallelTask::destroy() {
    bool result = true;
    for (std::vector <Task*> ::const_iterator iter = this->tasks.begin(); iter != this->tasks.end(); iter++) {
        result = result && (*iter)->destroy();
    }
    return result;
}

bool ParallelTask::isEnd() {
    bool result = true;
    for (std::vector <Task*> ::const_iterator iter = this->tasks.begin(); iter != this->tasks.end(); iter++) {
        result = result && (*iter)->isEnd();
    }
    return result;
}

bool ParallelTask::update() {
    bool result = true;
    for (std::vector <Task*> ::const_iterator iter = this->tasks.begin(); iter != this->tasks.end(); iter++) {
        result = result && (*iter)->update();
    }
    return result;
}

ParallelTask::ParallelTask(const std::vector <Task*> &tasks) : Task(), tasks(tasks) {

}
