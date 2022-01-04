#include <iostream>
#include <windows.h>
#include <fstream>
#include <stdlib.h>
#include <direct.h>
#include <shlobj.h>

using namespace std;

class dataBase
{
    private:

    string tempStorage,command;
    bool lockdb_flag;
    string AMS_Path;

    void checkIfalreadyLockedDb()
    {
     string locker = AMS_Path + "\\OTHER\\mn-cs-gxv-jsnfe-1008-jsn-db-lock.ini";

     if(fileExists(locker))
     {
       lockdb_flag = false;
     }
     else
     {
       lockdb_flag = true;
     }

    }

    bool fileExists(const string &path) //checking function if file exists or not 
    {   
       bool status_flag = false;
       ifstream read(path.c_str(),ios::binary|ios::in);     // file opened in binary mode 
       if(!read.is_open())
       {
        status_flag=false; // not exists 
       }
       else
       {
         status_flag=true; //exists
       }
       read.close();
       return(status_flag); 
    }

    void writeDataToFile(string path, string write_data) //?write string data to given path file at latest line
    {
        ofstream write(path.c_str(), ios::app); //file opened in write mode 
    
        if (!write.is_open())//if file is not opened 
        { 
          cout << "something went wrong...";
          exit(1);
        }
        else
        {
          write << write_data << endl; // write data
        }
         write.close();//file closed
    }

    string getDataBasePath()
    {

      CHAR pathDocument[MAX_PATH];   // string to store path
      HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL,SHGFP_TYPE_CURRENT,pathDocument); // getting documents path
  
      if (result == S_OK) // check if documents path is successfully stored in pathdocuments
      {
        AMS_Path = pathDocument;       // take original documents path into string
        AMS_Path = AMS_Path + "\\{JSN-1008-JSK-22-10-2021}"; // making AMS folder path
      }
      else
      { 
        cout <<endl << "something went wrong....";
        exit(1);
      }

      return(AMS_Path);
    }
   

    public:

    void lockDataBase() 
    {  
        if(lockdb_flag)
        {

        string path = AMS_Path;
        tempStorage = path ;
        path = path + "\\OTHER\\mn-cs-gxv-jsnfe-1008-jsn-db-lock.ini";
        writeDataToFile(path,"[.shellClassInfo]");
        writeDataToFile(path,"CLSID = {63E23168-BFF7-4E87-A246-EF024425E4EC}");
        
        command = "attrib +h +s " + tempStorage;
        WinExec(command.c_str(),0);

        }
        
    }  

    dataBase()
    {
      lockdb_flag=false;
      getDataBasePath();
      checkIfalreadyLockedDb();
    }
    ~dataBase()
    {
   
    }

    protected:

};

int main()
{   
    dataBase D;
    D.lockDataBase();
    return(0);
}
