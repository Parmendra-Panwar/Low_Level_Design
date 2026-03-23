#pragma once
#include <iostream>
#include "../strategies/CustomQueueStrategy.hpp"
#include "../strategies/RandomPlayStrategy.hpp"
#include "../strategies/SequentialPlayStrategy.hpp"
#include "../enums/PlayStrategyType.hpp"

using namespace std;

class StrategyManager {
    private:
    static StrategyManager* instance;
    SequentialPlayStrategy* sequentialStrategy;
    RandomPlayStrategy* randomStrategy;
    CustomPlayStrategy* customStrategy;

    StrategyManager(){
        sequentialStrategy = new SequentialPlayStrategy();
        randomStrategy = new RandomPlayStrategy();
        customStrategy = new CustomPlayStrategy();
    }
    public:
    static StrategyManager* getInstance(){
        if(!instance) instance = new StrategyManager();

        return instance;
    }
    PlayStrategy* getStategy(PlayStrategyType type){
        if(type == PlayStrategyType::SEQUENTIAL){
            return sequentialStrategy;
        }else if(type == PlayStrategyType::RANDOM){
            return randomStrategy;
        }else{
            return customStrategy;
        }  
    }
};

StrategyManager* StrategyManager::instance = nullptr;