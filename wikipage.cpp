#include "wikipage.h"

//Written by Brian Faure
//Tested by Brian Faure
//Debugged by Brian Faure

void menu();

//Get current directory
string get_path(){
    const int max_path_size = 500;
    char temp[max_path_size];
    getcwd(temp, max_path_size);
    string cwd(temp);
    return cwd;
}

//Make a directoy in current folder
void create_directory(string directory){
    char *p = new char[500];
    string path = get_path();
    string mkdir = "mkdir ";
    string quote = "\"";
    string command = mkdir+quote+path+directory+quote;
    char *c = const_cast<char*>(command.c_str());
    system(c);
    return;
}

void create_global_directory(string directory){
    char *p = new char[500];
    string mkdir = "mkdir ";
    string quote = "\"";
    string command = mkdir+quote+directory+quote;
    char *c = const_cast<char*>(command.c_str());
    system(c);
    return;
}

//Create readme.txt files to hold info
void create_readme(string parent, string code){
    if(code=="one"){
        time_t _tm = time(NULL);
        struct tm* curtime = localtime(&_tm);
        string cache_date = "Cache Date "+string(asctime(curtime))+"\n";
        ofstream file("readme.txt");
        file<<cache_date;
        return;
    }
    string good = parent+"good/readme.txt";
    string bad = parent+"bad/readme.txt";
    string reg = parent+"regular/readme.txt";
    string redir = parent+"redirect/readme.txt";
    vector<string> readmes = {good, bad, reg, redir};

    time_t _tm = time(NULL);
    struct tm* curtime = localtime(&_tm);
    string cache_date = "Cache Date "+string(asctime(curtime))+"\n";

    for(int i=0; i<readmes.size(); i++){
        string temp = readmes[i];
        ofstream file(temp);
        file<<cache_date;
    }
}

//Create readme.txt files to hold info
void create_readme(string parent){
    string good = parent+"good/readme.txt";
    string bad = parent+"bad/readme.txt";
    string reg = parent+"regular/readme.txt";
    string redir = parent+"redirect/readme.txt";
    vector<string> readmes = {good, bad, reg, redir};

    time_t _tm = time(NULL);
    struct tm* curtime = localtime(&_tm);
    string cache_date = "Cache Date "+string(asctime(curtime))+"\n";

    for(int i=0; i<readmes.size(); i++){
        string temp = readmes[i];
        ofstream file(temp);
        file<<cache_date;
    }
}

//Remove a directoy in current folder
void remove_global_directory(string directory){
    string rm = "rm -rf ";
    string quote = "\"";
    string command = rm+quote+directory+quote;
    char *c = const_cast<char*>(command.c_str());
    system(c);
    return;
}

//Remove a directoy in current folder
void remove_directory(string directory){
    char *p = new char[500];
    string path = get_path();
    string rm = "rm -rf ";
    string quote = "\"";
    string command = rm+quote+path+directory+quote;
    char *c = const_cast<char*>(command.c_str());
    system(c);
    return;
}

void global_remove_file(string filename){
    size_t space_location = 0;
    string new_space = "\\ \\";
    while(true){
        space_location = filename.find(" ", space_location);
        if(space_location != string::npos){
            string temp1 = filename.substr(0, space_location);
            string temp2 = filename.substr(space_location+1, string::npos);
            filename = temp1+new_space+temp2;
            space_location+=2;
        }
        else{
            break;
        }
    }
    char *p = new char[500];
    string temp = "rm "+filename;
    char *c = const_cast<char*>(temp.c_str());
    system(c);
    return;
}

//Check if string "tag1" is within string "str"
bool isWithin(string &str, string tag1) {
    return (str.find(tag1) != string::npos);
}

// Parse the contents between a pair of tags
string parse(string &str, string tag1, string tag2) {
    size_t p1 = str.find(tag1);
    size_t p2 = str.find(tag2, p1);
    if (p1 != string::npos and p2 != string::npos) {
        return str.substr(p1+tag1.size(), p2-p1-tag1.size());
    }
    else {
        return "";
    }
}

// Populate the given vector with all matches, in given string, between given tags
// Returns the index immediately after last match (for purposes of block shifting)
int parse(string &str, string tag1, string tag2, vector<string> &result) {
    int pos = 0;                                            // Current position in string
    while(true) {
        size_t p1 = str.find(tag1, pos);
        size_t p2 = str.find(tag2, p1);
        if (p1 != string::npos and p2 != string::npos) {    // If new match, push it back
            pos = p2+tag2.size();
            string parsed = str.substr(p1+tag1.size(), p2-p1-tag1.size());
            result.push_back(parsed);
        }
        else {break;}                                       // Break otherwise
    }
    return pos;
}

//Grab the number of pictures in article
short picCount(string &article){
    short count=0;
    bool condition=true;
    string pic = ".jpg";
    size_t location = 0;
    while(condition){
        location = article.find(pic, location);
        if(location!=string::npos){
            count++;
            location += pic.size();
        }
        else{
            condition=false;
        }
    }
    return count;
}

//Check article for cleanup templates
bool getTemplates(string &input, string &temp){
    vector<string> templates = {"{{Multiple issues", "stub}}", "{{Cleanup", "{{Advert", "{{Update", "{{Tone", "{{Plot", "{{Essay-like", "{{Peacock", "{{Technical", "{{Confusing"};
    vector<string> clean = {"multiple", "stub", "cleanup", "advert", "update", "tone", "plot", "essay-like", "peacock", "technical", "confusing"};
    for(int i=0; i<templates.size(); i++){
        if(input.find(templates[i]) != string::npos){
            temp = clean[i];
            return true;
        }
    }
    return false;
}

bool check_for_cleanup(const string &input, vector<string> &templates){
    vector<string> targets = {"{{All plot", "{{Advert", "{{Buzzword", "{{Repetition",
                              "{{Tone|article", "{{Peacock",
                              "{{Incomprehensible",
                              "{{Weasel", "{{Generalize",
                              "{{Partisan", "{{Unbalanced"};

    vector<string> clean = {"plot", "advert", "buzzword", "repetition", "tone",
                            "peacock", "incomprehensible", "weasel",
                            "generalize", "partisan", "unbalanced"};

    bool found_cleanup = false;

    for(int i=0; i<targets.size(); i++){
        if(input.find(targets[i]) != string::npos){
            found_cleanup = true;
            templates.push_back(clean[i]);
        }
    }
    return found_cleanup;
}

bool check_for_cleanup(const string &input){
    vector<string> targets = {"{{All plot", "{{Advert", "{{Buzzword", "{{Repetition",
                              "{{Tone|article", "{{Peacock",
                              "{{POV", "{{Incomprehensible",
                              "{{Weasel", "{{Cleanup", "{{Generalize", "{{Off topic",
                              "{{Partisan", "{{Unbalanced"};

    for(int i=0; i<targets.size(); i++){
        if(input.find(targets[i]) != string::npos){
            return true;
        }
    }
    return false;
}

//Get redirection title
string getRedirect(string &input){
    string begin = "[[";
    string end = "]]";
    size_t location = input.find(begin);
    size_t endlocation = input.find(end, location+begin.size());
    string title = input.substr(location+begin.size(), endlocation-location-end.size());
    return title;
}

