#include <iostream>
#include <ctime>
#include <vector>
#include <mars.hpp>

int main( int argc, char *argv[] ){
    srand(time(NULL));
    if( argc< 4 ){
        std::cout<<"pls give default FILE_NAME FILE_NAME"<<std::endl;
        return 0;
    }
    if( std::string(argv[1]) == std::string("default") ){
        std::vector<std::string> in;
        for(int i = 2; i < argc; ++i){
            in.push_back(argv[i]);
        }
        MARS mars( in);
        for ( int i = 0; i < 234; ++i){
            mars.iterate();
        }
    }
    return 0;
}

