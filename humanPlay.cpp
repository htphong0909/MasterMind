#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

random_device dev;
mt19937 random(dev());
using getRd = uniform_int_distribution<std::mt19937::result_type>;

void build();
void letPlay();
vector<string> possibleCodes = {"1234", "1235", "1236", "1243", "1245", "1246", "1253", "1254", "1256", "1263", "1264", "1265", "1324", "1325", "1326", "1342", "1345", "1346", "1352", "1354", "1356", "1362", "1364", "1365", "1423", "1425", "1426", "1432", "1435", "1436", "1452", "1453", "1456", "1462", "1463", "1465", "1523", "1524", "1526", "1532", "1534", "1536", "1542", "1543", "1546", "1562", "1563", "1564", "1623", "1624", "1625", "1632", "1634", "1635", "1642", "1643", "1645", "1652", "1653", "1654", "2134", "2135", "2136", "2143", "2145", "2146", "2153", "2154", "2156", "2163", "2164", "2165", "2314", "2315", "2316", "2341", "2345", "2346", "2351", "2354", "2356", "2361", "2364", "2365", "2413", "2415", "2416", "2431", "2435", "2436", "2451", "2453", "2456", "2461", "2463", "2465", "2513", "2514", "2516", "2531", "2534", "2536", "2541", "2543", "2546", "2561", "2563", "2564", "2613", "2614", "2615", "2631", "2634", "2635", "2641", "2643", "2645", "2651", "2653", "2654", "3124", "3125", "3126", "3142", "3145", "3146", "3152", "3154", "3156", "3162", "3164", "3165", "3214", "3215", "3216", "3241", "3245", "3246", "3251", "3254", "3256", "3261", "3264", "3265", "3412", "3415", "3416", "3421", "3425", "3426", "3451", "3452", "3456", "3461", "3462", "3465", "3512", "3514", "3516", "3521", "3524", "3526", "3541", "3542", "3546", "3561", "3562", "3564", "3612", "3614", "3615", "3621", "3624", "3625", "3641", "3642", "3645", "3651", "3652", "3654", "4123", "4125", "4126", "4132", "4135", "4136", "4152", "4153", "4156", "4162", "4163", "4165", "4213", "4215", "4216", "4231", "4235", "4236", "4251", "4253", "4256", "4261", "4263", "4265", "4312", "4315", "4316", "4321", "4325", "4326", "4351", "4352", "4356", "4361", "4362", "4365", "4512", "4513", "4516", "4521", "4523", "4526", "4531", "4532", "4536", "4561", "4562", "4563", "4612", "4613", "4615", "4621", "4623", "4625", "4631", "4632", "4635", "4651", "4652", "4653", "5123", "5124", "5126", "5132", "5134", "5136", "5142", "5143", "5146", "5162", "5163", "5164", "5213", "5214", "5216", "5231", "5234", "5236", "5241", "5243", "5246", "5261", "5263", "5264", "5312", "5314", "5316", "5321", "5324", "5326", "5341", "5342", "5346", "5361", "5362", "5364", "5412", "5413", "5416", "5421", "5423", "5426", "5431", "5432", "5436", "5461", "5462", "5463", "5612", "5613", "5614", "5621", "5623", "5624", "5631", "5632", "5634", "5641", "5642", "5643", "6123", "6124", "6125", "6132", "6134", "6135", "6142", "6143", "6145", "6152", "6153", "6154", "6213", "6214", "6215", "6231", "6234", "6235", "6241", "6243", "6245", "6251", "6253", "6254", "6312", "6314", "6315", "6321", "6324", "6325", "6341", "6342", "6345", "6351", "6352", "6354", "6412", "6413", "6415", "6421", "6423", "6425", "6431", "6432", "6435", "6451", "6452", "6453", "6512", "6513", "6514", "6521", "6523", "6524", "6531", "6532", "6534", "6541", "6542", "6543"};
string compareFeedback(const string& s, const string& hidden);

namespace human {
    struct prediction {
        string inp, feedback;
        explicit prediction(const string& _inp);
    };

    vector<prediction> predictions;
    int playCount = 6;
    getRd rd(0, possibleCodes.size() - 1);
    string hidden = possibleCodes[rd(random)];

    void play();
    string getPredict();
    int check();
    void printAttempts();

    void play() {
        while (playCount) {
            system("cls");
            predictions.emplace_back(getPredict());
            if (check() == 1) playCount--;
            if (check() == 2) {
                system("cls");
                printAttempts();
                cout << "\nYOU WIN!!!!\n";
                system("pause");
                return;
            }
        }
        system("cls");
        printAttempts();
        cout << "\nYOU LOSE!!!!\n";
        system("pause");
    }

    string getPredict() {
        printAttempts();
        cout << "W: white peg\n";
        cout << "B: back peg\n";
        cout << "Play count remaining: " << playCount << '\n';
        cout << "The input is a permutation of length 4 consisting of the numbers 1 to 6:";
        string predict;
        cin >> predict;
        return predict;
    }

    prediction::prediction(const string& _inp) {
        inp = _inp;
        if (!binary_search(possibleCodes.begin(), possibleCodes.end(), inp)) feedback = "Invalid feedback";
        else feedback = compareFeedback(inp, hidden);
    }

    int check() {
        if (predictions.empty() || predictions.back().feedback == "Invalid feedback") return 0;
        if (predictions.back().feedback == "BBBB") return 2;
        return 1;
    }

    void printAttempts() {
        for (int i = 1; const auto& [inp, feedback] : predictions) {
            cout << "----------------Attempt " << i << "----------------\n";
            cout << "Your prediction: " << inp << '\n';
            cout << "Feedback: " << feedback << '\n';
            i++;
        }
        cout << "-------------------------------------------------------------\n";
    }
}

string compareFeedback(const string& s, const string& hidden) {
    string feedback;
    map<char, int> pos;
    for (int i = 1; char k : hidden) {
        pos[k] = i;
        i++;
    }
    for (int i = 1; char k : s) {
        if (pos[k] == i) feedback += "B";
        else if (pos[k] > 0) feedback += "W";
        i++;
    }
    sort(feedback.begin(), feedback.end());
    return feedback;
}

void letPlay() {
    cout << "Instructions for playing Mastermind:" << endl;
    cout << endl;
    cout << "1. The computer will randomly generate a secret code." << endl;
    cout << "2. The code consists of 4 pegs, each of which can be one of 6 colors." << endl;
    cout << "   The colors are usually represented by numbers from 1 to 6, where:" << endl;
    cout << "      1 = Red" << endl;
    cout << "      2 = Green" << endl;
    cout << "      3 = Blue" << endl;
    cout << "      4 = Yellow" << endl;
    cout << "      5 = Orange" << endl;
    cout << "      6 = Purple" << endl;
    cout << "3. Your goal is to guess the secret code in as few attempts as possible." << endl;
    cout << "4. For each guess, the computer will provide feedback:" << endl;
    cout << "   - A black peg indicates a correct color in the correct position." << endl;
    cout << "   - A white peg indicates a correct color in the wrong position." << endl;
    cout << "   - No peg means the color does not appear in the code." << endl;
    cout << "5. You have 6 attempts to crack the code" << endl;
    cout << "6. Good luck, and have fun!" << endl;
    system("pause");
    human::play();
}

int main() {
    letPlay();
    return 0;
}
