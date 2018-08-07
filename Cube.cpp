//
//  Cube.cpp
//  BldMemoGenerator
//
//  Created by Xuzhi Zhang on 12/9/16.
//  Copyright © 2016 Xuzhi Zhang. All rights reserved.
//

#include "Cube.h"

//bunch of errors
class InvalidDirectionException {};
class SamePieceException {};
class InvalidMoveException {};
class CornerRepresentationException {};
//------------------------------Letters---------------------------
std::string eLetter::conversion_chart = "ABCDEFGHIJKLMNOPQRSTWXYU";
int eLetter::state = 0;
std::string cLetter::conversion_chart = "ABCDEFGHIJKLWMNOPQRSTXYU";
int cLetter::state = 0;
//edge letters

eLetter::eLetter(int i): repr(i) {}

eLetter::eLetter(char c){
    for(int i = 0; i < (int)conversion_chart.size(); i++) {
        if(conversion_chart[i] == c){
            repr = i;
            return;
        }
    }
}
eLetter::operator int() {
    return repr;
}

void eLetter::print(std::ostream& os) {
    os << conversion_chart[repr];
    if(state) os << " ";
    state = (state + 1) % 2;
}

std::ostream& operator << (std::ostream& os, eLetter e) {
    e.print(os);
    return os;
}
//corner letters

cLetter::cLetter(int i): repr(i) {}


cLetter::cLetter(char c) {
    for(int i = 0; i < (int)conversion_chart.size(); i++) {
        if(conversion_chart[i] == c){
            repr = i;
            return;
        }
    }
}

cLetter::operator int() {
    return repr;
}

void cLetter::print(std::ostream& os) {
    os << conversion_chart[repr];
    if(state) os << " ";
    state = (state + 1) % 2;
}

std::ostream& operator<<(std::ostream& os, cLetter c) {
    c.print(os);
    return os;
}

//-------------------------------Cubes----------------------------

//Constructors
//no alg - initialise to a solved cube
Cube::Cube(): edge_buffer(0), corner_buffer(0){
    for(int i = 0; i < NUM_STICKERS; i++) {
        edges[i] = corners[i] = i;
    }
    for(int i = 0; i < NUM_EDGES; i++) {
        edge_pieces.push_back(i);
    }
    for(int i = 0; i < NUM_CORNERS; i++) {
        corner_pieces.push_back(i);
    }
}



//3 algs - initialise to a certain scramble and buffer pieces
Cube::Cube(const std::string scramble, eLetter ebuffer, cLetter cbuffer):
edge_buffer(ebuffer), corner_buffer(cbuffer) {
    for(int i = 0; i < NUM_STICKERS; i++) {
        edges[i] = corners[i] = i;
    }
    edge_pieces.push_back(get_edge_pieces(ebuffer));
    corner_pieces.push_back(get_corner_pieces(cbuffer));
    for(int i = 0; i < NUM_EDGES; i++) {
        if(i != get_edge_pieces(ebuffer)) {
            edge_pieces.push_back(i);
        }
    }
    for(int i = 0; i < NUM_CORNERS; i++) {
        if(i != get_corner_pieces(cbuffer)) {
            corner_pieces.push_back(i);
        }
    }
    scramble_cube(scramble);
}


//Swaps four pieces in the cube
//Intended for simulating moves
void Cube::edge_four_cycle(const std::vector<int> related_edges, int direction) {
    if(direction == 1) {
        int temp = edges[related_edges[0]];
        for(int i = 0; i < 3; i++)
            edges[related_edges[i]] = edges[related_edges[i + 1]];
        edges[related_edges[3]] = temp;
    }
    else if (direction == -1) {
        int temp = edges[related_edges[3]];
        for(int i = 3; i > 0; i--)
            edges[related_edges[i]] = edges[related_edges[i - 1]];
        edges[related_edges[0]] = temp;
    }
    else if(direction == 2) {
        std::swap(edges[related_edges[0]], edges[related_edges[2]]);
        std::swap(edges[related_edges[1]], edges[related_edges[3]]);
    } else throw InvalidDirectionException();
}

void Cube::corner_four_cycle(const std::vector<int> related_edges, int direction) {
    if(direction == 1) {
        int temp = corners[related_edges[0]];
        for(int i = 0; i < 3; i++)
            corners[related_edges[i]] = corners[related_edges[i + 1]];
        corners[related_edges[3]] = temp;
    }
    else if (direction == -1) {
        int temp = corners[related_edges[3]];
        for(int i = 3; i > 0; i--)
            corners[related_edges[i]] = corners[related_edges[i - 1]];
        corners[related_edges[0]] = temp;
    }
    else if(direction == 2) {
        std::swap(corners[related_edges[0]], corners[related_edges[2]]);
        std::swap(corners[related_edges[1]], corners[related_edges[3]]);
    } else throw InvalidDirectionException();
}

