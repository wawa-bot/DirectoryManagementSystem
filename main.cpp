#include <iostream>
#include <windows.h> // For Windows directory operations
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    string currentDir = "";

    int choice;
    do {
        cout << "Main Menu:\n";
        cout << "[1] List Files\n";
        cout << "[2] Create Directory\n";
        cout << "[3] Change Directory\n";
        cout << "[4] Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int listChoice;
                cout << "List Files Menu:\n";
                cout << "[1] List All Files\n";
                cout << "[2] List Files by Extension\n";
                cout << "[3] List Files by Pattern\n";
                cout << "Enter your choice: ";
                cin >> listChoice;

                string filter;
                WIN32_FIND_DATA findFileData;
                HANDLE hFind;

                switch (listChoice) {
                    case 1:
                        hFind = FindFirstFile("*.*", &findFileData);
                        if (hFind != INVALID_HANDLE_VALUE) {
                            cout << "Listing all files:\n";
                            do {
                                if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                                    cout << findFileData.cFileName << "\n";
                                }
                            } while (FindNextFile(hFind, &findFileData));
                            FindClose(hFind);
                        }
                        break;
                    case 2:
                        cout << "Enter the file extension (e.g., .txt): ";
                        cin >> filter;
                        hFind = FindFirstFile(("*" + filter).c_str(), &findFileData);
                        if (hFind != INVALID_HANDLE_VALUE) {
                            cout << "Listing files with extension " << filter << ":\n";
                            do {
                                if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                                    cout << findFileData.cFileName << "\n";
                                }
                            } while (FindNextFile(hFind, &findFileData));
                            FindClose(hFind);
                        }
                        break;
                    case 3:
                        cout << "Enter the file pattern (e.g., moha*.*): ";
                        cin >> filter;
                        hFind = FindFirstFile(filter.c_str(), &findFileData);
                        if (hFind != INVALID_HANDLE_VALUE) {
                            cout << "Listing files matching pattern " << filter << ":\n";
                            do {
                                if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                                    cout << findFileData.cFileName << "\n";
                                }
                            } while (FindNextFile(hFind, &findFileData));
                            FindClose(hFind);
                        }
                        break;
                    default:
                        cout << "Invalid choice.\n";
                }
                break;
            }
            case 2: {
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
            case 3: {
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
            case 4:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);
    
    return 0;
}

