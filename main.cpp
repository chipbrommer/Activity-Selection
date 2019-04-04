/***************************************************************************************************
 *
 * Author: Chip Brommer
 * Date: March 23, 2019
 * Contact: Fredrick.Brommer@usm.edu
 * Class: CSC 413 - Algorithms
 * Professor: Dr. Zhou
 *
 * Description: Implement a greedy search algorithm for the activity selection problem.
 
 ***************************************************************************************************/

#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

//A Struct to hold an activity with a start time and end time.
struct Activity
{
    int start;
    int end;
};

void welcomeMessage();
void activityEntry();
void scheduleVisualConvert(Activity[], char[][17], int);
void printSchedule(char[][17], int);
void singleActivityPrint(char[][17], int, int);
void maxActivity(Activity[], char[][17], int);
bool compareTime(Activity, Activity);
int activityRestrictor(int);
int timeRestrictor(int, char);
void runAgain();
void programEnd();

int main()
{
    //Calling the welcome message
    welcomeMessage();
    
    //Calling the activity entry
    activityEntry();

    return 0;
}

//-------------------------------------------------------------------------------------------------
//welcomeMessage - This function holds the welcome message for the program and prints it to the
//                 console for the user.
//-------------------------------------------------------------------------------------------------
void welcomeMessage()
{
    cout << "\t\t\tChips Activity Selection Project\n"
    << "\t\t------------------------------------------\n\n";
    cout << "\tThis program will tell you how to reach the most activities.\n";
    cout << "\tCurrent sortable time frame is 0 to 16 for up to 20 activities.\n\n";
}

//-------------------------------------------------------------------------------------------------
//activityEntry - This function will take the start time and end time of a activity and insert it
//                into an array.
//-------------------------------------------------------------------------------------------------
void activityEntry()
{
    int activNum = -1; //Variable to hold the number of activities
                      //set to -1 so user can set to 0 and it be real
    int start = -1;     //Variable to hold the start time.
    int end = -1;       //Variabel to hold the end time.
    
    //User to enter the number of activities.
    //while(!goodInput(activNum)) //restricting to 17 max activities.
    {
        cout << "Enter the number of activities: ";
        cin >> activNum;
        
        activNum = activityRestrictor(activNum);
    }
    cout << endl << endl;
    
    Activity activityArray[activNum]; //Array of structs for our activities.
    char scheduleArray[activNum][17];   //Creating the scedule array for chars.
    
    //User to enter the start time and end time for each activity.
    for(int x = 0; x < activNum; x++)
    {
        printf("Activity %d", x+1);
        //while(!goodInput(start)) //restricting to 17 max time.
        {
            cout << "\n\tEnter Start Time: ";
            cin >> start;
            
            start = timeRestrictor(start, 's'); //sending s to designate start time
        }
        
        //while(!goodInput(end)) //restricting to 17 max time.
        {
            cout << "\tEnter End Time: ";
            cin >> end;
            
            end = timeRestrictor(end, 'e'); //sending e to designate end time
        }
        cout << endl;
        
        //End time cannot come before the start time.
        while(end < start)
        {
            cout << "\n\tThe end time cannot be before the start time.\n";
            cout << "\tTo skip this activity entry, enter 99.\n";

            cout << "\tEnter End Time: ";
            cin >> end;
            
            end = timeRestrictor(end, 'e'); //sending e to designate end time
            
            cout << endl;
        }
        
        //If the user is not wanting to cancel the activity input, input the values into the struct
        if(end != 99)
        {
            activityArray[x].start = start;
            activityArray[x].end = end;
        }
    }//End x for loop
    
    //sorting the users activity inputs to get the schedule in order using the compare bool.
    sort(activityArray, activityArray+activNum, compareTime);
    
    //Converting the activities into a visual schedule.
    scheduleVisualConvert(activityArray, scheduleArray, activNum);
    
    cout << "\nYour Schedule:\n";
    //Calling the printer function and sending the scheduleArray and the number of activities.
    printSchedule(scheduleArray, activNum);
    
    //Calling the maxAtivity function to find the maximum number of activities.
    maxActivity(activityArray, scheduleArray, activNum);
    
    //Asking the user if they'd like to run again
    runAgain();
}

//-------------------------------------------------------------------------------------------------
//printActivities - This function will print the schedule of the activities for viewing pleasure of
//                  the user
//-------------------------------------------------------------------------------------------------
void scheduleVisualConvert(Activity activityArray[], char scheduleArray[][17], int activNum)
{
    if(activNum == 0)
    {
        //do nothing
    }
    else
    {
        for(int x = 0; x < activNum; x++)
        {
            for(int y = 0 ; y < 17 ; y++)
            {
                //If the value of Y is between start and end, enter an N
                if(y >= activityArray[x].start && y <= activityArray[x].end)
                {
                    scheduleArray[x][y] = 'X';
                }
                else //Else enter a _
                {
                    scheduleArray[x][y] = '_';
                }
            }
        }
    }
}