//Functions to recover wikiPages from files
void getFileHeaderTitle(ifstream &wikiFile, string &subject){
    string colon = ":";
    int size = colon.size();
    string line;
    getline(wikiFile, line);
    size_t location = line.find(colon);
    subject = line.substr(location+size+2, string::npos);
    return;
}
void getFileHeader(ifstream &wikiFile, string &subject){
    string colon = ":";
    int size = colon.size();
    string line;
    getline(wikiFile, line);
    size_t location = line.find(colon);
    subject = line.substr(location+size+1, string::npos);
    return;
}
void getFileHeader(ifstream &wikiFile, int &subject){
    string colon = ":";
    int size = colon.size();
    string line;
    getline(wikiFile, line);
    size_t location = line.find(colon);
    line = line.substr(location+size+1, string::npos);
    subject = std::stoi(line, nullptr);
    return;
}
void getFileHeader(ifstream &wikiFile, short &subject){
    string colon = ":";
    int size = colon.size();
    string line;
    getline(wikiFile, line);
    size_t location = line.find(colon);
    line = line.substr(location+size+1, string::npos);
    int temp = std::stoi(line, nullptr);
    subject = short(temp);
    return;
}
void getFileHeader(ifstream &wikiFile, bool &subject){
    string colon = ":";
    int size = colon.size();
    string line;
    getline(wikiFile, line);
    size_t location = line.find(colon);
    line = line.substr(location+size+1, string::npos);
    int sub = std::stoi(line, nullptr);
    subject=false;
    if(sub==1){
        subject=true;
    }
    return;
}


string get_class(string input){
    vector<string> common = {"{{All plot", "{{Advert", "{{Buzzword", "{{Repetition",
                              "{{Tone|article", "{{Peacock", "{{Incomprehensible",
                              "{{Weasel", "{{Generalize", "{{Partisan", "{{Unbalanced",
                             "{{Featured article}}", "{{Good article}}", "#REDIRECT", "{{Stub", "stub}}"};

    vector<string> clean = {"plot", "advert", "buzzword", "repetition", "tone",
                            "peacock", "incomprehensible", "weasel",
                            "generalize", "partisan", "unbalanced", "featured",
                            "good", "redirect", "stub", "stub"};

    for(int i=0; i<common.size(); i++){
        if(isWithin(input, common[i])){
            return clean[i];
        }
    }
    return "other";
}

void removeTarget(string &temp, string target);

void fix_cat(vector<string> &cat){
    vector<string> temp;
    for(int i=0; i<cat.size(); i++){
        string str = cat[i];
        removeTarget(str, "|");
        temp.push_back(str);
    }
    cat = temp;
}
void replaceTarget(string &temp, string target, string new_target);

void fix_title(string &title){
    bool condition = true;
    while(condition){
        size_t location = title.find("/");
        if(location != string::npos){
            title.replace(location, 1, ".");
        }
        else{
            condition=false;
        }
    }
    condition = true;
    while(condition){
        size_t location = title.find(" ");
        if(location != string::npos){
            title.replace(location, 1, "_");
        }
        else{
            condition=false;
        }
    }
}

void removeBetween(string &temp, string target, string endtarget, string code){
    while(true){
        size_t location = temp.find(target);
        if(location!=string::npos){
            size_t endlocation = temp.find(endtarget, location+target.size());
            if((endlocation!=string::npos) and ((endlocation - location) < 50)){
                temp.erase(location, endlocation+endtarget.size()-location);
            }
            else{
                return;
            }
        }
        else{
            return;
        }
    }
}

void replaceTarget(string &temp, string target, string new_target, string code){
    size_t loc = 0;
    while(true){
        size_t location = temp.find(target, loc);
        if(location!=string::npos){
            temp.replace(location, target.size(), new_target);
            loc = location + new_target.size();
        }
        else{
            return;
        }
    }
}

// Used in wikiGUI
// wikipage simple constructor
// Only saves the titles and bodies of the text and type
//if formatting is false then function will remove all formatting
//if formatting is true then function will leave all formatting
wikiPage::wikiPage(string pagestr, bool formatting, string code) {
    if(code=="multi_strict"){
        title = parse(pagestr, "<title>", "</title>");
        fix_title(title);
        parse(pagestr, "[[Category:", "]]", categories);
        fix_cat(categories);
        text = parse(pagestr, "<text xml:space=\"preserve\">", "</text>");
        classification = get_class(pagestr);
        isRedirect = false;
        if(isWithin(text, "#REDIRECT"))
            isRedirect = true;
        isJunk = false;
        size = sizeof(pagestr);
        removeFormatting();
        removeBetween(text, "<ref name", ";", "strict");
        removeTarget(text, "—");
        removeTarget(text, "()");
        replaceTarget(text, ".", ". ", "strict");
        replaceTarget(text, ".   ", ".  ", "string");
        return;
    }
    if(code=="multi"){
        title = parse(pagestr, "<title>", "</title>");
        fix_title(title);
        parse(pagestr, "[[Category:", "]]", categories);
        fix_cat(categories);
        text = parse(pagestr, "<text xml:space=\"preserve\">", "</text>");
        classification = get_class(pagestr);
        isRedirect = false;
        if(isWithin(text, "#REDIRECT"))
            isRedirect = true;
        isJunk = false;
        size = sizeof(pagestr);
        removeFormatting();
        return;
    }
    if(code=="title"){
        title = parse(pagestr, "<title>", "</title>");
        text = parse(pagestr, "<text xml:space=\"preserve\">", "</text>");
        isJunk = false;
        removeFormatting();
        isRedirect = false;
        if(isWithin(text, "#REDIRECT"))
            isRedirect = true;
        return;
    }
    //Set the title of the page
    title = parse(pagestr, "<title>", "</title>");

    //Collect all categories for article
    parse(pagestr, "[[Category:", "]]", categories);

    //Grab the text portion of the page
    text = parse(pagestr, "<text xml:space=\"preserve\">", "</text>");

    isRedirect = false;
    if(isWithin(text, "#REDIRECT")){
        quality=0;									//Quality=0 for redirect articles
        redirection = getRedirect(text);
        isRedirect = true;
    }
    else{
        quality=1;									//Quality=1 for regular
    }

    //Set the quality if a featured or good article
    if(isWithin(text, "{{Featured article}}") || isWithin(text, "{{Good article}}")){
        quality=2;									//Quality=2 for featured or good
    }
    //Get cleanup templates (if any)
    //bool istemp = getTemplates(text, templates);
    /*
    if(istemp){
        quality=3;
    }
    */
    if(check_for_cleanup(pagestr, template_vec)){
        quality=3;
    }

    isJunk = false;

    if(!formatting){
        removeFormatting();
    }
}




