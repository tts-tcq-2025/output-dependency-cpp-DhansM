/*#include <iostream>
#include <assert.h>

int printColorMap() {
    const char* majorColor[] = {"White", "Red", "Black", "Yellow", "Violet"};
    const char* minorColor[] = {"Blue", "Orange", "Green", "Brown", "Slate"};
    int i = 0, j = 0;
    for(i = 0; i < 5; i++) {
        for(j = 0; j < 5; j++) {
            std::cout << i * 5 + j << " | " << majorColor[i] << " | " << minorColor[i] << "\n";
        }
    }
    return i * j;
}

void testPrintColorMap() {
    std::cout << "\nPrint color map test\n"; 
    int result = printColorMap();
    assert(result == 25);
    std::cout << "All is well (maybe!)\n";

}*/

#include <sstream>
#include <string>
#include <cassert>
#include <iostream>

std::string getColorMapText() {
    std::ostringstream oss;
    const char* majorColor[] = {"White", "Red", "Black", "Yellow", "Violet"};
    const char* minorColor[] = {"Blue", "Orange", "Green", "Brown", "Slate"};
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            oss << (i * 5 + j) << " | " << majorColor[i] << " | " << minorColor[i] << "\n";
        }
    }
    return oss.str();
}

void testSpecificPairs() {
    std::string output = getColorMapText();
    
    // Assertions
    assert(output.find("0 | White | Blue") != std::string::npos);
    assert(output.find("1 | White | Orange") != std::string::npos);
    assert(output.find("5 | Red | Blue") != std::string::npos);
    assert(output.find("22 | Violet | Green") != std::string::npos);  // expecting Violet-Green at index 22
    assert(output.find("3 | White | Brown") != std::string::npos);
    assert(output.find("24 | Violet | Slate") != std::string::npos);

    std::cout << "Detected all expected pairings—if any of these asserts fail, the test will catch the defect.\n";
}

int main() {
    testSpecificPairs();
    return 0;
}
