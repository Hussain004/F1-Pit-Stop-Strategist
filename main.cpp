#include <iostream> // for input and output
#include <string> // for string manipulation
#include <fstream> // for file handling
#include <cstdlib> // for string to double conversion
#include <unistd.h> // for sleep function
#include "termcolor.hpp" // for coloured text

using namespace std;
using namespace termcolor;

// structure to hold data relating to the car
struct Car {
    string name; // name of the car
    double pace; // pace of the car
    int downforce; // downforce level of the car
};

// structure to hold data relating to the track
struct Circuit {
    string name; // name of the track as entered by the user
    int laps; // total number of laps
    string surface; // abrasion level of the track
    double temperature; // temperature of the track as entered by the user
    double length; // length of the track
    string title; // title of the track
};


// function declarations
void ReadTrackData(Circuit & User_Track, int & line);  // reads the track data from the file
void ReadCarData(Car & User_Car, int & line, string * team);  // reads the car data from the file
void RaceInformation(Circuit & User_Track);  // displays information regarding the circuit
double CalculateTyreDegred(Circuit & User_Track, Car & User_Car, string * tyres, int index);  // calculates the tyre degredation
double CalculateLapTime(double tyredegred, double lap_time);  // calculates the lap time
int ChooseBestTyre(string * tyres, int remaining_laps, int tyre_index, int pit_count);  // chooses the best tyre to use
void DisplayStrategy(string tyre1, string tyre2, string tyre3, string tyre4, int stint1, int stint2, int stint3, int stint4, int pit_count);  // displays the strategy
void SimulateRace(Circuit & User_Track, Car & User_Car, string * tyres, int tyre_index);  // function to simulate the whole race (dry)
void RainStrategy (Circuit & User_Track, Car & User_Car, string * tyres);  // function to simulate the whole race (rain)
void DisplayLights();  // displays the lights (just for fun)


