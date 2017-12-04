#include <iostream>
#include <fstream>
#include <cstring>
#include <math.h>
#include <iostream>
#include <cstring>
#include "Huffman.h"
#include <fstream>
#include <sstream>
#include <bitset>
#include <string>
#include<time.h>
#include <chrono>
using namespace std;
using namespace chrono;
int16_t responsecodes[62]= {100,101,102,200,201,202,203,204,205,206,207,208,226,300,301,302,303,304,305,306,307,308,400,401,402,403,404,405,406,407,408,409,410,411,412,413,414,415,416,417,418,421,422,423,424,426,428,429,431,451,500,501,502,503,504,505,506,507,508,509,510,511};


////////////////////////////////////////////////////////usefull methods/////////////////////////////////////////////////////
string getdata(string path,int m) {
    string data;
    int i = 0;
    int cnt = 0;
    while (path[i]!=' '){
        if(path[i]='/'){
            cnt++;
            i++;
            if (data.length()>0){
                return data;
            }
            while(path[i]!='/') {
                if (cnt==m) {
                    data += path[i];
                }
                i++;
            }

        }
    }


}
string ref_slash(string path){
    for (int j = 0; j <path.length() ; ++j) {
        if(path[j]==':'){
            path = path.substr(j+2);
        }
    }
    path+='/';
    return path;
}
int ref_lvl_counter(string path){
    if(path==""){
        return 0;
    }
    for (int j = 0; j <path.length() ; ++j) {
        if(path[j]==':'){
            path = path.substr(j+2);
            break;
        }
    }
    path+='/';
    short i = -1;
    for(char c:path){
        if(c=='/'){
            i++;
        }
    }
    return i;
}
int head_lvl_counter(string path){
    for (int j = 0; j <path.length() ; ++j) {
        if(path[j]==' '){
            path = path.substr(j+1);
            break;
        }
    }
    short cnt = 0;
    for (int i = 0; i <path.length() ; ++i) {
        if(path[i]=='/'){
            if(path[i+1]==' '){
            } else {
                cnt++;
            }
        }
        if (path[i]==' '){
            break;
        }

    }
    return cnt;

}
int head_max_lvl_counter(string path){
    for (int j = 0; j <path.length() ; ++j) {
        if(path[j]==' '){
            path = path.substr(j+1);
            break;
        }
    }
    short cnt = 0;
    for (int i = 0; i <path.length() ; ++i) {
        if(path[i]=='/' or path[i]=='?' or path[i]=='&'){
            if(path[i+1]==' '){
            } else {
                cnt++;
            }
        }
        if (path[i]==' '){
            break;
        }

    }
    return cnt;
}
bool headhttp(string path){
    if(path[path.length()-1]=='0'){
        return true;
    }
    return false;
}
char head_method(string path){
    if(path[0]=='P'){
        if(path[1]=='O'){
            return 'S';
        }
        if(path[1]=='U'){
            return 'U';
        }
    } else{
        return path[0];
    }
}
string user_changer(string ss){
    for(char c:ss){
        if (c=='/'){
            c=' ';
        }
    }
    return ss;

}
/*string get_head_data(string path,int m){
    for (int j = 0; j <path.length() ; ++j) {
        if(path[j]==' '){
            path = path.substr(j+1);
            break;
        }
    }
    path+='/';
    string data;
    int head = 0;
    int last = 0;
    for (int i = 0; i <path.length() ; ++i) {
        if(m==1){
            if(path[i]=='/' or path[i]=='?' or path[i]=='&' or path[i]==' '){
                head=i;
            }
        }
        if(m==0){
            if(path[i]=='/' or path[i]=='?' or path[i]=='&' or path[i]==' '){
                last=i;
                break;
            }
        }
        else{
            if(path[i]=='/' or path[i]=='?' or path[i]=='&' or path[i]==' '){
                m--;
            }
        }

    }
    return path.substr(head+1,last-head-1);

}*/
string get_head_data(string path,int m){
    for (int j = 0; j <path.length() ; ++j) {
        if(path[j]==' '){
            path = path.substr(j+1);
            break;
        }
    }
    path+='/';
    string data;
    int head = 0;
    int last = 0;
    for (int i = 0; i <path.length() ; ++i) {
        if(m==1){
            if(path[i]=='/' or path[i]=='?' or path[i]=='&' or path[i]==' '){
                head=i;
            }
        }
        if(m==0){
            if(path[i]=='/' or path[i]=='?' or path[i]=='&' or path[i]==' '){
                last=i+1;
                break;
            }
        }
        else{
            if(path[i]=='/' or path[i]=='?' or path[i]=='&' or path[i]==' '){
                m--;
            }
        }

    }
    return path.substr(head+1,last-head-1);

}
string get_ref_data(string path,int m) {
    for (int j = 0; j <path.length() ; ++j) {
        if(path[j]==':'){
            path = path.substr(j+2);
            break;
        }
    }
    path+='/';
    string data;
    int head = 0;
    int last = 0;
    for (int i = 0; i <path.length() ; ++i) {
        if(m==1){
            if(path[i]=='/'){
                head=i;
            }
        }
        if(m==0){
            if(path[i]=='/'){
                last=i;
                break;
            }
        }
        else{
            if(path[i]=='/'){
                m--;
            }
        }
    }
    return path.substr(head+1,last-head-1);

}
/*string get_user_data(string user , int m){

    user = ' '+ user +' ';
    string data;
    int head = 0;
    int last = 0;
    for (int i = 0; i <user.length() ; ++i) {
        if(m==1){
            if(user[i]==' '){
                head=i;
            }
            if(user[i]=='/'){
                head=i;
            }
        }
        if(m==0){
            if(user[i]==' '){
                last=i;
                break;
            }

            if(user[i]=='/'){
                last=i;
                break;
            }
        }
        else{
            if(user[i]==' '){
                m--;
            }
            if(user[i]=='/'){
                m--;
            }

        }
    }
    return user.substr(head+1,last-head-1);


}*/
string get_user_data(string user , int m){

    user = ' '+ user +' ';
    string data;
    int head = 0;
    int last = 0;
    for (int i = 0; i <user.length() ; ++i) {
        if(m==1){
            if(user[i]==' '){
                head=i;
            }
            if(user[i]=='/'){
                head=i;
            }
        }
        if(m==0){
            if(user[i]==' '){
                last=i;
                break;
            }

            if(user[i]=='/'){
                last=i+1;
                break;
            }
        }
        else{
            if(user[i]==' '){
                m--;
            }
            if(user[i]=='/'){
                m--;
            }
        }

    }
    return user.substr(head+1,last-head-1);


}
int user_lvl_counter(string user){
    user = ' '+ user +' ';
    short i = -1;
    for(char c:user){
        if(c==' '){
            i++;
        }
        if(c=='/'){
            i++;
        }
    }
    return i;

}
long getthree(unsigned long data,int i){
    if(i==0){
        return  data /pow(10, 3*3);
    } if (i==1){
        return (data - getthree(data,0)*pow(10,9))/pow(10,6);
    }if (i==2){
        return (data - getthree(data,1)*pow(10,6) -getthree(data,0)*pow(10,9))/pow(10,3);
    }
    if (i==3){
        return (data - getthree(data,2)*pow(10,3)- getthree(data,1)*pow(10,6) -getthree(data,0)*pow(10,9))/pow(10,0);
    }

}
int get_code_index(int a){
    for (int i = 0; i <65 ; ++i) {
        if(responsecodes[i]==a){
            return  i;

        }
    }
}
int backcounter(char w,string s){
    int cnt=0;
    for (char c:s){
        if(c== w){
            cnt++;
        }

    }
    return cnt;
}
int str_to_int(string str){
    int num =0;
    for (int i=0 ; i<str.length() ; i++){
        num+= (str[i]-'0')*pow(10,str.length()-i-1);
    }
    return num ;

}
long str_to_ip(string str) {
    str+=".";
    int cnt = 9;
    string temp_str;
    long temp_int = 0;
    short lenght = str.length();
    for (int i =0; i<lenght+1;i++) {
        if ( str[i]!= '.') {
            temp_str += str[i];
        } else{
            temp_int += str_to_int(temp_str)*pow(10,cnt);
            temp_str="";
            cnt-=3;
        }
    }
    return temp_int;
}
int month_to_int(string month){
    if(month=="Jan"){
        return 1;
    }if(month=="Feb"){
        return 2;
    }if(month=="Mar"){
        return 3;
    }if(month=="Apr"){
        return 4;
    }if(month=="May"){
        return 5;
    }if(month=="Jun"){
        return 6;
    }if(month=="Jul"){
        return 7;
    }if(month=="Aug"){
        return 8;
    }if(month=="Sept"){
        return 9;
    }if(month=="Sep"){
        return 9 ;
    }if(month=="Oct"){
        return 10;
    }if(month=="Nov"){
        return 11;
    }if(month=="Dec"){
        return 12;
    }
}
int utc_to_time(string utc){
    int hour = 10*str_to_int(utc.substr(1,2));
    if (utc.substr(3,2)=="30"){
        hour++;
    }
    if(utc.substr(0,1)=="-"){
        hour++;
    }


}