// original wikipage constructor
//if formatting is false then function will remove all formatting
//if formatting is true then function will leave all formatting
wikiPage::wikiPage(string pagestr, bool formatting) {
    //Set the title of the page
    title = parse(pagestr, "<title>", "</title>");
    //Set the namespace
    ns = parse(pagestr, "<ns>", "</ns>");
    //Grab the text portion of the page
    text = parse(pagestr, "<text xml:space=\"preserve\">", "</text>");
    //Grab the categories for the page
    parse(pagestr, "[[Category:", "]]", categories);
    //Grab the contributor for latest edit
    contrib = parse(pagestr, "<username>", "</username>");
    //Grab the latest timestamp on the page
    timestamp = parse(pagestr, "<timestamp>", "</timestamp>");
    // Categorize based on text
    isRedirect = isWithin(text, "#REDIRECT");
    if(isRedirect){
        quality=0;									//Quality=0 for redirect articles
        redirection = getRedirect(text);
    }
    else{
        quality=1;									//Quality=1 for stub
    }
    //Set the quality if a featured or good article
    if(isWithin(text, "{{Featured article}}") || isWithin(text, "{{Good article}}")){
        quality=2;									//Quality=2 for featured or good
    }
    //Get cleanup templates (if any)
    bool istemp = getTemplates(text, templates);
    if(istemp){
        quality=3;
    }
    //Count number of pictures present in article
    pic = picCount(pagestr);

    isJunk = false;

    if(!formatting){
        removeFormatting();
    }
}

wikiPage::wikiPage(ifstream &wikiFile){
    string versionOneTag = "---> VERSION 1.0";
    string buffer;
    getline(wikiFile, buffer);
    if(buffer.find(versionOneTag)!=string::npos){
        version=1;
        getFileHeaderTitle(wikiFile, title);
        getFileHeader(wikiFile, ns);
        getline(wikiFile, buffer);
        getFileHeader(wikiFile, isRedirect);
        getFileHeader(wikiFile, redirection);
        getFileHeader(wikiFile, quality);
        getFileHeader(wikiFile, contrib);
        getFileHeader(wikiFile, timestamp);
        getFileHeader(wikiFile, pic);
        getFileHeader(wikiFile, templates);
        while(true){
            getline(wikiFile, buffer);
            text+=buffer;
            if(wikiFile.eof()){
                break;
            }
        }
    }
    else{
        cout<<"Save version not recognized!\n";
        return;
    }
}

//Both begintarg & endtarg must be same length for function to work
void nestedRemoval(string begintarg, string endtarg, string &text, size_t &current, size_t begin, int &openCt, int &ct){
    ct++;
    if(ct >= 300){
        cout<<"\r\t--> Error in nested removal; page is junk; continuing...\t\t\t\n";
        cout.flush();
        return;
    }
    if(openCt<=0){
        text.erase(begin, current+endtarg.size()-begin);
        return;
    }
    size_t closeLocation = text.find(endtarg, current+begintarg.size());
    if(closeLocation==string::npos){
        text.erase(begin, string::npos);
        return;
    }
    size_t temp = current;
    while(true){
        size_t nests = text.find(begintarg, temp+begintarg.size());
        if((nests>closeLocation) or (nests==string::npos)){
            break;
        }
        else{
            openCt++;
            temp = nests;
        }
    }
    openCt--;
    return nestedRemoval(begintarg, endtarg, text, closeLocation, begin, openCt, ct);
}

void removeBetween(string &temp, string target, string endtarget){
    while(true){
        size_t location = temp.find(target);
        if(location!=string::npos){
            size_t endlocation = temp.find(endtarget, location+target.size());
            if(endlocation!=string::npos){
                temp.erase(location, endlocation+endtarget.size()-location);
            }
            else{
                return;
            }
        }
        else{
            return;
        }
    }
}

//reverse removeBetween
void r_removeBetween(string &temp, string target, string endtarget){
    while(true){
        size_t location = temp.rfind(endtarget);
        if(location!=string::npos){
            size_t endlocation = temp.rfind(target, location-target.size());
            if(endlocation!=string::npos){
                temp.erase(endlocation, location+endtarget.size()-endlocation);
            }
            else{
                return;
            }
        }
        else{
            return;
        }
    }
}

void removeTarget(string &temp, string target){
    while(true){
        size_t location = temp.find(target);
        if(location!=string::npos){
            temp.erase(location,target.size());
        }
        else{
            return;
        }
    }
}

void replaceTarget(string &temp, string target, string new_target){
    while(true){
        size_t location = temp.find(target);
        if(location!=string::npos){
            temp.replace(location, target.size(), new_target);
        }
        else{
            return;
        }
    }
}
void replaceTarget(string &temp, vector<string> target, string new_target){
    for(int i=0; i<target.size(); i++){
        string targ = target[i];
        bool condition=true;
        while(condition){
            size_t location = temp.find(targ);
            if(location!=string::npos){
                temp.replace(location, targ.size(), new_target);
            }
            else{
                condition=false;
            }
        }
    }
}

void removeReferences(string &temp){
    size_t ref = temp.find('*');
    if(ref!=string::npos){
        temp.erase(ref);
    }
}

void wikiPage::removeFormatting(){

    string temp = text;

    bool condition  = true;
    string open     = "{{";
    string close    = "}}";
    while(condition){
        size_t location = temp.find(open);
        if(location!=string::npos){
            int openCt  = 1;
            int ct      = 0;
            nestedRemoval(open, close, temp, location, location, openCt, ct);
            if(ct>=300){
                condition=false;
                isJunk = true; //There was an error
                return;        //So not going to save this article
            }
        }
        else{
            condition=false;
        }
    }

    string target = "[[Category:";
    string endtarget = "]]";
    removeBetween(temp, target, endtarget);

    target = "[[";
    endtarget = "|";
    r_removeBetween(temp, target, endtarget);


    target = "]]";
    removeTarget(temp, target);

    target = "[[";
    removeTarget(temp, target);

    target = "'''";
    removeTarget(temp, target);

    target = "&lt;";
    endtarget = "&lt;/";
    removeBetween(temp, target, endtarget);

    target = "==";
    endtarget = "==";
    removeBetween(temp, target, endtarget);

    target = "===";
    endtarget = "===";
    removeBetween(temp, target, endtarget);

    target = "ref&gt;";
    replaceTarget(temp,target," ");


    replaceTarget(temp, {"     ","    ","  "}, " ");

    removeTarget(temp, "&quot;");

    removeTarget(temp, "''");

    removeTarget(temp, "&amp;");
    removeTarget(temp, "nbsp;");

    vector<string> vec{"...",".."};
    replaceTarget(temp, vec, ".");

    replaceTarget(temp, "=", " ");

    removeReferences(temp);

    removeTarget(temp, "&gt");

    removeBetween(temp, "(;", ")");

    removeBetween(temp, "{|", "}");


    text = temp;
    return;
}


