// 
// 
// 

#include "ExecutionTypeManager.h"
#include "ExecutionType.h"

//The current executiontype (Dafault is normal)
ExecutionType executionType;

ExecutionTypeManager::ExecutionTypeManager() {
    executionType = ExecutionType::normal;
}

void ExecutionTypeManager::receiveTestButtonSignal() {
    if (executionType != ExecutionType::test) {
        //notify main controller to start test execution
    }
}

void ExecutionTypeManager::receiveNormalButtonSignal() {
    if (executionType != ExecutionType::normal) {
        //notify main controller to start normal execution
    }
}