string int_to_string(int a){
    stringstream ss;
    ss << a;
    string str = ss.str();
    return str;
}
string int_to_month(int month){
    if(month==1){
        return "Jan";
    }
    if(month==2){
        return "Feb";
    }
    if(month==3){
        return "Mar" ;
    }
    if(month==4){
        return "Apr" ;
    }
    if(month==5){
        return "May" ;
    }
    if(month==6){
        return "Jun" ;
    }
    if(month==7){
        return "Jul" ;
    }
    if(month==8){
        return "Aug" ;
    }
    if(month==9){
        return "Sep" ;
    }
    if(month==10){
        return "Oct" ;
    }
    if(month==11){
        return "Nov" ;
    }
    if(month==12){
        return "Dec" ;
    }





}
unsigned int convertor(string time){
    ///19/Oct/2017:08:53:05 +0000
    int tm_sec = str_to_int(time.substr(18,2));
    int tm_min = str_to_int(time.substr(15,2));
    int tm_hour = str_to_int(time.substr(12,2));
    int tm_yday = str_to_int(time.substr(0,2)) ;
    int tm_month = month_to_int(time.substr(3,3)) ;
    int tm_year = str_to_int(time.substr(7,4)) - 2000 ;
    //  cout << tm_year ;
    return   tm_sec + tm_min*60 + tm_hour*(60*60) + tm_yday*(24*60*60) +tm_month*(30*24*60*60) + tm_year*(12*30*24*60*60);

}
string convert_back (unsigned int time){
    string year = to_string(2000 + time/(12*30*24*60*60)) ;
    int  month = (time%(12*30*24*60*60))/(30*24*60*60);
    string day = to_string(((time%(12*30*24*60*60))%(30*24*60*60))/(24*60*60));
    string hour = to_string((((time%(12*30*24*60*60))%(30*24*60*60))%(24*60*60))/(60*60));
    string min = to_string(((((time%(12*30*24*60*60))%(30*24*60*60))%(24*60*60))%(60*60))/(60));
    string sec = to_string(((((time%(12*30*24*60*60))%(30*24*60*60))%(24*60*60))%(60*60))%(60));
    ///19/Oct/2017:08:53:45 +0000
    return day+'/'+int_to_month(month)+'/'+year +':'+hour+':'+min+':'+sec +" +0000";
}