//Remove all formatting artifacts
void wikiPage::removeJunk() {
    string temp = text;
    //Searching for categories not yet removed
    bool condition=true;
    string target = "[[Category:";
    string endtarget = "]]";
    while(condition){
        size_t location = temp.find(target);
        if(location!=string::npos){
            size_t endlocation = temp.find(endtarget, location+target.size());
            temp.erase(location, endlocation+endtarget.size()-location);
        }
        else{
            condition=false;
        }
    }

    //Removing all content between &quot; denotions
    condition=true;
    string open = "ref&gt;";
    string close = "/ref&gt";
    while(condition){
        size_t location = temp.find(open);
        if(location!=string::npos){
            int openCt=1;
            int ct=0;
            nestedRemoval(open, close, temp, location, location, openCt, ct);
            if(ct>=1023999){
                condition=false;
            }
        }
        else{
            condition=false;
        }
    }

    //Removing all content between curly brackets
    condition=true;
    open = "{{";
    close = "}}";
    while(condition){
        size_t location = temp.find(open);
        if(location!=string::npos){
            int openCt=1;
            int ct=0;
            nestedRemoval(open, close, temp, location, location, openCt, ct);
            if(ct>=1023999){
                condition=false;
            }
        }
        else{
            condition=false;
        }
    }




    /*
    //Removing all content between brackets
    condition=true;
    open = "[[";
    close = "]]";
    while(condition){
        size_t location = temp.find(open);
        if(location!=string::npos){
            int openCt=1;
            int ct=0;
            nestedRemoval(open, close, temp, location, location, openCt, ct);
            if(ct>=1023999){
                condition=false;
            }
        }
        else{
            condition=false;
        }
    }
    */
    //Removing all sub-category headers
    condition=true;
    string both = "===";
    while(condition){
        size_t location = temp.find(both);
        if(location!=string::npos){
            size_t end = temp.find(both, location+both.size());
            temp.erase(location, end+both.size()-location);
        }
        else{
            condition=false;
        }
    }
    //Adding junk formatting to the targets vector...
    vector<string> targets{"'''","''","*","[","]","!:","?",";","(",")","$","'","ampndash","=="};
    //Removing all instances of junk strings...
    for(int i=0; i<targets.size(); i++){
        target = targets[i];
        condition=true;
        while(condition){
            size_t location = temp.find(target);
            if(location!=string::npos){
                temp.erase(location,target.size());
            }
            else{
                condition=false;
            }
        }
    }
    /*
    //Characters to be replaced by a space
    vector<string> tobereplaced{"-","/","=","_"};
    for(int i=0; i<tobereplaced.size(); i++){
        target = tobereplaced[i];
        condition=true;
        while(condition){
            size_t location = temp.find(target);
            if(location!=string::npos){
                temp.replace(location, 1, " ");
            }
            else{
                condition=false;
            }
        }
    }
    */

    //Remove all web addresses
    string address_start = "http";
    string address_end = " ";
    condition=true;
    while(condition){
        size_t location = temp.find(address_start);
        if(location!=string::npos){
            size_t end_location = temp.find(address_end, location);
            temp.erase(location, end_location+address_end.size()-location);
        }
        else{
            condition=false;
        }
    }

    //Replace | with 'or'
    condition=true;
    target = "|";
    while(condition){
        size_t location = temp.find(target);
        if(location!=string::npos){
            temp.replace(location, 1, " or ");
        }
        else{
            condition=false;
        }
    }


    //Remove empty lines
    string twoline = "\n\n";
    string oneline = "\n";
    condition = true;
    while(condition){
        size_t location = temp.find(twoline);
        if(location!=string::npos){
            temp.replace(location, twoline.size(), oneline);
        }
        else{
            condition=false;
        }
    }

    condition=true;
    open = "&quot";
    close = " ";
    while(condition){
        size_t location = temp.find(open);
        if(location!=string::npos){
            size_t end_location = temp.find(close, location+5);
            temp.erase(location, end_location+close.size()-location);
        }
        else{
            condition=false;
        }

    }




    text = temp;
    return;
}

//saving only the body of the article
void wikiPage::save_basic(ofstream &file){
    file<<text;
}

//Save function (save to file)
void wikiPage::save(ofstream &file){
    file<<">>>VERSION 1.0<<<\n";
    file<<(*this);
    file<<"Categories:\t";
    for(int i=0; i<categories.size(); i++){
        file<<categories[i]<<" ";
    }
    file<<"\nTemplates:\t";
    for(int i=0; i<template_vec.size(); i++){
        file<<template_vec[i]<<" | ";
    }
    file<<"\n"<<text<<"\n";
    file<<">>>EOA<<<\n";
}

//Save to HTML format of website
void wikiPage::saveHTML(ofstream &file){
    file<<"<!DOCTYPE html>\n";
    file<<"<html>\n";
    file<<"\t<head>\n";
    file<<"\t\t<link rel=\"stylesheet\" href=\"../styles/main.css\">\n";
    file<<"\t\t<title>"<<title<<"</title>\n";
    file<<"\t\t<script>\n";
    file<<"\t\t\tfunction colorText() {\n";
    file<<"\t\t\t\tvar p = document.getElementsByClassName('text')\";\n";
    file<<"\t\t\t\tvar colors = [\"#FFD700\",\"#FFD700\",\"#CCC\", \"#CCC\"]\";\n";
    file<<"\t\t\t\tfor(var i=0) \"; i < p.length\"; i++){\n";
    file<<"\t\t\t\t\tp[i].style.background = colors[i];\n";
    file<<"\t\t\t\t}\n";
    file<<"\t\t\t}\n";
    file<<"\t\t</script>\n";
    file<<"\t</head>\n";
    file<<"\t<body onload=\"colorText()\">\n";
    file<<"\t\t<div id=\"header\">\n";
    file<<"\t\t\t<a href=\"../index.html\">\n";
    file<<"\t\t\t\t<img id=\"logo\" class=\"center\" src=\"../images/logo.svg\" alt=\"WikiClassify\" width=\"250px\"/>\n";
    file<<"\t\t\t</a>\n";
    file<<"\t\t\t<input type=\"text\" name=\"search\" placeholder=\"Search\" id=\"search\" class=\"center\" >\n";
    file<<"\t\t</div>\n";
    file<<"\t\t<div id=\"content\" class=\"center box\">\n";
    file<<"\t\t\t<h1>"<<title<<"</h1>\n";

    if(quality==2){file<<"\t\t\t<span class=\"label featured\">Featured</span>\n";}
    if(quality==1){file<<"\t\t\t<span class=\"label stub\">Stub</span>\n";}

    file<<"\t\t\t<p>\n";

    string period = ".";
    size_t front = 0;
    size_t back=0;
    string temp;
    while(true){
        back = text.find(period, front);
        if(back!=string::npos){
            temp = text.substr(front,back-front);
            file<<"\t\t\t\t<span class='text'>"<<temp<<"</span>\n";
            front = back+2;
        }
        else{
            break;
        }
    }

    file<<"\t\t\t</p>\n";
    file<<"\t\t</div>\n";
    file<<"\t\t\t<nav>\n";
    file<<"\t\t\t\t<a href=\"../about.html\">About</a>\n";
    file<<"\t\t\t\t<a href=\"../login.html\">Login</a>\n";
    file<<"\t\t\t</nav>\n";
    file<<"\t\t</div>\n";
    file<<"\t</body>\n";
    file<<"</html>\n";
}