//simulating one move in the form X, X' or X2
void Cube::move(const std::string m) {
    std::vector<int> related_edges_1, related_edges_2, related_corners_1, related_corners_2, related_corners_3;
    if(m[0] == 'R') {
        related_edges_1 = {7, 23, 15, 17};
        related_edges_2 = {6, 22, 14, 16};
        related_corners_1 = {10, 8, 19, 23};
        related_corners_2 = {9, 7, 18, 22};
        related_corners_3 = {11, 6, 20, 21};
    }
    else if(m[0] == 'U') {
        related_edges_1 = {4, 6, 0, 2};
        related_edges_2 = {5, 7, 1, 3};
        related_corners_1 = {0, 3, 6, 9};
        related_corners_2 = {1, 4, 7, 10};
        related_corners_3 = {2, 5, 8, 11};
    }
    else if(m[0] == 'L') {
        related_edges_1 = {3, 19, 11, 21};
        related_edges_2 = {2, 18, 10, 20};
        related_corners_1 = {13, 17, 4 ,2};
        related_corners_2 = {14, 15, 5,0};
        related_corners_3 = {12, 16, 3, 1};
    }
    else if(m[0] == 'D') {
        related_edges_1 = {8, 14, 12, 10};
        related_edges_2 = {9, 15, 13, 11};
        related_corners_1 = {21, 18, 15, 12};
        related_corners_2 = {22, 19, 16, 13};
        related_corners_3 = {23, 20, 17, 14};
    }
    else if(m[0] == 'F') {
        related_edges_1 = {1, 16, 9, 18};
        related_edges_2 = {0, 17, 8, 19};
        related_corners_1 = {11, 22, 14, 1};
        related_corners_2 = {10, 21, 13, 0};
        related_corners_3 = {9, 23, 12, 2};
    }
    else if(m[0] == 'B') {
        related_edges_1 = {5, 20, 13, 22};
        related_edges_2 = {4, 21, 12, 23};
        related_corners_1 = {20, 7, 5, 16};
        related_corners_2 = {18, 8, 3, 17};
        related_corners_3 = {19, 6, 4, 15};
    }
    else throw InvalidMoveException();
    
    int direction;
    if(m.size() == 1) direction = -1;
    else if(m[1] == '\'') direction = 1;
    else if(m[1] == '2') direction = 2;
    else throw InvalidDirectionException();
    
    edge_four_cycle(related_edges_1, direction);
    edge_four_cycle(related_edges_2, direction);
    corner_four_cycle(related_corners_1, direction);
    corner_four_cycle(related_corners_2, direction);
    corner_four_cycle(related_corners_3, direction);

}

//Use the move function to scramble the cube
void Cube::scramble_cube(const std::string scramble) {
    std::stringstream ss(scramble);
    std::string m;
    while(ss >> m) move(m);
}

//given an edge sticker, return the piece it belongs
int Cube::get_edge_pieces(int sticker) {
    assert(sticker < NUM_STICKERS);
    return sticker / 2;
}

//given a corner sticker, return the piece it belongs
int Cube::get_corner_pieces(int sticker) {
    assert(sticker < NUM_STICKERS);
    return sticker / 3;
}

//given an edge sticker, return the other sticker
//that also belongs to the same piece
int Cube::get_other_edge_sticker(int sticker) {
    return sticker%2 ? sticker - 1 : sticker + 1;
}

//given a corner sticker, return the next sticker
//clockwise that belongs to the same piece
int Cube::get_next_corner_sticker(int sticker) {
    if(sticker % 3 == 2) return sticker - 2;
    else return sticker + 1;
}

//swaps two edges around in a certain orientation
void Cube::edge_swap(int s1, int s2) {
    if(get_edge_pieces(s1) == get_edge_pieces(s2))
        throw SamePieceException();
    
    std::swap(edges[s1], edges[s2]);
    std::swap(edges[get_other_edge_sticker(s1)],
              edges[get_other_edge_sticker(s2)]);
}

//swaps two corners around in a certain orientation
void Cube::corner_swap(int s1, int s2) {
    if(get_corner_pieces(s1) == get_corner_pieces(s2))
        throw SamePieceException();
    
    std::swap(corners[s1], corners[s2]);
    std::swap(corners[s1 = get_next_corner_sticker(s1)],
              corners[s2 = get_next_corner_sticker(s2)]);
    std::swap(corners[s1 = get_next_corner_sticker(s1)],
              corners[s2 = get_next_corner_sticker(s2)]);
}


//returns the first edge sticker that is not in place
//if none exist, return -1
int Cube::edge_index_not_in_place() {
    for(int i = 0; i < NUM_STICKERS; i++) {
        if(edges[i] - i) return i;
    }
    return -1;
}