////////////// Structs//////////////////////////////
struct TimeNode{
    unsigned int time;
    TimeNode * next;
};
struct DataHolder{
    DataHolder* next = nullptr;
    int data[5];
    TimeNode* time = nullptr;
};
class DataList{
public:
    DataHolder * holder;
    DataList(){
        holder=new DataHolder();
    }
    void add_data(int useragent,int head,int refrer,int8_t rescode,unsigned int reqsize,unsigned int time){
        TimeNode * timeNode ;
        if(holder->time== nullptr){
            holder->data[0]=useragent;
            holder->data[1]=head;
            holder->data[2]=refrer;
            holder->data[3]=rescode;
            holder->data[4]=reqsize;
            holder->time = new TimeNode();
            holder->time->time=time;
        } else{
            if(equalholder(holder,useragent,head,refrer,rescode,reqsize)){
                if(holder->time== nullptr){
                    holder->time=new TimeNode();
                    holder->time->time=time;
                } else{
                    if(holder->time->time==time){
                        return;
                    }
                    timeNode = holder->time;
                    while  (timeNode->next!= nullptr){
                        if(timeNode->time==time){
                            return;
                        }
                        timeNode = timeNode->next;
                    }
                    if(timeNode->time==time){
                        return;
                    }
                    timeNode->next = new TimeNode();
                    timeNode->next->time=time;
                    return;
                }
            }
            while(holder->next!= nullptr){
                if(equalholder(holder,useragent,head,refrer,rescode,reqsize)){
                    if(holder->time== nullptr){
                        holder->time=new TimeNode();
                        holder->time->time=time;
                        timeNode = holder->time;
                    } else{
                        while  (timeNode->next!= nullptr){
                            if(timeNode->time==time){
                                return;
                            }
                            timeNode = timeNode->next;
                        }
                        timeNode->next = new TimeNode();
                        timeNode->next->time=time;

                    }
                    return;

                }
                holder = holder->next;
            }
            holder->next=new DataHolder();
            holder->next->data[0]=useragent;
            holder->next->data[1]=head;
            holder->next->data[2]=refrer;
            holder->next->data[3]=rescode;
            holder->next->data[4]=reqsize;
            holder->next->time=new TimeNode();
            holder->next->time->time=time;
        }

    }
    bool equalholder(DataHolder *d1,unsigned int useragent,unsigned int head,unsigned int refrer, int8_t rescode,unsigned int reqsize){
        unsigned  int array[5]={useragent,head,refrer,rescode,reqsize};
        for (int i = 0; i <5 ; ++i) {
            if(d1->data[i]!=array[i]){
                return false;
            }
        }
        return true;
    }bool has_req(int id,DataHolder * dataHolder){
        DataHolder *holder = dataHolder;
        while (holder!= nullptr){
            if(holder->data[1]==id){
                return true;
            }
            holder= holder->next;
        }
        return false;
    }

};
struct headNode{
    bool http = false;
    unsigned int id =0;
    bool isleaf = false;
    char method = 'G';
    headNode* child;
    headNode* sibiling;
    string data ;
};
union mydata{
    int ip;
    DataList *datalist;
};
union headname{
    string name;
    int8_t ansid;
    headname(){
        name ="";
    }
};
struct node{
    bool isleaf = false;
    bool islog = false;
    node* next;
    node* child;
    mydata data;
};///  Ip
struct addressnode{
    unsigned int id;
    string name;
    addressnode * next;
};
struct namenode{
    string name;
    namenode * next;
};
struct refnode{
    unsigned int id;
    bool secure;
    string name;
    refnode* child  ;
    refnode* sibiling ;
};// Referer
struct usernode{
    unsigned  int id =0;
    string name;
    usernode* child;
    usernode* sibiling;
};//UserAgent
////////////////////////////////////////Classes///////////////////////////////////////////
class addressList{
    addressnode* root;
};
class reflist {
public:
    unsigned int count ;
    refnode *root=new refnode();
    reflist() {
        count=0;

    }

