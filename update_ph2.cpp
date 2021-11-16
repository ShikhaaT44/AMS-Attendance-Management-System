#include <iostream>  // * c++ code style use
#include <stdio.h>   //* for c style code use
#include <stdlib.h>  // * standard library like dynamic memory allocation and exit macros and other..
#include <conio.h>   // *  console input output
#include <windows.h> // * windows console related functions handle
#include <unistd.h>  // * for sleep function
#include <iomanip>   // * for manipulator
#include <cwchar>    //*for console font purpose
#include <string.h>  //* C style string related functions access
#include <stdbool.h> // * boolean operation
#include <math.h>    //* math operations
#include <fstream>   //* file handling functions access
#include <string>    //* C++ STL( string library) function access
#include <regex>     //* for email validation
#include <algorithm> //* for transform function access
#include <ctime>     //* for getting current date and time
#include <sstream>   //* for conversion to string
#include <vector>    //*STL DYNAMIC ARRAY used
#include <tuple>     //* for using tuples (group of element key->value type)

//--------FOR-DOCUMENT PATH GETTING------/

#include <shlobj.h>
#include <sys/types.h>

#include <sys/stat.h>
#include <direct.h>

#pragma comment(lib, "shell32.lib") //? for document path finding

//--------FOR-DOCUMENT PATH GETTING------/

#ifndef _WIN32_WINNT //*if that macro not exist then condtional compila6ion would be done and those files will be included
#define _WIN32_WINNT 0x0601
#include <wincon.h>
#include <string>

 #endif  // user 1

typedef struct _CONSOLE_FONT_INFOEX
{
  ULONG cbSize;
  DWORD nFont;
  COORD dwFontSize;
  UINT FontFamily;
  UINT FontWeight;
  WCHAR FaceName[LF_FACESIZE];
} CONSOLE_FONT_INFOEX, *PCONSOLE_FONT_INFOEX;

#ifdef __cplusplus
extern "C"
{
#endif
  BOOL WINAPI SetCurrentConsoleFontEx(HANDLE hConsoleOutput, BOOL bMaximumWindow, PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx);
#ifdef __cplusplus
}
#endif

// #endif // user 2

using namespace std; //? standard namespace for  resolving naming coflicts

/*******************APP-CONTROL_CLASS********************************/

class APP //*GRAND PARENT CLASS
{

public:
  static int MODULE_CHOICE; //*module selector static variable

  APP()
  {
    //*******************GET-CURRENT-DATE**************************//
    string temp;                      //temp variable for storage
    time_t tmNow;                     // structure variable
    tmNow = time(NULL);               //set to initial zero=NULL
    struct tm t = *localtime(&tmNow); //pre defined function

    stringstream ss; //string stream class object
    ss << t.tm_mday; // pass day
    temp = ss.str(); // it returns as string
    CUR_DATE = temp; // save to input parameter

    ss.str(""); //flush string stream class so new input can be taken

    ss << (t.tm_mon + 1);       //pass months
    temp = ss.str();            //returns month
    CUR_DATE = CUR_DATE + "/";  //add slash
    CUR_DATE = CUR_DATE + temp; //concate to input para

    ss.str("");
    ss << (t.tm_year + 1900);   //pass year
    temp = ss.str();            //returns year
    CUR_DATE = CUR_DATE + "/";  //add slash
    CUR_DATE = CUR_DATE + temp; //concate to input para

    ss.str(""); //flush string stream class so new input can be taken

    //*******************CURRENT-DATE**********************************//

    //*******************GET-CURRENT-TIME******************************//

    int meridiem_Flag = 0; //0=AM 1=PM
    if (t.tm_hour > 12)    // if hours is greter than 12 then convert into 12 hour formet
    {
      t.tm_hour = (t.tm_hour - 12);
      meridiem_Flag = 1; //Flag set to show AM-PM
    }

    ss << t.tm_hour; // pass Hours
    temp = ss.str(); // it returns as string
    CUR_TIME = temp;

    if (stoi(CUR_TIME) < 10) // if hours is between 1 to 9 the like 09 ,01 ...put zero before digit
    {
      CUR_TIME = "0" + CUR_TIME;
    }
    ss.str("");
    ss << (t.tm_min);
    temp = ss.str();
    if (stoi(temp) < 10) //convert to int for cheking condition
    {
      temp = "0" + temp;
    }
    CUR_TIME = CUR_TIME + ":";
    CUR_TIME = CUR_TIME + temp;

    ss.str("");

    CUR_TIME += (meridiem_Flag == 0) ? " AM" : " PM"; //AM and PM
    //*******************CURRENT-TIME*********************************//
  }

  void SetColor(int ForgC) //?for setting individual text color
  {
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi; //We use csbi for the wAttributes word.
    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
      //Mask out all but the background attribute, and add in the forgournd color
      wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
      SetConsoleTextAttribute(hStdOut, wColor);
    }
  }

  void setCursorPos(int x, int y = 0) //?IMPORTANT : ->relative position is set
  {

    //*vertical lines space

    while (x > 0)
    {
      cout << endl;
      x--;
    }
    while (y != 0) //*horizontal cursor space by 1 charecter
    {
      printf(" ");
      y--;
    }
  }

  void ShowConsoleCursor(bool showFlag) //? for hiding the cursor just  set showFlag = false(bool value)
  {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
  }

  void scrClr(float i = 0.0) //?for clearing screen afer some time
  {
    //*by default set to zero with default arguements
    sleep(i);      // * going in sleep mode
    system("cls"); // * clear screen
  }

  void buildVerticalWall(int briks) //? for making vertical side
  {
    cout << "*";
    while (briks > 0)
    {
      cout << "-";
      briks--;
    }
    cout << "*";
  }

  void buildHorizontalWall(int endBrick, string data) //? for making horizontal side
  {
    cout << "|";
    int run = 1;
    while (run < endBrick)
    {

      if (run == (endBrick / 6)) //
      {
        cout << data;
        run += (data.length() - 1);
        cout << " ";
      }
      else
      {
        cout << " ";
      }

      run++;
    }
    cout << "|";
  }

  void debug(int do_what = 0) //?for debugging purposes at last we will delete it 0=pause 1=pause & print
  {                           //!will remove this at last @viraj note down
#include <conio.h>            // * console input output library
    if (!do_what)
      getch();
    else
      cout << endl
           << "DEBUGING" << endl;
  }

  void startApp() //? for startup of home screen
  {
    if (MODULE_CHOICE == 0) //* only 1 time initiaization function need to be called after 1 time just we need ro refresh home screen so is/else here
    {
      initApp();
      MODULE_CHOICE = HomeScreen(); //return module choice for first time
    }
    else
    {
      MODULE_CHOICE = HomeScreen(); //return module choice after first time
    }
  }

  ~APP() {}

