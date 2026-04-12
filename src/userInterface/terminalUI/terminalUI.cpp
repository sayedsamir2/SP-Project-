#include <iostream>
#include <limits>
#include "../../dataStore/dataStore.hpp"
#include "../../projectLogic/auth.hpp"
#include "../../projectLogic/crud.hpp"
#include "../../projectLogic/compute.hpp"
#include "../../projectLogic/compute.hpp"
#include "../../projectLogic/analytics.hpp"

using namespace std;

// --- Session state ---
bool isLoggedIn = false;

void showMenu()
{
    cout << "\n==============================\n";
    cout << "  🎯 Virtual Hackathon System\n";
    cout << "==============================\n";
    if (isLoggedIn)
        cout << "  [Logged in as Admin]\n";
    cout << "==============================\n";
    cout << "1. Login Admin\n";
    cout << "2. Register Team\n";
    cout << "3. Add Evaluation        [Admin only]\n";
    cout << "4. Modify Team           [Admin only]\n";
    cout << "5. Submit Project\n";
    cout << "6. Show Final Report\n";
    cout << "7. Calculate Scores\n";
    cout << "0. Exit\n";
    cout << "==============================\n";
    cout << "Choose: ";
}

// Helper: read a whole line safely
string readLine(const string& prompt)
{
    cout << prompt;
    string line;
    getline(cin, line);
    return line;
}

// Helper: read a validated integer in [minVal, maxVal]
int readInt(const string& prompt, int minVal, int maxVal)
{
    int value;
    while (true)
    {
        cout << prompt;
        if (cin >> value && value >= minVal && value <= maxVal)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "⚠️  Please enter a number between " << minVal << " and " << maxVal << ".\n";
    }
}

void loginFlow()
{
    cout << "Username: ";
    string username;
    cin >> username;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Password: ";
    string password;
    cin >> password;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Response res = loginAdmin(username, password);

    if (res.status_ == Status::STATUS_200_OK)
    {
        isLoggedIn = true;
        cout << "✅ Login Successful!\n";
    }
    else if (res.status_ == Status::STATUS_401_UNAUTHORIZED)
        cout << "❌ Wrong password!\n";
    else
        cout << "else Admin not found!\n";
}

int main()
{
    loadData();

    int choice;

    do {
        showMenu();

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "⚠️  Please enter a number!\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
            loginFlow();
            break;

        case 2:
        {
            string name    = readLine("Team Name: ");
            string uni     = readLine("University: ");
            int members    = readInt("Members: ", 1, 100);
            string project = readLine("Project Title: ");

            registerNewTeam(name, uni, static_cast<unsigned short>(members), project);
            cout << "✅ Team Registered!\n";
            break;
        }

        case 3:
        {
            if (!isLoggedIn)
            {
                cout << "🔒 Admin login required!\n";
                break;
            }

            string teamId  = readLine("Team ID: ");
            string judgeId = readLine("Judge ID: ");
            int inno  = readInt("Innovation (0-10): ", 0, 10);
            int tech  = readInt("Technical  (0-10): ", 0, 10);
            int pres  = readInt("Presentation (0-10): ", 0, 10);

            AddEvaluation(teamId, judgeId,
                          static_cast<unsigned short>(inno),
                          static_cast<unsigned short>(tech),
                          static_cast<unsigned short>(pres));
            cout << "✅ Evaluation Added!\n";
            break;
        }

        case 4:
        {
            if (!isLoggedIn)
            {
                cout << "🔒 Admin login required!\n";
                break;
            }

            string id      = readLine("Team ID: ");
            string name    = readLine("New Name: ");
            string uni     = readLine("University: ");
            int members    = readInt("Members: ", 1, 100);
            string project = readLine("Project: ");

            Response res = modifyTeamById(id, name, uni,
                                          static_cast<unsigned short>(members), project);
            if (res.status_ == Status::STATUS_200_OK)
                cout << "✅ Team Updated!\n";
            else
                cout << "❌ Team not found!\n";
            break;
        }

        case 5:
        {
            string id      = readLine("Team ID: ");
            string project = readLine("New Project Title: ");

            Response res = submitProjectByTeamId(id, project);
            if (res.status_ == Status::STATUS_200_OK)
                cout << "🚀 Project Submitted!\n";
            else
                cout << "❌ Team not found!\n";
            break;
        }

        case 6:
            displayFinalReport();
            break;

        case 7:
        {
            string teamId = readLine("Team ID: ");

            float score = calculateFinalScore(teamId);
            if (score < 0.0f)
                cout << "❌ Team not found!\n";
            else if (score == 0.0f)
                cout << "⚠️  No evaluations found for this team!\n";
            else
                cout << "⭐ Final Score = " << score << "\n";
            break;
        }

        case 0:
            saveData();
            cout << "💾 Data Saved. Goodbye!\n";
            break;

        default:
            cout << "⚠️  Invalid choice, please choose between 0 and 7!\n";
        }

    } while (choice != 0);

    return 0;
}