ostream& operator<<(ostream& os, wikiPage& wp)
{
    os <<"Title:\t\t"<<wp.title<<"\nNamespace:\t"<<wp.ns<<"\nArticle size:\t"<<wp.text.size()<<"\nRedirect:\t"<<wp.isRedirect<<"\nRedirection:\t"<<wp.redirection<<"\nQuality:\t"<<wp.quality<<"\nContributor:\t"<<wp.contrib<<"\nTimestamp:\t"<<wp.timestamp<<"\nPic Count:\t"<<wp.pic<<"\nTemplate:\t"<<wp.templates<<"\n";
    return os;
}

//Get a page from the data dump
void getPage(ifstream &dataDump, bool &end, string &pagestr){

    unsigned short buffersize = 4096;
    unsigned long blocksize = 1024000;
    string block;
    char buffer[buffersize];

    string line;
    bool condition=true;
    while(condition){
        getline(dataDump, line);
        if(line.find("<page>") != string::npos){
            while(true){
                getline(dataDump, line);
                if(line.find("</page>") != string::npos){
                    return;
                }
                pagestr.append(line);
            }
        }
    }
}

//Save version for plaintext
void savePage(int &N, wikiPage &temp, ofstream &hash, vector<wikiPage> &redirBuffer, vector<wikiPage> &goodBuffer, vector<wikiPage> &badBuffer, vector<wikiPage> &regBuffer, unsigned long &goodCt, unsigned long &redirectCt, unsigned long &regCt, unsigned long &badCt){
    string goodFolder = "good/vol-";
    string regFolder = "regular/vol-";
    string redirFolder = "redirect/vol-";
    string badFolder = "bad/vol-";
    string parent = "parsed/";

    string file;
    int fileNum;
    string hashOutput;
    bool save=false;
    vector<wikiPage> outputBuffer;
    switch(temp.quality){
        case 1:
        regBuffer.push_back(temp);
        regCt++;
        if(regBuffer.size()>=N){
            fileNum = regCt/N;
            hashOutput = regFolder+to_string(fileNum)+".txt";
            file = parent+hashOutput;
            outputBuffer=regBuffer;
            regBuffer.clear();
            save=true;
        }
        break;
        case 0:
        redirBuffer.push_back(temp);
        redirectCt++;
        if(redirBuffer.size()>=N){
            fileNum = redirectCt/N;
            hashOutput = redirFolder+to_string(fileNum)+".txt";
            file = parent+hashOutput;
            outputBuffer=redirBuffer;
            redirBuffer.clear();
            save=true;
        }
        break;
        case 2:
        goodBuffer.push_back(temp);
        goodCt++;
        if(goodBuffer.size()>=N){
            fileNum = goodCt/N;
            hashOutput = goodFolder+to_string(fileNum)+".txt";
            file = parent+hashOutput;
            outputBuffer=goodBuffer;
            goodBuffer.clear();
            save=true;
        }
        break;
        case 3:
        badBuffer.push_back(temp);
        badCt++;
        if(badBuffer.size()>=N){
            fileNum = badCt/N;
            hashOutput = badFolder+to_string(fileNum)+".txt";
            file = parent+hashOutput;
            outputBuffer=badBuffer;
            badBuffer.clear();
            save=true;
        }
    }
    if(save){
        ofstream output(file);
        for(int i=0; i<N; i++){
            hash<<"["<<outputBuffer[i].title<<"] "<<hashOutput<<"\n";
            outputBuffer[i].save(output);
        }
    }
}


void save_pg(wikiPage &page, const string &cat, const int &cur_cat_size, const string &folder){
    string cur_folder = folder+cat;

    if(cur_cat_size == 1){                      //Need to create new directory for new category
        create_global_directory(cur_folder);
    }

    string file_name = cur_folder+"/"+page.title+".txt";

    ofstream output(file_name);
    page.save_basic(output);
    return;
}





//Save version for plaintext, used in GUI version, no hashfile
void savePage(bool headers, string parent, int &N, wikiPage &temp, vector<wikiPage> &redirBuffer, vector<wikiPage> &goodBuffer, vector<wikiPage> &badBuffer, vector<wikiPage> &regBuffer, unsigned long &goodCt, unsigned long &redirectCt, unsigned long &regCt, unsigned long &badCt, bool good, bool bad, bool regular, bool redirect){

    string goodFolder = "good/vol-";
    string regFolder = "regular/vol-";
    string redirFolder = "redirect/vol-";
    string badFolder = "bad/vol-";

    string file;
    int fileNum;
    string hashOutput;
    bool save=false;
    vector<wikiPage> outputBuffer;
    switch(temp.quality){
        case 1:
        if(!regular){
            regCt++;
            return;
        }
        regBuffer.push_back(temp);
        regCt++;
        if(regBuffer.size()>=N){
            fileNum = regCt/N;
            hashOutput = regFolder+to_string(fileNum)+".txt";
            file = parent+hashOutput;
            outputBuffer=regBuffer;
            regBuffer.clear();
            save=true;
        }
        break;

        case 0:
        if(!redirect){
            redirectCt++;
            return;
        }
        redirBuffer.push_back(temp);
        redirectCt++;
        if(redirBuffer.size()>=N){
            fileNum = redirectCt/N;
            hashOutput = redirFolder+to_string(fileNum)+".txt";
            file = parent+hashOutput;
            outputBuffer=redirBuffer;
            redirBuffer.clear();
            save=true;
        }
        break;

        case 2:
        if(!good){
            goodCt++;
            return;
        }
        goodBuffer.push_back(temp);
        goodCt++;
        if(goodBuffer.size()>=N){
            fileNum = goodCt/N;
            hashOutput = goodFolder+to_string(fileNum)+".txt";
            file = parent+hashOutput;
            outputBuffer=goodBuffer;
            goodBuffer.clear();
            save=true;
        }
        break;

        case 3:
        if(!bad){
            badCt++;
            return;
        }
        badBuffer.push_back(temp);
        badCt++;
        if(badBuffer.size()>=N){
            fileNum = badCt/N;
            hashOutput = badFolder+to_string(fileNum)+".txt";
            file = parent+hashOutput;
            outputBuffer=badBuffer;
            badBuffer.clear();
            save=true;
        }
    }
    if(save){
        ofstream output(file);
        for(int i=0; i<N; i++){
            if(headers){
                outputBuffer[i].save(output);
            }
            else{
                outputBuffer[i].save_basic(output);
            }
        }
    }
}