//-------------------------------------------------------------------------------------------------
//printActivities - This function will print the schedule of the activities for viewing pleasure of
//                  the user
//-------------------------------------------------------------------------------------------------
void printSchedule(char scheduleArray[][17], int activNum)
{
    //Printing the schedule header
    printf("             ");
    for(int a = 0; a < 17; a++)
    {
        printf("%3d", a);
    }
    cout << endl;
    
    if(activNum == 0)
    {
       //Do Nothing
        cout << endl;
    }
    else
    {
        //Printing the schedule
        for(int x = 0; x < activNum; x++)
        {
            cout << "Activity " << x+1 << ": ";
            
            //extra space for alignment with double digit numbers
            if(x < 9)
            {
                cout << " ";
            }
            
            for(int y = 0; y < 17; y++)
            {
                printf("%3c", scheduleArray[x][y]);
            }
        
            cout << endl;
        }
    
        cout << endl;
    }
}

//-------------------------------------------------------------------------------------------------
//singleActivityPrint - This function will print a single activity schedule
//-------------------------------------------------------------------------------------------------
void singleActivityPrint(char scheduleArray[][17], int activNum, int totalActiv)
{
    if(totalActiv == 0)
    {
        cin.clear();
        cout << "\nNo Actvities Entered.\n";
    }
    else
    {
        cout << "Activity " << activNum+1 << ": ";
        
        //extra space for alignment with double digit numbers
        if(activNum < 9)
        {
            cout << " ";
        }
        
        for(int y = 0; y < 17; y++)
        {
            printf("%3c", scheduleArray[activNum][y]);
        }
    }
    cout << endl;
}

//-------------------------------------------------------------------------------------------------
//maxActivity - This function finds the maximum number of activities possible to hit from a
//              user input list.
//-------------------------------------------------------------------------------------------------
void maxActivity(Activity activityArray[], char scheduleArray[][17], int activNum)
{
    cout << "Selected Activities: " << endl;
    
    printf("             ");
    //Printing the schedule header
    for(int a = 0; a < 17; a++)
    {
        printf("%3d", a);
    }
    cout << endl;
    
    int x = 0;// first activity as 0 is selected
    
    /* This will print the activites numerically - commented out for only visual print
    cout << "Activity: " << x+1 << " , Start: " << activityArray[x].start << " End: " << activityArray[x].end <<endl;
     */
    
    //Printing the single Activity
    singleActivityPrint(scheduleArray, x, activNum);
    
    //for all other activities
    for (int y = 1; y < activNum; y++)
    {
        //when start time is >= end time, print the activity
        if (activityArray[y].start >= activityArray[x].end)
        {
            /* This will print the activites numerically - commented out for only visual print
            //cout << "Activity: " << y+1 << " , Start: " <<activityArray[y].start << " End: " << activityArray[y].end <<endl;
             */
            x = y;
            
            //Printing the single Activity - sending the array, the current activity we want to print,
            //and the total number of activities.
            singleActivityPrint(scheduleArray, y, activNum);
        }
    }
    
    //Spacer before ending
    cout << endl;
}

//-------------------------------------------------------------------------------------------------
//compareTime - takes the time of two activities and compares the ending times.
//-------------------------------------------------------------------------------------------------
bool compareTime(Activity activity1, Activity activity2)
{
    return (activity1.end < activity2.end);
}

//---------------------------------------------------------------------------------------
//timeRestrictor - this function ensures a lowest time of 0 and max time of 16 is entered
//---------------------------------------------------------------------------------------
int timeRestrictor(int numberEntered, char input)
{
    if(numberEntered == 99 && input == 'e') //user wants to cancel the time input
    {
        return numberEntered;
    }
    else //Normal input
    {
        if(input == 'e') //Time is end time.
        {
            while(numberEntered < 0 || numberEntered > 16)
            {
                cout << "\tEnter End Time: ";
                cin >> numberEntered;
                cout << endl;
            }
        }
        else //Time is start time.
        {
            while(numberEntered < 0 || numberEntered > 16)
            {
                cout << "\tEnter Start Time: ";
                cin >> numberEntered;
            }
        }
    }
    return numberEntered;
}

//---------------------------------------------------------------------------------------
//activityRestrictor - this function ensures a lowest of 0 max of 20 activities are entered
//---------------------------------------------------------------------------------------
int activityRestrictor(int numberEntered)
{
    while(numberEntered < 0 || numberEntered > 20)
    {
        cout << "Enter the number of activities: ";
        cin >> numberEntered;
    }
    
    return numberEntered;
}

//---------------------------------------------------------------------------------------
//runAgain - Asks the user if they'd like to run again. If yes, send to mainWorker function
//---------------------------------------------------------------------------------------
void runAgain()
{
    char userSelection;     //Holds the user selection
    
    cout << "\nWould you like to check another schedule?\n";
    cout << "Enter Y for Yes, Else ends program.\n";
    cout << "\tUser Input: ";
    cin >> userSelection;
    
    //converts to char input to an upper character and compares it,
    //if the input was a 'Y' then sends back to the worker function
    if(toupper(userSelection) == 'Y')
    {
        cout << endl;
        cout << "\t\t------------------------------------------\n\n";
        activityEntry();
    }
    else //input was not a 'Y' , defaults to program end function
    {
        programEnd();
    }
}

//-------------------------------------------------------------------------------------------------
//programEnd - Prompts the user to enter any key to close the program, then ends the program.
//-------------------------------------------------------------------------------------------------
void programEnd()
{
    cout << "\nPress any key to end...\n";
    cin.get();
    exit(0);
}
