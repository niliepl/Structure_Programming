#include <iostream>
#include <fstream>
#include <valarray>
#include <vector>
#include <iomanip>
#include <map>

using namespace std;

typedef struct{
    int year;
    int pupil_count;
    string level;
    string Category;
    string district;
    string state;
    string gender;
}Details;

void analyzeDistrictTrends(const vector<Details>& pupilData) {
    map<string, map<int, int>> primaryDistrictTotals, secondaryDistrictTotals;
    
    // Aggregate data by district and year
    for (const auto& pupil : pupilData) {
        if (pupil.level == "Primary") {
            primaryDistrictTotals[pupil.district][pupil.year] += pupil.pupil_count;
        } else if (pupil.level == "Secondary") {
            secondaryDistrictTotals[pupil.district][pupil.year] += pupil.pupil_count;
        }
    }

    cout << "\n=== SIGNIFICANT DISTRICT CHANGES (≥20%) ===\n";
    cout << setprecision(2) << fixed;
    
    // Format headers
    cout << setw(15) << "Level" << setw(20) << "District" << setw(15) << "2019" 
         << setw(15) << "2020" << setw(15) << "Change" << setw(20) << "Status" << endl;
    cout << string(100, '-') << endl;

    // Analyze Primary Level
    for (const auto& districtData : primaryDistrictTotals) {
        string district = districtData.first;
        int pupils2019 = districtData.second.at(2019);
        int pupils2020 = districtData.second.at(2020);
        double pctChange;
        
        // Handle new districts (2019 = 0)
        if (pupils2019 == 0 && pupils2020 > 0) {
            pctChange = 100.0;  // Set to +100% for new districts
        } else {
            pctChange = (pupils2020 - pupils2019) * 100.0 / pupils2019;
        }
        
        if (abs(pctChange) >= 20) {
            cout << setw(15) << "Primary"
                 << setw(20) << district 
                 << setw(15) << pupils2019
                 << setw(15) << pupils2020
                 << setw(15) << pctChange<<"%" 
                 << setw(20) << (pctChange > 0 ? "Increase" : "Decrease") << endl;
        }
    }

    // Analyze Secondary Level
    for (const auto& districtData : secondaryDistrictTotals) {
        string district = districtData.first;
        int pupils2019 = districtData.second.at(2019);
        int pupils2020 = districtData.second.at(2020);
        double pctChange;
        
        // Handle new districts (2019 = 0)
        if (pupils2019 == 0 && pupils2020 > 0) {
            pctChange = 100.0;  // Set to +100% for new districts
        } else {
            pctChange = (pupils2020 - pupils2019) * 100.0 / pupils2019;
        }
        
        if (abs(pctChange) >= 20) {
            cout << setw(15) << "Secondary"
                 << setw(20) << district 
                 << setw(15) << pupils2019
                 << setw(15) << pupils2020
                 << setw(15) << pctChange<<"%" 
                 << setw(20) << (pctChange > 0 ? "Increase" : "Decrease") << endl;
        }
    }

    cout << "\n";
    cout << "Planning recommendations:\n";
    cout << "- Districts with increases: Prepare additional resources and staff\n";
    cout << "- Districts with decreases: Review factors causing enrollment decline\n";
}

