/*
Copyright (c) 2022 Timothy Hutchins

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the Software), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED AS IS, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "deskentry.h"
#include <thread>
#include <chrono>
std::map<std::string, std::string> DeskEntry::getEntries(std::filesystem::path path) {
    if (std::filesystem::is_directory(path)) {
        return std::map<std::string, std::string>();
    }
    std::fstream entry(path, std::ios::in);
    std::string line;
    std::map<std::string, std::string> entries;
    bool eof = false;
    bool comment = false;
    while (line != "[Desktop Entry]") {
        if (entry.eof()) {
            eof = true;
            break;
        }
        std::getline(entry, line);
    }
    while (!eof) {
        comment = false;
        if (entry.eof()) {
            eof = true;
        }
        std::getline(entry, line);
        for (unsigned int i = 0; i < 3; i++) {
            if (line[i] == '#') {
                comment = true;
            }
        }
        if (!comment) {
            size_t separator = line.find("=");
            if (separator!=std::string::npos) {
                entries.insert(std::pair<std::string, std::string>(line.substr(0, separator), line.substr(separator + 1, line.size())));
            }
        }
    }
    return entries;
}
