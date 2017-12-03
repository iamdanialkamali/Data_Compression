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
using namespace std;
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
unsigned int convertor(string time){
    unsigned int num = str_to_int(time.substr(18,2))+str_to_int(time.substr(12,2))*3600+str_to_int(time.substr(15,2))*60+str_to_int(time.substr(0,2))*3600*24+(month_to_int(time.substr(3,3))-1)*3600*24*30+(str_to_int(time.substr(9,2))-1)*3600*24*365;
    return num;




}
string int_to_string(int a){
    stringstream ss;
    ss << a;
    string str = ss.str();
    return str;
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

void xmlparser(string path) {
    userlist *UserAgentList = new userlist();
    Iplist * HostList = new Iplist();
    reflist * RefererList = new reflist();
    headlist *HeadList = new headlist();
    namelist * headlist = new namelist();

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
                    if(!one) {
                        /*  cout<<"LOG: \n";
                          cout << "head :" <<
                                           HeadList->insert(HeadList->root,1,Head.substr(0,Head.length()-8))
                                                 << '\n';
                          cout << "useragent: " ;
                         cout<<
                              UserAgentList->insert(UserAgentList->root, 1, UserAgent)
                                      << '\n';*/
                        /*cout << "referer: " <<  referer<<'\n'<<
                         RefererList->insert(RefererList->root,1, referer)<< '\n';
                        cout << "rq size: " << requestsize << '\n';*/
                        //cout << "res code: " <<responsecode<<'\n';
                        //get_code_index(str_to_int(responsecode))<< '\n';
                        /*
                       cout << "time : " <<convertor(time)<< '\n';
                        cout << "host : " << host << '\n';*/
                        HostList->insert(UserAgentList->insert(UserAgentList->root, 1, UserAgent)
                                ,HeadList->insert(HeadList->root,1,Head)
                                ,RefererList->insert(RefererList->root, 1, referer)
                                , get_code_index(str_to_int(responsecode))
                                ,str_to_int(requestsize),
                                         convertor(time), HostList->root, 1, str_to_ip(host));

                    }
                    one = false;
                    time ="";
                    UserAgent="";
                    Head ="";
                    host="";
                    referer = "";
                    requestsize="";
                    responsecode="";
                    input.ignore(3, '>');
                }
                if (w == 'H') {
                    input >> w;
                    if (w == 'e') {
                        input.ignore(3, '>');
                        input.get(buffer, 2000, '>');
                        Head = buffer;
                        Head = Head.substr(0,Head.length()-6);
                        //cout<<Head<<'\n';

                    }
                    if (w == 'o') {
                        //cout << "Host:";
                        input.ignore(4, '>');
                        //  input.seekp(3, ios::cur);
                        input.get(buffer, 2000, '>');
                        host = buffer;
                        host = host.substr(0,host.length()-6);
                        // cout << host << '\n';

                    }
                }
                if (w == 'T') {
                    //cout << "Time:";
                    input.ignore(6, '>');
                    // input.seekp(5,ios::cur);
                    input.get(buffer, 2000, '>');
                    time = buffer;
                    time = time.substr(0,time.length()-6);
                    //cout<<time<<'\n';
                }
                if (w == 'U') {
                    // cout << "UserAgent:";
                    input.ignore(10, '>');
                    //input.seekp(9,ios::cur);
                    input.get(buffer, 2000, '>');
                    UserAgent = buffer;
                    UserAgent=UserAgent.substr(0,UserAgent.length()-11);
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
                        referer=referer.substr(0,referer.length()-9);
                        //  cout<<referer<<'\n';
                    } else if (w == 's') {
                        // cout << "Response Code:";
                        input.ignore(11, '>');

                        //input.seekp(10,ios::cur);
                        input.get(buffer, 2000, '>');
                        responsecode = buffer;
                        responsecode=responsecode.substr(0,responsecode.length()-14);
                        //cout<<buffer<<'\n';
                    } else if (w == 'q') {
                        // cout << "RequestSize:";
                        input.ignore(11, '>');

                        //input.seekp(9,ios::cur);
                        input.get(buffer, 2000, '>');
                        requestsize = buffer;
                        requestsize=requestsize.substr(0,requestsize.length()-13);
                        //cout<<requestsize<<'\n';
                    }
                }
        }
    }