private:
  void initApp() //?setting up first time APP screen by making console in full screen
  {

    // get handle to the console window
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    // retrieve screen buffer info
    CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;
    GetConsoleScreenBufferInfo(hOut, &scrBufferInfo);

    // current window size
    short winWidth = scrBufferInfo.srWindow.Right - scrBufferInfo.srWindow.Left + 1;
    short winHeight = scrBufferInfo.srWindow.Bottom - scrBufferInfo.srWindow.Top + 1;

    // current screen buffer size
    short scrBufferWidth = scrBufferInfo.dwSize.X;
    short scrBufferHeight = scrBufferInfo.dwSize.Y;

    // to remove the scrollbar, make sure the window height matches the screen buffer height
    COORD newSize;
    newSize.X = scrBufferWidth;
    newSize.Y = winHeight;

    // set the new screen buffer dimensions
    SetConsoleScreenBufferSize(hOut, newSize);

    ::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);

    setConsoleSize();

    system("color F0"); //set white background and text black
  }

  

  int GetDesktopResolution() //? for getting particular device size screen
  {
    int size = 22;                            //specified intial size for small screen
    RECT desktop;                             // Get a handle to the desktop window
    const HWND hDesktop = GetDesktopWindow(); // Get the size of screen to the variable desktop
    GetWindowRect(hDesktop, &desktop);
    // The top left corner will have coordinates (0,0)
    // and the bottom right corner will have coordinates
    // (horizontal, vertical)

    int horizontal = desktop.right; // horizontal
    int vertical = desktop.bottom;  // vertical

    //-RM(remove at last) printf("h : %d v : %d ",horizontal,vertical);

    if (horizontal <= 600)
    {
      size = 30;
    } // ?setting up console inside size according to device size and resolution
    else if (horizontal <= 800)
    {
      size = 33;
    }
    else if (horizontal <= 1000)
    {
      size = 35;
    }
    else if (horizontal <= 1400)
    {
      size = 38;
    }
    else if (horizontal <= 1900)
    {
      size = 42;
    }
    else if (horizontal <= 2500)
    {
      size = 45;
    }
    else if (horizontal <= 3200)
    {
      size = 50;
    }
    else if (horizontal <= 4000)
    {
      size = 55;
    }
    else if (horizontal <= 4800)
    {
      size = 58;
    }

    return (size);
  }

  void setConsoleSize() //? for setting console size
  {
    CONSOLE_FONT_INFOEX cfi;  //structure variable
    cfi.cbSize = sizeof(cfi); //total bytes of cfi
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;                                                  // Width of each character in the font
    cfi.dwFontSize.Y = GetDesktopResolution();                             // Height getting
    cfi.FontFamily = FF_DONTCARE;                                          // font family doesn't matter
    cfi.FontWeight = FW_NORMAL;                                            //font normally bold
    std::wcscpy(cfi.FaceName, L"JetBrains Mono Bold");                     // Choose your font BY SETTING FONT FACE
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi); //pass reference of that structure to OUTPUT HANDLE
  }

protected:
  string CUR_DATE, CUR_TIME; //*CURRENT DATE TIME FOR APPLICATION
  int ConvertChoiceToINT;    //*variable for converting string input to integer

  void askChoice(int h, int v, string &input) //*general choice taking function
  {
    setCursorPos(h, v);
    ShowConsoleCursor(true);
    cout << "CHOICE : ";
    fflush(stdin);       //flushind standard input buffer
    getline(cin, input); //taking white space string input
    ShowConsoleCursor(false);
  }

  void InvalidInputErr() //*invalid input error function
  {
    scrClr(0.5);
    ShowConsoleCursor(false);
    setCursorPos(8, 26);
    SetColor(4);
    cout << "INVALID CHOICE ENTERTED !" << endl;
    setCursorPos(1, 20);
    cout << "PLEASE RE-ENTER YOUR CHOICE CORRECTLY !" << endl;
    ShowConsoleCursor(false);
    scrClr(1);
    SetColor(0);
  }
  void InvalidInputErr(string err_msg, int color, int pos) //? overloaded version //?medium level error
  {
    scrClr();
    setCursorPos(9, pos);     //set cursor position
    SetColor(color);          //setting text color
    ShowConsoleCursor(false); //hide cursor
    cout << err_msg << endl;  //error on sem semester creation
    scrClr(2);                // screen stops so user can read message
    SetColor(0);
  }

  void succeedMSG(string msg, string msg2, int color, int color2, int pos)
  {
    scrClr();
    setCursorPos(9, pos);
    SetColor(color);
    ShowConsoleCursor(false); //hide cursor
    cout << msg;              //mess 1 st
    SetColor(color2);
    cout << msg2; //mess 2  nd
    scrClr(2);    // screen stops so user can read message
    SetColor(0);
  }
  int validateString(string input, int Bnd, int start) //* string input validate as integer
  {

    int flag = 0, tem = 1;
    if (start == 0)
      start++;
    for (tem = start; tem <= Bnd; tem++)
    {

      if (to_string(tem) == input) //convert tem int to string to check input valid condition
      {
        flag = 1;
        break;
      }
    }

    if (flag == 0) //*IF flag=0 means input is invalid
    {
      InvalidInputErr(); //*error msg
      return 0;
    }
    else
    {
      return tem; //*returns converted string.to_int(INt)
    }
  }