    int insert(refnode*sub,short lvl,string path) {
        short final_lvl = ref_lvl_counter(path);
        if (lvl==final_lvl){
            string data = get_ref_data(path,final_lvl);
            if (sub->child== nullptr) {
                sub->child = new refnode();
                if(path[4]=='s'){
                    sub->child->secure=true;
                }
                sub->child->name=data;
                count++;
                sub->child->id=count;
                return count;

            }  else{
                sub=sub->child;
                while(sub->sibiling!= nullptr){
                    if(sub->name==data) {
                        return sub->id;
                    }
                    sub = sub->sibiling;
                }
                sub->sibiling = new refnode();
                sub->sibiling->name=data;

                if(path[4]=='s'){
                    sub->sibiling->secure= true;
                }
                count++;
                sub->sibiling->id=count;
                return count;
            }
            return sub->id;
        }
        if(final_lvl==0){
            return 0;
        }
        if (lvl==1){
            string data = get_ref_data(path,lvl);
            if (sub->child == nullptr) {
                sub->child = new refnode();
                sub->child->name= data;
                return insert(sub->child, lvl + 1, path);

            } else {
                sub = sub->child;
                if (data == sub->name) {
                    return insert(sub, lvl + 1, path);
                } else {
                    while (sub != nullptr) {
                        if (sub->name == data) {
                            return insert(sub, lvl + 1, path);

                        }
                        if (sub->sibiling != nullptr) {
                            sub = sub->sibiling;
                        } else {
                            break;
                        }
                    }
                    sub->sibiling= new refnode();
                    sub->sibiling->name=data;
                    return insert(sub->sibiling, lvl + 1, path);
                }

            }
        }
        else {
            string data = get_ref_data(path,lvl);
            if (sub->child == nullptr) {
                sub->child = new refnode();
                sub->child->name= data;
                return insert(sub->child, lvl + 1, path);

            } else {
                sub = sub->child;
                if (data == sub->name) {
                    return insert(sub, lvl + 1, path);

                } else {
                    while (sub != nullptr) {
                        if (sub->name == data) {
                            return insert(sub, lvl + 1, path);

                        }
                        if (sub->sibiling != nullptr) {
                            sub = sub->sibiling;
                        } else {
                            break;
                        }
                    }
                    sub->sibiling= new refnode();
                    sub->sibiling->name=data;
                    if(path[4]=='s'){
                        sub->sibiling->secure= true;
                    }
                    return insert(sub->sibiling, lvl + 1, path);

                }

            }

        }


    }
};
class namelist{
public:
    unsigned int len=0;
    namenode* root;
    namelist(){
        root = new namenode();
    }
    unsigned int insert(string file){
        namenode *tempnode=root;
        unsigned  int cnt=0;
        /*  tempnode->next=new namenode;
          tempnode->next->name="444";*/
        while(tempnode->next){
            if(tempnode->name==file){
                return cnt;
            }
            tempnode =tempnode->next;
            cnt++;

        }
        tempnode->next=new namenode();
        tempnode->name=file;
        len++;
        return cnt;

    }
};
class Iplist {
public:
    Iplist() {
    }
    node *root = new node();
    void insert(int useragent,int head,int refrer,int8_t rescode,unsigned int reqsize,unsigned int time, node *sub, int lvl, long value) {
        if (lvl==1){
            int data = getthree(value,lvl-1);
            if (sub->child == nullptr) {
                sub->child = new node();
                sub->child->data.ip= data;
                return insert(useragent,head,refrer,rescode,reqsize,time,sub->child, lvl + 1,value);

            } else {
                sub = sub->child;
                if (data == sub->data.ip) {
                    return insert(useragent,head,refrer,rescode,reqsize,time,sub, lvl + 1,value);
                } else {
                    while (sub != nullptr) {
                        if (sub->data.ip == data) {
                            return insert(useragent,head,refrer,rescode,reqsize,time,sub, lvl + 1,value);

                        }
                        if (sub->next != nullptr) {
                            sub = sub->next;
                        } else {
                            break;
                        }
                    }
                    sub->next= new node();
                    sub->next->data.ip=data;
                    return insert(useragent,head,refrer,rescode,reqsize,time,sub->next, lvl + 1,value);
                }

            }
        }
        if (lvl==4){
            int data = getthree(value,lvl-1);
            if (sub->child== nullptr) {
                sub->child = new node();
                sub->child->data.ip=data;
                sub->child->isleaf= true;
                sub->child->child = new node();
                sub->child->child->islog= true;
                sub->child->child->data.datalist = new DataList();
                sub->child->child->data.datalist->add_data(useragent,head,refrer,rescode,reqsize,time);
                return;
            } else{
                sub=sub->child;
                while(sub->next!= nullptr){
                    if(sub->data.ip==data) {
                        sub->child->data.datalist->add_data(useragent,head,refrer,rescode,reqsize,time);
                        return;
                    }
                    sub = sub->next;
                }

                    if(sub->data.ip==data) {
                        sub->child->data.datalist->add_data(useragent,head,refrer,rescode,reqsize,time);
                        return;

                }
                sub->next = new node();
                sub->next->data.ip=data;
                sub->next->isleaf= true;
                sub->next->child = new node();
                sub->next->child->islog= true;
                sub->next->child->data.datalist = new DataList();
                sub->next->child->data.datalist->add_data(useragent,head,refrer,rescode,reqsize,time);
            }
        }

        else {
            int data = getthree(value,lvl-1);
            if (sub->child == nullptr) {
                sub->child = new node();
                sub->child->data.ip= data;
                return insert(useragent,head,refrer,rescode,reqsize,time,sub->child, lvl + 1,value);

            } else {
                sub = sub->child;
                if (data == sub->data.ip) {
                    return insert(useragent,head,refrer,rescode,reqsize,time,sub, lvl + 1,value);

                } else {
                    while (sub != nullptr) {
                        if (sub->data.ip == data) {
                            return insert(useragent,head,refrer,rescode,reqsize,time,sub, lvl + 1,value);

                        }
                        if (sub->next != nullptr) {
                            sub = sub->next;
                        } else {
                            break;
                        }
                    }
                    sub->next= new node();
                    sub->next->data.ip=data;
                    return insert(useragent,head,refrer,rescode,reqsize,time,sub->next, lvl + 1,value);

                }

            }

        }


    }



};
class userlist{
public:
    unsigned int count ;
    usernode *root=new usernode();
    userlist() {
        count=0;
    }

