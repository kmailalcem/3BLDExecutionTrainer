//
//  main.cpp
//  BldMemoGenerator
//
//  Created by Nelson Zhang on 12/9/16.
//  Copyright © 2016 Nelson Zhang. All rights reserved.
//

#include "Cube.h"
#include "Scramble.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdio>
using namespace std;

static bool user_finished_solving = false;

void print_time() {
    auto start = chrono::high_resolution_clock::now();
    while (!user_finished_solving) {
        auto end = chrono::high_resolution_clock::now();
        cout << fixed << setprecision(3) << 
            static_cast<std::chrono::duration<float>>(end - start).count() 
            << '\r';
    }
    auto end = chrono::high_resolution_clock::now();
    cout << fixed << setprecision(3) << '\r' << 
        static_cast<std::chrono::duration<float>>(end - start).count() 
        << endl;
}

int main(int argc, const char * argv[]) {
    if(argc != 1 && argc != 2 && argc != 3) {
        cout << "USAGE: ./main (edge_buffer) (corner_buffer)" << endl;
        cout << "OR: ./main [scramble_file_name]" << endl;
        exit(EXIT_FAILURE);
    }
    
    if(argc != 2) {
        string scramble;
        string r;
        char cbuffer;
        char ebuffer;
        cout << "Welcome to 3BLD execution trainer!" << endl;
        if(argc == 1) {
            cout << "Please enter your edge buffer: "; cin >> ebuffer;
            cout << "Please enter your corner buffer: "; cin >> cbuffer;
        } else {
            ebuffer = argv[1][0];
            cbuffer = argv[2][0];
        }
        cout << "Please choose an option: " << endl;
        cout << "Type 'random' for random scrambles" << endl;
        cout << "Type 'solve' to solve a scramble of your choice" << endl;
        string user_choice;
        cin >> user_choice;
        if (user_choice == "solve") {
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
        } else if (user_choice == "random") {
            cout << endl;
            char cont = 'n';
            do {
                string scramble = get_scramble();

                cin.get();
                cout << "Start the timer when you have "
                    "scrambled the cube by pressing enter" << endl;
                cout << scramble << '\r'; 
                Cube cube(scramble, ebuffer, cbuffer);
                //cube.show_cube(cout);
                cube.solve();
                cin.get();
                cout << endl;
                cube.print_memo(cout);
                cout << endl;

                this_thread::sleep_for(.5s);
                thread timer(print_time);
                cin.get();
                user_finished_solving = true;
                timer.join();
                user_finished_solving = false;
                
                cout << "\nContinue?(y/n)"; cin >> cont;
            } while (cont != 'n');
        } else {
            cout << "Unknown choice but whatever"
                "thanks for using 3BLD execution trainer" << endl;
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
    
    cout << "Thank you for using 3BLD execution trainer!" << endl;
    return 0;
}