int main() {

    string Compounds[2][5] = {{"Soft","Medium","Hard","Intermediate","Wet"},
                              { "20",   "30",   "40",     "30",      "40"}};
    string * tyre = &Compounds[0][0];

    string Constructors[10] = {"Red Bull", "Ferrari", "Mercedes", "McLaren", "Aston Martin", "Alpine", "Williams", "Alpha Tauri", "Alpha Romeo", "Haas"};
    string * team = &Constructors[0];

    int line = 0;
    bool rain = false;

    Circuit User_Track;
    Car User_Car;
    system("cls"); // clears the screen
    cout << red << on_red << "_|_|_|_|" << reset << "                                              " << red << on_red << "_|" << reset << "                  " << red << on_red << "_|"  << reset << endl; 
    cout << red << on_red << "_|" << reset << "        " << red << on_red << "_|_|" << reset << "    " << red << on_red << "_|" << reset << "  "<< red << on_red << "_|_|" << reset << "  " << red << on_red << "_|_|_|" << reset << "  "<< red << on_red << "_|_|" << reset << "    " << red << on_red << "_|" << reset << "    "<< red << on_red << "_|" << reset << "  " << red << on_red << "_|" << reset << "    "<< red << on_red << "_|_|_|" << reset << "      " << red << on_red << "_|_|"  << reset << endl; 
    cout << red << on_red << "_|_|_|" << reset << "  " << red << on_red << "_|" << reset << "    " << red << on_red << "_|" << reset << "  " << red << on_red << "_|_|" << reset << "      " << red << on_red << "_|" << reset << "    " << red << on_red << "_|" << reset << "    "<< red << on_red << "_|" << reset << "  " << red << on_red << "_|" << reset << "    " << red << on_red << "_|" << reset << "  "<< red << on_red << "_|" << reset << "  " << red << on_red << "_|" << reset << "    " << red << on_red << "_|" << reset << "        " << red << on_red << "_|"  << reset << endl; 
    cout << red << on_red << "_|" << reset << "      " << red << on_red << "_|" << reset << "    " << red << on_red << "_|" << reset << "  " << red << on_red << "_|" << reset << "        " << red << on_red << "_|" << reset << "    " << red << on_red << "_|" << reset << "    " << red << on_red << "_|" << reset << "  " << red << on_red << "_|" << reset << "    " << red << on_red << "_|" << reset << "  " << red << on_red << "_|" << reset << "  " << red << on_red << "_|" << reset << "    " << red << on_red << "_|" << reset << "        " << red << on_red << "_|" << reset << endl;  
    cout << red << on_red << "_|" << reset << "        " << red << on_red << "_|_|" << reset << "    " << red << on_red << "_|" << reset << "        " << red << on_red << "_|" << reset << "    " << red << on_red << "_|" << reset << "    " << red << on_red << "_|" << reset << "    " << red << on_red << "_|_|_|" << reset << "  " << red << on_red << "_|" << reset << "    " << red << on_red << "_|_|_|" << reset << "        " << red << on_red << "_|" << reset << endl;  

    cout << "\n\n                       " << bold << blue << "F1 Pit Strategy Calculator\n" << reset;
    cout << "                                " << bold << blue << "Welcome!\n" << reset;
    cout << "                           " << bold << blue << "Ready for the race?\n\n\n" << reset;

    system("pause"); // pauses the program until the user presses a key
    system("cls"); // clears the screen

    DisplayLights(); // displays the starting lights

    cout << underline << "2023 FIA FORMULA ONE WORLD CHAMPIONSHIP RACE CALENDAR: \n\n" << reset;
    cout << "1. Bahrain Grand Prix (Bahrain) \n";
    cout << "2. Saudi Arabian Grand Prix (Jeddah) \n";
    cout << "3. Australian Grand Prix (Melbourne) \n";
    cout << "4. Azerbaijan Grand Prix (Azerbaijan) \n";
    cout << "5. Miami Grand Prix (Miami) \n";
    cout << "6. Emilia Romagna Grand Prix (Imola) \n";
    cout << "7. Monaco Grand Prix (Monte Carlo) \n";
    cout << "8. Spanish Grand Prix (Barecelona) \n";
    cout << "9. Canadian Grand Prix (Montreal) \n";
    cout << "10. Austrian Grand Prix (Spielberg) \n";
    cout << "11. British Grand Prix (England) \n";
    cout << "12. Hungarian Grand Prix (Budapest) \n";
    cout << "13. Belgian Grand Prix (Belgium) \n";
    cout << "14. Dutch Grand Prix (Netherlands) \n";
    cout << "15. Italian Grand Prix (Monza) \n";
    cout << "16. Singapore Grand Prix (Singapore) \n";
    cout << "17. Japanese Grand Prix (Japan) \n";
    cout << "18. Qatar Grand Prix (Qatar) \n";
    cout << "19. United States Grand Prix (Austin) \n";
    cout << "20. Mexican Grand Prix (Mexico) \n";
    cout << "21. Brazilian Grand Prix (Brazil) \n";
    cout << "22. Las Vegas Grand Prix (Las Vegas) \n";
    cout << "23. Abu Dhabi Grand Prix (Abu Dhabi) \n";
    cout << "\nWhere are we heading? \n";
    getline (cin,User_Track.name);
    ReadTrackData(User_Track, line); // reads the track data from the file
    system("cls"); // clears the screen

    cout << underline << "FORMULA ONE RACING TEAMS 2023: \n\n" << reset;
    cout << blue << "1. Red Bull \n" << reset;
    cout << red << "2. Ferrari \n" << reset;
    cout << grey << "3. Mercedes \n" << reset;
    cout << yellow << "4. McLaren \n" << reset;
    cout << green << "5. Aston Martin \n" << reset;
    cout << cyan << "6. Alpine \n" << reset;
    cout << blue << "7. Williams \n" << reset;
    cout << magenta << "8. Alpha Tauri \n" << reset;
    cout << red << "9. Alfa Romeo \n" << reset;
    cout << white << "10. Haas \n" << reset;
    cout << "\nWhich team are you? \n";
    getline (cin,User_Car.name); 
    ReadCarData(User_Car, line, team); // reads the car data from the file
    system("cls"); // clears the screen

    RaceInformation(User_Track); // displays information regarding the circuit

    bool correct = false;
    while (correct == false) {
        cout << "Enter track temperature: ";
        cin >> User_Track.temperature;
            if (User_Track.temperature > 0 && User_Track.temperature < 50) {
                correct = true;
            }
            else {
                cout << "Invalid temperature value. Try again. \n";
            }
    }

    cout << "\nKeeping in mind the track details, let's setup our car for this track! \n";
    cout << "Setting up the right amount of downforce is crucial for each track. Do you wish to know more about downforce before we move on? \n(Yes/No): ";
    string reply;
    cin >> reply;

    correct = false;
    // input validation
    while (correct == false) {
        if (reply == "Yes" || reply == "No") {
            correct = true;
        }
        else {
            cout << "Invalid input. Try again. \n";
            cin >> reply;
        }
    }

    if (reply == "Yes") {
        cout << "Downforce is the vertical component of the aerodynamic force acting on a car. When you reduce the downforce levels, \nthe car has less grip on the corners but is much faster down the straights. On the other hand, \nwhen you increase the downforce levels, the car will have more grip on the corners but will be much slower down the straights. \nAlmost as if a parachute is attached to the car. \n";
    }

    correct = false;
    // input validation
    while (correct == false) {
        cout << "\nHow much downforce should the car have? (1-5): ";
        cin >> User_Car.downforce;
            if (User_Car.downforce >= 1 && User_Car.downforce <= 5) {
                correct = true;
            }
            else {
                cout << "Invalid downforce value, it should be between 1 and 5. Try again. \n";
            }
    }

    cout << "\nNow that our car is set up, let's head on over to the track. \n";

    correct = false;
    // input validation
    while (correct == false) {
        cout << "Is it forecasted to rain today? (Yes/No): ";
        cin >> reply;
            if (reply == "Yes" || reply == "No") {
                correct = true;
            }
            else {
                cout << "Invalid input. Try again. \n";
            }
    }

    system("cls"); // clears the screen

    if (reply == "Yes" || reply == "yes") {
        rain = true;
    }
    else {
        rain = false;
    }

    if (rain == false) {
        system("cls");  // clears the screen
        cout << underline << "Strategy #1: \n" << reset;
        cout << "Started the race with " << red <<  "Soft" << reset << " tyres. \n";
        SimulateRace(User_Track, User_Car, tyre, 0);
        cout << underline << "\nStrategy #2: \n" << reset;
        cout << "Started the race with " << yellow << "Medium" << reset << " tyres. \n";
        SimulateRace(User_Track, User_Car, tyre, 1);
        cout << underline << "\nStrategy #3: \n" << reset;
        cout << "Started the race with " << white << "Hard" << reset << " tyres. \n";
        SimulateRace(User_Track, User_Car, tyre, 2);
    }
    else if (rain == true) {
        RainStrategy(User_Track, User_Car, tyre);
    }

    sleep(10);

    return 0;
}