    int insert(usernode*sub,short lvl,string user) {
        short final_lvl = user_lvl_counter(user);

        if (lvl==final_lvl){
            string data = get_user_data(user,final_lvl);
            if (sub->child== nullptr) {
                sub->child = new usernode();
                sub->child->name=data;
                count++;
                sub->child->id=count;
                return count;

            } else{
                sub=sub->child;
                while(sub->sibiling!= nullptr){
                    if(sub->name==data) {
                        return sub->id;
                    }
                    sub = sub->sibiling;
                }
                sub->sibiling = new usernode();
                sub->sibiling->name=data;
                count++;
                sub->sibiling->id=count;
                return count;


            }
            return sub->id;
        } else {
            string data = get_user_data(user,lvl);
            if (sub->child == nullptr) {
                sub->child = new usernode();
                sub->child->name= data;
                return insert(sub->child, lvl + 1, user);

            } else {
                sub = sub->child;
                if (data == sub->name) {
                    return insert(sub, lvl + 1, user);

                } else {
                    while (sub != nullptr) {
                        if (sub->name == data) {
                            return insert(sub, lvl + 1, user);

                        }
                        if (sub->sibiling != nullptr) {
                            sub = sub->sibiling;
                        } else {
                            break;
                        }
                    }
                    sub->sibiling= new usernode();
                    sub->sibiling->name=data;
                    return insert(sub->sibiling, lvl + 1, user);

                }

            }

        }        if (lvl==1){
            string data = get_user_data(user,lvl);
            if (sub->child == nullptr) {
                sub->child = new usernode();
                sub->child->name= data;
                return insert(sub->child, lvl + 1, user);

            } else {
                sub = sub->child;
                if (data == sub->name) {
                    return insert(sub, lvl + 1, user);
                } else {
                    while (sub != nullptr) {
                        if (sub->name == data) {
                            return insert(sub, lvl + 1, user);

                        }
                        if (sub->sibiling != nullptr) {
                            sub = sub->sibiling;
                        } else {
                            break;
                        }
                    }
                    sub->sibiling= new usernode();
                    sub->sibiling->name=data;
                    return insert(sub->sibiling, lvl + 1, user);
                }

            }
        }


    }
};
class headlist{
public:
    headlist(){
        count=0;
    }
    unsigned int count ;
    headNode * root = new headNode();
    int insert(headNode*sub,short lvl,string path) {
        short final_lvl = head_max_lvl_counter(path);
        short leaf_lvl = head_lvl_counter(path);
        if (lvl==final_lvl or final_lvl==0){
            string data = get_head_data(path,final_lvl);
            if (sub->child== nullptr) {
                sub->child = new headNode();
                sub->child->data=data;
                count++;
                sub->child->id=count;
                sub->child->method=head_method(path);
                sub->child->http=headhttp(path);
                return count;

            }  else{
                sub=sub->child;
                while(sub->sibiling!= nullptr){
                    if(sub->data==data) {
                        return sub->id;
                    }
                    sub = sub->sibiling;
                }
                sub->sibiling = new headNode();
                sub->sibiling->data=data;
                count++;
                sub->sibiling->id=count;
                sub->sibiling->method=head_method(path);
                sub->sibiling->http=headhttp(path);
                return count;
            }
            return sub->id;
        }if(path==""){
            return 0;
        }
        if(lvl ==leaf_lvl ){
            string data = get_head_data(path,lvl);
            if (sub->child == nullptr) {
                sub->child = new headNode();
                sub->child->data= data;
                return insert(sub->child, lvl + 1, path);

            } else {
                sub = sub->child;
                if (data == sub->data) {
                    return insert(sub, lvl + 1, path);

                } else {
                    while (sub != nullptr) {
                        if (sub->data == data) {
                            return insert(sub, lvl + 1, path);

                        }
                        if (sub->sibiling != nullptr) {
                            sub = sub->sibiling;
                        } else {
                            break;
                        }
                    }
                    sub->sibiling= new headNode();
                    sub->sibiling->data=data;
                    sub->sibiling->isleaf= true;

                    return insert(sub->sibiling, lvl + 1, path);

                }

            }


        }
        if (lvl==1){
            string data = get_head_data(path,lvl);
            if (sub->child == nullptr) {
                sub->child = new headNode();
                sub->child->data= data;
                return insert(sub->child, lvl + 1, path);

            } else {
                sub = sub->child;
                if (data == sub->data) {
                    return insert(sub, lvl + 1, path);
                } else {
                    while (sub != nullptr) {
                        if (sub->data == data) {
                            return insert(sub, lvl + 1, path);

                        }
                        if (sub->sibiling != nullptr) {
                            sub = sub->sibiling;
                        } else {
                            break;
                        }
                    }
                    sub->sibiling= new headNode();
                    sub->sibiling->data=data;
                    return insert(sub->sibiling, lvl + 1, path);
                }

            }
        }
        else {
            string data = get_head_data(path,lvl);
            if (sub->child == nullptr) {
                sub->child = new headNode();
                sub->child->data= data;
                return insert(sub->child, lvl + 1, path);

            } else {
                sub = sub->child;
                if (data == sub->data) {
                    return insert(sub, lvl + 1, path);

                } else {
                    while (sub != nullptr) {
                        if (sub->data == data) {
                            return insert(sub, lvl + 1, path);

                        }
                        if (sub->sibiling != nullptr) {
                            sub = sub->sibiling;
                        } else {
                            break;
                        }
                    }
                    sub->sibiling= new headNode();
                    sub->sibiling->data=data;
                    return insert(sub->sibiling, lvl + 1, path);

                }

            }

        }


    }

};
////////////////////////////////////////Parser/////////////////////////////

