// This program aims to read in the contents of a set of data into three arrays which represents scores on three separate exams.
// Language: C++
// The program will neatly print into an output file the original data and then compute a weighted average of the scores and print that average.
// Then the program will find the smallest score on each exam and it's position within the array.

/* data.txt contents for reference (data.txt included)
 
 90 75 95
 75 80 85
 65 70 90
 85 90 95
 60 65 70
 70 75 80
 80 85 55
 95 60 75
 65 70 75
 70 85 90
 75 85 90
 80 90 95
 90 95 55
 75 80 90
 65 80 95
 75 85 90
 80 90 95
 55 95 65
 75 80 90
 65 80 95
 
 */

// I added some additional parameters to the functions in the use of ofstream& outFile since I was having issues with letting the functions. (maintly the print1array and findsmallestandpos functions printing their results into the output file)

// Sources: ChatGPT for error checking in the event that my build fails and general questions such as file writing

#include <iostream>
#include <fstream> // fstream is required for file operation in C++
#include <string> // ensures that the program knows about the std::string class and it's methods.

using namespace std;

// Function Prototypes (I use ofstream& to handle file writing and direct outputs to the output file rather than the terminal)
void read3arrays(double[], double[], double[], int, ofstream&);
void print1array(double[], int, ofstream&);
void makeweightedavg(double[], double[], double[], int, double[], ofstream&);
void findsmallestandpos(double[], int, double &, double &, ofstream&);