// function to read the track data from the file
void ReadTrackData(Circuit & User_Track, int & line) {

    bool found = false;
    string search = "";

    // searching for the track name in the file
    do {

        ifstream TrackInfo("TrackDetails.txt"); // opening the file
        string file_line;

        for (int a = 1; a <= 23 && found == false; a++) {

            getline(TrackInfo,file_line);

            // extracting track name from the file
            for (int b = 0; file_line.substr(b+1,1) != "&"; b++) {
                search = search + file_line.substr(b,1);
            }

            // if the track name is found in the file, then the loop will stop
            if (search == User_Track.name) {
                found = true;
                line = a;
            }

            search = "";

        }

        // if the track name is not found in the file, then the user will be asked to input the name again
        if (found == false) {
            cout << "The circuit you entered doesn't exist in the F1 2023 calendar. Input the name again: ";
            getline (cin,User_Track.name);
        }

        TrackInfo.close(); // closing the file
        
    } while (found == false);


    ifstream TrackInfo("TrackDetails.txt");
    string file_line;

    // the loop will stop when the line of the file is the same as the line of the track name
    for (int d = 1; d <= line; d++) {
        getline(TrackInfo,file_line);
    }

    int count = 0;
    string data = "";

    // reading the line from the file
    for (int e = 0; e < file_line.length(); e++) {

        if (file_line.substr(e,1) == "&") {
            data = "";
            count = count + 1;
            continue;
        }

        data = data + file_line.substr(e,1);

        // extracting track surface from the file
        if (file_line.substr(e+1,1) == "&" && count == 1) {
            User_Track.surface = data;
        }
        // extracting track length from the file
        else if (file_line.substr(e+1,1) == "&" && count == 2) {
            User_Track.length = stod(data);
        }
        // extracting total laps from the file
        else if (file_line.substr(e+1,1) == "&" && count == 3) {
            User_Track.laps = stoi(data);
        }
        // extracting track title from the file
        else if (e == file_line.length() - 1) {
            User_Track.title = data;
        }
    }
}

// function to read the car data from the file
void ReadCarData(Car & User_Car, int & line, string * team) {

    bool found = false;

    do {
        
        // checking if the car name is in the list of cars
        for (int a = 0; a < 10 && found == false; a++) {
            if (*(team+a) == User_Car.name) {
                found = true;
            }
        }

        // if the car name is not found in the list of cars, then the user will be asked to input the name again
        if (found == false) {
            cout << "The car you entered doesn't exist in F1 2023. Input the name again: ";
            getline (cin,User_Car.name);
        }

    } while (found == false);

    int position = 0;

    // finding the position of the car name in the list of cars
    for (int b = 0; b < 10; b++) {
        if (*(team+b) == User_Car.name) {
            position = b;
            break;
        }
    }

    ifstream CarInfo("CarDetails.txt");
    string file_line;

    // the loop will stop when the line of the file is the same as the line of the car name
    for (int a = 1; a <= line; a++) {
        getline(CarInfo,file_line);
    }

    int count = 0;
    string data = "";

    for (int c = 0; c < file_line.length() - 1; c++) {
            
        if (file_line.substr(c,1) == "&") {
            data = "";
            count = count + 1;
            continue;
        }

        // extracting car pace from the file
        if (file_line.substr(c+1,1) == "&" && count == position) {
            User_Car.pace = stod(data);
        }

        data = data + file_line.substr(c,1);
    }


}

// displays information regarding the circuit
void RaceInformation(Circuit & User_Track) {
    cout << underline << "Welcome to " << User_Track.title << "!" << reset << endl;
    cout << endl;
    cout << "Track Abrasion Level: " << User_Track.surface << endl;
    cout << "Track Length: " << User_Track.length << " km" << endl;
    cout << "Total Laps: " << User_Track.laps << endl;
    cout << endl;
}

// function to calculate the tyre degredation
double CalculateTyreDegred(Circuit & User_Track, Car & User_Car, string * tyres, int index) {
    
        double degred = 0;
        double lap_diff = 2.5;
        string tyre_type = *(tyres+index);

        // calculating tyre degredation based on the tyre type
        if (tyre_type == "Soft") {
            degred = degred + 0.57;
        }
        else if (tyre_type == "Medium") {
            degred = degred + 0.37;
        }
        else if (tyre_type == "Hard") {
            degred = degred + 0.17;
        }
        else if (tyre_type == "Intermediate") {
            degred = degred + 0.30;
        }
        else if (tyre_type == "Wet") {
            degred = degred + 0.15;
        }
 
        // calculating tyre degredation based on the track temperature
        if (User_Track.temperature >= 40.0) {
            degred = degred + 0.005;
        }
        else if (User_Track.temperature >= 30.0 && User_Track.temperature < 40.0) {
            degred = degred + 0.004;
        }
        else if (User_Track.temperature >= 20.0 && User_Track.temperature < 30.0) {
            degred = degred + 0.003;
        }
        else if (User_Track.temperature >= 10.0 && User_Track.temperature < 20.0) {
            degred = degred + 0.002;
        }
        else if (User_Track.temperature >= 0.0 && User_Track.temperature < 10.0) {
            degred = degred + 0.001;
        }

        // calculating tyre degredation based on the track surface
        if (User_Track.surface == "Extreme") {
            degred = degred + 0.30;
        }
        else if (User_Track.surface == "Very High") {
            degred = degred + 0.25;
        }
        else if (User_Track.surface == "High") {
            degred = degred + 0.10;
        }
        else if (User_Track.surface == "Medium") {
            degred = degred - 0.005;
        }
        else if (User_Track.surface == "Low") {
            degred = degred - 0.05;
        }

        // calculating tyre degredation based on the downforce level
        switch (User_Car.downforce) {
            case 1:
                degred = degred + 0.004;
                break;
            case 2:
                degred = degred + 0.002;
                break;
            case 3:
                degred = degred - 0.002;
                break; 
            case 4:
                degred = degred - 0.004;
                break;
            case 5:
                degred = degred - 0.008;
                break;
        }
    
        return degred;
}

// function to calculate the lap time
double CalculateLapTime(double tyredegred, double lap_time) {
    double current_laptime = 0.0;
    // calculating the current lap time based on the tyre degredation
    current_laptime = lap_time + tyredegred;
    return current_laptime;
}

