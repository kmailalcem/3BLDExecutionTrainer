//
//  main.cpp
//  BldMemoGenerator
//
//  Created by Nelson Zhang on 12/9/16.
//  Copyright © 2016 Nelson Zhang. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "Cube.h"
using namespace std;



int main(int argc, const char * argv[]) {
    if(argc != 1 && argc != 2 && argc != 3) {
        cout << "USAGE: ./main [edge_buffer] [corner_buffer]" << endl;
        cout << "OR: ./main [scramble_file_name]" << endl;
        exit(EXIT_FAILURE);
    }
    
    if(argc != 2) {
        string scramble;
        string r;
        char cbuffer;
        char ebuffer;
        if(argc == 1) {
            cout << "Please enter your edge buffer: "; cin >> ebuffer;
            cout << "Please enter your corner buffer: "; cin >> cbuffer;
        } else {
            ebuffer = argv[1][0];
            cbuffer = argv[2][0];
        }
        char cont = 'y';
        while(cont != 'n') {
            cout << "Please enter a scramble: "; 
            cin >> r; getline(cin, scramble);
            scramble = r + scramble;
            Cube cube(scramble, ebuffer, cbuffer);
            cube.show_cube(cout);
            cube.solve();
            cube.print_memo(cout);
            cout << "Continue?(y/n)"; cin >> cont;
        }
    } else {
        string scramble_file_name = argv[1];
        ifstream fin(scramble_file_name);
        if(!fin) {
            cout << "Error opening file: " << scramble_file_name << endl;
            exit(EXIT_FAILURE);
        }
        string scramble;
        char cbuffer, ebuffer, end;
        fin >> ebuffer >> cbuffer;
        fin.get(end);
        int count = 1;
        while(getline(fin, scramble)) {
            cout << count << "." << endl;
            Cube cube(scramble, ebuffer, cbuffer);
            cube.solve();
            cout << "Scramble: " << scramble << endl << endl;
            cube.print_memo(cout);
            cout << endl;
            count++;
        }
    }
    
    return 0;
}
