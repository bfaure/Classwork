#ifndef WIKIPAGE_H
#define WIKIPAGE_H

//Written by Brian Faure
//Tested by Brian Faure
//Debugged by Brian Faure

#include <string>
using std::string;
using std::getline;
using std::size_t;
using std::to_string;

#include <vector>
using std::vector;

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <time.h>
#include <unistd.h>
#include <limits>
#include <stdio.h>
#include <sys/stat.h>
#include <algorithm>

#include <iostream>
using std::cout;
using std::endl;
using std::ostream;
using std::cin;



class wikiPage
{
public:
    string          title;
    string          ns;
    string          text;
    vector<string>  categories;
    bool            isRedirect;
    string          redirection;
    int             quality;
    string          contrib;
    string          timestamp;
    short           pic;
    string          templates;
    vector<string>  template_vec;
    short           version;
    bool            isJunk;
    string          classification;
    unsigned long   size;
    string          save_location;

    wikiPage(string pagestr);
    wikiPage(ifstream &wikiFile);
    wikiPage(string pagestr, bool formatting);
    wikiPage(string pagestr, bool formatting, string code);

    void save(ofstream &file);
    void saveHTML(ofstream &file);
    void save_basic(ofstream &file);

    void removeFormatting();
    void removeJunk();
    friend ostream& operator<<(ostream& os, wikiPage& wp);
};

void removeBetween(string &temp, string target, string endtarget);


string get_path();
void create_directory(string directory);
void create_global_directory(string directory);
void create_readme(string parent, string code);
void create_readme(string parent);
void remove_directory(string directory);

bool isWithin(string &str, string tag1);
string parse(string &str, string tag1, string tag2);
int parse(string &str, string tag1, string tag2, vector<string> &result);

short picCount(string &article);
bool getTemplates(string &input, string &temp);
string getRedirect(string &input);

void getFileHeaderTitle(ifstream &wikiFile, string &subject);
void getFileHeader(ifstream &wikiFile, string &subject);
void getFileHeader(ifstream &wikiFile, int &subject);
void getFileHeader(ifstream &wikiFile, short &subject);
void getFileHeader(ifstream &wikiFile, bool &subject);

void nestedRemoval(string begintarg, string endtarg, string &text, size_t &current, size_t begin, int &openCt, int &ct);
void getPage(ifstream &dataDump, bool &end, string &pagestr);
void savePage(string parent, int &N, wikiPage &temp, ofstream &hash, vector<wikiPage> &redirBuffer, vector<wikiPage> &goodBuffer, vector<wikiPage> &badBuffer, vector<wikiPage> &regBuffer, unsigned long &goodCt, unsigned long &redirectCt, unsigned long &regCt, unsigned long &badCt);
void savePage(bool headers, string parent, int &N, wikiPage &temp, vector<wikiPage> &redirBuffer, vector<wikiPage> &goodBuffer, vector<wikiPage> &badBuffer, vector<wikiPage> &regBuffer, unsigned long &goodCt, unsigned long &redirectCt, unsigned long &regCt, unsigned long &badCt, bool good, bool bad, bool regular, bool redirect);

void savePage(int &N, wikiPage &temp, ofstream &hash, vector<wikiPage> &redirBuffer, vector<wikiPage> &goodBuffer, vector<wikiPage> &badBuffer, vector<wikiPage> &regBuffer, unsigned long &goodCt, unsigned long &redirectCt, unsigned long &regCt, unsigned long &badCt);

void savePageHTML(int &N, wikiPage &temp, ofstream &hash, vector<wikiPage> &redirBuffer, vector<wikiPage> &goodBuffer, vector<wikiPage> &badBuffer, vector<wikiPage> &regBuffer, unsigned long &goodCt, unsigned long &redirectCt, unsigned long &regCt, unsigned long &badCt);

void flush(bool headers, vector<wikiPage> &buffer, unsigned long &ct, const int &N, string file, string hashOutput);
void flush(ofstream &hash, vector<wikiPage> &buffer, unsigned long &ct, const int &N, string file, string hashOutput);
void flushHTML(ofstream &hash, vector<wikiPage> &buffer, unsigned long &ct, const int &N, string file, string hashOutput);

void compile(string filename, int N, bool &formatting);
void compile(string filename, int N, bool formatting, string folder);
bool isRequired(wikiPage &temp, vector<string> &titles);

void compileHTML(string filename, vector<string> titles, bool leaveFormatting);
void compileHTML(string filename);

void setup(string &filename, string parent);
void setup(string parent);
void setup_no_parsed_folder(string parent, bool good, bool bad, bool regular, bool redirect);
void titleSearch(string &title);
void fetch_requested_titles(vector<string> &titles, string filename);
void menu();
void global_remove_file(string filename);
void save_pg(wikiPage &page, const string &cat, const int &cur_cat_size, const string &folder);
void remove_global_directory(string directory);

#endif // WIKIPAGE_H