string getUser(int id , string ss ,usernode * sub) {
    string res = ss;

    if (sub->id > 0 && sub->id != id) {
        return "";
    }
    if(sub->id == id){
        return res+sub->name ;
    }
    if(sub->child!= nullptr && sub->sibiling!= nullptr) {
        return getUser(id,res, sub->sibiling) + getUser(id, res+ sub->name, sub->child);
    }
    if(sub->child!= nullptr && sub->sibiling== nullptr){
        return getUser(id, res + sub->name , sub->child);
    }

    if(sub->child== nullptr && sub->sibiling!= nullptr){
        return getUser(id,res, sub->sibiling);
    }
    if(sub->child== nullptr && sub->sibiling== nullptr){
        return "";
    }
}
string getref(int id , string ss ,refnode * sub) {
    string res = ss;

    if (sub->id > 0 && sub->id != id && sub->sibiling== nullptr) {
        return "";
    }
    if(sub->id == id){
        if(sub->secure){
            return "https://"+res+sub->name ;

        } else
        {
            return "http://"+res+sub->name ;

        }

    }
    if(sub->child!= nullptr && sub->sibiling!= nullptr) {
        return getref(id,res, sub->sibiling) + getref(id, res+ sub->name, sub->child);
    }
    if(sub->child!= nullptr && sub->sibiling== nullptr){
        return getref(id, res + sub->name , sub->child);
    }

    if(sub->child== nullptr && sub->sibiling!= nullptr){
        return getref(id,res, sub->sibiling);
    }
}
string getreq(int id , string ss, headNode * sub){
    string res = ss;
    if (sub->id > 0 && sub->id != id && sub->sibiling== nullptr) {
        return "";
    }
    if(sub->id == id){
        string ss = res;
        if(sub->method=='G'){
            ss = "GET "+ss;
        }else if(sub->method=='O'){
            ss = "OPTIONS "+ss;
        }else if(sub->method=='U'){
            ss = "PUT "+ss;
        }else if(sub->method=='S'){
            ss = "POST "+ss;
        }else if(sub->method=='D'){
            ss = "DELETE "+ss;
        }else if(sub->method=='C'){
            ss = "CONNECT "+ss;
        }else if(sub->method=='H'){
            ss = "HEAD "+ss;
        }
        ss = ss+ sub->data;
        if(sub->http== true){
            ss  = ss+ "HTTP/1.0";
        }
        if(sub->http== false){
            ss  = ss+ "HTTP/1.1";
        }
        return ss;


        return res+sub->data ;
    }
    if(sub->child== nullptr && sub->sibiling== nullptr){
        return "";
    }
    if(sub->child!= nullptr && sub->sibiling!= nullptr) {

        string s2 = getreq(id, res+ sub->data, sub->child);
        string s1 = getreq(id,res, sub->sibiling);
        return  s1 +s2 ;
    }
    if(sub->child!= nullptr && sub->sibiling== nullptr){
        return getreq(id, res + sub->data , sub->child);
    }

    if(sub->child== nullptr && sub->sibiling!= nullptr){
        return getreq(id,res, sub->sibiling);
    }


}
node* get_ip(string ip , node* sub,short lvl){
    while (sub!=nullptr) {
        int temp = getthree(str_to_ip(ip),lvl);
        if (sub->isleaf && sub->data.ip==temp){
            //cout<<sub->child->data.datalist->holder->time->time;
            return sub;
        }
        if(sub->data.ip==temp){
            return get_ip(ip,sub->child,lvl+1);
        }
        sub = sub->next;
    }
}
void  get_firstTime_request(string ip,node* sub,headNode * headNode,refnode* refnode, usernode * usernode){
    DataHolder *star= get_ip(ip,sub->child,0)->child->data.datalist->holder;
    cout<<"LOG:"<<'\n';
    cout << getUser(star->data[0], "", usernode) << '\n';
    cout << getref(star->data[2], "", refnode) << '\n';
    //cout << getreq(star->data[1], "", headNode) << '\n';
    cout<< responsecodes[star->data[3]]<<'\n';
    cout<< star->data[4]<<'\n';
    cout << convert_back(star->time->time)<<'\n';

}
int count(TimeNode* timeNode){
    int cnt = 0;
    TimeNode * time=timeNode;
    while (time!= nullptr){
        cnt++;
        time = time->next;
    }
    return cnt;
}
bool get_all_ips_of_a_request(int id ,node* sub ,string ss){
    if(sub->isleaf){
        string dd = ss+'.'+int_to_string(sub->data.ip);
        if(sub->data.ip==id) {
            dd = dd.substr(3);
            cout << dd << '\n';
        }

    }
    if(sub->child!= nullptr && sub->next!= nullptr) {
        return get_all_ips_of_a_request(id,sub->next ,ss) & get_all_ips_of_a_request(id,sub->child , ss+'.'+int_to_string(sub->data.ip));
    }
    if(sub->child!= nullptr && sub->next== nullptr){
        return get_all_ips_of_a_request(id,sub->child,ss +'.'+int_to_string(sub->data.ip));
    }

    if(sub->child== nullptr && sub->next!= nullptr){
        return get_all_ips_of_a_request(id,sub->next ,ss);
    }
    if(sub->child== nullptr && sub->next== nullptr){
        return 0;
    }

}
bool get_similarity(int id ,node* sub ,string ss){
    if(sub->isleaf){
        string dd = ss+'.'+int_to_string(sub->data.ip);
            dd = dd.substr(3);
            cout << dd << '\n';


    }
    if(sub->child!= nullptr && sub->next!= nullptr) {
        return get_all_ips_of_a_request(id,sub->next ,ss) & get_all_ips_of_a_request(id,sub->child , ss+'.'+int_to_string(sub->data.ip));
    }
    if(sub->child!= nullptr && sub->next== nullptr){
        return get_all_ips_of_a_request(id,sub->child,ss +'.'+int_to_string(sub->data.ip));
    }

    if(sub->child== nullptr && sub->next!= nullptr){
        return get_all_ips_of_a_request(id,sub->next ,ss);
    }
    if(sub->child== nullptr && sub->next== nullptr){
        return 0;
    }

}
bool get_all_requests_of_an_ip(node * sub,string ip,headNode * headNode,refnode* refnode, usernode * usernode){
    DataHolder *star= get_ip(ip,sub->child,0)->child->data.datalist->holder;
    TimeNode * timeNode1;
    while(star!= nullptr){
        timeNode1=star->time;
        while (timeNode1!= nullptr) {
            cout<<"LOG:"<<'\n';
            cout << getUser(star->data[0], "", usernode) << '\n';
            cout << getref(star->data[2], "", refnode) << '\n';
           // cout << getreq(star->data[1], "", headNode) << '\n';
            cout<< responsecodes[star->data[3]]<<'\n';
            cout<< star->data[4]<<'\n';
            cout << convert_back(timeNode1->time)<<'\n';
            timeNode1=timeNode1->next;
        }
        star = star->next;
    }
}

