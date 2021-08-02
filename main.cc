#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unistd.h>
#include <stdlib.h>
#include <string>
using namespace std;


int main(int argc, char* argv[]){
    if (argc == 0){
        cerr << "Not enough arguments " << argv[0] << '\n';
        exit(0);
    }

    string filedata = "";
    string data;
    
    int rows = 0;
    int columns = 0;
    int somecolumn = 0;

    char dead = '.';
    char alive = 'O';
    int n;
    bool goption = false;
    //bool inf = false;
    bool lseen = false;
    bool dseen = false;
    bool iseen = false;
    bool gseen = false;
    bool noborn = false;
    bool nosurvive = false;
    bool checkzero = false;
    bool inf = false;
    string born;
    string survive;
    string holdBandS;
    unsigned int hold;
    unsigned int holdzero;
    int bornv = 0;
    int survivev = 0;
    bool checkbs = false;
    
    while ((n = getopt(argc, argv, "+l:d:g:i")) != -1){
        switch(n){
            case 'l':
                if (lseen == true){
                    cerr << "Used -l too many times " << argv[0] << '\n';
                    exit(0);
                }
                alive = *(optarg);
                lseen = true;
                break;
            case 'd':
                if (dseen == true){
                    cerr << "Used -d too many times " << argv[0] << '\n';
                    exit(0);
                }
                dead = *(optarg);
                dseen = true;
                break;
            case 'i':
                if (iseen == true){
                    cerr << "Used -i too many times " << argv[0] << '\n';
                    exit(0);
                }
                inf = true;
                iseen = true;
                break;
            case 'g':{
                if (gseen == true){
                    cerr << "Used -g too many times " << argv[0] << '\n';
                    exit(0);
                }
                goption = true;
                holdBandS = (optarg);
                hold = holdBandS.find('/');
                holdzero = holdBandS.find('0');
                if (holdzero < holdBandS.size()){
                    checkzero= true;
                }
                //cout << "whats the size  " << holdBandS.size() << '\n';
                //(holdBandS.size()== 3) &&
                if (holdBandS == "B/S"){
                    checkbs = true;
                    gseen = true; 
                    break;
                }
                if (holdBandS[0] == 'B' && (holdBandS[hold+1]  == 'S' )){
                    born = holdBandS.substr(1, (holdBandS.find('/')-1));
                    for (unsigned int d = 0; d < born.size(); d++){
                        //cout << born[d];
                        if (born[d] == '9'){
                           cerr << "Incorrect input " << born[d] << "   " << argv[0] << '\n';
                            exit(0); 
                        }
                        if(born != "" && isdigit(born[d])){
                            bornv = stoi(born);
                        }
                        else{
                            cerr << "Incorrect input " << born[d] << "   " << argv[0] << '\n';
                            exit(0);
                        }
                    }
                    survive = holdBandS.substr((holdBandS.find('/'))+2);
                    for (unsigned int g = 0; g < survive.size(); g++){
                        //cout << survive[g];
                        if (survive[g] == '9'){
                           cerr << "Incorrect input " << survive[g] << "   " << argv[0] << '\n';
                            exit(0); 
                        }
                        if (survive != "" && isdigit(survive[g])){
                            survivev = stoi(survive);
                        }
                        else{
                            cerr << "Incorrect input " << survive[g] << "  " << argv[0] << '\n';
                            exit(0);
                        }
                    }
                    // check if input is B/S123
                    if(holdBandS[0] == 'B' && holdBandS[1] == '/' && holdBandS[2] == 'S' && holdBandS.size() > 3){
                        noborn = true; 
                        for (unsigned int h = 0; h < survive.size()-1; h++){
                            if((survive[h] < survive[h+1]) && !(survive.find("9") < survive.size()) && (survive.size() <= 9)){
                                continue;
                            }
                            else{
                                cerr << "Bval or Sval are invalid input(s) " << argv[0] << '\n';
                                exit(0);
                            }
                        }
                    }
                    //check if input is B123/S
                    else if (holdBandS[0] == 'B' && holdBandS[1] != '/' && survive == ""){
                        nosurvive = true;
                        for (unsigned int g = 0; g < born.size()-1; g++){
                            if((born[g] < born[g+1]) && !(born.find("9") < born.size()) && born.size() <= 9){
                                continue;
                            }
                            else{
                                cerr << "Bval or Sval are invalid input(s) " << argv[0] << '\n';
                                exit(0);
                            }
                        }
                    } 
                    else{
                        for (unsigned int g = 0; g < born.size()-1; g++){
                            if((born[g] < born[g+1]) && !(born.find("9") < born.size()) && born.size() <= 9){
                                continue;
                            }
                            else{
                                cerr << "Bval or Sval are invalid input(s) " << argv[0] << '\n';
                                exit(0);
                            }
                        }
                        for (unsigned int h = 0; h < survive.size()-1; h++){
                            //cout << survive[h] << '\n';
                            if((survive[h] < survive[h+1]) && !(survive.find("9") < survive.size()) && (survive.size() <= 9)){
                                continue;
                            }
                            else{
                                cerr << "Bval or Sval are invalid input(s) " << argv[0] << '\n';
                                exit(0);
                            }
                        }
                    }
                }
                else{
                    cerr << "Bval or Sval are invalid input(s) " << argv[0] << '\n';
                    exit(0);
                }
                gseen = true;
                }
                break;
            case ':':
                cerr << "That is an invalid option, can only have -i, -g, -l, -d. This is the invalid option: " << argv[optind-1] << "  " << argv[0] << '\n';
                break;
            case '?':
                cerr << "That is an invalid option, can only have -i, -g, -l, -d. This is the invalid option: " << argv[optind-1] << "  " << argv[0] << '\n';
                exit(0);
                break;
            default:
                cerr << "There is an error reading in the command " << argv[0] << '\n';
                exit(0);
                break;
        }
    }
    
    if(argv[optind] != NULL){
            ifstream in (argv[optind]);
            if(!in){
                cerr << "Error reading in standard file " << argv[argc-1] << " " << argv[0] << '\n';
                exit(0);
            }
            while(getline(in, data)){
                columns = data.length();
                if ((somecolumn != columns) && (rows != 0)){
                    cerr << "The lines are incorrect, change the input. " << "Error in input. " << argv[0] << '\n';
                    return 0;
                }
                somecolumn = columns;
                filedata += data;
                rows++;
            }
            
            //cout << "test reading input from initial filename " << filedata << '\n'; 
        }

        // read the initial state from standard input
    else{
        
            while(getline(cin, data)){
                columns = data.length();
                if((somecolumn != columns) && (rows != 0)){
                    cerr << "The lines are incorrect, change the input. " << "Error in " << argv[0] << '\n';
                    return 0;
                }
                somecolumn = columns;
                filedata += data;
                rows++;
                
            }
        }
 
    // check not enough row and columns to play the game
    if(rows < 2 || columns < 2){
        cerr << "Can't play Conway game because there are not enough rows and/or columns " << argv[0] << '\n';
        return 0;
    }

        //create a vector and get each character from the string, . is dead, O is alive
        vector<vector<char> > myvector(rows, vector<char>(columns));
        int myint = 0;
        char mychar;
        for (int i = 0; i < rows; i++){
            for (int j = 0; j < columns; j++){
                mychar = filedata.at(myint);
                if(mychar == dead){
                    myvector[i][j] = dead;
                }
                else if (mychar == alive){
                    myvector[i][j] = alive;
                }
                else{
                    cerr << "Wrong character input " << argv[0] << '\n';
                    return 0;
                }
                myint++;
            }
        }
        do{
        // find the number of neighbors that are alive and count how many are alive for each 
        vector<vector<char> > newvector(rows, vector<char>(columns));
        for (int i = 0; i < rows; i++){
            for (int j = 0; j < columns; j++){
                int num = 0;
                // neighbor 1 down left
                if ((myvector[((i + 1) % rows)][((j + (columns - 1)) % columns)] == alive)){
                    num++;
                }
                // neighbor 2 down 
                if ((myvector[((i + 1) % rows)][(j)] == alive)){
                    num++;
                }
                // neighbor 3 down right 
                if ((myvector[((i + 1) % rows)][((j + 1) % columns)] == alive)){
                    num++;
                }
                // neighbor 4 up left
                if ((myvector[((i + (rows - 1)) % rows)][((j + (columns - 1)) % columns)] == alive)){
                    num++;
                }
                // neighbor 5 up 
                if ((myvector[((i + (rows - 1)) % rows)][(j % columns)] == alive)){
                    num++;
                }
                //neighbor 6 up right
                if ((myvector[((i + (rows - 1)) % rows)][((j + 1) % columns)] == alive)){
                    num++;
                }   
                //neighbor 7 left
                if ((myvector[(i)][((j + (columns - 1)) % columns)] == alive)){
                    num++;
                }
                // neighbor 8 right
                if ((myvector[(i)][((j + 1) % columns)] == alive)){
                    num++;
                }

                if (optind + 1 < argc){
                    cerr << "Incorrect input " << argv[0] << '\n';
                    exit(0);
                }

                // Rules for the Next Generation
                // live cell default
                // do these if there is no -g
                if (goption == false){
                    // live cell any character
                    if (myvector[i][j] == alive){
                        if(num == 2 || num == 3){
                            newvector[i][j] = alive;
                        }
                        else{
                            newvector[i][j] = dead;
                        }
                    }
                    // dead cell any character
                    else if(myvector[i][j] == dead){
                        if(num == 3){
                            newvector[i][j] = alive;
                        }
                        else{
                            newvector[i][j] = dead;
                        } 
                    }
                    //dead default
                    else{
                        cerr << "Error with number of alive and dead neighbors" << argv[0] << '\n';
                    }
                }
                else{
                    //check B/S input
                    if (checkbs == true){
                        newvector[i][j] = dead;
                        continue;
                    }
                    if (myvector[i][j] == alive){
                        if (num == 0 && checkzero == true){
                            newvector[i][j] = alive;
                            continue;
                        }
                        if(nosurvive == true){
                            newvector[i][j] = dead;
                            continue;
                        }
                        if ((num == 0) && (survivev == 0)){
                            newvector[i][j] = alive;
                            continue;
                        }
                        for (int b = survivev; b > 0; b/=10){
                            //cout << "   WHATS IN B % 10   " << (b % 10) << '\n';
                                if(num == (b % 10)){
                                    //cout << "test" << '\n';
                                    newvector[i][j] = alive;
                                    break;
                                }
                                else{
                                    newvector[i][j] = dead;
                                }
                        }
                    }
                        else if(myvector[i][j] == dead){
                            if (num == 0 && checkzero == true){
                                newvector[i][j] = alive;
                                continue;
                            }
                            if (noborn == true){
                                newvector[i][j] = dead;
                                continue;
                            }
                            if ((num == 0) && (bornv == 0)){
                                newvector[i][j] = alive;
                                continue;
                            }
                            for (int f = bornv; f > 0; f/=10){
                                //cout << "   WHATS IN F % 10   " << (f % 10) << '\n';
                                if(num == (f % 10)){
                                    newvector[i][j] = alive;
                                    break;
                                }
                                else{
                                    newvector[i][j] = dead;
                                } 
                            }
                        }
                        else{
                            cerr << "Error with number of alive and dead neighbors" << argv[0] << '\n';
                    }
                }
            }
        }
   
    // print next generation
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++){
            cout << newvector[i][j];
        }
        cout << '\n';
    }
    if (inf){
        cout << '\n';
        myvector = newvector;
    }
        }while(inf);
    return 0;
}
    
    
    
    