//Save version for plaintext, used in GUI version
void savePage(string parent, int &N, wikiPage &temp, ofstream &hash, vector<wikiPage> &redirBuffer, vector<wikiPage> &goodBuffer, vector<wikiPage> &badBuffer, vector<wikiPage> &regBuffer, unsigned long &goodCt, unsigned long &redirectCt, unsigned long &regCt, unsigned long &badCt){
    string goodFolder = "good/vol-";
    string regFolder = "regular/vol-";
    string redirFolder = "redirect/vol-";
    string badFolder = "bad/vol-";

    string file;
    int fileNum;
    string hashOutput;
    bool save=false;
    vector<wikiPage> outputBuffer;
    switch(temp.quality){
        case 1:
        regBuffer.push_back(temp);
        regCt++;
        if(regBuffer.size()>=N){
            fileNum = regCt/N;
            hashOutput = regFolder+to_string(fileNum)+".txt";
            file = parent+hashOutput;
            outputBuffer=regBuffer;
            regBuffer.clear();
            save=true;
        }
        break;
        case 0:
        redirBuffer.push_back(temp);
        redirectCt++;
        if(redirBuffer.size()>=N){
            fileNum = redirectCt/N;
            hashOutput = redirFolder+to_string(fileNum)+".txt";
            file = parent+hashOutput;
            outputBuffer=redirBuffer;
            redirBuffer.clear();
            save=true;
        }
        break;
        case 2:
        goodBuffer.push_back(temp);
        goodCt++;
        if(goodBuffer.size()>=N){
            fileNum = goodCt/N;
            hashOutput = goodFolder+to_string(fileNum)+".txt";
            file = parent+hashOutput;
            outputBuffer=goodBuffer;
            goodBuffer.clear();
            save=true;
        }
        break;
        case 3:
        badBuffer.push_back(temp);
        badCt++;
        if(badBuffer.size()>=N){
            fileNum = badCt/N;
            hashOutput = badFolder+to_string(fileNum)+".txt";
            file = parent+hashOutput;
            outputBuffer=badBuffer;
            badBuffer.clear();
            save=true;
        }
    }
    if(save){
        ofstream output(file);
        for(int i=0; i<N; i++){
            hash<<"["<<outputBuffer[i].title<<"] "<<hashOutput<<"\n";
            outputBuffer[i].save(output);
        }
    }
}

//Save version for HTML
void savePageHTML(int &N, wikiPage &temp, ofstream &hash, vector<wikiPage> &redirBuffer, vector<wikiPage> &goodBuffer, vector<wikiPage> &badBuffer, vector<wikiPage> &regBuffer, unsigned long &goodCt, unsigned long &redirectCt, unsigned long &regCt, unsigned long &badCt){
    string goodFolder = "good/vol-";
    string regFolder = "regular/vol-";
    string redirFolder = "redirect/vol-";
    string badFolder = "bad/vol-";
    string parent = "parsedHTML/";

    string file;
    int fileNum;
    string hashOutput;
    bool save=false;
    vector<wikiPage> outputBuffer;
    switch(temp.quality){
        case 1:
        regBuffer.push_back(temp);
        regCt++;
        if(regBuffer.size()>=N){
            fileNum = regCt/N;
            hashOutput = regFolder+to_string(fileNum)+".html";
            file = parent+hashOutput;
            outputBuffer=regBuffer;
            regBuffer.clear();
            save=true;
        }
        break;
        case 0:
        redirBuffer.push_back(temp);
        redirectCt++;
        if(redirBuffer.size()>=N){
            fileNum = redirectCt/N;
            hashOutput = redirFolder+to_string(fileNum)+".html";
            file = parent+hashOutput;
            outputBuffer=redirBuffer;
            redirBuffer.clear();
            save=true;
        }
        break;
        case 2:
        goodBuffer.push_back(temp);
        goodCt++;
        if(goodBuffer.size()>=N){
            fileNum = goodCt/N;
            hashOutput = goodFolder+to_string(fileNum)+".html";
            file = parent+hashOutput;
            outputBuffer=goodBuffer;
            goodBuffer.clear();
            save=true;
        }
        break;
        case 3:
        badBuffer.push_back(temp);
        badCt++;
        if(badBuffer.size()>=N){
            fileNum = badCt/N;
            hashOutput = badFolder+to_string(fileNum)+".html";
            file = parent+hashOutput;
            outputBuffer=badBuffer;
            badBuffer.clear();
            save=true;
        }
    }
    if(save){
        ofstream output(file);
        for(int i=0; i<N; i++){
            hash<<"["<<outputBuffer[i].title<<"] "<<hashOutput<<"\n";
            outputBuffer[i].saveHTML(output);
        }
    }
}

//Save remaining wikiPages left in the buffers after compile() is over, no hashfile version
void flush(bool headers, vector<wikiPage> &buffer, unsigned long &ct, const int &N, string file, string hashOutput){
    if(buffer.size()>0){
        string file_ext = ".txt";
        string file_num = to_string((ct/N)+1);
        string file_full = file+file_num+file_ext;
        ofstream flushed(file_full);
        for(int i=0; i<buffer.size(); i++){
            //hash<<"["<<buffer[i].title<<"] "<<hashOutput<<file_num<<".txt\n";
            if(headers){
                buffer[i].save(flushed);
            }
            else{
                buffer[i].save_basic(flushed);
            }
        }
    }
}

//Save remaining wikiPages left in the buffers after compile() is over
void flush(ofstream &hash, vector<wikiPage> &buffer, unsigned long &ct, const int &N, string file, string hashOutput){
    if(buffer.size()>0){
        string file_ext = ".txt";
        string file_num = to_string((ct/N)+1);
        string file_full = file+file_num+file_ext;
        ofstream flushed(file_full);
        for(int i=0; i<buffer.size(); i++){
            hash<<"["<<buffer[i].title<<"] "<<hashOutput<<file_num<<".txt\n";
            buffer[i].save(flushed);
        }
    }
}

//Save remaining wikiPages left in the buffers after compile() is over
void flushHTML(ofstream &hash, vector<wikiPage> &buffer, unsigned long &ct, const int &N, string file, string hashOutput){
    if(buffer.size()>0){
        string file_ext = ".html";
        string file_num = to_string((ct/N)+1);
        string file_full = file+file_num+file_ext;
        ofstream flushed(file_full);
        for(int i=0; i<buffer.size(); i++){
            hash<<"["<<buffer[i].title<<"] "<<hashOutput<<file_num<<".txt\n";
            buffer[i].saveHTML(flushed);
        }
    }
}

//N articles per file, formatting true = leaving formatting in files
void compile(string filename, int N, bool &formatting){

    string folder = "parsed/";
    string hashfile = "hashfile.txt";

    create_readme(folder);

    unsigned long goodCt = 0;
    unsigned long redirectCt = 0;
    unsigned long regCt = 0;
    unsigned long badCt = 0;

    ofstream hash(folder+hashfile);
    ifstream dataDump(filename);

    time_t _tm = time(NULL);
    struct tm* curtime = localtime(&_tm);
    string cache_date = "Cache Date "+string(asctime(curtime))+"\n";
    hash<<cache_date;
    //hash<<"Cache Date: "<<asctime(curtime)<<"\n";

    unsigned long long pageCt = 0;
    float pageCtFloat = 0;
    bool end = false;

    cout<<"Fetching, parsing, and saving...\n";
    time_t start = clock();

    vector<wikiPage> redirBuffer;
    vector<wikiPage> goodBuffer;
    vector<wikiPage> badBuffer;
    vector<wikiPage> regBuffer;

    while(dataDump.eof()==false){
        string pagestr;
        getPage(dataDump, end, pagestr);
        wikiPage temp(pagestr, formatting);
        savePage(N, temp, hash, redirBuffer, goodBuffer, badBuffer, regBuffer, goodCt, redirectCt, regCt, badCt);

        pageCt++;
        pageCtFloat = pageCt;

        cout<<"\r                                                                                                                   ";
        cout.flush();
        cout<<"\rGood: "<<goodCt<<"\tRedirect: "<<redirectCt<<"\tReg: "<<regCt<<"  \tBad: "<<badCt<<" \tTotal: "<<pageCt<<"\tProg: ~"<<(pageCtFloat/5100000)*100<<"%   \tArt/Second: "<<(pageCtFloat/((clock()-start)/CLOCKS_PER_SEC));
        cout.flush();
    }
    cout<<"\n";
    flush(hash, redirBuffer, redirectCt, N, "parsed/redirect/vol-", "redirect/vol-");
    flush(hash, goodBuffer, goodCt, N, "parsed/good/vol-", "good/vol-");
    flush(hash, regBuffer, regCt, N, "parsed/regular/vol-", "regular/vol-");
    flush(hash, badBuffer, badCt, N, "parsed/bad/vol-", "bad/vol-");
    return;
}

