
#include <iostream>
#include "FFT.h"

int main() {

    ofstream FILE;
    int retval =0;

    // Declare signals
    bool clk = 0;
    bool rst_n = 0;

    hs_is_t a_i, b_i, c_i, d_o;
    bool clear,enable,function,start;
    shift_t shift;
    len_t len;
    len_t f_cnt;
    bool f_valid;


    // Initialize inputs
    a_i.data = 0; a_i.valid = false; a_i.ready = false;
    b_i.data = 0; b_i.valid = false; b_i.ready = false;
    c_i.data = 0; c_i.valid = true; c_i.ready = false;
    d_o.data = 0; d_o.valid = false; d_o.ready = false;
    clear = false;
    enable = false;
    start = false;
    function =0;
    len = 4;
    shift = 0;

    // Apply reset
    rst_n = 0;
    clear = 1;
    cont(&a_i, &b_i, &c_i, &d_o, clear,enable,function, start, shift, len, &f_cnt,&f_valid);
    rst_n = 1;
    clear = 0;


    // open file to write results 
    FILE.open ("result.dat");

    //  Apply stimulus
    for (int t = 0; t < 15; t++) {
        cont(&a_i, &b_i, &c_i, &d_o, clear,enable,function, start, shift, len, &f_cnt,&f_valid);

        // Example: provide inputs
        if (t == 2) {
            a_i.data = 256; a_i.valid = true;
            b_i.data = 2; b_i.valid = true;
            enable = true;
            start = true;
        }
        
        if(t==3){
            a_i.data = 2; a_i.valid = true;
            b_i.data = 1; b_i.valid = true;
            start = false;

        }

        if (t == 4){
            a_i.data = 0; a_i.valid = true;
            b_i.data = 1; b_i.valid = true;
            enable = true;
        }

        if (t == 5){
            a_i.data = 5; a_i.valid = true;
            b_i.data = 3; b_i.valid = true;
            enable = true;
        }

        if(t==6){
            enable = false;
        }

        // Mark downstream ready
        d_o.ready = true; // assume consumer always ready

        std::cout << "t=" << t << " f_cnt=" << f_cnt<< std::endl;
        std::cout << "t=" << t << " f_valid=" << f_valid<< std::endl;
        //std::cout << "t=" << t << " d_o.data=" << d_o.data<< std::endl;
        // Print outputs
        if (d_o.valid == 1) { 
            std::cout << "t=" << t << " d_o.data=" << d_o.data<< std::endl;
            FILE << d_o.data << endl;
            //FILE << f_cnt<< endl;
        }

    }
    FILE.close();

    retval = system("diff -u -w result.dat result.golden.dat");

    if (retval != 0) {
        printf("Test failed  !!!\n");
        retval = 1;
    } else {
        printf("Test passed !\n");
    }

    // Return 0 if the test passed
    return retval;
}

/* Code for printing the result if needed for debugging 
  
    ifstream infile("result.dat");
    if (!infile) {
        cerr << "Cannot open result.dat!" << endl;
        return 1;
    }

    string firstLine;
    if (getline(infile, firstLine)) {
        cout << "First line of result.dat: [" << firstLine << "]" << endl;
    } else {
        cout << "File is empty!" << endl;
    }

    infile.close();*/


   