int HomeScreen() //*ask choice at Home screen of APP
  {
    int line;

  gotoHomeScreen:

    Date(1, 15); //current date print
    Time(0, 16); //current time print

    setCursorPos(2);
    cout << setw(55) << " || ATTENDANCE MANAGEMENT SYSTEM ||" << endl; //TITLE OF APP

    string operationChoice;

    setCursorPos(1, 15);

    buildVerticalWall(43);

    line = 0; //* re used variable

    while (line < 11)
    {
      setCursorPos(1, 15);
      if (line == 1)
        buildHorizontalWall(43, "1) NEW SETUP FOR SEMESTER");
      else if (line == 3)
        buildHorizontalWall(43, "2) TAKE ATTENDANCE ");
      else if (line == 5)
        buildHorizontalWall(43, "3) CUSTOMIZED ATTENDANCE REPORT ");
      else if (line == 7)
        buildHorizontalWall(43, "4) SEARCH & UPDATE DETAILS ");
      else if (line == 9)
        buildHorizontalWall(43, "5) EXIT ");
      else
        buildHorizontalWall(43, " ");
      line++;
    }

    setCursorPos(1, 15);
    buildVerticalWall(43);

    askChoice(2, 30, operationChoice);

    if (!cin)
    {
      cin.clear();
      cin.ignore(80, '\n');
    }

    ConvertChoiceToINT = validateString(operationChoice, 5, 1);

    if (!ConvertChoiceToINT)
    {
      goto gotoHomeScreen;
    }

    return (ConvertChoiceToINT);
  }

  int validateString(string input) //?overloaded version of validating string input of yes/no
  {
    if (input == "YES" || input == "yes" || input == "Yes")
    {
      return 1; //yes
    }
    else if (input == "NO" || input == "no" || input == "No")
    {
      return 0; //no
    }
    else
    {
      return -1; // error
    }
  }
  void Date(int v, int h)
  {
    setCursorPos(v, h);
    cout << "DATE : ";
    SetColor(2);
    cout << CUR_DATE;
    SetColor(0);
  }
  void Time(int v, int h)
  {
    setCursorPos(v, h);
    cout << "TIME : ";
    SetColor(2);
    cout << CUR_TIME;
    SetColor(0);
  }
};

//---------STATIC DEFINATIONS  OF APP-----------//
int APP::MODULE_CHOICE = 0; //? MODULE CHOICE WILL BE ACT LIKE GLOBALLY
//---------------------------------------------//

/****************************APP-CLASS-END***************************/

/****************************MODULE-START*****************************************/
class MODULE_GENERAL : public APP
{
  //TODO: ALL MD development TEAM PLEASE CONTRIBUTE YOUR FUNCTIONS HERE AND INHERIT THIS CLASS TO YOURS
  // ? this are general function class which can be used by all 4 module developers
  // *email functionalities also be included here since all 2 modules are using it
  // ? you have to make functions very generalized so other MD developers can use it
  // ?use can you OOP concepts here function overloading and other...concepts like template

private:
public:
  MODULE_GENERAL()
  {
    AppPath(AMS_Path);
  }

  ~MODULE_GENERAL()
  {
  }

protected:
  virtual void SetNoObj() = 0; //*for disable object creation of APP

  //********** MAIN MODULE_GENERAL *************/

  string AMS_Path;
  string command;
  string SemPath;
  string tempStorage;

  /********************************************/

  //********** FACULTY *************/

  string FacultyName;
  string FacultyEmail;
  string course_name;
  string sem;
  string subject_name;

  /********************************/

  //********** STUDENT *************/

  string student_name;
  string student_email;
  string RoLLNo;
  string numberOfstudents;

  /*******************************/

  void AppPath(string &path) //?Getting Project path for each module Variable used Ams_Path for storing path
  {
    CHAR pathDocument[MAX_PATH];                                                                    //string to store path
    HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, pathDocument); //getting documents path

    if (result == S_OK) //check if  documents path is successfully stored in pathdocuments
    {
      path = pathDocument;   // take original documents path into string
      path = path + "\\AMS"; //making AMS folder path
    }
    else
    {
      cout << "ERROR PATH NOT FOUND : " << result << "\n"; //*error
    }
  }

  void getDataFromFile(string path, string &FcName, int lineNo) //?getData file given path form given line as string
  {
    ifstream read(path.c_str(), ios::in);

    if (!read.is_open())
    {
      cout << endl
           << "UNABLE TO OPEN THE FILE AT GIVEN PATH : " << path << endl;
    }
    else
    {
      int FileLine = 1;
      while (FileLine <= lineNo)
      {
        getline(read, FcName);
        FileLine++;
      }
    }
    read.close();
  }

  void writeDataToFile(string path, string &FcName) //?write string data to particular path file
  {
    ofstream write(path.c_str(), ios::app);

    if (!write.is_open())
    {
      cout << endl
           << "UNABLE TO OPEN THE FILE AT GIVEN PATH : " << path << endl;
    }
    else
    {
      write << FcName << endl;
    }
    write.close();
  }

  string convertIntToString(int &in) //?meaning itself defining
  {
    string str = to_string(in);
    return str;
  }

  string convertArrayTostring(char *arg) //?meaning itself defining
  {
    string re(arg);
    return re;
  }

  void replaceWithHyphen(string &str) //?file-folderName not allowed special symbols so hyphen conversion
  {
    int i = 0, j = 0;
    string list = "#%&{}\\/*>< $!:\'\"@+`|="; //*need to be checked as thease are restricated symbols

    for (i = 0; i <= list.length(); i++)
    {
      for (j = 0; j <= str.length(); j++)
      {
        if (str[j] == list[i])
        {
          str[j] = '-';
        }
      }
    }

    transform(str.begin(), str.end(), str.begin(), ::toupper); //*convert to uppercase
  }

  bool EmptyInput(string &input) //?checking if input is empty(hint : enter key)
  {
    if (input.empty())
    {
      return true; //if emty then returns  true
    }
    else
    {
      return false; // if not then returns false
    }
  }

  bool validateEmail(string email) //?checking for email validation (for space or any other special character which is not supported in email)
  {
    const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    return regex_match(email, pattern);
  }

  int dirExists(const char *path) //?checking if directory exists or not 1=EXIST 0=NOT EXIST
  {
    struct stat info;

    if (stat(path, &info) != 0)
      return 0;
    else if (info.st_mode & S_IFDIR)
      return 1;
    else
      return 0;
  }
};

class MODULE_1 : public MODULE_GENERAL //*module 1 class
{

