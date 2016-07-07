#include "compilethread.h"
#include <QtCore>
#include <QDebug>
#include <iostream>

//Written by Brian Faure
//Tested by Brian Faure
//Debugged by Brian Faure

compileThread::compileThread(QObject *parent) : QThread(parent){
    //qDebug() << "Inside constructor for compileThread in compilethread.cpp";

}

void compileThread::set_shared_data(shared_data *share){
    //qDebug() << "Inside set_shared_data in compileThread.cpp";
    data = new shared_data;
    memcpy(data, share, sizeof(*share));
}


void scrape(vector<direct_struct> &folders, const unsigned long long &pageCt,  unsigned long long &junkCt, string code){

    //qDebug() << "Inside scrape";

    int longer_sweep = 25000;
    int longer_sweep_tolerance = 25;

    int shorter_sweep = 1000;
    int shorter_sweep_tolerance = 2;

    int middle_sweep = 10000;
    int middle_sweep_tolerance = 10;

    if(code == "end"){
        shorter_sweep = 0;
        shorter_sweep_tolerance = 50;
    }

    for(vector<direct_struct>::iterator it = folders.begin(); it!=folders.end(); ){
        //unsigned long diff = pageCt - folders[i].created;
        unsigned long diff = pageCt - (*it).created;

        if(((*it).article_ct < shorter_sweep_tolerance) && (diff >= shorter_sweep)){
            (*it).remove();
            junkCt += (*it).article_ct;
            folders.erase(it);
        }
        else{
            ++it;
        }
    }

    for(vector<direct_struct>::iterator it = folders.begin(); it!=folders.end(); ){
        //unsigned long diff = pageCt - folders[i].created;
        unsigned long diff = pageCt - (*it).created;

        if(((*it).article_ct < middle_sweep_tolerance) && (diff >= middle_sweep)){
            (*it).remove();
            junkCt += (*it).article_ct;
            folders.erase(it);
        }
        else{
            ++it;
        }
    }

    for(vector<direct_struct>::iterator it = folders.begin(); it!=folders.end(); ){
        //unsigned long diff = pageCt - folders[i].created;
        unsigned long diff = pageCt - (*it).created;

        if(((*it).article_ct < longer_sweep_tolerance) && (diff >= longer_sweep)){
            (*it).remove();
            junkCt += (*it).article_ct;
            folders.erase(it);
        }
        else{
            ++it;
        }
    }

}

void flush_buffers(vector<direct_struct> &folders){
    //qDebug() << "Inside flush buffers";
    for(int i=0; i<folders.size(); i++){
        folders[i].flush();
    }
}


