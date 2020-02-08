#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <time.h>

using namespace std;

int 
main(int argc, char* argv[]) {
  // FixMe: do proper argument parsing.
  // FixMe: add option --help to show help info.
  // FixMe: add option --show to cat the notes.txt file.
  // FixMe: handle exclamation points

  if(argc<2) {
    return 0;
  }

  // FixMe: check for path validity.
  stringstream path;
  char const* const notepath(getenv("NOTE_PATH"));
  char const* const homepath(getenv("HOME"));
  string pathpre;
  if(notepath) {
    pathpre = notepath; 
  } else if(homepath) {
    pathpre = homepath;
  } else {
    cerr << "Must set env var NOTE_PATH or HOME." << endl;
    return -1;
  }
  path << pathpre << "/notes.txt";

  ofstream myfile(path.str(), ios::app);
  if(!myfile.is_open()) {
    cerr << "Could not open file." << endl;
    return -1;
  }

  time_t rawtime;
  struct tm* timeinfo;
  char timebuff[80];

  time(&rawtime);
  timeinfo = localtime(&rawtime);
  strftime(timebuff,80,"%Y-%m-%d--%H:%M:%S",timeinfo);
  myfile << timebuff << " @@ " << argv[1] << "\n";

  myfile.close();
  return 0;
}