int main(){

    vector<Details> pupilData;//vector(dynamic array) to store the data in Pupil Statistics
    vector<Details>Primary;//Store Secondary School Data
    vector<Details>Secondary;//Store Primary School Data
    ifstream in_stream;//Input file Pupil Statistics
    ofstream output_Secondary;//Output data into Secondary text file
    ofstream output_Primary;//Output data into Primary text file

    string inputPath = "Pupil_Statistics.txt";
    in_stream.open(inputPath);
    if (!in_stream) {
        cerr << "Error: Could not open input file\nYou don't have this file!!";
        return -1;
    }

    int selection;
    while(true){
        cout<<"==========================="<<endl;
        cout<<"1.School Category\n2.Descriptive\n3.Planning"<<endl;
        cout<<"==========================="<<endl;
        cout<<"Please Enter The Function You Want To Use:";cin>>selection;
   
        while(!in_stream.eof()){ 
            Details pupil;
            in_stream>>pupil.level>>pupil.state>>pupil.district>>pupil.year>>pupil.Category>>pupil.gender>>pupil.pupil_count;
            pupilData.push_back(pupil);
            if (in_stream.eof()) {
                break;
            }
        }

        in_stream.close();
    
        if (selection == 1) {

            output_Primary.open("Primary.txt");
            output_Secondary.open("Secondary.txt");
    
            // Add headers 
            output_Primary  << setw(15) << left << "Level"<< setw(25) << left << "State"<< setw(25) << left << "District"
                            << setw(15) << left << "Year"<< setw(15) << left << "Category"<< setw(22) << left << "Gender"
                            << setw(12) << left << "Pupil Count" << endl;

            output_Secondary << setw(15) << left << "Level"<< setw(25) << left << "State"<< setw(25) << left << "District"
                             << setw(15) << left << "Year"<< setw(15) << left << "Category"<< setw(22) << left << "Gender"
                             << setw(12) << left << "Pupil Count" << endl;

            // Write data based on level of study(school category) into respective files using for loop
            for (int i = 0; i < pupilData.size(); i++) {
                if (pupilData[i].level == "Secondary") {
                    output_Secondary<< setw(15) << left << pupilData[i].level << setw(25) << left << pupilData[i].state << setw(25) << left << pupilData[i].district
                                    << setw(15) << left << pupilData[i].year << setw(15) << left << pupilData[i].Category << setw(22) << left << pupilData[i].gender
                                    << setw(12) << left << pupilData[i].pupil_count << endl;

                    Secondary.push_back(pupilData[i]);

                }
                else if (pupilData[i].level == "Primary") {
                    output_Primary  << setw(15) << left << pupilData[i].level << setw(25) << left << pupilData[i].state << setw(25) << left << pupilData[i].district
                                    << setw(15) << left << pupilData[i].year << setw(15) << left << pupilData[i].Category << setw(22) << left << pupilData[i].gender
                                    << setw(12) << left << pupilData[i].pupil_count << endl;
                
                    Primary.push_back(pupilData[i]);
                }
            }

            output_Primary.close();
            output_Secondary.close();
            cout<<"File was Successfully spilt"<<endl;

        }
        else if (selection == 2) {
            // Map to store total pupils per district for each year, by level of studies
            map< string, map<int, int> > Secondary_districtTotals; // map< district, map<year, total pupils> >
            map< string, map<int, int> > Primary_districtTotals; // map< district, map<year, total pupils> >
            int Total_Secondary_pupil2019 = 0, Total_Secondary_pupil2020 = 0;
            int Total_Primary_pupil2019 = 0, Total_Primary_pupil2020 = 0;

            for(int i=0;i<Secondary.size();i++){
                if(Secondary[i].year == 2019){
                    Total_Secondary_pupil2019 += Secondary[i].pupil_count;
                    Secondary_districtTotals[Secondary[i].district][2019] += Secondary[i].pupil_count;
                }   
                else {
                    Total_Secondary_pupil2020 += Secondary[i].pupil_count;
                    Secondary_districtTotals[Secondary[i].district][2020] += Secondary[i].pupil_count;
                }   
            }
            for(int i=0;i<Primary.size();i++){
                if(Primary[i].year == 2019){
                    Total_Primary_pupil2019 += Primary[i].pupil_count;
                    Primary_districtTotals[Primary[i].district][2019] += Primary[i].pupil_count;
                }   
                else {
                    Total_Primary_pupil2020 += Primary[i].pupil_count;
                    Primary_districtTotals[Primary[i].district][2020] += Primary[i].pupil_count;
                }   
            }
            // Display total pupil count per year and per district for each level
            cout << "Total pupils in Secondary - 2019: " << Total_Secondary_pupil2019 << endl;
            cout << "Total pupils in Secondary - 2020: " << Total_Secondary_pupil2020 << endl;
            cout << "Total pupils in Primary - 2019: " << Total_Primary_pupil2019 << endl;
            cout << "Total pupils in Primary - 2020: " << Total_Primary_pupil2020 << endl;

            // Display district-specific totals and calculate percentages, averages, and standard deviations for secondary
            cout << "\nSecondary Level District Totals:\n";
            for (map<string, map<int, int> >::iterator it = Secondary_districtTotals.begin(); it != Secondary_districtTotals.end(); ++it) {
                string district = it->first;
                map<int, int> yearData = it->second;

                cout << "District: " << district << endl;
        
                // Calculate statistics for each year
                for (map<int, int>::iterator year_it = yearData.begin(); year_it != yearData.end(); ++year_it) {
                    int year = year_it->first;
                    int count = year_it->second;
            
                    // Calculate percentage
                    double percentage = (year == 2019) ? (count * 100.0 / Total_Secondary_pupil2019) : (count * 100.0 / Total_Secondary_pupil2020);
                    cout << "Year: " << year << "\nPupils: " << count << " \nPercentage: " << percentage << "%" << endl;
                }
            }

            // Display district-specific totals and calculate percentages, averages, and standard deviations for primary
            cout << "\nPrimary Level District Totals:\n";
            for (map<string, map<int, int> >::iterator it = Primary_districtTotals.begin(); it != Primary_districtTotals.end(); ++it) {
                string district = it->first;
                map<int, int> yearData = it->second;

                cout << "District: " << district << endl;
        
                // Calculate statistics for each year
                for (map<int, int>::iterator year_it = yearData.begin(); year_it != yearData.end(); ++year_it) {
                    int year = year_it->first;
                    int count = year_it->second;

                    // Calculate percentage
                    double percentage = (year == 2019) ? (count * 100.0 / Total_Primary_pupil2019) : (count * 100.0 / Total_Primary_pupil2020);
                    cout << "Year: " << year << "\nPupils: " << count << "\nPercentage: " << percentage << "%" << endl;
                }
            }
           
            //Calculate average and standard deviation for each district
            for (map<string, map<int, int> >::iterator it = Secondary_districtTotals.begin(); it != Secondary_districtTotals.end(); ++it) {
                string district = it->first;
                map<int, int> yearData = it->second;
        
                double sum = 0.0, mean = 0.0, std_dev = 0.0;
                int count = yearData.size();

                for (map<int, int>::iterator year_it = yearData.begin(); year_it != yearData.end(); ++year_it) {
                    sum += year_it->second;
                }
                mean = sum / count; //average number of pupils for each district across years by summing pupil counts and dividing by the number of years available.

                //Calculate standard deviation
                double variance = 0.0;
                for (map<int, int>::iterator year_it = yearData.begin(); year_it != yearData.end(); ++year_it) {
                    variance += pow(year_it->second - mean, 2);
                }
                std_dev = sqrt(variance / count);  //standard deviation of pupil counts in each district by calculating the variance and then taking the square root.

                cout << "District: " << district << "\nAverage Pupils: " << mean << "\nStandard Deviation: " << std_dev << endl;
            }
            
        }else if (selection == 3) {
            analyzeDistrictTrends(pupilData);
        }

        else{
            break;
        }
    
    }

    return 0;
}