/*    cout << "head :" << HeadList->insert(HeadList->root,1,Head) << '\n';
    cout << "useragent: " << UserAgentList->insert(UserAgentList->root,1,UserAgent) << '\n';
    cout << "referer: " << RefererList->insert(RefererList->root,1,referer) << '\n';
    cout << "rq size: " << requestsize << '\n';
    cout << "res code: " << get_code_index( str_to_int(responsecode))  << '\n';
    cout << "time : " << convertor(time) << '\n';
    cout << "host : " << host << '\n';*/
    HostList->insert(UserAgentList->insert(UserAgentList->root, 1, UserAgent)
            ,HeadList->insert(HeadList->root,1,Head)
            ,RefererList->insert(RefererList->root, 1, referer)
            , get_code_index(str_to_int(responsecode))
            ,str_to_int(requestsize),
                     convertor(time), HostList->root, 1, str_to_ip(host));
}
///////////////////////////////////Phase2//////////////////////////////////////////////////////////////////
/*string get_ip_leaf(string before,string req , node* sub){
    string temp = before;
    while (sub->next!= nullptr){

    }
    if(sub->isleaf){
        cout<<before<<'\n';
    }

}
void requestURL(string requrl , headlist*sub,node*sub1){
    // gotoleafs(sub->insert(sub->root,1,requrl),"",sub1);
}
string getreq(int id , string ss, headNode * sub){
    string temp ="";
    if(sub->id==0){
        if(sub->sibiling!= nullptr) {
            temp = temp + getreq(id, "", sub->sibiling);
        }
        if(sub->child!= nullptr) {
            temp = temp + getreq(id, "", sub->child);
        }

    }
    if (sub->id != 0) {
        string temp1 ="";
        if (id == sub->id) {
            if (sub->http == false) {
                temp1 = temp1 + "HTTP/1.0";
            } else {
                temp1 = temp1 + "HTTP/1.1";
            }
            if (sub->method = 'G') { temp = "GET" + temp; }
            else if (sub->method = 'O') { temp = "OPTIONS" + temp; }
            else if (sub->method = 'U') { temp = "PUT" + temp; }
            else if (sub->method = 'S') { temp = "POST" + temp; }
            else if (sub->method = 'H') { temp = "HEAD" + temp; }
            else if (sub->method = 'D') { temp = "DELETE" + temp; }
            else if (sub->method = 'C') { temp = "CONNECT" + temp; }
            else if (sub->method = 'T') { temp = "TRACE" + temp; }
            return temp1;
            //cout << temp << '\n';
        } else return "";
    }
}
node* get_ip(string ip , node* sub,short lvl){
    while (sub!=nullptr) {
        int temp = getthree(str_to_ip(ip),lvl);
        if (sub->isleaf and sub->data.ip==temp){
            //cout<<sub->child->data.datalist->holder->time->time;
            return sub;
        }
        if(sub->data.ip==temp){
            return get_ip(ip,sub->child,lvl+1);
        }


        sub = sub->next;
    }

}
int count(TimeNode* timeNode){
    if(timeNode== nullptr){
        return 0;
    } else{
        return count(timeNode->next)+1;
    }
}
*/
///////
string get_ip_leaf(string before,string req , node* sub){
    string temp = before;
    while (sub->next!= nullptr){

    }
    if(sub->isleaf){
        cout<<before<<'\n';
    }

}
void requestURL(string requrl , headlist*sub,node*sub1){
    // gotoleafs(sub->insert(sub->root,1,requrl),"",sub1);
}
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
}
string getreq(int id , string ss, headNode * sub){
    string res = ss;

    if (sub->id > 0 && sub->id != id) {
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
    if(sub->child!= nullptr && sub->sibiling!= nullptr) {
        return getreq(id,res, sub->sibiling) + getreq(id, res+ sub->data, sub->child);
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
        if (sub->isleaf){
            /*while (sub!= nullptr){
            }*/
            //  cout<<sub->data.ip;
        }

        sub = sub->next;
    }

}
int count(TimeNode* timeNode){
    if(timeNode== nullptr){
        return 0;
    } else{
        return count(timeNode->next)+1;
    }
}
bool gotoleaf(int id ,node* sub ,string ss){
    /*node * temp =sub;
   while(temp!= nullptr){
        node * nexttemp =temp;
        while(nexttemp!= nullptr){
            if(nexttemp->isleaf){
                cout<<nexttemp->data.ip<<'\n';
            }

            nexttemp = nexttemp->next;
        }
        temp = temp->child;
    }*/
    if(sub->isleaf){
        string dd = ss+'.'+int_to_string(sub->data.ip);
        if(sub->child->data.datalist->has_req(id,sub->child->data.datalist->holder)){
            dd= dd.substr(3);
            cout<<dd<<'\n';
        }

    }
    if(sub->child!= nullptr && sub->next!= nullptr) {
        return gotoleaf(id,sub->next ,ss) & gotoleaf(id,sub->child , ss+'.'+int_to_string(sub->data.ip));
    }
    if(sub->child!= nullptr && sub->next== nullptr){
        return gotoleaf(id,sub->child,ss +'.'+int_to_string(sub->data.ip));
    }

    if(sub->child== nullptr && sub->next!= nullptr){
        return gotoleaf(id,sub->next ,ss);
    }
    if(sub->child== nullptr && sub->next== nullptr){
        return 0;
    }

}


///int calc_percentage_of_a_response_for_a_url_of_an_ip(int responseCode,string url, string ip)
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
                cnt1 += 1*count(datanode->time);
                cnt2+= 1*count(datanode->time);
            } else{
                cnt2+= 1*count(datanode->time);
            }

        }
        datanode=datanode->next;

    }
    cnt1=cnt1*100;
    return(cnt1/cnt2);
}