// function to calcaulate the best tyre to use based on the remaining laps and number of pits done
int ChooseBestTyre(string * tyres, int remaining_laps, int tyre_index, int pit_count) {
    int index = -1;

    if (pit_count > 2) {index = 0;}
    else if (pit_count == 0 || pit_count == 1 || pit_count == 2) {
        if (remaining_laps > 50) {index = 2;}
        else if (remaining_laps >= 45) {index = 1;}
        else if (remaining_laps >= 35 && tyre_index != 2) {index = 2;}
        else if (remaining_laps >= 35 && tyre_index == 2) {index = 1;}
        else if (remaining_laps >= 20 && tyre_index != 1) {index = 1;}
        else if (remaining_laps >= 10) {index = 0;}
        else {index = -1;}
    }

    return index;
}

// function to display the strategy
void DisplayStrategy(string tyre1, string tyre2, string tyre3, string tyre4, int stint1, int stint2, int stint3, int stint4, int pit_count) {
    char block = 219;

    if (tyre1 == "Soft" && pit_count >= 0) {
        for (int a = 0; a < stint1; a++) {cout << red << on_red << block << reset;}
    }
    else if (tyre1 == "Medium" && pit_count >= 0) {
        for (int a = 0; a < stint1; a++) {cout << yellow << on_yellow << block << reset;}
    }
    else if (tyre1 == "Hard" && pit_count >= 0) {
        for (int a = 0; a < stint1; a++) {cout << white << on_white << block << reset;}
    }
    else if (tyre1 == "Intermediate" && pit_count >= 0) {
        for (int a = 0; a < stint1; a++) {cout << green << on_green << block << reset;}
    }
    else if (tyre1 == "Wet" && pit_count >= 0) {
        for (int a = 0; a < stint1; a++) {cout << blue << on_blue << block << reset;}
    }

    if (tyre2 == "Soft" && pit_count >= 1) {
        for (int a = 0; a < stint2; a++) {cout << red << on_red << block << reset;}
    }
    else if (tyre2 == "Medium" && pit_count >= 1) {
        for (int a = 0; a < stint2; a++) {cout << yellow << on_yellow << block << reset;}
    }
    else if (tyre2 == "Hard" && pit_count >= 1) {
        for (int a = 0; a < stint2; a++) {cout << white << on_white << block << reset;}
    }
    else if (tyre2 == "Intermediate" && pit_count >= 1) {
        for (int a = 0; a < stint2; a++) {cout << green << on_green << block << reset;}
    }
    else if (tyre2 == "Wet" && pit_count >= 1) {
        for (int a = 0; a < stint2; a++) {cout << blue << on_blue << block << reset;}
    }

    if (tyre3 == "Soft" && pit_count >= 2) {
        for (int a = 0; a < stint3; a++) {cout << red << on_red << block << reset;}
    }
    else if (tyre3 == "Medium" && pit_count >= 2) {
        for (int a = 0; a < stint3; a++) {cout << yellow << on_yellow << block << reset;}
    }
    else if (tyre3 == "Hard" && pit_count >= 2) {
        for (int a = 0; a < stint3; a++) {cout << white << on_white << block << reset;}
    }
    else if (tyre3 == "Intermediate" && pit_count >= 2) {
        for (int a = 0; a < stint3; a++) {cout << green << on_green << block << reset;}
    }
    else if (tyre3 == "Wet" && pit_count >= 2) {
        for (int a = 0; a < stint3; a++) {cout << blue << on_blue << block << reset;}
    }

    if (tyre4 == "Soft" && pit_count >= 3) {
        for (int a = 0; a < stint4; a++) {cout << red << on_red << block << reset;}
    }
    else if (tyre4 == "Medium" && pit_count >= 3) {
        for (int a = 0; a < stint4; a++) {cout << yellow << on_yellow << block << reset;}
    }
    else if (tyre4 == "Hard" && pit_count >= 3) {
        for (int a = 0; a < stint4; a++) {cout << white << on_white << block << reset;}
    }
    else if (tyre4 == "Intermediate" && pit_count >= 3) {
        for (int a = 0; a < stint4; a++) {cout << green << on_green << block << reset;}
    }
    else if (tyre4 == "Wet" && pit_count >= 3) {
        for (int a = 0; a < stint4; a++) {cout << blue << on_blue << block << reset;}
    }

}