  //*=============================DATA-MEMBERS================================//

private:
public:
protected:
  //*=============================DATA-MEMBERS-END================================//

  //*=============================MEMBERS-FUNCTIONS===================================//

private:
  int createSemester() //? return 1=semester created successfully & return 0=not created
  {

    tempStorage = course_name;
    replaceWithHyphen(tempStorage); //hyphen convert

    SemPath = AMS_Path + "\\" + tempStorage + "-SEM-" + sem; //making semesterpath with coursename

    tempStorage = subject_name;
    replaceWithHyphen(tempStorage); //hyphen convert

    SemPath = SemPath + "-" + tempStorage; //proper subject folder create

    if (!dirExists(SemPath.c_str())) //if directory not exists then create it
    {
      command = "mkdir " + SemPath; //making commad which will pass in cmd

      system(command.c_str()); // creating  directory by CMD

      /*********************  FOLDERS *******************/

      command = "mkdir " + SemPath + "\\DAILY-RECORD"; // making COMMAND FOR DAILY_RECORD folder

      system(command.c_str()); // creating DAILY_RECORD directory by CMD

      command = "mkdir " + SemPath + "\\FAC-STUD-DETAILS"; // making COMMAND FOR FAC&STUD_DETAILS folder

      system(command.c_str()); // creating FAC&STUD_DETAILS directory by CMD

      command = "mkdir " + SemPath + "\\MONTHLY-REPORTS"; // making COMMAND FOR MONTHLY_REPORTS folder

      system(command.c_str()); // creating MONTHLY_REPORTS directory by CMD

      /**************************************************/

      /*******************  FILES *********************/

      command = "cd. > " + SemPath + "\\DAILY-RECORD\\records.txt"; // RECORDS.TXT file
      system(command.c_str());

      command = "cd. > " + SemPath + "\\FAC-STUD-DETAILS\\faculty" + "-sem-" + sem + ".txt"; // faculty_details.TXT file
      system(command.c_str());

      command = "cd. > " + SemPath + "\\FAC-STUD-DETAILS\\student" + "-sem-" + sem + ".txt"; // student_details.TXT file
      system(command.c_str());

      tempStorage = course_name; //re used tempStorage
      replaceWithHyphen(tempStorage);

      command = course_name + "|" + sem + "|" + subject_name + "|" + tempStorage + "-SEM-" + sem + "-";

      tempStorage = subject_name; //re used tempStorage
      replaceWithHyphen(tempStorage);

      command = command + tempStorage; //command for making path for writting data to file

      tempStorage = AMS_Path + "\\OTHER\\semesterRecord.txt"; //* it will keep record of each semester that is created like all data of faculty | folderName

      writeDataToFile(tempStorage, command); //*writting data to file
      return 1;                              //all above code works then returns 1 = successfully
                                             /***********************************************/
    }
    else //if that semester already exist
    {
      InvalidInputErr("SEMSTER WITH THAT SUBJECT ALREADY EXIST !", 2, 19); //*overloadedversion called
      return 0;                                                            //returns 0=failed as we are trying to create that same folder again
    }
  }

  /************   FACULTY DETAILS CONFIRMATION AND MODIFICATION   ****************************/

  int confirmation() //basic confirmation message for user
  {
    int line;

  reConfirm:
    scrClr(0.5);
    setCursorPos(4, 15);
    cout << "FACULTY NAME " << right << setw(9) << ": " << FacultyName;
    setCursorPos(1, 15);
    cout << "FACULTY E-MAIL " << right << setw(7) << ": " << FacultyEmail;
    setCursorPos(2, 15);
    cout << "COURSE NAME " << right << setw(10) << ": " << course_name;
    setCursorPos(1, 15);
    cout << "SEMESTER " << right << setw(13) << ": " << sem;
    setCursorPos(1, 15);
    cout << "SUBJECT " << right << setw(14) << ": " << subject_name;
    setCursorPos(1, 15);
    cout << "NUMBER OF STUDENTS " << right << setw(3) << ": " << numberOfstudents;

    setCursorPos(2, 15);

    buildVerticalWall(43);
    line = 0;
    while (line < 3)
    {
      setCursorPos(1, 15);
      if (line == 1)
      {
        buildHorizontalWall(43, "Confirm these details (yes/no) ");
      }
      else
      {
        buildHorizontalWall(43, " ");
      }

      line++;
    }
    setCursorPos(1, 15);
    buildVerticalWall(43);

    setCursorPos(2, 30);

    fflush(stdin);
    ShowConsoleCursor(true);
    cout << "Type : ";
    getline(cin, tempStorage); //*re-used tempStorage for storage
    ShowConsoleCursor(false);

    ConvertChoiceToINT = validateString(tempStorage); //validate input

    if (ConvertChoiceToINT == -1) //validate input
    {
      InvalidInputErr(); //error message
      goto reConfirm;
    }

    return (ConvertChoiceToINT); //returns basic confirmation value yes=1 / no=0
  }

  int InfoModification() //? MODIFICATIONS OF FACULTY DETAILS
  {

    int line;
  reInputOfmodchoice:

    line = 0;
    setCursorPos(1);
    cout << setw(62) << " => WHICH INFORMATION DO YOU WANT TO MODIFY ? " << endl;

    setCursorPos(1, 25);

    buildVerticalWall(27);

    while (line < 13)
    {
      setCursorPos(1, 25);
      if (line == 0)
        buildHorizontalWall(27, "1) FACULTY NAME ");
      else if (line == 2)
        buildHorizontalWall(27, "2) FACULTY E-MAIL ");
      else if (line == 4)
        buildHorizontalWall(27, "3) COURSE NAME ");
      else if (line == 6)
        buildHorizontalWall(27, "4) SEMESTER ");
      else if (line == 8)
        buildHorizontalWall(27, "5) SUBJECT ");
      else if (line == 10)
        buildHorizontalWall(27, "6) NUMBER OF STUDENTS ");
      else if (line == 12)
        buildHorizontalWall(27, "7) NO CHANGE ");
      else
        buildHorizontalWall(27, " ");
      line++;
    }

    setCursorPos(1, 25);
    buildVerticalWall(27);

    askChoice(2, 32, tempStorage);

    if (!cin)
    {
      cin.clear();
      cin.ignore(80, '\n');
    }
    ConvertChoiceToINT = validateString(tempStorage, 7, 1); //validate input

    if (ConvertChoiceToINT == 0) //if wrong input
    {
      goto reInputOfmodchoice; //re take choice of modification
    }
    else
    {
      return (ConvertChoiceToINT); //returns number option of modification
    }
  }

