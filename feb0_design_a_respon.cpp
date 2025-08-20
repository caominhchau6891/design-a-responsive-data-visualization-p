#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// Data structure to hold the data points
struct DataPoint {
    string category;
    double value;
};

// Data structure to hold the parsed data
struct ParsedData {
    vector<string> categories;
    vector<vector<double>> values;
};

// Function to parse the data from a string
ParsedData parseData(const string& data) {
    ParsedData parsedData;
    vector<string> rows;
    string row;
    for (char c : data) {
        if (c == '\n') {
            rows.push_back(row);
            row.clear();
        } else {
            row += c;
        }
    }
    if (!row.empty()) {
        rows.push_back(row);
    }

    for (const string& row : rows) {
        vector<string> cols;
        string col;
        for (char c : row) {
            if (c == ',') {
                cols.push_back(col);
                col.clear();
            } else {
                col += c;
            }
        }
        if (!col.empty()) {
            cols.push_back(col);
        }

        if (parsedData.categories.empty()) {
            parsedData.categories = cols;
        } else {
            parsedData.values.push_back(vector<double>());
            for (size_t i = 1; i < cols.size(); ++i) {
                parsedData.values.back().push_back(stod(cols[i]));
            }
        }
    }

    return parsedData;
}

// Function to generate the responsive data visualization HTML
string generateHTML(const ParsedData& data) {
    string html = "<html><head><style>";
    html += "table { border-collapse: collapse; }";
    html += "th, td { border: 1px solid #ddd; padding: 8px; text-align: left; }";
    html += "</style></head><body><table>";
    html += "<tr>";
    for (const string& category : data.categories) {
        html += "<th>" + category + "</th>";
    }
    html += "</tr>";

    for (const vector<double>& values : data.values) {
        html += "<tr>";
        for (double value : values) {
            html += "<td>" + to_string(value) + "</td>";
        }
        html += "</tr>";
    }

    html += "</table></body></html>";
    return html;
}

int main() {
    string data = "Category,A,B,C\n"
                  "Row 1,10,20,30\n"
                  "Row 2,40,50,60\n"
                  "Row 3,70,80,90\n";

    ParsedData parsedData = parseData(data);
    string html = generateHTML(parsedData);

    cout << html << endl;

    return 0;
}