// function to simulate the whole race (dry)
void SimulateRace(Circuit & User_Track, Car & User_Car, string * tyres, int tyre_index) {

    double lap_time = User_Car.pace;   // initial lap time
    double lap_diff = 2.5;  // difference between the lap time and the pit time 
    double tyre_degred = 0.0;  // initial tyre degredation
    int pit_lap = 0;  // number of pits
    int pit_count = 0;  // number of pits done
    int fast_laps = 0;  // number of laps done with no tyre degredation
    int degred_laps = 1; // number of laps done with tyre degredation
    string tyre = *(tyres + tyre_index);
    int life = stoi(*(tyres + tyre_index + 5));  // life of the tyre
    string tyre1, tyre2, tyre3, tyre4;
    int stint1, stint2, stint3, stint4;
    tyre1 = tyre;

    // loop to represent the whole race
    for (int lap = 0; lap < User_Track.laps; lap++) {
        
        if (lap+1 == User_Track.laps && pit_count > 1) {
            stint3 = lap - stint1 - stint2 + 1;
        }
        else if (lap+1 == User_Track.laps) {
            stint2 = lap - stint1 + 1;
        }

        // for the first half of the life of the tyre, it will not degrade
        if (fast_laps < life/2) {
            if (tyre == "Soft") {
                lap_time = lap_time - 0.3;
                fast_laps = fast_laps + 1;
                continue;
            }
            else if (tyre == "Medium") {
                lap_time = lap_time - 0.2;
                fast_laps = fast_laps + 1;
                continue;
            }
            else if (tyre == "Hard") {
                lap_time = lap_time - 0.05;
                fast_laps = fast_laps + 1;
                continue;
            }
        }

        // for the other half of the life of the tyre, it will degrade
        tyre_degred = CalculateTyreDegred(User_Track, User_Car, tyres, tyre_index);
        lap_time = CalculateLapTime(tyre_degred, lap_time);

        if (lap_time >= User_Car.pace + lap_diff) { // time to pit
            pit_lap = lap;
            tyre_index = ChooseBestTyre(tyres, User_Track.laps - lap, tyre_index, pit_count);
            if (tyre_index == -1) { //  if only a few laps left then do not pit
                continue;
            }
            pit_count = pit_count + 1;
            if (pit_count == 1) {
                stint1 = lap;
                tyre2 = *(tyres + tyre_index);
            }
            else if (pit_count == 2) {
                stint2 = lap - stint1;
                tyre3 = *(tyres + tyre_index);
            }
            fast_laps = 0;
            degred_laps = 1;
            lap_time = User_Car.pace;
            tyre = *(tyres + tyre_index);
            life = stoi(*(tyres + tyre_index + 5));
            cout << "Pit stop on lap " << pit_lap << " for " << tyre << " tyres." << endl;
        }
        
        degred_laps = degred_laps + 1;

    }
    cout << endl;
    DisplayStrategy(tyre1,tyre2,tyre3,tyre4,stint1,stint2,stint3,stint4,pit_count);
    cout << endl << endl;
}