  /***************************************************************************/

  /********** STUDENT DETAILS CONFIRMATION AND MODIFICATION **********/

  int studConfirmation() //?basic confirmation message for user
  {
    int line;

  reConfirm:

    setCursorPos(5, 15);
    cout << "STUDENT ROLL NO " << right << setw(4) << ": " << RoLLNo;
    setCursorPos(1, 15);
    cout << "STUDENT NAME " << right << setw(7) << ": " << student_name;
    setCursorPos(1, 15);
    cout << "STUDENT E-MAIL " << right << setw(5) << ": " << student_email;

    setCursorPos(2, 15);
    buildVerticalWall(43);

    line = 0;
    while (line < 3)
    {
      setCursorPos(1, 15);
      if (line == 1)
      {
        buildHorizontalWall(43, "Confirm these details (yes/no) ");
      }
      else
      {
        buildHorizontalWall(43, " ");
      }

      line++;
    }
    setCursorPos(1, 15);
    buildVerticalWall(43);

    setCursorPos(2, 30);

    fflush(stdin);
    ShowConsoleCursor(true);
    cout << "Type : ";
    getline(cin, tempStorage); //*re-used tempStorage for storing
    ShowConsoleCursor(false);

    ConvertChoiceToINT = validateString(tempStorage);

    if (ConvertChoiceToINT == -1) //validate input
    {
      InvalidInputErr(); //error message
      goto reConfirm;
    }

    return (ConvertChoiceToINT); //returns basic confirmation value yes=1 / no=0
  }

  int InfoStudModification() //? MODIFICATIONS OF STUDENTS DETAILS
  {

    int line;
  reInputOfmod:

    line = 0;
    setCursorPos(3);
    cout << setw(62) << " => WHICH INFORMATION DO YOU WANT TO MODIFY ? " << endl;

    setCursorPos(2, 25);

    buildVerticalWall(23);

    while (line < 7)
    {
      setCursorPos(1, 25);
      if (line == 1)
        buildHorizontalWall(23, "1) STUDENT NAME ");
      else if (line == 3)
        buildHorizontalWall(23, "2) STUDENT E-MAIL ");
      else if (line == 5)
        buildHorizontalWall(23, "3) NO CHANGE");
      else
        buildHorizontalWall(23, " ");
      line++;
    }

    setCursorPos(1, 25);
    buildVerticalWall(23);

    askChoice(3, 32, tempStorage);

    if (!cin)
    {
      cin.clear();
      cin.ignore(80, '\n');
    }
    ConvertChoiceToINT = validateString(tempStorage, 3, 1); //validate input

    if (ConvertChoiceToINT == 0) //if wrong input
    {
      goto reInputOfmod; //re take choice of modification
    }
    else
    {
      return (ConvertChoiceToINT); //returns number option of modification
    }
  }

  /************************************************************************/

  void UpdateName(string &input) //?Faculty & student name update input
  {
  reinput:
    scrClr(0.5);
    setCursorPos(9, 20);
    cout << "ENTER NAME : ";
    fflush(stdin);
    ShowConsoleCursor(true);
    getline(cin, input);
    ShowConsoleCursor(false);
    if (EmptyInput(input))
    {
      InvalidInputErr(); // input error
      goto reinput;
    }
  }
  void UpdateEmail(string &input) //?Faculty-student email address update & input
  {
  reinputOfEmail:
    scrClr(0.5);
    setCursorPos(9, 16);
    cout << "ENTER E-MAIL : ";
    fflush(stdin);
    ShowConsoleCursor(true);
    getline(cin, input);
    ShowConsoleCursor(false);
    if (EmptyInput(input))
    {
      InvalidInputErr(); // input error
      goto reinputOfEmail;
    }
    else if (!validateEmail(input)) //email validation
    {
      InvalidInputErr("INVALID E-MAIL ADDRESS !", 4, 26);
      goto reinputOfEmail;
    }
    scrClr(0.5); //screen stops for reading
  }
  void EnterCourseName() //?course name input
  {
  reinputOfcourseName:
    scrClr(0.5);
    setCursorPos(9, 26); //set Cursor Position
    cout << "ENTER COURSE NAME : ";
    fflush(stdin);
    ShowConsoleCursor(true);     // show cursor for taking input
    getline(cin, course_name);   //input
    ShowConsoleCursor(false);    // hide cursor for flickring cursor
    if (EmptyInput(course_name)) // if empty input like enter key so we have set error for that
    {
      InvalidInputErr(); //error on wrong input
      goto reinputOfcourseName;
    }
    scrClr(0.5);
  }
  void EnterSem() //?input of semester
  {
  reinputOfsem:
    scrClr(0.5); //clear screen
    fflush(stdin);
    setCursorPos(9, 26);
    cout << "ENTER SEMESTER : ";
    fflush(stdin);
    ShowConsoleCursor(true);  // show cursor for taking input
    getline(cin, sem);        //input
    ShowConsoleCursor(false); // hide cursor for flickring cursor

    if (!validateString(sem, 10, 1)) //validate sem input
    {
      goto reinputOfsem;
    }
  }
  void EnterSubject() //?input subject
  {
  reinput:
    scrClr(0.5);
    setCursorPos(9, 26);
    cout << "ENTER SUBJECT : ";
    ShowConsoleCursor(true); // show cursor for taking input
    fflush(stdin);
    getline(cin, subject_name);   //input
    ShowConsoleCursor(false);     // hide cursor for flickring cursor
    if (EmptyInput(subject_name)) // if empty input like enter key so we have set error for that
    {
      InvalidInputErr(); //error on wrong input
      goto reinput;
    }
  }

  void rollNo(int RollNo) //?show Roll Number
  {
    scrClr(0.5);              //clear screen
    ShowConsoleCursor(false); // hide cursor to stop flickring cursor
    setCursorPos(9, 27);
    cout << " ROLL NO. : " << RollNo;
    scrClr(1); // user can read no.
  }