///////
///int calc_percentage_of_a_response_for_a_url_of_an_ip(int responseCode,string url, string ip)
/*int calc_percentage_of_a_response_for_a_url_of_an_ip(int responseCode,int url, string ip,node* sub){
    int cnt1 = 0;
    int cnt2 = 0;
    int rescode = responseCode;
    int id =url;
    //ref->insert(ref->root,1,url);
    node * node1 = get_ip(ip , sub,0)->child;
    DataHolder* datanode = node1->data.datalist->holder;
    while (datanode!= nullptr){
        int tempid  = datanode->data[3];
        if(id==tempid){
            int temp = datanode->data[1];
            if( rescode==temp){
                cnt1 += 1*count(datanode->time);
                cnt2+= 1*count(datanode->time);
            } else{
                cnt2+= 1*count(datanode->time);
            }

        }
        datanode=datanode->next;

    }
    cnt1=cnt1*100;
    return(cnt1/cnt2);
}
*/


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
int main() {


    //cout<<"End"<<'\n';

    //while(true){

    //}
    //   xmlparser("/home/alan/Documents/C++/DS_Project/out.xml");
   /*  DataList* dataList = new DataList();
      dataList->add_data(1,2,3,4,5,6);
      dataList->add_data(1,2,3,4,5,7);
      dataList->add_data(1,2,3,4,4,8);
      dataList->add_data(1,2,3,4,5,9);
      dataList->add_data(1,2,3,4,5,10);

/*
     //cout<<getthree(192168001001,0);
      Iplist *iplist = new Iplist();
      iplist->insert(1,2,3,4,5,6,iplist->root,1,192168008001);
      iplist->insert(1,2,3,4,4,6,iplist->root,1,192168008001);
      iplist->insert(1,2,3,4,5,8,iplist->root,1,192168008001);
      iplist->insert(1,2,3,4,5,9,iplist->root,1,192168008001);
      iplist->insert(1,2,3,4,5,10,iplist->root,1,192168008001);
      iplist->insert(1,5,3,4,5,5,iplist->root,1,192168008001);
      //iplist->insert(7,6,4,4,6,4,iplist->root,1,192168004002);
      //iplist->insert(8,4,5,6,2,1,iplist->root,1,191168008002);
      //iplist->insert(8,7,2,2,9,5,iplist->root,1,191168009002);
      node* ss = get_ip("192.168.8.2",iplist->root->child,0);
      cout<<ss->data.ip;
      //cout<<calc_percentage_of_a_response_for_a_url_of_an_ip(102,4,"192.168.8.1",iplist->root->child);
      //get_ip_leaf("","",iplist->root);*/
    //iplist->insert(93,iplist->root,1,193168058002);
    //iplist->insert(84,iplist->root,1,193165008002);
    //iplist->insert(85,iplist->root,1,193165008003);*/
    /*  iplist->insert(192068001001,iplist->root);
      iplist->insert(192168001005,iplist->root);
      iplist->insert(192168001004,iplist->root);
      iplist->insert(192168001001,iplist->root);*/
    /* holder holder15;
    holder15.data=10;
    cout<<holder15.data;
    //string string1 = getdata("/25/221351/51513/",1);
    //  cout<<string1;
    */
    /*reflist *khar = new reflist();
  //  khar->insert(khar->root,1,"http://localhost:9020");
   /* string ss =get_ref_data("http://localhost:9020",1);
    int ssss = ref_lvl_counter("http://localhost:9020");
    int lvl = ref_lvl_counter("https://test.ariogames.ir/news/31");
 /*   Iplist * khar = new Iplist;
    khar->insert(55,khar->root,1,192168001002);
    khar->insert(55,khar->root,1,192168011002);
    khar->insert(55,khar->root,1,192168841002);
   */
    /*headlist * khar = new headlist;
     khar->insert(khar->root,1,"GET /ad/ba/ca/dd/df?sg&fdd HTTP/1.0");
     khar->insert(khar->root,1,"GET /mainpage/news?lidmit=10&offset=0&ssssss HTTP/1.1");
     khar->insert(khar->root,1,"GET /mainpage/news?limait=10&offset=0&ssssss&SDASD=454 HTTP/1.0");
     khar->insert(khar->root,1,"GET /mainpage/news?limdit=10&offset=0&sssssddds&SDASD=454 HTTP/1.1");
     cout<<getreq(2,"",khar->root);
    cout<<"Done";
    while (true){
    cout<<"Datadonde"<<'\n';
    }


    return 1;

}
*/
int main(){
        //xmlparser("/home/alan/Documents/C++/DS_Project/out.xml");
        /*     userlist * userlist1 = new userlist();
             userlist1->insert(userlist1->root,1,"Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/61.0.3163.100 Safari/537.36");
             userlist1->insert(userlist1->root,1,"Mozilla/5.1 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/61.0.3163.100 Safari/537.36");
             userlist1->insert(userlist1->root,1,"Mozilla/5.2 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/61.0.3163.100 Safari/537.36");
             userlist1->insert(userlist1->root,1,"Mozilla/5.3 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/61.0.3163.100 Safari/537.36");

             usernode *root =userlist1->root;
             cout << getUser(1,"",root->child)<<'\n' <<getUser(2,"",root->child)<<'\n'<<getUser(3,"",root->child)<<'\n'<<getUser(4,"",root->child)<<'\n';
        *//*
             headlist *headlist1 = new headlist();
             headlist1->insert(headlist1->root,1,"GET /mainpage1/news?limit=10&offset=0 HTTP/1.1");
             headlist1->insert(headlist1->root,1,"GET /mainpage2/news?limit=10&offset=0 HTTP/1.1");
             headlist1->insert(headlist1->root,1,"GET /mainpage3/news?limit=10&offset=0 HTTP/1.1");
             headlist1->insert(headlist1->root,1,"GET /mainpage4/news?limit=10&offset=0 HTTP/1.1");

             headNode *root =headlist1->root ;
             cout << getreq(1,"",root)<<'\n'<< getreq(2,"",root)<<'\n'<< getreq(3,"",root)<<'\n'<< getreq(4,"",root)<<'\n';
                */
        Iplist *iplist = new Iplist();
        iplist->insert(1,2,3,4,5,6,iplist->root,1,192168008001);
        iplist->insert(1,2,3,4,4,6,iplist->root,1,192168008002);
        iplist->insert(1,2,3,4,5,8,iplist->root,1,192168008003);
        iplist->insert(1,2,3,4,5,9,iplist->root,1,192168008004);
        iplist->insert(1,2,3,4,5,1,iplist->root,1,192168008005);
        iplist->insert(1,5,3,4,5,5,iplist->root,1,192168008006);
        iplist->insert(1,5,3,4,5,5,iplist->root,1,192168008007);
        iplist->insert(1,5,3,4,5,5,iplist->root,1,192168008008);
        iplist->insert(1,5,3,4,5,5,iplist->root,1,192160008009);
        iplist->insert(1,5,3,4,5,5,iplist->root,1,192168008010);
        iplist->insert(1,5,3,4,5,5,iplist->root,1,192168007011);
        iplist->insert(1,5,3,4,5,5,iplist->root,1,198168008012);

        gotoleaf(2,iplist->root,"");
        //iplist->insert(7,6,4,4,6,4,iplist->root,1,192168004002);
        //iplist->insert(8,4,5,6,2,1,iplist->root,1,191168008002);
        // iplist->insert(8,7,2,2,9,5,iplist->root,1,191168009002);
        //node* ss = get_ip("192.168.8.3",iplist->root->child,0);
        //cout<< ss->child->data.datalist->req_is_in(ss->child->data.datalist->holder,2);
        //cout<<ss->child->data.datalist->holder->time->time;
        //cout<<calc_percentage_of_a_response_for_a_url_of_an_ip(102,4,"192.168.8.1",iplist->root->child);
        //get_ip_leaf("","",iplist->root);*/
        //iplist->insert(93,iplist->root,1,193168058002);
        //iplist->insert(84,iplist->root,1,193165008002);
        //iplist->insert(85,iplist->root,1,193165008003);*/
       /* while (true){
                    cout<<"Done"<<'\n';

                }*/
}