// function to simulate the whole race (rain)
void RainStrategy (Circuit & User_Track, Car & User_Car, string * tyres) {
    string intensity = ""; // intensity of the rain
    int start = 0; // lap the rain starts
    int end = 0;  // lap the rain ends
    int tyre_index;  // index of the tyre
    double lap_time = User_Car.pace;   // initial lap time
    double lap_diff = 2.5;  // difference between the lap time and the pit time 
    double tyre_degred = 0.0;  // initial tyre degredation
    int pit_lap = 0;  // number of pits
    int pit_count = 0;  // number of pits done
    int fast_laps = 0;  // number of laps done with no tyre degredation
    int degred_laps = 1; // number of laps done with tyre degredation
    string tyre1, tyre2, tyre3, tyre4;
    int stint1, stint2, stint3, stint4;

    bool correct = false;
    // input validation
    do {
        cout << "What is the anticipated intensity of rainfall in the upcoming weather forecast (Heavy or Light): ";
        cin >> intensity;
        if (intensity == "Heavy" || intensity == "Light") 
            {correct = true;}
        else {cout << "Invalid input. Try again. \n";}
    }
    while (correct == false);

    correct = false;
    // input validation
    do {
        cout << "What lap is the rain expected to start: ";
        cin >> start;
        if (start < 1 || start > User_Track.laps) 
            {cout << "Invalid lap number. Try again. \n";}
        else {correct = true;}
    } while (correct == false);
    
    correct = false;
    // input validation
    do {
        cout << "What lap is the rain expected to end: ";
        cin >> end;
        if (end < start || end > User_Track.laps) 
            {cout << "Invalid lap number. Try again. \n";}
        else {correct = true;}
    } while (correct == false);

    // if rain is shortlived then no need to pit for rain tyres
    if (end - start < 5) {
        system("cls");
        cout << underline << "Strategy #1: \n" << reset;
        cout << "Started the race with " << red <<  "Soft" << reset << " tyres. \n";
        SimulateRace(User_Track, User_Car, tyres, 0);
        cout << underline << "\nStrategy #2: \n" << reset;
        cout << "Started the race with " << yellow << "Medium" << reset << " tyres. \n";
        SimulateRace(User_Track, User_Car, tyres, 1);
        cout << underline << "\nStrategy #3: \n" << reset;
        cout << "Started the race with " << white << "Hard" << reset << " tyres. \n";
        SimulateRace(User_Track, User_Car, tyres, 2);
        return;
    }

    system("cls");
    
    if (start > 35) {
        tyre_index = 2;
        cout << "Started the race with Hard tyres." << endl;
    }
    else if (start > 20) {
        tyre_index = 1;
        cout << "Started the race with Medium tyres." << endl;
    }
    else if (start > 5) {
        tyre_index = 0;
        cout << "Started the race with Soft tyres." << endl;
    }
    else if (intensity == "Light") {
        tyre_index = 3;
        cout << "Started the race with Intermediate tyres." << endl;
    }
    else if (intensity == "Heavy") {
        tyre_index = 4;
        cout << "Started the race with Wet tyres." << endl;
    }

    string tyre = *(tyres + tyre_index);  // type of tyre
    int life = stoi(*(tyres + tyre_index + 5));  // life of the tyre
    tyre1 = tyre;
    
    // simulating the race
    for (int lap = 0; lap < User_Track.laps; lap++) {

        // stint calculations
        if (lap+1 == User_Track.laps && pit_count == 3) {
            stint4 = lap - stint1 - stint2 - stint3 + 1;
        }
        else if (lap+1 == User_Track.laps && pit_count == 2) {
            stint3 = lap - stint1 - stint2 + 1;
        }
        else if (lap+1 == User_Track.laps && pit_count == 1) {
            stint2 = lap - stint1 + 1;
        }

        // checking if the rain has started
        if (lap == start - 1) {

            if (intensity == "Heavy" && tyre_index != 4 && tyre_index != 3) { 
                tyre_index = 4; //  if rain is heavy then pit for wet tyres
                tyre = *(tyres + tyre_index);
                pit_count = pit_count + 1;
                cout << "Pit stop on lap " << lap + 1 << " for " << tyre << " tyres." << endl;
            }
            else if (intensity == "Light" && tyre_index != 3 && tyre_index != 4) {
                tyre_index = 3;  // if rain is light then pit for intermediate tyres
                tyre = *(tyres + tyre_index);
                pit_count = pit_count + 1;
                cout << "Pit stop on lap " << lap + 1 << " for " << tyre << " tyres." << endl;
            }

            // stint calculation
            if (pit_count == 1) {
                stint1 = lap;
                tyre2 = *(tyres + tyre_index);
            }
            else if (pit_count == 2) {
                stint2 = lap - stint1;
                tyre3 = *(tyres + tyre_index);
            }
            else if (pit_count == 3) {
                stint3 = lap - stint1 - stint2;
                tyre4 = *(tyres + tyre_index);
            }

            //  during the rain, tyres don't degrade much but are still made to pit because of safety reasons
            for (int rainy_laps = 0; rainy_laps <= end - start; rainy_laps++) {
                lap_time = lap_time + 0.27*User_Car.pace;
                lap++;
                degred_laps = degred_laps + 1;

                if (pit_count > 1 && lap+1 == User_Track.laps) {
                    stint3 = lap - stint1 - stint2;
                }
                else if (pit_count > 0 && lap+1 == User_Track.laps) {
                    stint2 = lap - stint1;
                }

                if (degred_laps >= 30 && end-start-rainy_laps > 5) {

                    cout << "Pit stop on lap " << lap + 1 << " for " << tyre << " tyres." << endl;
                    pit_count = pit_count + 1;

                    if (pit_count == 1) {
                        stint1 = lap;
                        tyre2 = *(tyres + tyre_index);
                    }
                    else if (pit_count > 1 && lap+1 == User_Track.laps) {
                        stint2 = lap - stint1;
                    }
                    else if (pit_count == 2) {
                        stint2 = lap - stint1;
                        tyre3 = *(tyres + tyre_index);
                    }
                    else if (pit_count == 3) {
                        stint3 = lap - stint1 - stint2;
                        tyre4 = *(tyres + tyre_index);
                    }
                    else if (pit_count == 4) {
                        stint4 = lap - stint1 - stint2 - stint3;
                    }

                    degred_laps = 0;
                }
            }
        }

        // for the first half of the life of the tyre, it will not degrade (DRY)
        if (fast_laps < life/2 && tyre_index != 3 && tyre_index != 4) {
            if (tyre == "Soft") {
                lap_time = lap_time - 0.3;
                fast_laps = fast_laps + 1;
                continue;
            }
            else if (tyre == "Medium") {
                lap_time = lap_time - 0.2;
                fast_laps = fast_laps + 1;
                continue;
            }
            else if (tyre == "Hard") {
                lap_time = lap_time - 0.05;
                fast_laps = fast_laps + 1;
                continue;
            }
        }

        // for the other half of the life of the tyre, it will degrade (DRY)
        tyre_degred = CalculateTyreDegred(User_Track, User_Car, tyres, tyre_index);
        lap_time = CalculateLapTime(tyre_degred, lap_time);

        if (lap_time >= User_Car.pace + lap_diff) { //time to pit
            tyre_index = ChooseBestTyre(tyres, User_Track.laps - lap, tyre_index, pit_count);
            if (tyre_index == -1) { //  if only a few laps left then do not pit
                continue;
            }
            pit_lap = lap;
            pit_count = pit_count + 1;
            if (pit_count == 1) {
                stint1 = lap;
                tyre2 = *(tyres + tyre_index);
            }
            else if (pit_count == 2) {
                stint2 = lap - stint1;
                tyre3 = *(tyres + tyre_index);
            }
            else if (pit_count == 3) {
                stint3 = lap - stint1 - stint2;
                tyre4 = *(tyres + tyre_index);
            }
            else if (pit_count == 4) {
                stint4 = lap - stint1 - stint2 - stint3;
            }
            fast_laps = 0;
            degred_laps = 1;
            lap_time = User_Car.pace;
            tyre = *(tyres + tyre_index);
            life = stoi(*(tyres + tyre_index + 5));
            cout << "Pit stop on lap " << pit_lap << " for " << tyre << " tyres." << endl;
        }

        degred_laps = degred_laps + 1; // incrementing the number of laps done with tyre degredation

        // stint calculations
        if (lap == User_Track.laps || lap+1 == User_Track.laps && pit_count > 2) {
            stint4 = lap - stint1 - stint2 - stint3 + 1;
        }
        else if (lap == User_Track.laps || lap+1 == User_Track.laps) {
            stint3 = lap - stint1 - stint2 + 1;
        }


    }

    cout << endl;
    DisplayStrategy(tyre1,tyre2,tyre3,tyre4,stint1,stint2,stint3,stint4,pit_count);
    cout << endl << endl;
}

