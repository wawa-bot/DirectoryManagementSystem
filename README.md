#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

int main() {
    string currentDir;
    char choice;
    do {
            cout<< "Main Menu:\n";
            cout<< "[1] List Files\n";
            cout<< "[2] Create Directory\n";
            cout<< "[3] Change Directory\n";
            cout<< "[4] Exit\n";
            cout<< "Enter your choice: ";
            cin>> choice;
        if (choice == '4') {
                cout<<" Exiting the Program.\n";
            break;   
        }
        switch (choice) {
            case '1': {
                char  listChoice;
                    cout<< "\nLIST Files Menu:\n";
                    cout<< "[1]List All Files:\n";
                    cout<< "[2]List Files by Expression:\n";
                    cout<< "Enter your choice:";
                    cin>> listChoice;
                WIN32_FIND_DATA findFileData;
                HANDLE  hFind;
                string filter;
                switch(listChoice) {
                    case '1': {
                        hFind = FindFirstFile("*.*", &findFileData);
                        if(hFind != INVALID_HANDLE_VALUE) {
                            cout<<"\nAll Files\n";
                            do {
                                if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                                        cout<< findFileData.cFileName << "\n";
                                }                         
                            } while (FindNextFile(hFind, &findFileData));
                                FindClose(hFind);
                        } else {
                            cout << "No files found.\n";
                        }
                        break;
                  
                    }
                    case '2':     {
                            cout<<"Enter File Extension (e.g., .text): ";
                        cin>>filter;
                        string searchPattern = "*" + filter; 

                        hFind = FindFirstFile(searchPattern.c_str(), &findFileData);
                        if (hFind != INVALID_HANDLE_VALUE) {
                            cout << "\nFiles with " << filter << " extension:\n";
                            do {
                                if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                                    cout << findFileData.cFileName << "\n";
                                }
                            } while (FindNextFile(hFind, &findFileData));
                            FindClose(hFind);
                        } else {
                            cout << "No files found with that extension.\n";
                        }
                        break;
                    }
                    default:
                        cout << "Invalid choice for list files menu.\n";
                }
                break;
            }
     
            case '2': {
                string dirName;
                cout << "Enter the name of the directory to create: ";
                cin >> dirName;

                if (CreateDirectory(dirName.c_str(), NULL) || 
                    GetLastError() == ERROR_ALREADY_EXISTS) {
                    if (GetLastError() == ERROR_ALREADY_EXISTS) {
                        cout << "Error: Directory " << dirName << " already exists.\n";
                    } else {
                        cout << "Directory " << dirName << " created successfully.\n";
                    }
                } else {
                    cout << "Error creating directory " << dirName << ".\n";
                }
                break;
            }
            case '3': {
                string newDir;
                cout << "Enter the path of the directory to change to: ";
                cin >> newDir;

                if (SetCurrentDirectory(newDir.c_str())) {
                    char buffer[MAX_PATH];
                    GetCurrentDirectory(MAX_PATH, buffer);
                    currentDir = buffer;
                    cout << "Changed working directory to " << currentDir << "\n";
                } else {
                    cout << "Error: Directory " << newDir << " does not exist or is not accessible.\n";
                }
                break;
            }
            case '4':
                cout << "Exit the program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != '4');
    
    return 0;
}