void compileThread::content_then_quality(){
    //qDebug() << "Inside content_then_quality";

    unsigned long long num_articles = all_data.total_articles;
    string folder = all_data.base_folder;
    string filename = all_data.datadump_location;

    ifstream data(filename);

    vector<direct_struct> folders;
    vector<wikiPage> output_buffer;
    unsigned long buffer_size;

    unsigned long long pageCt = 0;
    unsigned long long junkCt = 0;
    unsigned long long viewCt = 0;
    unsigned long long copyCt = 0;
    unsigned long long saveCt = 0;
    float copy_per_cat;
    float copy_float;
    float cat_float;
    float junk_float;

    return_data.goodCt = 0;
    return_data.badCt = 0;
    return_data.bytes = 0;
    return_data.redirectCt = 0;
    return_data.regCt = 0;
    return_data.done = false;

    int clean = 1;

    int flush_rate = 5000;
    int sweep_rate = 1000;


    while(data.eof()==false and pageCt<num_articles){
        viewCt++;

        //qDebug() << "Inside while loop";

        string pagestr;
        bool done = false;
        getPage(data, done, pagestr);

        wikiPage page(pagestr, false, "multi_strict");

        if((!page.isJunk) and (!page.isRedirect) and (page.classification != "other")){
            cat_float = folders.size();
            copy_float = copyCt;
            junk_float = junkCt;
            copy_per_cat = (copy_float-junk_float) / cat_float;
            return_data.copy_per_cat = copy_per_cat;

            clean++;
            string quality = page.classification;
            vector<string> content;
            if(page.categories.size() >=1){
                content = page.categories;
            }
            else{
                content = {"no_category"};
            }
            pageCt++;
            bool create_primary;
            bool create_secondary;

            for(int i=0; i<content.size(); i++){
                copyCt++;
                create_primary = true;
                create_secondary = true;
                string article_category = content[i];

                for(int j=0; j<folders.size(); j++){

                    string folder_category = folders[j].name;
                    if(article_category == folder_category){
                        create_primary = false;

                        for(int k=0; k<folders[j].cats.size(); k++){
                            string subfolder_quality = folders[j].cats[k];
                            if(quality == subfolder_quality){
                                create_secondary = false;
                                string save_location = folder+content[i]+"/"+quality+"/"+page.title+".txt";
                                //ofstream output(save_location);
                                //std::cout<<"Location one: saving "<<page.title<<" to "<<save_location<<"\n";
                                //page.save_basic(output);
                                page.save_location = save_location;
                                folders[j].buffer(page);
                            }
                        }
                        //folders[j].article_ct++;
                        folders[j].size += sizeof(page);
                        if(create_secondary){
                            //create_global_directory(folder+article_category+"/"+quality);
                            folders[j].add_cat(quality);
                            //folders[j].cats.push_back(quality);
                            string save_location = folder+content[i]+"/"+quality+"/"+page.title+".txt";
                            //ofstream output(save_location);
                            //std::cout<<"Location two: saving "<<page.title<<" to "<<save_location<<"\n";
                            //page.save_basic(output);
                            page.save_location = save_location;
                            folders[j].buffer(page);
                        }
                    }
                }
                if(create_primary){
                    direct_struct temp;
                    temp.add_cat(quality);
                    temp.created = pageCt;
                    temp.name = content[i];
                    //temp.article_ct = 1;
                    temp.size = sizeof(page);
                    //temp.cats.push_back(quality);
                    string location = folder+content[i];
                    temp.location = location;
                    //folders.push_back(temp);
                    string save_location = folder+content[i]+"/"+quality+"/"+page.title+".txt";
                    page.save_location = save_location;
                    temp.buffer(page);
                    folders.push_back(temp);

                    //ofstream output(save_location);
                    //std::cout<<"Location three: saving "<<page.title<<" to "<<save_location<<"\n";
                    //page.save_basic(output);
                }
            }
            return_data.pageCt = pageCt;
            emit send_data(return_data);
        }
        if(clean % sweep_rate == 0){
            scrape(folders, pageCt, junkCt, " ");
            return_data.badCt = junkCt;
            emit send_data(return_data);
        }
        return_data.goodCt = copyCt;
        return_data.regCt = folders.size();
        emit send_data(return_data);

        if(clean % flush_rate == 0){
            flush_buffers(folders);
        }

        return_data.viewCt = viewCt;
        emit send_data(return_data);
    }

    scrape(folders, pageCt, junkCt, "end");
    flush_buffers(folders);

    return_data.badCt = junkCt;
    return_data.done = true;
    emit send_data(return_data);
    return;
}




void compileThread::multi_folder(){

    content_then_quality();
    return;

    unsigned long long num_articles = all_data.total_articles;
    string folder = all_data.base_folder;
    string filename = all_data.datadump_location;

    ifstream data(filename);
    vector<string> categories;                                  // Will be filled with all categories found
    vector<int> cat_size;                                       // Will be filled with number of instances found

    unsigned long long pageCt = 0;
    unsigned long long scanCt = 0;

    return_data.goodCt = 0;
    return_data.badCt = 0;
    return_data.bytes = 0;
    return_data.redirectCt = 0;
    return_data.regCt = 0;

    while(data.eof()==false and pageCt<num_articles){

        scanCt++;

        string pagestr;
        bool done = false;
        getPage(data, done, pagestr);

        wikiPage page(pagestr, false, "multi");
        string cat = page.classification;

        if((!page.isJunk) and (cat != "other")){
            pageCt++;
            string save_location;

            bool new_cat = true;
            int cur_cat_size = 1;

            for(int i=0; i<categories.size(); i++){
                if(cat == categories[i]){
                    cat_size[i]++;
                    new_cat = false;
                    cur_cat_size = cat_size[i];
                }
            }

            if(new_cat){
                categories.push_back(cat);
                cat_size.push_back(1);
            }

            save_pg(page, cat, cur_cat_size, folder);
            return_data.pageCt = pageCt;
            //emit send_data(return_data);
        }
        return_data.viewCt = scanCt;
        emit send_data(return_data);

    }
}