  void askNumberOfStudents() //?asking number of students
  {
  reAskNumStud:
    scrClr(0.5);
    setCursorPos(7, 23);
    cout << " HOW MANY STUDENTS DO YOU HAVE ? ";
    setCursorPos(4, 27);
    cout << "NUMBER OF STUDENT : ";
    fflush(stdin);
    ShowConsoleCursor(true);
    getline(cin, numberOfstudents);
    ShowConsoleCursor(false);
    ConvertChoiceToINT = validateString(numberOfstudents, 5000, 1);
    if (ConvertChoiceToINT == 0)
    {
      goto reAskNumStud;
    }
  }

public:
  MODULE_1()
  {
  }

  void askFacDetails() //?asking faculty details
  {

  reAskFacDet: //re asking  details of faculty

    EnterCourseName(); //course name input
    EnterSem();        //sem input
    EnterSubject();    //subject input

    if (!createSemester()) //semester confirmation
    {
      goto reAskFacDet; //*reasking faculty details as semester already exists
    }

    askNumberOfStudents(); //number of students

    command = AMS_Path + "\\USER-INFO\\userdetails.txt"; // making path for getting data from file

    getDataFromFile(command, FacultyName, 1);  //taking data of from file
    getDataFromFile(command, FacultyEmail, 2); //taking data of from file

  confirmAgain: //final confirmation

    if (confirmation()) // basic confirmation dialog if yes then semester folder create
    {
      command = SemPath + "\\FAC-STUD-DETAILS\\faculty" + "-sem-" + sem + ".txt"; //path making for writting into file

      writeDataToFile(command, FacultyName); //writting faculty data to files
      writeDataToFile(command, FacultyEmail);
      writeDataToFile(command, course_name);
      writeDataToFile(command, sem);
      writeDataToFile(command, subject_name);
      writeDataToFile(command, numberOfstudents);
    }
    else
    {
      scrClr(0.5); //clear screen so flickring won't happen

      switch (InfoModification()) //which details do you want to update that function returns
      {
      case 1:
      {
        UpdateName(FacultyName);
        break;
      } // each function called according to requirement
      case 2:
      {
        UpdateEmail(FacultyEmail);
        break;
      }
      case 3:
      {
        EnterCourseName();
        break;
      }
      case 4:
      {
        EnterSem();
        break;
      }
      case 5:
      {
        EnterSubject();
        break;
      }
      case 6:
      {
        askNumberOfStudents();
        break;
      }
      case 7:
      {
        scrClr(0.5);
        break;
      }
      }
      goto confirmAgain; //ask user to final confirmation
    }
  }

  void askStudDetails() //? asking students details
  {
    int ROLLNO = 0;
    while (ROLLNO < stoi(numberOfstudents))
    {
      ROLLNO++;

      rollNo(ROLLNO);             // for take input of roll no
      UpdateName(student_name);   //for take input of student name
      UpdateEmail(student_email); //for taking input of email

    confirmAgain: //final confirmation
      RoLLNo = convertIntToString(ROLLNO);
      if (studConfirmation()) // basic confirmation dialog if yes then semester folder create
      {
        command = SemPath + "\\FAC-STUD-DETAILS\\student" + "-sem-" + sem + ".txt"; //path making for writting into file
        RoLLNo = convertIntToString(ROLLNO);                                        //rollNo Int to string
        tempStorage = RoLLNo + "|" + student_name + "|" + student_email;            // folder name
        writeDataToFile(command, tempStorage);                                      //writting data to files
      }
      else
      {
        scrClr(0.5); //clear screen so flickring won't happen

        switch (InfoStudModification()) //which details do you want to update that function returns
        {
        case 1:
        {
          UpdateName(student_name);
          break;
        }
        case 2:
        {
          UpdateEmail(student_email);
          break;
        }
        case 3:
        {
          scrClr(0.5);
          break;
        }
        }
        goto confirmAgain; //ask user to final confirmation
      }
    }
  }

  void SetUpSucceed() //module 1 successfully worked
  {
    tempStorage = course_name + " SEM " + sem + " " + subject_name;
    succeedMSG("SET UP SUCCESSFUL OF ", tempStorage, 2, 0, 20);
  }

  ~MODULE_1() //TODO:DESTRUCTOR
  {
  }

protected:
  void SetNoObj()
  {
    //? by empty defination of pure virtual function here we are restricating creation of parent class
  }
  //*==============================MEMBERS-FUNCTIONS===================================//
};

class MODULE_2 : public MODULE_GENERAL //*module 2 class
{

  //******************************** DATA -MEMBERS *********************************/
private:
  vector<string> buffer, LIST;                        //vector buffer for file handling data receiver
  vector<tuple<string, string, string, string>> DATA; // search-access vector-tuple

public:
protected:
  //*********************************************************************************/

  //******************************** MEMBER-FUNCTIONS *********************************/
private:

  int checkDuplicateRecord(vector<string> vec, string search) //*for cheking if duplicate records found in vector_storage
  {
    vector<string>::iterator it; //iterator

    it = find(vec.begin(), vec.end(), search); // finding elemnt in vector

    if (it != vec.end())
    {
      return 0; // if found then return 0
    }
    else
    {
      return 1; // if not found then return 1
    }
  }

