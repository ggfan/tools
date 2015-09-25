//
//  main.cpp
//  power_code
//
//  Created by gfan on 3/27/15.
//  Copyright (c) 2015 gfan. All rights reserved.
//  Simple tool analyze the power commands in android native code
//  build:g++ -std=c++11 power_code.cpp

#include <iostream>
#include <unordered_map>

struct android_native_power_definitions {
    const char*  name;
    uint32_t     value;
};

const struct android_native_power_definitions cmds[] = {
    { "APP_CMD_INPUT_CHANGED",  0},
    { "APP_CMD_INIT_WINDOW",    1},
    { "APP_CMD_TERM_WINDOW",    2},
    { "APP_CMD_WINDOW_RESIZED", 3},
    { "APP_CMD_WINDOW_REDRAW_NEEDED",4},
    { "APP_CMD_CONTENT_RECT_CHANGED",5},
    { "APP_CMD_GAINED_FOCUS",   6},
    { "APP_CMD_LOST_FOCUS",     7},
    { "APP_CMD_CONFIG_CHANGED", 8},
    { "APP_CMD_LOW_MEMORY",  9 },
    { "APP_CMD_START",       10},
    { "APP_CMD_RESUME",      11},
    { "APP_CMD_SAVE_STATE",  12},
    { "APP_CMD_PAUSE",       13},
    { "APP_CMD_STOP",        14},
    { "APP_CMD_DESTROY",     15},

};
const int32_t cmd_size = sizeof(cmds) / sizeof(cmds[0]);


int main(int argc, const char * argv[]) {
    if (argc < 2 ) {
        std::cout<<"usage: power_code command_enum command_string"<<std::endl;
        return 1;
    }
    
    std::unordered_map<uint32_t, std::string>  power_commands;
    
    for(int32_t i=0; i < cmd_size; i++){
        power_commands[cmds[i].value] = std::string(cmds[i].name);
    }
    
    for (int32_t i =1; i < argc; i++) {
        if (argv[i][0] <'0' || argv[i][0] > '9') {
            bool found_it = false;
            for (auto val : power_commands) {
                if (val.second == std::string(argv[i])) {
                    std::cout<<val.first<<" ";
                    found_it = true;
                    break;
                }
            }
            if (!found_it)
                std::cout<<"unknown_command ";
        } else {
            auto it = power_commands.find(std::stoi(std::string(argv[i])));
            if (it == power_commands.end()) {
                std::cout<<"unknown_command ";
            } else {
                std::cout<<it->second.c_str()<<" ";
            }
        }
    }
    std::cout<<std::endl;
    return 0;
}