//N articles per file, formatting true = leaving formatting in files, used for gui version
void compile(string filename, int N, bool formatting, string folder){

    string hashfile = "hashfile.txt";

    create_readme(folder);

    unsigned long goodCt = 0;
    unsigned long redirectCt = 0;
    unsigned long regCt = 0;
    unsigned long badCt = 0;

    ofstream hash(folder+hashfile);
    ifstream dataDump(filename);

    time_t _tm = time(NULL);
    struct tm* curtime = localtime(&_tm);
    string cache_date = "Cache Date "+string(asctime(curtime))+"\n";
    hash<<cache_date;
    //hash<<"Cache Date: "<<asctime(curtime)<<"\n";

    unsigned long long pageCt = 0;
    float pageCtFloat = 0;
    bool end = false;

    //cout<<"Fetching, parsing, and saving...\n";
    time_t start = clock();

    vector<wikiPage> redirBuffer;
    vector<wikiPage> goodBuffer;
    vector<wikiPage> badBuffer;
    vector<wikiPage> regBuffer;

    while(dataDump.eof()==false){
        string pagestr;
        getPage(dataDump, end, pagestr);
        wikiPage temp(pagestr, formatting);
        savePage(folder, N, temp, hash, redirBuffer, goodBuffer, badBuffer, regBuffer, goodCt, redirectCt, regCt, badCt);

        pageCt++;
        pageCtFloat = pageCt;

        //cout<<"\r                                                                                                                   ";
        //cout.flush();
        //cout<<"\rGood: "<<goodCt<<"\tRedirect: "<<redirectCt<<"\tReg: "<<regCt<<"  \tBad: "<<badCt<<" \tTotal: "<<pageCt<<"\tProg: ~"<<(pageCtFloat/5100000)*100<<"%   \tArt/Second: "<<(pageCtFloat/((clock()-start)/CLOCKS_PER_SEC));
        //cout.flush();
    }
    //cout<<"\n";
    flush(hash, redirBuffer, redirectCt, N, "parsed/redirect/vol-", "redirect/vol-");
    flush(hash, goodBuffer, goodCt, N, "parsed/good/vol-", "good/vol-");
    flush(hash, regBuffer, regCt, N, "parsed/regular/vol-", "regular/vol-");
    flush(hash, badBuffer, badCt, N, "parsed/bad/vol-", "bad/vol-");
    return;
}

bool isRequired(wikiPage &temp, vector<string> &titles){
    string title = temp.title;
    for(int i=0; i<titles.size(); i++){
        if(titles[i]==title){
            return true;
        }
    }
    return false;
}

//New function to only save titles found in vector of required titles
void compileHTML(string filename, vector<string> titles, bool leaveFormatting){

    string folder = "../../../site/wikiclassify/wiki/";
    string hashfile = "hashfile.txt";

    create_readme(folder);

    ofstream hash(folder+hashfile);
    ifstream dataDump(filename);

    time_t _tm = time(NULL);
    struct tm* curtime = localtime(&_tm);
    string cache_date = "Cache Date "+string(asctime(curtime))+"\n";
    hash<<cache_date;
    //hash<<"Cache Date: "<<asctime(curtime)<<"\n";

    int num_done=0;
    unsigned long num_read=0;
    bool end = false;

    cout<<"Fetching, parsing, and saving...\n";
    time_t start = clock();

    string hashOutput;

    int num_titles = titles.size();

    while(dataDump.eof()==false and num_done<num_titles){
        string pagestr;
        getPage(dataDump, end, pagestr);
        wikiPage temp(pagestr, leaveFormatting);
        if(isRequired(temp, titles)){
            string current = temp.title;
            hashOutput = "art-"+to_string(num_done)+".html";
            string fileLocation = folder+hashOutput;
            ofstream htmlFile(fileLocation);
            hash<<"["<<current<<"] "<<hashOutput<<"\n";
            temp.saveHTML(htmlFile);
            num_done++;
        }
        num_read++;
        cout<<"\r                                                                                                                   ";
        cout.flush();
        cout<<"\rNumber Matched = "<<num_done<<"\tNumber Read = "<<num_read;
        cout.flush();
    }
    cout<<"\n";
    return;
}

//Compile articles
void compileHTML(string filename){

    int N = 1;
    bool formatting=true;

    string folder = "../../../site/wikiclassify/wiki/";
    string hashfile = "hashfile.txt";

    create_readme(folder);

    unsigned long goodCt = 0;
    unsigned long redirectCt = 0;
    unsigned long regCt = 0;
    unsigned long badCt = 0;

    ofstream hash(folder+hashfile);
    ifstream dataDump(filename);

    time_t _tm = time(NULL);
    struct tm* curtime = localtime(&_tm);
    string cache_date = "Cache Date "+string(asctime(curtime))+"\n";
    hash<<cache_date;
    //hash<<"Cache Date: "<<asctime(curtime)<<"\n";

    unsigned long long pageCt = 0;
    float pageCtFloat = 0;
    bool end = false;

    cout<<"Fetching, parsing, and saving...\n";
    time_t start = clock();

    vector<wikiPage> redirBuffer;
    vector<wikiPage> goodBuffer;
    vector<wikiPage> badBuffer;
    vector<wikiPage> regBuffer;

    while(dataDump.eof()==false){
        string pagestr;
        getPage(dataDump, end, pagestr);
        wikiPage temp(pagestr, formatting);
        savePageHTML(N, temp, hash, redirBuffer, goodBuffer, badBuffer, regBuffer, goodCt, redirectCt, regCt, badCt);

        pageCt++;
        pageCtFloat = pageCt;

        cout<<"\r                                                                                                                   ";
        cout.flush();
        cout<<"\rGood: "<<goodCt<<"\tRedirect: "<<redirectCt<<"\tReg: "<<regCt<<"  \tBad: "<<badCt<<" \tTotal: "<<pageCt<<"\tProg: ~"<<(pageCtFloat/5100000)*100<<"%   \tArt/Second: "<<(pageCtFloat/((clock()-start)/CLOCKS_PER_SEC));
        cout.flush();
    }
    cout<<"\n";
    flushHTML(hash, redirBuffer, redirectCt, N, "parsedHTML/redirect/vol-", "redirect/vol-");
    flushHTML(hash, goodBuffer, goodCt, N, "parsedHTML/good/vol-", "good/vol-");
    flushHTML(hash, regBuffer, regCt, N, "parsedHTML/regular/vol-", "regular/vol-");
    flushHTML(hash, badBuffer, badCt, N, "parsedHTML/bad/vol-", "bad/vol-");
    return;
}