int count_2(int rescode ,node* sub,int id){
    int cnt2 = 0;
    if(sub->isleaf){
        DataHolder *dataHolder = sub->child->data.datalist->holder;
        while (dataHolder!= nullptr){
            if(dataHolder->data[3]==id)
            {
                cnt2 += count(dataHolder->time);
            }
            dataHolder=dataHolder->next;
        }
        return cnt2;
    }
    if(sub->child!= nullptr && sub->next!= nullptr) {
        return count_2(rescode,sub->next,id) + count_2(rescode,sub->child , id);
    }
    if(sub->child!= nullptr && sub->next== nullptr){
        return count_2(rescode,sub->child,id);
    }

    if(sub->child== nullptr && sub->next!= nullptr){
        return count_2(rescode,sub->next ,id);
    }
    if(sub->child== nullptr && sub->next== nullptr){
        return 0;
    }
}
int count_1(int rescode ,node* sub,int id){
    int cnt2 = 0;
    if(sub->isleaf){

        DataHolder *dataHolder = sub->child->data.datalist->holder;
        while (dataHolder!= nullptr){
            if(dataHolder->data[3]==id and dataHolder->data[1]==rescode)
            {
                cnt2 += count(dataHolder->time);
            }
            dataHolder=dataHolder->next;
        }
        return cnt2;
    }
    if(sub->child!= nullptr && sub->next!= nullptr) {
        return count_2(rescode,sub->next,id) + count_2(rescode,sub->child , id);
    }
    if(sub->child!= nullptr && sub->next== nullptr){
        return count_2(rescode,sub->child,id);
    }

    if(sub->child== nullptr && sub->next!= nullptr){
        return count_2(rescode,sub->next ,id);
    }
    if(sub->child== nullptr && sub->next== nullptr){
        return 0;
    }
}


int calc_percentage_of_a_response_for_a_url(int rescode ,node* sub,int id){
    int a = count_1(rescode,sub,id);
    int b = count_2(rescode,sub,id);

}

int calc_percentage_of_a_response_for_a_url_of_an_ip(int responseCode,int url, string ip,node* sub){
    int cnt1 = 0;
    int cnt2 = 0;
    int rescode = get_code_index(responseCode);
    int id =url;
    //ref->insert(ref->root,1,url);
    node * node1 = get_ip(ip , sub,0)->child;
    DataHolder* datanode = node1->data.datalist->holder;
    while (datanode!= nullptr){
        int tempid  = datanode->data[3];
        if(id==tempid){
            int temp = datanode->data[1];
            if( rescode==temp){
                cnt1 += count(datanode->time);
                cnt2+= count(datanode->time);
            } else{
                cnt2+= count(datanode->time);
            }

        }
        datanode=datanode->next;

    }
    return(100*cnt1/(cnt2+cnt1));
}