//returns the first corner sticker that is not in place
//if none exist, return -1
int Cube::corner_index_not_in_place() {
    for(int i = 0; i < NUM_STICKERS; i++) {
        if(corners[i] - i) return i;
    }
    return -1;

}

//check whether an edge piece is in place
//regardless of orientation
bool Cube::edge_is_in_place(int sticker) {
    return get_edge_pieces(sticker) == get_edge_pieces(edges[sticker]);
}

//check whether a corner piece is in place
//regardless of orientation
bool Cube::corner_is_in_place(int sticker) {
    return get_corner_pieces(sticker) == get_corner_pieces(corners[sticker]);
}

//checks whether the cube is solved
bool Cube::cube_is_solved(){
    for(int i = 0; i < NUM_STICKERS; i++) {
        if(edges[i] != i || corners[i] != i) return false;
    }
    return true;
}

//shows all the edges that need to be flipped
void Cube::edge_flip(){
    for(int i = 0; i < NUM_STICKERS; i++) {
        assert(edge_is_in_place(i));
        if(edges[i] - i) edge_flips.push_back(i);
    }
}

//shows all the corners that need to be twisted
void Cube::corner_twist(){
    for(int i = 0; i < NUM_STICKERS; i++) {
        assert(corner_is_in_place(i));
        if(corners[i] - i) corner_twists.push_back(i);
    }
}

//given a sticker, tells the direction of the corner twist
std::string Cube::corner_flip_direction(int i){
    if(corners[i] == i) return "correct";
    else if (corners[i] == i + 1 || corners[i] == i - 2) return "clockwise";
    else if (corners[i] == i + 2 || corners[i] == i - 1) return "anti-clockwise";
    else throw CornerRepresentationException();
}

//generate the appropriate memo for edges
//and store them in the member vector
void Cube::generate_edge_memo(){
    for(int j = 0; j < NUM_EDGES; j++) {
        int i = edge_pieces[j];
        if(i != get_edge_pieces(edge_buffer) && !edge_is_in_place(2 * i)) {
            edge_memo.push_back(2 * i);
            edge_swap(edge_buffer, 2 * i);
        }
        while(!edge_is_in_place(edge_buffer)) {
            edge_memo.push_back(edges[edge_buffer]);
            edge_swap(edge_buffer, edges[edge_buffer]);
        }
    }
}

//generate the appropriate memo for corners
//and store them in the member vector
void Cube::generate_corner_memo(){
    for(int i = 0; i < NUM_CORNERS; i++) {
        int j = corner_pieces[i];
        if(j != get_corner_pieces(corner_buffer) && !corner_is_in_place(3 * j)) {
            corner_memo.push_back(3 * j);
            corner_swap(corner_buffer, 3 * j);
        }
        while(!corner_is_in_place(corner_buffer)) {
            corner_memo.push_back(corners[corner_buffer]);
            corner_swap(corner_buffer, corners[corner_buffer]);
        }
    }
}

void Cube::show_cube(std::ostream& os) {
    os << "let correctEdge = [";
    for(int i = 0; i < NUM_STICKERS; i++) {
        os << edges[i] << ((i == NUM_STICKERS - 1)? "" : ", ");
    }
    os << "]" << std::endl << "let correctCorner = [";
    for(int i = 0; i < NUM_STICKERS; i++) {
        os << corners[i] << ((i == NUM_STICKERS - 1)? "" : ", ");
    }
    os << "]" << std::endl;
}

void Cube::solve() {
    generate_edge_memo();
    generate_corner_memo();
    edge_flip();
    corner_twist();
}

std::ostream& Cube::print_memo(std::ostream& os) {
    os << "Edge memo: ";
    for(int i = 0; i < (int)edge_memo.size(); i++) {
        os << edge_memo[i];
    }
    os << std::endl << "Corner memo: ";
    for(int i = 0; i < (int)corner_memo.size(); i++) {
        os << corner_memo[i];
    }
    
    eLetter::state = 0;
    os << std::endl << "Edge flips: ";
    for(auto item : edge_flips) os << item;
    
    cLetter::state = 0;
    os << std::endl << "Corner twists: ";
    for(int i = 0; i < (int)corner_twists.size(); i++) {
        os << corner_twists[i]; cLetter::state = 0;
        if(i % 3 == 2) {
            os << " ";
            os << corner_flip_direction(corner_twists[i]) << " ";
        }
    }
    os << std::endl;
    
    return os;
}

std::string Cube::give_edge_memo(){
    std::stringstream ss;
    for(int i = 0; i < (int)edge_memo.size(); i++) {
        ss << edge_memo[i];
    }
    return ss.str();
}

std::string Cube::give_corner_memo(){
    std::stringstream ss;
    for(int i = 0; i < (int)corner_memo.size(); i++) {
        ss << corner_memo[i];
    }
    return ss.str();
}