// displays the starting lights (just for fun)
void DisplayLights() {

    char o = 219;
    cout << red << endl;
    system("cls");

    cout << "    " << o << o << o << o << o << o << o << "    " << "      " << endl;
    cout << "  " << o << o << o << o << o << o << o << o << o << o << o << "  " << "      " << endl;
    cout << o << o << o << o << o << o << o << o << o << o << o << o << o << o << o << "      " << endl;
    cout << o << o << o << o << o << o << o << o << o << o << o << o << o << o << o << "      " << endl;
    cout << "  " << o << o << o << o << o << o << o << o << o << o << o << "  " << "      " << endl;
    cout << "    " << o << o << o << o << o << o << o << "    " << "      " << endl;

    sleep(1);
    system("cls");

    cout << "    " << o << o << o << o << o << o << o << "    " << "      " << "    " << o << o << o << o << o << o << o << "    " << "      " << endl;
    cout << "  " << o << o << o << o << o << o << o << o << o << o << o << "  " << "      " << "  " << o << o << o << o << o << o << o << o << o << o << o << "  " << "      " << endl;
    cout << o << o << o << o << o << o << o << o << o << o << o << o << o << o << o << "      " << o << o << o << o << o << o << o << o << o << o << o << o << o << o << o << "      " << endl;
    cout << o << o << o << o << o << o << o << o << o << o << o << o << o << o << o << "      " << o << o << o << o << o << o << o << o << o << o << o << o << o << o << o << "      " << endl;
    cout << "  " << o << o << o << o << o << o << o << o << o << o << o << "  " << "      " << "  " << o << o << o << o << o << o << o << o << o << o << o << "  " << "      " << endl;
    cout << "    " << o << o << o << o << o << o << o << "    " << "      " << "    " << o << o << o << o << o << o << o << "    " << "      " << endl;

    sleep(1);
    system("cls");

    cout << "    " << o << o << o << o << o << o << o << "    " << "      " << "    " << o << o << o << o << o << o << o << "    " << "      " << "    " << o << o << o << o << o << o << o << "    " << "      " << endl;
    cout << "  " << o << o << o << o << o << o << o << o << o << o << o << "  " << "      " << "  " << o << o << o << o << o << o << o << o << o << o << o << "  " << "      " << "  " << o << o << o << o << o << o << o << o << o << o << o << "  " << "      " << endl;
    cout << o << o << o << o << o << o << o << o << o << o << o << o << o << o << o << "      " << o << o << o << o << o << o << o << o << o << o << o << o << o << o << o << "      " << o << o << o << o << o << o << o << o << o << o << o << o << o << o << o << "      " << endl;
    cout << o << o << o << o << o << o << o << o << o << o << o << o << o << o << o << "      " << o << o << o << o << o << o << o << o << o << o << o << o << o << o << o << "      " << o << o << o << o << o << o << o << o << o << o << o << o << o << o << o << "      " << endl;
    cout << "  " << o << o << o << o << o << o << o << o << o << o << o << "  " << "      " << "  " << o << o << o << o << o << o << o << o << o << o << o << "  " << "      " << "  " << o << o << o << o << o << o << o << o << o << o << o << "  " << "      " << endl;
    cout << "    " << o << o << o << o << o << o << o << "    " << "      " << "    " << o << o << o << o << o << o << o << "    " << "      " << "    " << o << o << o << o << o << o << o << "    " << "      " << endl;

    sleep(1);
    system("cls");

    cout << "    " << o << o << o << o << o << o << o << "    " << "      " << "    " << o << o << o << o << o << o << o << "    " << "      " << "    " << o << o << o << o << o << o << o << "    " << "      " << "    " << o << o << o << o << o << o << o << "    " << "      " << endl;
    cout << "  " << o << o << o << o << o << o << o << o << o << o << o << "  " << "      " << "  " << o << o << o << o << o << o << o << o << o << o << o << "  " << "      " << "  " << o << o << o << o << o << o << o << o << o << o << o << "  " << "      " << "  " << o << o << o << o << o << o << o << o << o << o << o << "  " << "      " << endl;
    cout << o << o << o << o << o << o << o << o << o << o << o << o << o << o << o << "      " << o << o << o << o << o << o << o << o << o << o << o << o << o << o << o << "      " << o << o << o << o << o << o << o << o << o << o << o << o << o << o << o << "      " << o << o << o << o << o << o << o << o << o << o << o << o << o << o << o << "      " << endl;
    cout << o << o << o << o << o << o << o << o << o << o << o << o << o << o << o << "      " << o << o << o << o << o << o << o << o << o << o << o << o << o << o << o << "      " << o << o << o << o << o << o << o << o << o << o << o << o << o << o << o << "      " << o << o << o << o << o << o << o << o << o << o << o << o << o << o << o << "      " << endl;
    cout << "  " << o << o << o << o << o << o << o << o << o << o << o << "  " << "      " << "  " << o << o << o << o << o << o << o << o << o << o << o << "  " << "      " << "  " << o << o << o << o << o << o << o << o << o << o << o << "  " << "      " << "  " << o << o << o << o << o << o << o << o << o << o << o << "  " << "      " << endl;
    cout << "    " << o << o << o << o << o << o << o << "    " << "      " << "    " << o << o << o << o << o << o << o << "    " << "      " << "    " << o << o << o << o << o << o << o << "    " << "      " << "    " << o << o << o << o << o << o << o << "    " << "      " << endl;

    sleep(1);
    system("cls");

    cout << "    " << o << o << o << o << o << o << o << "    " << "      " << "    " << o << o << o << o << o << o << o << "    " << "      " << "    " << o << o << o << o << o << o << o << "    " << "      " << "    " << o << o << o << o << o << o << o << "    " << "      " << "    " << o << o << o << o << o << o << o << "    " << "      " << endl;
    cout << "  " << o << o << o << o << o << o << o << o << o << o << o << "  " << "      " << "  " << o << o << o << o << o << o << o << o << o << o << o << "  " << "      " << "  " << o << o << o << o << o << o << o << o << o << o << o << "  " << "      " << "  " << o << o << o << o << o << o << o << o << o << o << o << "  " << "      " << "  " << o << o << o << o << o << o << o << o << o << o << o << "  " << "      " << endl;
    cout << o << o << o << o << o << o << o << o << o << o << o << o << o << o << o << "      " << o << o << o << o << o << o << o << o << o << o << o << o << o << o << o << "      " << o << o << o << o << o << o << o << o << o << o << o << o << o << o << o << "      " << o << o << o << o << o << o << o << o << o << o << o << o << o << o << o << "      " << o << o << o << o << o << o << o << o << o << o << o << o << o << o << o << "      " << endl;
    cout << o << o << o << o << o << o << o << o << o << o << o << o << o << o << o << "      " << o << o << o << o << o << o << o << o << o << o << o << o << o << o << o << "      " << o << o << o << o << o << o << o << o << o << o << o << o << o << o << o << "      " << o << o << o << o << o << o << o << o << o << o << o << o << o << o << o << "      " << o << o << o << o << o << o << o << o << o << o << o << o << o << o << o << "      " << endl;
    cout << "  " << o << o << o << o << o << o << o << o << o << o << o << "  " << "      " << "  " << o << o << o << o << o << o << o << o << o << o << o << "  " << "      " << "  " << o << o << o << o << o << o << o << o << o << o << o << "  " << "      " << "  " << o << o << o << o << o << o << o << o << o << o << o << "  " << "      " << "  " << o << o << o << o << o << o << o << o << o << o << o << "  " << "      " << endl;
    cout << "    " << o << o << o << o << o << o << o << "    " << "      " << "    " << o << o << o << o << o << o << o << "    " << "      " << "    " << o << o << o << o << o << o << o << "    " << "      " << "    " << o << o << o << o << o << o << o << "    " << "      " << "    " << o << o << o << o << o << o << o << "    " << "      " << endl;
    cout << reset;
    sleep(1);
    system("cls");

    cout << " ___  _________  ________           ___       ___  ________  ___  ___  _________  ________           ________  ___  ___  _________        ________  ________   ________       " << endl;
    cout << "|\\  \\|\\___   ___\\   ___ _\\         |\\  \\     |\\  \\|\\   ____\\|\\  \\|\\  \\|\\___   ___\\\\   ____\\         |\\   __  \\|\\  \\|\\  \\|\\___   ___\\     |\\   __  \\|\\   ___  \\|\\   ___ \\ " << endl;
    cout << "\\ \\  \\|___ \\  \\_\\ \\  \\___|_        \\ \\  \\    \\ \\  \\ \\  \\___|\\ \\  \\\\\\  \\|___ \\  \\_\\ \\  \\___|_        \\ \\  \\|\\  \\ \\  \\\\\\  \\|___ \\  \\_|     \\ \\  \\|\\  \\ \\  \\ \\   \\ \\  \\_|\\ \\ " << endl;
    cout << " \\ \\  \\   \\ \\  \\ \\ \\_____  \\        \\ \\  \\    \\ \\  \\ \\  \\  __\\ \\   __  \\   \\ \\  \\ \\ \\_____  \\        \\ \\  \\\\\\  \\ \\  \\\\\\  \\   \\ \\  \\       \\ \\   __  \\ \\  \\ \\   \\ \\  \\ \\\\ \\  " << endl;
    cout << "  \\ \\  \\   \\ \\  \\ \\|____|\\  \\        \\ \\  \\____\\ \\  \\ \\  \\|\\  \\ \\  \\ \\  \\   \\ \\  \\ \\|____|\\  \\        \\ \\  \\\\\\  \\ \\  \\\\\\  \\   \\ \\  \\       \\ \\  \\ \\  \\ \\  \\ \\   \\ \\  \\_\\\\ \\" << endl;
    cout << "   \\ \\__\\   \\ \\__\\  ____\\_\\  \\        \\ \\_______\\ \\__\\ \\_______\\ \\__\\ \\__\\   \\ \\__\\  ____\\_\\  \\        \\ \\_______\\ \\_______\\   \\ \\__\\       \\ \\__\\ \\__\\ \\__\\ \\___\\ \\_______\\   " << endl;
    cout << "    \\|__|    \\|__| |\\_________\\        \\|_______|\\|__|\\|_______|\\|__|\\|__|    \\|__| |\\_________\\        \\|_______|\\|_______|    \\|__|        \\|__|\\|__|\\|__| \\|__|\\|_______|  " << endl;
    cout << "                   \\|_________|                                                     \\|_________|                                                                             " << endl;
    cout << "                                     ________  ___       __   ________      ___    ___      ___       __   _______           ________  ________  ___                           " << endl;
    cout << "                                    |\\   __  \\|\\  \\     |\\  \\|\\   __  \\    |\\  \\  /  /|    |\\  \\     |\\  \\|\\  ___ \\         |\\   ____\\|\\   __  \\|\\  \\ " << endl;
    cout << "                                    \\ \\  \\|\\  \\ \\  \\    \\ \\  \\ \\  \\|\\  \\   \\ \\  \\/  / /    \\ \\  \\    \\ \\  \\ \\   __/|        \\ \\  \\___|\\ \\  \\|\\  \\ \\  \\" << endl;
    cout << "                                     \\ \\   __  \\ \\  \\  __\\ \\  \\ \\   __  \\   \\ \\    / /      \\ \\  \\  __\\ \\  \\ \\  \\_|/__       \\ \\  \\  __\\ \\  \\\\\\  \\ \\  \\" << endl;
    cout << "                                      \\ \\  \\ \\  \\ \\  \\|\\__\\_\\  \\ \\  \\ \\  \\   \\/  /  /        \\ \\  \\|\\__\\_\\  \\ \\  \\_|\\ \\       \\ \\  \\|\\  \\ \\  \\\\\\  \\ \\__\\" << endl;
    cout << "                                       \\ \\__\\ \\__\\ \\____________\\ \\__\\ \\__\\__/  / /           \\ \\____________\\ \\_______\\       \\ \\_______\\ \\_______\\|__|" << endl;
    cout << "                                        \\|__|\\|__|\\|____________|\\|__|\\|__|\\___/ /             \\|____________|\\|_______|        \\|_______|\\|_______|   ___ " << endl;
    cout << "                                                                          \\|___|/                                                                     |\\__\\" << endl;
    cout << "                                                                                                                                                      \\|__| " << endl;

    sleep(3);
    system("cls");
}