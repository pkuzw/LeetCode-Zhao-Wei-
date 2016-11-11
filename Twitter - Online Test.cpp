#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <iomanip>

using namespace std;
class Record {
public:
    string date;
    string time;
    string endPoint;
    string mark;
};

bool myCmp(Record a, Record b) {
    if (a.date != b.date) return a.date < b.date;
    else if (a.time != b.time) return a.time < b.time;
    else return a.endPoint < b.endPoint;
}


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    string str;
    vector<Record> ht;
    while (getline(cin, str)) {
        int i = 0;
        while (str[i] != '[') i++;
        
        Record r;
        r.date = str.substr(i + 1, 2);
        r.date = "-" + r.date;
        string month = str.substr(i + 4, 3);
        if (month == "Sep")         r.date = "-09" + r.date;
        else if (month == "Oct")    r.date = "-10" + r.date;
        else if (month == "Nov")    r.date = "-11" + r.date;
        else if (month == "Dec")    r.date = "-12" + r.date;
        else if (month == "Jan")    r.date = "-01" + r.date;
        else if (month == "Feb")    r.date = "-02" + r.date;
        else if (month == "Mar")    r.date = "-03" + r.date;
        else if (month == "Apr")    r.date = "-04" + r.date;
        else if (month == "May")    r.date = "-05" + r.date;
        else if (month == "Jun")    r.date = "-06" + r.date;
        else if (month == "Jul")    r.date = "-07" + r.date;
        else    r.date = "-08" + r.date;
        string year = str.substr(i + 8, 4);
        r.date = year + r.date;
        
        string time = str.substr(i + 13, 5);
        r.time = time;
        
        while (str[i] != ']')   i++;
        while (str[i] != '/')   i++;
        int j = 0;
        while (str[i] != ' ' && str[i] != '?') {
            i++;
            j++;
        }
        r.endPoint = str.substr(i - j, j);
        
        while (str[i] != '\"') i++;
        
        i += 2;
        j = 0;
        while (str[i] != ' ') {
            i++;
            j++;
        }
        r.mark = str.substr(i - j, j);
        ht.push_back(r);
    }
    
    sort(ht.begin(), ht.end(), myCmp);
    
    for (int i =0; i < ht.size() ; i++)
        cout << ht[i].time << " " << ht[i].endPoint << endl;
    
    return 0;
}
