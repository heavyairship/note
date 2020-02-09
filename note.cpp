#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <string>
#include <time.h>
#include <unistd.h>

using namespace std;

int 
main(int argc, char* argv[]) {
  // FixMe: have an option to vc/backup notes file on git
  // FixMe: add ability to encryt locally and in vc.
  // FixMe: add dank C++ APIs

  if(argc<2) {
    return 0;
  }

  int help = 0;
  int showshort = 0;
  int showlong = 0;
  char *cvalue = NULL;
  int index;
  int c;
  opterr = 0;

  // Parse arguments
  while ((c = getopt(argc, argv, "hsl")) != -1)
    switch (c) {
      case 'h':
        help = 1;
        break;
      case 's':
        showshort = 1;
        break;
      case 'l':
        showlong = 1;
        break;
      case 'e':
        encrypt = 1;
        break;
      case '?':
        if (isprint (optopt)) {
          fprintf(stderr, "Unknown option `-%c'.\n", optopt);
        } else {
          fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
        }
        return -1;
      default:
        abort();
    }

  // Print help
  if(help) {
    cout << "\n"
         << "Usage: note [-h -s -l] [message]\n"
         << "Appends a note message to $NOTE_PATH/notes.txt if set or $HOME/notes.txt by default\n"
         << "Options:\n"
         << "\t -h  print this message\n"
         << "\t -s  show the last 10 lines of the notes file\n"
         << "\t -l  show the whole notes file\n"
         << "\t -e  encrypt file\n"
         << "\n";
    return 0;
  }

  // FixMe: check for path validity
  // Compute path to notes file
  stringstream path;
  char const* const notepath(getenv("NOTE_PATH"));
  char const* const homepath(getenv("HOME"));
  if(notepath) {
    path << notepath; 
  } else if(homepath) {
    path << homepath;
  } else {
    cerr << "Must set env var NOTE_PATH or HOME." << endl;
    return -1;
  }
  path << "/notes.txt";

  string line;
  ifstream infile(path.str());
  int numlines;
  while(getline(infile, line)) {
    ++numlines;
  }

  // Print last 10 lines of notes file
  if(showshort) {
    infile.clear();
    infile.seekg(0, ios::beg);
    int start = numlines < 10 ? 0 : numlines - 10;
    int end = numlines;
    int curr = 0;
    while(getline(infile, line)) {
      if(curr >= start && curr < numlines) {
        cout << line << "\n";
      }
      ++curr;
    }
    infile.close();
    return 0;
  }

  // Print entire notes file
  if(showlong) {
    infile.clear();
    infile.seekg(0, ios::beg);
    while(getline(infile, line)) {
      cout << line << "\n";
    }
    infile.close();
    return 0;
  }

  // Write a note
  ofstream ofile(path.str(), ios::app);
  if(!ofile.is_open()) {
    cerr << "Could not open file." << endl;
    return -1;
  }
  time_t rawtime;
  struct tm* timeinfo;
  char timebuff[80];
  time(&rawtime);
  timeinfo = localtime(&rawtime);
  strftime(timebuff,80,"%Y-%m-%d--%H:%M:%S",timeinfo);
  ofile << timebuff << " @@ " << argv[1] << "\n";
  ofile.close();

  return 0;
}
