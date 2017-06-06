// STD Headers
#include <fstream>  // Input/output stream class to operate on files
#include <sstream>  // Stream class to operate on strings.
#include <iostream> // Standard Input / Output Streams Library
#include <string>   // Introduces string types
#include <vector>   // Introduces vector types
#include <cmath>    // Used for cmath::lround
#include <cassert>  // std::assert

using namespace std;

// Function for parsing the input file
vector<vector<string>> parseCSV (ifstream &ifile){

    // Variables for storaging input file
    string line;    
    vector<vector<string>> values;

    // Check that file is OK
    if(ifile.good()){
    // Parse and store input file
        while(getline(ifile, line)){

            string cell;
            vector<string> line_values;
            stringstream lineStream(line);

            while(getline(lineStream, cell, ',') || getline(lineStream, cell, ' ')){

                line_values.push_back(cell);

            }

            values.emplace_back(line_values);

        }
    }

    return values;
}

// Function for fixing the data and write it to a file
void fixAndSave (const vector<vector<string>> &data, const int &k, ofstream &ofile){

    vector<vector<string>> values = data;

    // Check errors and save to output file
    for(unsigned int i = 0; i < values.size(); i++){
        for(unsigned int j = 0; j < values[i].size(); j++){

            // If there is an error, interpolate its value with its k-neighbors
            if (strtof(values[i][j].c_str(),0) == 0) {

                float interp = 0;
                uint8_t n = 0;

                for(char u = -k; u <= k; u++){
                    for(char v = -k; v <= k; v++){
                        if( (u != 0) && (v != 0) && 
                            (i+u >= 0) && (j+v >= 0) && 
                            (i+u <= values.size()-1) && (j+v <= values.size()-1)){

                                interp += strtof(values[i+u][j+v].c_str(),0);
                                n++;

                        }
                    }
                }

                values[i][j] = to_string(lround(interp/n));

            }
            
            // Save the data in the output file
            if (j == values.size()-1)
                ofile << values[i][j] << endl;
            else
                ofile << values[i][j] << ",";
        }
    }
    // Close the file
    ofile.close();
}

// Function for checking input arguments
bool checkArgs(const int &argc, char* argv[]){

    // Check number of arguments
    if (argc != 3){
        // Print usage info
        std::cerr << "\n\n\tUsage: " << argv[0] << " <input>" << " <output>\n\n" << std::endl;
        return false;
    }
    return true;
}

// Main Function
int main(int argc, char* argv[])
{
    // Arguments check
	assert(checkArgs(argc, argv));

    // Files paths
    const char* const ipath = argv[1];
    const char* const opath = argv[2];

    // Input / Output files
    ifstream ifile(ipath);
    ofstream ofile(opath);
    
    // k neighbors for interpolation
    uint8_t k = 1;

    // Variable for storaging the parsed input file
    vector<vector<string>> values = parseCSV(ifile);

    // Check errors, interpolate them and save to file
    fixAndSave(values, k, ofile);


    return 0;
}