//Extended user interface
void setup(string parent){
        parent = parent+"/parsed";
        remove_directory(parent);
        create_global_directory(parent);
        string bad = parent+"/bad";
        create_global_directory(bad);
        string good = parent+"/good";
        create_global_directory(good);
        string redirect = parent+"/redirect";
        create_global_directory(redirect);
        string reg = parent+"/regular";
        create_global_directory(reg);
        return;
}

//Extended user interface
void setup_no_parsed_folder(string parent, bool good, bool bad, bool regular, bool redirect){
        string sbad = parent+"/bad";
        string sgood = parent+"/good";
        string sredirect = parent+"/redirect";
        string sreg = parent+"/regular";

        remove_global_directory(sbad);
        if(bad){
            create_global_directory(sbad);
        }

        remove_global_directory(sgood);
        if(good){
            create_global_directory(sgood);
        }

        remove_global_directory(sredirect);
        if(redirect){
            create_global_directory(sredirect);
        }

        remove_global_directory(sreg);
        if(regular){
            create_global_directory(sreg);
        }
}

//Extended user interface
void setup(string &filename, string parent){
    bool bash=false;
    cout<<"parser: Skip setup? [y/n]: ";
    string input;
    cin>>input;
    if(input=="Y" or input=="y"){
        cout<<"Starting process...\n\n";
        return;
    }
    cout<<"\n--> Is this the name of your data dump file: "<<filename<<" (it should be in same folder as wikipedia.cpp) [y/n]: ";
    cin>>input;
    if(input=="n" or input=="N"){
        cout<<"--> Enter the name of your data dump file: ";
        cin>>filename;
    }

    cout<<"--> Are you running linux or osx (or have bash installed) [y/n]: ";
    cin>>input;
    if(input=="y" or input=="Y"){
        cout<<"--> Deleting any former parsedHTML files and creating file structure...\n";
        remove_directory(parent);
        create_directory(parent);
        string bad = parent+"/bad";
        create_directory(bad);
        string good = parent+"/good";
        create_directory(good);
        string redirect = parent+"/redirect";
        create_directory(redirect);
        string reg = parent+"/regular";
        create_directory(reg);
        cout<<"--> Starting Process...\n\n";
        return;
    }
    cout<<"--> For now you will have to create the file structure by hand...\n";
    cout<<"--> The parsed wikiPages will be held in a sub-directory named "<<parent<<", have you created this? [y/n]: ";
    cin>>input;
    if(input=="N" or input=="n"){
        cout<<"--> Create the folder and input 'ready' when completed: ";
        cin>>input;
    }
    cout<<"--> Within "<<parent<<" you need the following 4 folders; good, bad, redirect & regular, do you have these? [y/n]: ";
    cin>>input;
    if(input=="n" or input=="N"){
        cout<<"--> Create these 4 folders, input 'ready' when complete: ";
        cin>>input;
    }
    cout<<"--> Starting process... \n\n";
}

//Temporary title search function
void titleSearch(string &title){
    cout<<"Searching...";
    cout.flush();
    ifstream hash("parsed/hashfile.txt");
    string line;
    string file;
    time_t start = clock();
    while(!hash.eof()){
        getline(hash, line);
        if(line.find(title)!=string::npos){
            cout<<" exact article found in "<<(double(clock()-start)/CLOCKS_PER_SEC)<<" Seconds\n";
            size_t location = line.find("]");
            file = line.substr(location+2, string::npos);
            cout<<"Would you like to view the article details? [y/n]: ";
            string input;
            cin>>input;
            if(input=="y" or input=="Y"){
                string folder = "parsed/";
                string filename = folder+file;
                ifstream wikiFile(filename);
                wikiPage temp(wikiFile);
                cout<<"\n"<<temp<<"\n";
                if(temp.isRedirect){
                    string other = temp.redirection;
                    cout<<"Detected a redirect, would you like to search for the target artcle? [y/n]: ";
                    cin>>input;
                    if(input=="y" or input=="Y"){
                        return titleSearch(other);
                    }
                }
                cout<<"Would you like to view the article content? [y/n]: ";
                cin>>input;
                if(input=="y" or input=="Y"){
                    cout<<temp.text<<"\n";
                }
            }
            return menu();
        }
    }
    cout<<" Exact match not found.\n";
    cout.flush();
    return menu();
}

//Function to compile vector of titles to match to
void fetch_requested_titles(vector<string> &titles, string filename){
    ifstream file(filename);
    string title;
    while(!file.eof()){
        getline(file, title);
        titles.push_back(title);
        if(title=="Paulo Radmilovic"){
            return;
        }
    }
}

//Basic user interface
void menu(){
    cout<<"parser: [1] Search for a title (already compiled database only)\nparser: [2] Compile database (plaintext)\nparser: [3] Compile database (html)\nparser: [4] Compile database w/server\nparser: [5] Compile certain articles only (HTML)\nparser: [6] Split Data Dump into portions\nparser: [7] Exit\n";
    cout<<"parser: Enter choice: ";
    int in;
    cin>>in;
    if(in==1){
        string input;
        cout<<"parser: Enter the title: ";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(cin, input);
        titleSearch(input);
        return;
    }
    if(in==2){
        cout<<"parser: This will delete the prior parsed database (if one), are you sure [y/n]: ";
        string temp;
        cin>>temp;
        if(temp=="n" or temp=="N"){
            return;
        }
        bool formatting=false;
        cout<<"parser: Would you like to parse out all formatting? (much slower) [y/n]: ";
        string in;
        cin>>in;
        if(in=="n" or in=="N"){
            formatting = true;
        }
        cout<<"parser: How many articles per file? ";
        int N;
        cin>>N;
        string filename = "enwiki-20160113-pages-articles.xml";
        setup(filename, "/parsed");
        compile(filename, N, formatting);
        return;
    }
    if(in==3){
        cout<<"parser: This will delete the prior parsedHTML database (if one), are you sure [y/n]: ";
        string temp;
        cin>>temp;
        if(temp=="N" or temp=="n"){
            return;
        }
        string filename = "enwiki-20160113-pages-articles.xml";
        setup(filename, "/parsedHTML");
        compileHTML(filename);
        return;
    }
    if(in==4){
        unsigned long numPages;
        cout<<"parser: How many wikiPages would you like to index?: ";
        cin>>numPages;
        //curlWikiPages(numPages);
    }
    if(in==5){
        string people = "people.txt";
        vector<string> requested_titles;
        fetch_requested_titles(requested_titles, people);
        string filename = "enwiki-20160113-pages-articles.xml";
        bool formatting = true;
        cout<<"parser: Would you like to remove formatting [y/n]: ";
        string fInput;
        cin>>fInput;
        if(fInput=="y" or fInput=="Y"){
            formatting = false;
        }
        compileHTML(filename, requested_titles, formatting);
        return;
    }
    if(in==6){
        cout<<"parser: How many articles would you like per file?: ";
        int numInput;
        cin>>numInput;

    }
    if(in==7){
        return;
    }
}