int main(){

    // Defining our 3 arrays (exams 1, 2, and 3) (minimum of 20 columns)
    double exam1[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    double exam2[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    double exam3[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    double weighted_averages[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    
    // Creating the external file which will be our output of data gathered from the functions below.
    // Done for the purpose of my own personal machine, if you wish to run the code change this route accordingly.
    ofstream outFile("/Users/danielandrews/Desktop/CIS 3100 HW #2/output.txt");
    
    // Checking if outFile is opened and if so running all of the functions defined and printing them into the file.
    if(outFile.is_open()) {
        
        // Calling upon our read3arrays function
        read3arrays(exam1, exam2, exam3, 20, outFile);
        
        // Printing the arrays for exams 1-3
        outFile << "Exam 1 Grades: " << endl;
        print1array(exam1, 20, outFile); // k will be equal to 20 as we want to print out each value into our terminal (endl; after 6 values)
        
        // Spaces added for guidelines and readability
        outFile << endl;
        outFile << endl;
        
        outFile << "Exam 2 Grades: " << endl;
        print1array(exam2, 20, outFile);
        
        outFile << endl;
        outFile << endl;
        
        outFile << "Exam 3 Grades: " << endl;
        print1array(exam3, 20, outFile);
        
        outFile << endl;
        outFile << endl;
        
        // Filling in our weighted_averages array
        makeweightedavg(exam1, exam2, exam3, 20, weighted_averages, outFile);
        
        // Printing the weighted averages array for exams 1-3
        outFile << "Weighted Averages: " << endl;
        print1array(weighted_averages, 20, outFile);
        
        outFile << endl;
        outFile << endl;
        
        double smallest;
        double position;
        
        // Finding Smallest Value and Position in Exam 1 Array
        findsmallestandpos(exam1, 20, smallest, position, outFile);
        
        outFile << "The lowest grade in exam 1 is " << smallest << " at position " << position << endl;
        
        outFile << endl;
        outFile << endl;
        
        // Finding Smallest Value and Position in Exam 2 Array
        findsmallestandpos(exam2, 20, smallest, position, outFile);
        
        outFile << "The lowest grade in exam 2 is " << smallest << " at position " << position << endl;
        
        outFile << endl;
        outFile << endl;
 
        // Finding Smallest Value and Position in Exam 3 Array
        findsmallestandpos(exam3, 20, smallest, position, outFile);
        
        outFile << "The lowest grade in exam 3 is " << smallest << " at position " << position << endl;
        
        //Closing File afterwards
        outFile.close();
    }

    else{
        // If file is not opened give an error in the terminal
        cout << "Unable to open file" << endl;
    }
    
    return 0;
}

// This will be our read3arrays function which serves the purpose of reading a set of data into three arrays
// It possesses the parameters of exams 1-3 which along with k which represents the size of these arrays
void read3arrays(double array1[], double array2[], double array3[], int k, ofstream& outFile){ // Using & reference parameter so changes are recorded in the main function.

    // When bringing data into the program use ifstream
    // Because this is the route to my exams.txt data, I will be using this specificly for my device.
    ifstream inFile("/Users/danielandrews/Desktop/CIS 3100 HW #2/exams.txt");
    // I've included the file of exams.txt in the folder, please feel free to adjust this route to match your device if you wish to run the code.

    // Attempting to open file
    // In case there are any issues opening the file this will help let the user know there was an error
    // ! = not
    if(!inFile){
        cout << "Unable to open file for reading" << endl;
    }
    
    // Creation of variables
    int exam_one_grades, exam_two_grades, exam_three_grades; // first, second, and third column

    // While loop keeps running as long as you're able to read data into the program
    for(int i = 0; i < k; i++){
        while(inFile >> exam_one_grades >> exam_two_grades >> exam_three_grades){
            // printing exam grades as they are added to the array as specified in instructions
            cout << exam_one_grades << " added to exam 1" << endl;
            array1[i] = exam_one_grades;
            cout << exam_two_grades << " added to exam 2" << endl;
            array2[i] = exam_two_grades;
            cout << exam_three_grades << " added to exam 3" << endl;
            array3[i] = exam_three_grades;
            break;
        };
    }
    
    inFile.close(); // Closing file after the end of the function to ensure security
    
    return;
}

// This will be our read1array function which serves the purpose of printing the elements of the nums array neatly. Will print 6 elements per line before a space is called.
void print1array(double nums[], int k, ofstream& outFile){ // Using & reference parameter so changes are recorded in the main function.
    
    // prints out elements of array
    for(int i = 0; i < k; i++){
        outFile << nums[i] << " ";
        // After 6 numbers of the array are printed it will then call an endl; (sourced from ChatGPT when asked how to go about ending the line after 6 values are called)
        if ((i + 1) % 6 == 0 and i != k - 1){
            outFile << endl;
        }
    }
    outFile << endl;
    return;
}

// This will be our makeweightedavd function which takes values within the three exams and finds the weighted average.
void makeweightedavg(double array1[], double array2[], double array3[], int k, double averages[], ofstream& outFile){ // Using & reference parameter so changes are recorded in the main function.

    for(int i = 0; i < k; i++){
        // calling and keeping variables 0 after each loop
        double sum1 = 0; // sum of array1[i]*1
        double sum2 = 0; // sum of array2[i]*2
        double sum3 = 0; // sum of array3[i]*3
        double total_sum = 0; // sum of sum1, sum2, sum3
        double weighted_avg_value = 0;
        sum1 = array1[i] * 1;
        sum2 = array2[i] * 2;
        sum3 = array3[i] * 3;
        total_sum = sum1+sum2+sum3;
        weighted_avg_value = total_sum/k; // diving total sum by k (total amount of contents within array)
        averages[i] = weighted_avg_value; // adding weighted_avg_value to the averages array
    }
        
    return;
}

// This will be out findsmallestandpos function which will return the element in the array which is the smallest and position in the array of that smallest element.
void findsmallestandpos(double array1[], int k, double &smallest, double &location, ofstream& outFile){ // Using & reference parameter so changes are recorded in the main function.
    
    // Smallest value in array (starting with index 0 of array to avoid 0 being called as smallest)
    smallest = array1[0];
    // Position in array of smallest value
    location = 0;
    
    // For loop which will find the smallest value within the array and as well as the position
    for(int i = 0; i < k; i++){
        if(array1[i] <= smallest){
            smallest = array1[i];
            location = i;
        }
    }

    return;
}