  void DisplayList_Input(string &put, int select = 0) //* display the list and take appropriate input of corse/sem/subject
  {
    int listFlag = 1, chFlag = 0, countFlag = 0, temp = 1;
    auto i = LIST.begin();

    setCursorPos(1, 20);
    buildVerticalWall(35);
    setCursorPos(1, 20);
    buildHorizontalWall(35, " ");

    while (i != LIST.end())
    {

    displayAgain:
      chFlag = 0;
      setCursorPos(1, 20);
      if (select == 0)
        buildHorizontalWall(35, to_string(5 * countFlag + listFlag) + ") " + (*i));
      else
        buildHorizontalWall(35, to_string(5 * countFlag + listFlag) + ") " + "Sem-" + (*i));
      setCursorPos(1, 20);
      buildHorizontalWall(35, " ");
      listFlag++;
      i++;

      if (listFlag > 5 && i != LIST.end())
      {

        chFlag = 1;
        countFlag++;
        setCursorPos(1, 20);
        buildHorizontalWall(35, "TYPE '+' FOR EXTENDED LIST");
        setCursorPos(1, 20);
        buildHorizontalWall(35, " ");
        setCursorPos(1, 20);
        buildVerticalWall(35);
        askChoice(2, 35, tempStorage);
        scrClr(0.5);
        if (tempStorage == "+")
        {
          setCursorPos(1, 20);
          buildVerticalWall(35);
          listFlag = 1;
          chFlag = 0;
          setCursorPos(1, 20);
          buildHorizontalWall(35, " ");
          goto displayAgain;
        }
        else
        {
          ConvertChoiceToINT = validateString(tempStorage, countFlag * 5, (countFlag - 1) * 5);
          if (ConvertChoiceToINT == 0)
          {
            while (temp != (listFlag))
            {
              i--;
              temp++;
            }
            temp = 1;
            countFlag--;
            listFlag = 1;
            setCursorPos(1, 20);
            buildVerticalWall(35);
            chFlag = 0;
            setCursorPos(1, 20);
            buildHorizontalWall(35, " ");
            goto displayAgain;
          }
          else
          {
            break;
          }
        }
      }
    }
    if (chFlag == 0)
    {
      setCursorPos(1, 20);
      buildVerticalWall(35);
      askChoice(2, 30, tempStorage);

      if (tempStorage == "+")
      {
        InvalidInputErr();
        while (temp != (listFlag))
        {
          i--;
          temp++;
        }
        temp = 1;
        listFlag = 1;
        setCursorPos(1, 20);
        buildVerticalWall(35);
        setCursorPos(1, 20);
        buildHorizontalWall(35, " ");
        goto displayAgain;
      }
      ConvertChoiceToINT = validateString(tempStorage, (((countFlag)*5 + listFlag - 1)), ((countFlag)*5));
      if (ConvertChoiceToINT == 0)
      {
        while (temp != (listFlag))
        {
          i--;
          temp++;
        }
        temp = 1;
        listFlag = 1;
        setCursorPos(1, 20);
        buildVerticalWall(35);
        setCursorPos(1, 20);
        buildHorizontalWall(35, " ");
        goto displayAgain;
      }
      scrClr(0.5);
    }
    for (i = LIST.begin(), countFlag = 1; i != LIST.end(); ++i, countFlag++) // set data to string for searching
    {
      if (countFlag == ConvertChoiceToINT)
      {
        put = (*i);
      }
    }

    LIST.clear();        //flush vector data for re-using
    tempStorage.clear(); //flush string for re-using
  }

  void getFolderPath()
  {
    for (auto i = DATA.begin(); i != DATA.end(); ++i) //process to find folder path using vector tuple we have 3 input parameter coursename , sem , subject name
    {

      if (course_name == get<0>((*i)))
        if (sem == get<1>((*i)))
          if (subject_name == get<2>((*i)))
            SemPath = get<3>((*i));
    }
    SemPath = AMS_Path + "\\" + SemPath;
    //cout<<endl<<SemPath;
    //scrClr(2);
  }
  void getSemesterRecordFile() //* get data of course-semester-sub-path records
  {
    tempStorage = AMS_Path + "\\OTHER\\semesterRecord.txt"; //making path to AMS->OTHER->semsterRecord.txt
    fstream fin(tempStorage.c_str(), ios::in);              // file opened in reading mode

    if (!fin.is_open()) // if not opened
    {
      cout << " DATABASE ERROR 404 : FILE NOT OPENED !";
    }
    else // if opened
    {
      tempStorage.clear();       // clear for re-using
      getline(fin, tempStorage); // tempStorage used as temporary storage

      while (!fin.eof()) // data receive until file ends
      {
        buffer.push_back(tempStorage); // save that string(data) in vector
        getline(fin, tempStorage);     // fetch again from file
      }
      fin.close(); //file close
    }

    sort(buffer.begin(), buffer.end()); //sorted file data in vector in Dictionary order
    tempStorage.clear();                //clearing for re-using
  }

  void ExtractStringFromBuffer() //* extracting main string into substring like course - sem - sub - path
  {
    for (auto i = buffer.begin(); i != buffer.end(); ++i) //insert in to vector-tuple from vector buffer with extracting string
    {
      tempStorage = (*i);      // temp variable for moving vector tempStorage to string
      int found_pos, temp_pos; // temp variable for position storing

      found_pos = tempStorage.find("|");                // find the first occurance of '|'
      course_name = tempStorage.substr(0, (found_pos)); // get proper course name from string and save it to course_name
      temp_pos = (found_pos + 1);                       // making next finding position

      if (checkDuplicateRecord(LIST, course_name)) // cheking if duplicate course
      {
        LIST.push_back(course_name); //making list for input of UI screen of course select
      }

      found_pos = tempStorage.find("|", temp_pos);                //finds string till 1st pipe i.e coursename
      sem = tempStorage.substr(temp_pos, (found_pos - temp_pos)); //stores the string in TEMP_STR
      temp_pos = (found_pos + 1);                                 //searching next position

      found_pos = tempStorage.find("|", temp_pos);                         //finds string till 2nd pipe i.e. semester
      subject_name = tempStorage.substr(temp_pos, (found_pos - temp_pos)); //stores the string in TEMP_STR
      temp_pos = (found_pos + 1);                                          //searching next position

      found_pos = tempStorage.find("|", temp_pos); //finds string till 3rd pipe i.e. subjectname
      SemPath = tempStorage.substr(temp_pos);      //stores the string in TEMP_STR

      DATA.push_back(make_tuple(course_name, sem, subject_name, SemPath)); //makes a final string to display
    }
    tempStorage.clear();  //clearing for reusing
    course_name.clear();  //clearing for reusing
    sem.clear();          //clearing for reusing
    subject_name.clear(); //clearing for reusing
    SemPath.clear();      //clearing for reusing
  }

public:
  MODULE_2()
  {
  }

