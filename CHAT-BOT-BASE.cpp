#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

bool doesFileExist(const char *fileName) //Check whether or not our data file exists
{
    ifstream infile(fileName);
    return infile.good();
}

int main(){

  int loop = 0;

  if(doesFileExist("ChatBotData.txt") == true){ //if the Data file exists, then we can start teaching the chat bot
    for(loop = 1; loop > 0; loop++){
      string Input, Output, Holder, DataInput, DataOutput, TEMP;
      int Index, isThereCount;
      isThereCount = 0;
      bool wasInputFound = false;

      ifstream DataFile;
      ofstream OutputDataFile;

      DataFile.open("ChatBotData.txt");

      int numberOfLines = 0;

      while(getline(DataFile, TEMP)){
        numberOfLines++;
      }

      DataFile.close();

      DataFile.open("ChatBotData.txt");

      cout << "> \b";
      getline(cin, Input, '\n');

      if(Input == "Exit." || Input == "Stop." || Input == "Go away." || Input == "Terminate."){
        return 0;
      }
      else{
        while(getline(DataFile, Holder)){
          Index = Holder.find("=");
          DataInput = Holder.substr(0,Index);

          if(DataInput == Input){
            wasInputFound = true;
            DataOutput = Holder.substr(Index+1, Holder.length());
          }
          else{
            isThereCount++;
            wasInputFound = false;
            if(isThereCount == numberOfLines){
              string EQUATE;
              cout << Input << endl << ">> \b";
              getline(cin, EQUATE, '\n');
              OutputDataFile.open("ChatBotData.txt", std::ios_base::app);
              OutputDataFile << endl << Input << "=" << EQUATE;
              OutputDataFile.close();
            }
          }

          if(wasInputFound == true){
            cout << ">" << DataOutput << endl;
          }
        }
      }
    }

  }
  else{
    std::ofstream CreatedFile("ChatBotData.txt");
    CreatedFile << "\n" << endl;
    CreatedFile.close();

    cout << "The Data file has been created, please restart ChatBot";
  }
  return 0;
}
