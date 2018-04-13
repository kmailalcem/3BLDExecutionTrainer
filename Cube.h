//
//  Cube.h
//  BldMemoGenerator
//
//  Created by Nelson Zhang on 12/9/16.
//  Copyright © 2016 Nelson Zhang. All rights reserved.
//

#ifndef Cube_h
#define Cube_h

#include <string>
#include <iostream>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>

const int NUM_STICKERS = 24;
const int NUM_EDGES = 12;
const int NUM_CORNERS = 8;
//------------Letter Classes----------
//edges
class eLetter {
private:
    int repr;
    
public:
    static int state;
    static std::string conversion_chart;
    eLetter(int eletter);
    eLetter(char eletter);
    operator int();
    void print(std::ostream&);
};
std::ostream& operator << (std::ostream&, eLetter);

//corners
class cLetter {
private:
    int repr;
    
public:
    static int state;
    static std::string conversion_chart;
    cLetter(int cletter);
    cLetter(char cletter);
    operator int();
    void print(std::ostream&);
};
std::ostream& operator << (std::ostream&, cLetter);

//------------Cube Class-------------
class Cube {
private:
    int corners[NUM_STICKERS];
    int edges[NUM_STICKERS];
    
    eLetter edge_buffer;
    cLetter corner_buffer;
    
    std::vector<eLetter> edge_memo;
    std::vector<cLetter> corner_memo;
    
    std::vector<eLetter> edge_flips;
    std::vector<cLetter> corner_twists;
    
    std::vector<int> edge_pieces;
    std::vector<int> corner_pieces;
    
private:
    void edge_four_cycle(const std::vector<int>, int);
    void corner_four_cycle(const std::vector<int>, int);
    void convert_edges(char);
    void convert_corners(char);
    void move(const std::string);
    void scramble_cube(const std::string);
    int get_edge_pieces(int);
    int get_corner_pieces(int);
    int get_other_edge_sticker(int);
    int get_next_corner_sticker(int);
    void edge_swap(int, int);
    void corner_swap(int, int);
    int edge_index_not_in_place();
    int corner_index_not_in_place();
    bool edge_is_in_place(int);
    bool corner_is_in_place(int);
    bool cube_is_solved();
    void edge_flip();
    void corner_twist();
    std::string corner_flip_direction(int);
    void generate_edge_memo();
    void generate_corner_memo();
    
    //NO BIG THREE!!!!!!!!!
    Cube operator = (Cube&);
    Cube(Cube&);
    
public:
    Cube();
    Cube(const std::string, eLetter, cLetter);
    void solve();
    std::ostream& print_memo(std::ostream&);
    void show_cube(std::ostream&);
    std::string give_edge_memo();
    std::string give_corner_memo();
};


#endif /* Cube_h */
