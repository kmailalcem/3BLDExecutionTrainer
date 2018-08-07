#include "Scramble.h"
#include <iostream>

static const int MIN_SCRAMBLE_LENGTH = 20;
static const int MAX_SCRAMBLE_LENGTH = 28;

static int rand_int_in_range(int start, int end) {
    return rand() % (abs(end - start)) + 
        (start < end ? start : end);
}

std::string get_scramble() {
    srand(time(0));
    enum occupancy_e {EMPTY, LEFT, RIGHT, FULL};
    std::string faces[3] = {"LR", "FB", "UD"};
    occupancy_e occupancy[3] = {EMPTY, EMPTY, EMPTY};

    int scramble_length = rand_int_in_range
        (MIN_SCRAMBLE_LENGTH, MAX_SCRAMBLE_LENGTH);

    assert(MIN_SCRAMBLE_LENGTH <= scramble_length 
            && scramble_length < MAX_SCRAMBLE_LENGTH);

    std::string result;
    int processed = 0;
    while(processed < scramble_length) {
        int face_class = rand_int_in_range(0, 3);
        int face_within_class = rand_int_in_range(0, 2);
        bool occupied = false;
        switch (occupancy[face_class]) {
            case EMPTY: 
                result.push_back(faces[face_class][face_within_class]);
                if (face_within_class) 
                    occupancy[face_class] = RIGHT;
                else occupancy[face_class] = LEFT;
                processed++;
                occupied = true;
                break;
            case LEFT:
                if (face_within_class) {
                    result.push_back(
                            faces[face_class][face_within_class]);
                    occupancy[face_class] = FULL;
                    processed++;
                    occupied = true;
                }
                break;
            case RIGHT:
                if (!face_within_class) {
                    result.push_back(
                            faces[face_class][face_within_class]);
                    occupancy[face_class] = FULL;
                    processed++;
                    occupied = true;
                }
                break;
            case FULL:
                break;
            default:
                throw UnknownOccupancyException();
        }
        if (occupied) {
            for (int i = 0; i < 3; ++i) {
                if (i != face_class) occupancy[i] = EMPTY;
            }
        }
    }
    std::string result_final;
    for (int i = 0; i < scramble_length; ++i) {
        result_final.push_back(result[i]);
        int direction = rand_int_in_range(0, 3);
        switch(direction) {
            case 0:
                break;
            case 1:
                result_final.push_back('\'');
                break;
            case 2:
                result_final.push_back('2');
                break;
            default:
                throw UnknownDirectionException();
        }
        result_final.push_back(' ');
    }
    return result_final;
}