void xmlparser(string path) {
    userlist *UserAgentList = new userlist();
    Iplist *HostList = new Iplist();
    reflist *RefererList = new reflist();
    headlist *HeadList = new headlist();
    namelist *headlist = new namelist();

    string Head;
    string UserAgent;
    string host;
    string referer;
    string requestsize;
    string responsecode;
    string time;
    fstream input;
    input.open(path);
    char c;
    int cnt = 0;
    bool one = true;
    while (!input.eof()) {
        input >> c;
        switch (c) {
            case '<':
                char buffer[2000];
                char w = '0';
                input >> w;
                if (w == 'L') {
                    if (!one) {

                        HostList->insert(UserAgentList->insert(UserAgentList->root, 1, UserAgent),
                                         HeadList->insert(HeadList->root, 1, Head),
                                         RefererList->insert(RefererList->root, 1, referer),
                                         get_code_index(str_to_int(responsecode)), str_to_int(requestsize),
                                         convertor(time), HostList->root, 1, str_to_ip(host));

                    }
                    one = false;
                    time = "";
                    UserAgent = "";
                    Head = "";
                    host = "";
                    referer = "";
                    requestsize = "";
                    responsecode = "";
                    input.ignore(3, '>');
                }
                if (w == 'H') {
                    input >> w;
                    if (w == 'e') {
                        input.ignore(3, '>');
                        input.get(buffer, 2000, '>');
                        Head = buffer;
                        Head = Head.substr(0, Head.length() - 6);
                        //cout<<Head<<'\n';

                    }
                    if (w == 'o') {
                        //cout << "Host:";
                        input.ignore(4, '>');
                        //  input.seekp(3, ios::cur);
                        input.get(buffer, 2000, '>');
                        host = buffer;
                        host = host.substr(0, host.length() - 6);
                        // cout << host << '\n';

                    }
                }
                if (w == 'T') {
                    //cout << "Time:";
                    input.ignore(6, '>');
                    // input.seekp(5,ios::cur);
                    input.get(buffer, 2000, '>');
                    time = buffer;
                    time = time.substr(0, time.length() - 6);
                    //cout<<time<<'\n';
                }
                if (w == 'U') {
                    // cout << "UserAgent:";
                    input.ignore(10, '>');
                    //input.seekp(9,ios::cur);
                    input.get(buffer, 2000, '>');
                    UserAgent = buffer;
                    UserAgent = UserAgent.substr(0, UserAgent.length() - 11);
                    // cout<<UserAgent<<'\n';
                }
                if (w == 'R') {
                    //input.ignore(3, '>');
                    input.seekp(1, ios::cur);
                    input >> w;
                    if (w == 'f') {
                        // cout << "Referer:";
                        input.ignore(6, '>');
                        // input.seekp(5,ios::cur);
                        input.get(buffer, 2000, '>');
                        referer = buffer;
                        referer = referer.substr(0, referer.length() - 9);
                        //  cout<<referer<<'\n';
                    } else if (w == 's') {
                        // cout << "Response Code:";
                        input.ignore(11, '>');

                        //input.seekp(10,ios::cur);
                        input.get(buffer, 2000, '>');
                        responsecode = buffer;
                        responsecode = responsecode.substr(0, responsecode.length() - 14);
                        //cout<<buffer<<'\n';
                    } else if (w == 'q') {
                        // cout << "RequestSize:";
                        input.ignore(11, '>');

                        //input.seekp(9,ios::cur);
                        input.get(buffer, 2000, '>');
                        requestsize = buffer;
                        requestsize = requestsize.substr(0, requestsize.length() - 13);
                        //cout<<requestsize<<'\n';
                    }
                }
        }
    }

    HostList->insert(UserAgentList->insert(UserAgentList->root, 1, UserAgent),
                     HeadList->insert(HeadList->root, 1, Head), RefererList->insert(RefererList->root, 1, referer),
                     get_code_index(str_to_int(responsecode)), str_to_int(requestsize),
                     convertor(time), HostList->root, 1, str_to_ip(host));
/*
 * vector<string> (string reqUrl)
vector<Request> get_all requests_of_an_ip(string ip)
int calc_percentage_of_a_response_for_a_url(int responseCode, string url)
int calc_percentage_of_a_response_for_a_url_of_an_ip(int responseCode,
string url, string ip)
Request get_firstTime_request(string ip)
vector<string> get_similar_ip()*/
    while (true) {
        cout<<"Welcome To CLI!"<<'\n';
        string input;
        cin >> input;
        if (input.substr(0, 24) == "get_all_ips_of_a_request") {
            string url = input.substr(25, input.length() - 26);
            get_all_ips_of_a_request(HeadList->insert(HeadList->root, 1, url), HostList->root, "");
        } else if (input.substr(0, 25) == "get_all_requests_of_an_ip") {
            string ip = input.substr(26, input.length() - 27);
            get_all_requests_of_an_ip(HostList->root, ip, HeadList->root, RefererList->root, UserAgentList->root);
        } else if (input.substr(0, 52) ==
                   "int calc_percentage_of_a_response_for_a_url_of_an_ip(int responseCode,string url, string ip)") {
            string data = input.substr(53, input.length() - 54);
            string temp[3];
            int cnt = 0;
            for (char c : data) {
                if (c != ',') {
                    temp[cnt] += c;
                } else {
                    cnt++;
                }
            }
            cout << calc_percentage_of_a_response_for_a_url_of_an_ip(str_to_int(temp[0]),
                                                                     HeadList->insert(HeadList->root, 1, temp[1]),
                                                                     temp[2], HostList->root);

        } else if (input.substr(0, 21) == "get_firstTime_request") {
            string ip = input.substr(22, input.length() - 23);
            get_firstTime_request(ip,HostList->root,HeadList->root,RefererList->root,UserAgentList->root);
        } else if(input.substr(0,14)=="get_similar_ip"){
            get_similarity(0,HostList->root,"");
        }


    }
///////////////////////////////////Phase2//////////////////////////////////////////////////////////////////
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(){
       //xmlparser("/home/alan/Documents/C++/DS_Project/out.xml");

    }