void compileThread::titles_only(){
    string file = "/Users/Faure/Desktop/titles.txt";
    vector<string> titles;

    ifstream title_data(file);
    bool condition = true;
    string temp;
    return_data.message = "Parsing titles...";
    return_data.goodCt = 0;
    return_data.badCt = 0;
    return_data.redirectCt = 0;
    return_data.bytes = 0;
    return_data.pageCt = 0;
    return_data.regCt = 0;
    emit send_data(return_data);

    while(!title_data.eof() and condition){
        getline(title_data, temp);
        if(temp.find("Topology") != string::npos){
            condition = false;
        }
        titles.push_back(temp);
    }

    string folder = all_data.base_folder;
    string filename = all_data.datadump_location;

    unsigned long long scanCt = 0;
    int foundCt = 0;
    int redir_foundCt = 0;

    ifstream data(filename);
    condition = true;

    string redir = "#REDIRECT";

    return_data.message = "Pulling from data dump...";
    emit send_data(return_data);
    vector<string> titles_copy = titles;

    create_global_directory(folder+"redirects");

    while(data.eof()==false and condition){
        scanCt++;

        string pagestr;
        bool done = false;
        getPage(data, done, pagestr);

        wikiPage page(pagestr, false, "title");


        if(!page.isJunk){
            for(int i=0; i<titles.size(); i++){
                if(titles[i] == page.title){
                    foundCt++;
                    ofstream output(folder+page.title+".txt");
                    page.save_basic(output);
                    titles.erase(titles.begin()+i);
                    goto found_one;
                }
            }
            if(page.isRedirect){
                for(int i=0; i<titles_copy.size(); i++){
                    size_t location = page.text.find(titles_copy[i]);
                    if((location != string::npos) and (page.text.length() == titles_copy[i].length()+1+redir.length())){
                        redir_foundCt++;
                        ofstream output(folder+"redirects/"+page.title);
                        page.save_basic(output);
                        return_data.goodCt++;
                        emit send_data(return_data);
                    }
                }
            }
            found_one:
            return_data.pageCt = foundCt;
            return_data.bytes = scanCt;
            emit send_data(return_data);
            if(titles.size() == 0){
                return_data.message = "Finished.";
                emit send_data(return_data);
                return;
            }
        }
        else{
            return_data.pageCt = foundCt;
            return_data.bytes = scanCt;
            emit send_data(return_data);
        }
    }

}





void compileThread::run(){

    if(all_data.multi_folder){
        multi_folder();
        return;
    }

    if(all_data.specific_titles){
        titles_only();
        return;
    }

    string folder = all_data.base_folder;
    string filename = all_data.datadump_location;
    int N = all_data.articles_per_file;
    bool formatting = all_data.keep_formatting;
    int num_articles = all_data.total_articles;

    string hashfile = "hashfile.txt";

    //create_readme(folder, "one");

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

    if(!all_data.create_hash){
        global_remove_file(folder+hashfile);
    }

    unsigned long long pageCt = 0;
    bool end = false;

    vector<wikiPage> redirBuffer;
    vector<wikiPage> goodBuffer;
    vector<wikiPage> badBuffer;
    vector<wikiPage> regBuffer;

    unsigned long num_bytes = 0;

    while(dataDump.eof()==false and pageCt<num_articles){

        bool saved = true;

        string pagestr;
        getPage(dataDump, end, pagestr);

        if(all_data.create_hash){ //If creating a hash file
            wikiPage temp(pagestr, formatting);
            if(!temp.isJunk){
                savePage(folder, N, temp, hash, redirBuffer, goodBuffer, badBuffer, regBuffer, goodCt, redirectCt, regCt, badCt);
                num_bytes += sizeof(temp);
                pageCt++;
            }
        }
        else{ //If not creating a hash file
            wikiPage temp(pagestr, formatting, "simple"); // Calling simple constructor
            if(!temp.isJunk){
                savePage(all_data.article_headers, folder, N, temp, redirBuffer, goodBuffer, badBuffer, regBuffer, goodCt, redirectCt, regCt, badCt, all_data.save_good, all_data.save_bad, all_data.save_regular, all_data.save_redirect);
                //num_bytes += sizeof(temp);
                pageCt++;
            }
        }

        return_data.pageCt = pageCt;
        return_data.goodCt = goodCt;
        return_data.badCt = badCt;
        return_data.redirectCt = redirectCt;
        return_data.regCt = regCt;
        return_data.bytes = num_bytes;

        emit send_data(return_data);

    }
    if(all_data.create_hash){
        flush(hash, redirBuffer, redirectCt, N, folder+"redirect/vol-", "redirect/vol-");
        flush(hash, goodBuffer, goodCt, N, folder+"good/vol-", "good/vol-");
        flush(hash, regBuffer, regCt, N, folder+"regular/vol-", "regular/vol-");
        flush(hash, badBuffer, badCt, N, folder+"bad/vol-", "bad/vol-");
    }
    else{
        flush(all_data.article_headers, redirBuffer, redirectCt, N, folder+"redirect/vol-", "redirect/vol-");
        flush(all_data.article_headers, goodBuffer, goodCt, N, folder+"good/vol-", "good/vol-");
        flush(all_data.article_headers, regBuffer, regCt, N, folder+"regular/vol-", "regular/vol-");
        flush(all_data.article_headers, badBuffer, badCt, N, folder+"bad/vol-", "bad/vol-");
    }

}

void compileThread::receiveData(shared_data data_input){

    //data_input.print("Inside receiveData in compilethread.cpp");
    all_data = data_input;
    //run();
}