  bool checkDB() //* functions for checking first time database semster Records exists or not
  {

    tempStorage = AMS_Path + "\\OTHER\\semesterRecord.txt"; //making path to AMS->OTHER->semsterRecord.txt
    fstream read(tempStorage.c_str(), ios::in);             // file opened

    bool isEmpty;

    isEmpty = read.peek() == EOF; // check if file is empty or not
    if (isEmpty)
    {
      InvalidInputErr("NO SETUP EXIST ! PLEASE ADD ATLEST 1 SETUP", 4, 19);
      read.close();
      isEmpty = false;
    }
    else
    {
      read.close();
      getSemesterRecordFile();
      ExtractStringFromBuffer();
      isEmpty = true;
    }

    tempStorage.clear(); //clear for re-using
    return (isEmpty);
  }

  void askCourseChoice() //* take input choice of course for attendance
  {
    DisplayList_Input(course_name);

    for (auto i = DATA.begin(); i != DATA.end(); ++i) //process to make list of semester in particular course
    {

      if (course_name == get<0>((*i)))
      {
        if (checkDuplicateRecord(LIST, get<1>((*i)))) // cheking if duplicate
        {
          LIST.push_back(get<1>((*i))); //making distinguish list
        }
      }
    }
  }
  void askSemsterChoice() //* take input choice of semester for attendance
  {
    DisplayList_Input(sem, 1);

    for (auto i = DATA.begin(); i != DATA.end(); ++i) //process to make list of subject in particular course & semester
    {
      if (course_name == get<0>((*i)) && sem == get<1>((*i)))
      {
        if (checkDuplicateRecord(LIST, get<2>((*i)))) // cheking if duplicate
        {
          LIST.push_back(get<2>((*i))); //making distinguish list
        }
      }
    }
  }
  //TODO: TEAM VIRAJ-SANJAL-SHIKHAA-NUPUR CODE
  //* ******************************************************************************** *//

  //* YOUR FUCTIONS DEFINATIONS SHOULD BE HERE SO THAT IT CAN BE CALLED IN MAIN
  //* e.g. confirmation()

  bool confirm2() //* functions for reconfirming to proceed to attendance
  {
    scrClr(0.5);              //clear screen
    ShowConsoleCursor(false);

    Date(1, 15); //current date print
    Time(0, 16); //current time print

    

    /*string data;      //previous logic 
    int i=0;
    ifstream fin(SemPath + "\\FAC-STUD-DETAILS\\faculty.txt");

    if (!fin.is_open())
    {
        cout << " File isn't opened! "<<endl;
    }
    else
    {
        while (!fin.eof())
        {
            while (getline(fin,data))
            {
                setCursorPos(1, 35);
                buildHorizontalWall(35, data);
                setCursorPos(1, 35);
                buildHorizontalWall(35, " ");
            }
        }
    }
    setCursorPos(1, 35);
    buildVerticalWall(35);
    fin.close();*/

   command = SemPath + "\\FAC-STUD-DETAILS\\faculty.txt"; //making path to AMS->OTHER->semsterRecord.txt
    fstream read(tempStorage.c_str(), ios::in);             // file opened

    bool isEmpty;
    bool response;
    isEmpty = read.peek() == EOF; // check if file is empty or not
    if (isEmpty)
    {
      InvalidInputErr(" NO DATA AVAILABLE ", 4, 19);
      read.close();
      isEmpty = false;
    }
    else
    {
      setCursorPos(1, 20);
      buildVerticalWall(35);
      setCursorPos(1, 20);
      buildHorizontalWall(35, " ");

      cout<<" Confirmed Details : "<<endl;
      getDataFromFile(command,FacultyName,1);
      getDataFromFile(command,FacultyEmail,2);
      getDataFromFile(command,course_name,3);
      getDataFromFile(command,subject_name,4);
      getDataFromFile(command,sem,5);

      setCursorPos(1, 35);
      buildVerticalWall(35);

      read.close();

      cout<<"  Proceed further to take Attendance ? [Press 1 to proceed / 0 to exit ] "<<endl;
      cin>>response;
      if(response==1)
      {
          //further functions 
      }
      else
      {
         HomeScreen();
      }
       
    }
    tempStorage.clear(); //clear for re-using
   
    return (isEmpty);
  }

//* ******************************************************************************************* *//

  void askSubjectChoice() //* take input choice of subject for attendance
  {
    DisplayList_Input(subject_name);
    getFolderPath();
  }

  ~MODULE_2()
  {
    buffer.clear(); //clearing buffer
    LIST.clear();   //clearing List
  }

protected:
  void SetNoObj()
  {
    //? by empty defination of pure virtual function here we are restricating creation of parent(GENERAL MODULE) class
  }
  //************************************************************************************/
};

//---------------------------STATIC DEFINATIONS-MODULE-2------------------------------/

//-----------------------------------------------------------------------------------/

/****************************MODULE-END************************************/

int main()
{
  //*jay swaminrayan *//
  //*jay ganeshay namh *//
  //*jay kashtbhanjan dev *//

  bool loop = true; //set true to run app by 1 time

  APP A;

  while (loop)
  {
    A.startApp();
    A.scrClr();
    A.setCursorPos(2, 10);

    switch (APP::MODULE_CHOICE) // module choice asking
    {
    case 1:
    {
      MODULE_1 MD1;
      MD1.askFacDetails();
      MD1.askStudDetails();
      MD1.SetUpSucceed();
      break;
    }
    case 2:
    {
      MODULE_2 MD2;
      if (MD2.checkDB())
      {
        MD2.askCourseChoice();
        MD2.askSemsterChoice();
        MD2.askSubjectChoice();

        //TODO: TEAM VIRAJ-SANJAL-SHIKKHA-NUPUR CODE HERE
        //* phase 2 start
        //* //TODO: TEAM VIRAJ YOUR FUNCTION CALL START FROM HERE confirmation()
        if(MD2.confirm2())
        {

        }
        else
        {
           
        }

        //TODO: TEAM DRASHTI-SHUBHAM-HARSHIL
        //* phase 3 start
      }
      break;
    }
    case 3:
    {
      break;
    }
    case 4:
    {
      break;
    }
    case 5:
    {
      loop = false; // exit Application
      break;
    }
    default:
    {
      cout << endl
           << "ERROR: APPLICATION CRASHED!!!" << endl;
      exit(1);
      break;
    } //* exception case
    }

    A.scrClr(); // screen clear
  }

  return 0;
}

//*name  email  course subject sem date-time