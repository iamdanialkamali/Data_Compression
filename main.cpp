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
using namespace std;
int16_t responsecode[62]= {100,101,102,200,201,202,203,204,205,206,207,208,226,300,301,302,303,304,305,306,307,308,400,401,402,403,404,405,406,407,408,409,410,411,412,413,414,415,416,417,418,421,422,423,424,426,428,429,431,451,500,501,502,503,504,505,506,507,508,509,510,511};


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
        if(responsecode[i]==a){
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
                    while  (holder->time->next!= nullptr){
                        if(holder->time->time==time){
                            return;
                        }
                        holder->time = holder->time->next;
                    }
                    if(holder->time->time==time){
                        return;
                    }
                    holder->time->next = new TimeNode();
                    holder->time->next->time=time;
                    return;
                }

            }
        while(holder->next!= nullptr){
            if(equalholder(holder,useragent,head,refrer,rescode,reqsize)){
                if(holder->time== nullptr){
                    holder->time=new TimeNode();
                    holder->time->time=time;
                } else{
                    while  (holder->time->next!= nullptr){
                        if(holder->time->time==time){
                            return;
                        }
                        holder->time = holder->time->next;
                    }
                    holder->time->next = new TimeNode();
                    holder->time->next->time=time;

                }
                return;

            }
            holder = holder->next;
        }

        holder->next=new DataHolder();
        holder->data[0]=useragent;
        holder->data[1]=head;
        holder->data[2]=refrer;
        holder->data[3]=rescode;
        holder->data[4]=reqsize;

        }

    }
    bool equalholder(DataHolder *d1,unsigned int useragent,unsigned int head,unsigned int refrer, unsigned rescode,unsigned int reqsize){
        unsigned  int array[5]={useragent,head,refrer,rescode,reqsize};
        for (int i = 0; i <5 ; ++i) {
            if(d1->data[i]!=array[i]){
                return false;
            }
        }
        return true;
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
        if(path ==""){
            return 0;
        }
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
                while (sub->child!= nullptr){
                    sub = sub->child;
                }
                sub->child = new node();

                sub->child->data.datalist = new DataList();
                sub->child->data.datalist->add_data(useragent,head,refrer,rescode,reqsize,time);
                return;

            } else{
                sub=sub->child;
                while(sub->next!= nullptr){
                    if(sub->data.ip==data) {
                        while (sub->child!= nullptr){
                            sub = sub->child;
                        }
                        sub->child = new node();

                        sub->child->data.datalist = new DataList();
                        sub->child->data.datalist->add_data(useragent,head,refrer,rescode,reqsize,time);
                        return;
                    }
                    sub = sub->next;
                }
                if(sub->data.ip==data) {
                    sub->child->data.datalist->add_data(useragent,head,refrer,rescode,reqsize,time);
                    return;

                    sub->child = new node();

                    sub->child->data.datalist = new DataList();
                    sub->child->data.datalist->add_data(useragent,head,refrer,rescode,reqsize,time);
                    return;
                }
                while (sub->next!= nullptr){
                    sub = sub->next;
                }
                sub->next = new node();
                sub->next->data.ip=data;
                sub->next->isleaf= true;
                sub = sub->next;
                while (sub->child!= nullptr){
                    sub = sub->child;
                }
                sub->child = new node();

                sub->child->data.datalist = new DataList();
                sub->child->data.datalist->add_data(useragent,head,refrer,rescode,reqsize,time);
                return;
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
void xmlparser1(string path){
    fstream input;
    input.open(path);
    char c;
    while (!input.eof()){
        input>>c;
        switch(c){
            case '<':
                char buffer[4096000];
                char w='s' ;
                input>>w;

                if (w=='L'){
                    cout<<"Log:"<<'\n';
                    input.seekp(2,ios::cur);
                }
                if (w=='H'){
                    input>>w;
                    if(w=='e'){
                        cout << "Head:";
                        input.seekp(3, ios::cur);
                        input.get(buffer, 4096, '<');
                        cout << buffer << '\n';
                    }
                    if(w=='o'){
                        cout << "Host:";
                        input.seekp(3, ios::cur);
                        input.get(buffer, 4096, '<');
                        cout << buffer << '\n';
                    }
                }
                if (w=='T'){
                    cout<<"Time:";
                    input.seekp(5,ios::cur);
                    input.get(buffer,4096,'<');
                    cout<<buffer<<'\n';
                }
                if (w=='U'){
                    cout<<"UserAgent:";
                    input.seekp(9,ios::cur);
                    input.get(buffer,4096,'>');
                    cout<<buffer<<'\n';
                }
                if (w=='R'){
                    input.seekp(1,ios::cur);
                    input>>w;
                    if(w=='f'){
                        cout<<"Referer:";
                        input.seekp(5,ios::cur);
                        input.get(buffer,409600000,'>');
                        cout<<buffer<<'\n';
                    } else if(w=='s'){
                        cout<<"Response Code:";
                        input.seekp(10,ios::cur);
                        input.get(buffer,4096,'>');
                        cout<<buffer<<'\n';
                    }
                    else if(w=='q'){ cout<<"RequestSize:";
                        input.seekp(9,ios::cur);
                        input.get(buffer,4096,'>');
                        cout<<buffer<<'\n';
                    }

                }

        }
    }
}
void xmlparser(string path) {
     userlist *UserAgentList = new userlist();
     Iplist * HostList = new Iplist();
     reflist * RefererList = new reflist();
     namelist * NameList = new namelist();
     addressList * AddressList = new addressList();
     headlist *HeadList = new headlist();

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
                char buffer[2000000];
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
                                    << '\n';
                        cout << "referer: " <<
                         RefererList->insert(RefererList->root, 1, referer)<< '\n';
                        cout << "rq size: " << requestsize << '\n';
                        cout << "res code: " <<
                        get_code_index(str_to_int(responsecode))<< '\n';
                       cout << "time : " <<convertor(time)<< '\n';*/
                        cout << "host : " << host << '\n';
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
                        input.get(buffer, 2000000, '>');
                        Head = buffer;
                        Head = Head.substr(0,Head.length()-7);

                    }
                    if (w == 'o') {
                       // cout << "Host:";
                        input.ignore(4, '>');
                        //  input.seekp(3, ios::cur);
                        input.get(buffer, 2000000, '>');
                        host = buffer;
                        host = host.substr(0,host.length()-6);
                         //cout << buffer << '\n';

                    }
                }
                if (w == 'T') {
                    //cout << "Time:";
                    input.ignore(6, '>');
                    // input.seekp(5,ios::cur);
                    input.get(buffer, 2000000, '>');
                    time = buffer;
                    time = time.substr(0,time.length()-7);
                    //cout<<buffer<<'\n';
                }
                if (w == 'U') {
                    //cout << "UserAgent:";
                    input.ignore(10, '>');
                    //input.seekp(9,ios::cur);
                    input.get(buffer, 2000000, '>');
                    UserAgent = buffer;
                    UserAgent=UserAgent.substr(0,UserAgent.length()-11);
                    //cout<<buffer<<'\n';
                }
                if (w == 'R') {
                    input.ignore(3, '>');
                    //input.seekp(1, ios::cur);
                    input >> w;
                    if (w == 'f') {
                        //cout << "Referer:";
                        input.ignore(6, '>');
                        // input.seekp(5,ios::cur);
                        input.get(buffer, 2000000, '>');
                        referer = buffer;
                        referer=referer.substr(0,referer.length()-10);
                        //cout<<buffer<<'\n';
                    } else if (w == 's') {
                        cout << "Response Code:";
                        input.ignore(11, '>');

                        //input.seekp(10,ios::cur);
                        input.get(buffer, 2000000, '>');
                        responsecode = buffer;
                        responsecode=responsecode.substr(0,responsecode.length()-15);
                        //cout<<buffer<<'\n';
                    } else if (w == 'q') {
                       cout << "RequestSize:";
                        input.ignore(11, '>');

                        //input.seekp(9,ios::cur);
                        input.get(buffer, 2000000, '>');
                        requestsize = buffer;
                        requestsize=requestsize.substr(0,requestsize.length()-15);
                        //cout<<buffer<<'\n';
                    }

                }

        }


    }
    cout << "head :" << HeadList->insert(HeadList->root,1,Head) << '\n';
    cout << "useragent: " << UserAgentList->insert(UserAgentList->root,1,UserAgent) << '\n';
    cout << "referer: " << RefererList->insert(RefererList->root,1,referer) << '\n';
    cout << "rq size: " << requestsize << '\n';
    cout << "res code: " << get_code_index( str_to_int(responsecode))  << '\n';
    cout << "time : " << convertor(time) << '\n';
    cout << "host : " << host << '\n';
    HostList->insert(UserAgentList->insert(UserAgentList->root, 1, UserAgent)
            ,HeadList->insert(HeadList->root,1,Head)
            ,RefererList->insert(RefererList->root, 1, referer)
            , get_code_index(str_to_int(responsecode))
            ,str_to_int(requestsize),
                     convertor(time), HostList->root, 1, str_to_ip(host));

}
///////////////////////////////////Phase2//////////////////////////////////////////////////////////////////
/*
void gotoleafs(int id,string ss , node* sub){
    string temp ="";
    while (!sub->islog){
        if(sub->child== nullptr){
            delete sub->child;
        }
        if(sub->next== nullptr){
            delete sub->child;
        }
        if(sub->isleaf){
            temp = temp + ss+int_to_string(sub->data.ip);
        } else {
            temp = temp + ss + int_to_string(sub->data.ip) + ".";
        }
            if(sub->next!= nullptr) {
            gotoleafs(id,temp , sub->next);

        }

    sub = sub->child;
    }
    if(sub->islog){
     //   cout<<sub->data.ip<<'\n';

        while (sub!= nullptr){

            if(id == sub->data.){
                cout<<temp.substr(2)<<'\n';
            }
            sub=sub->child;
        }
    }

}
void requestURL(string requrl , headlist*sub,node*sub1){
    gotoleafs(sub->insert(sub->root,1,requrl),"",sub1);
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
void get_ip(string ip , node* sub,short lvl){
    while (sub!=nullptr) {
        if(sub->data.ip==getthree(str_to_ip(ip),lvl)){
            get_ip(ip,sub,lvl+1);
            return;
        }
        if (sub->isleaf){
            while (sub!= nullptr){
               // getreq(sub->data.array[0]);
                sub=sub->child;
            }
        }

    sub = sub->next;
    }

}


*/









/*
    holder * findnode(node* node1, short data , short lvl){
        node *root =node1->child;
        if(root== nullptr){
            node* newnode   =new node();
            newnode->data=data;
            node1->child=newnode;
            return newnode;
        }
        else{
            while (root->next!= nullptr) {
                if (root->data == data){
                    return root;
                }
                root=root->next;
            }if(lvl==3){
                holder *holder1 = new holder ;
                holder1->data = data;
                root->child = holder1;
                time_node * time_node1= new time_node;
                time_node1->time=500;
                holder1->time=time_node1;
                return holder1;
            }
            else {

                node *newnode = new node();
                newnode->data = data;
                root->next = newnode;
                return newnode;
            }
        }
    }
    void insert(long key, node *node1){
        for (int i = 0; i <4 ; ++i) {
            node *root=findnode(node1,getthree(key,i),i);
        }
    }
    void print(){
        node* temp = root;
        while(temp->child!= nullptr){
            while (temp->next!= nullptr){
                cout<<temp->data<<'\n';
                temp=temp->next;
            }
            temp = temp->child;
        }
    }*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 int main() {

    xmlparser("/home/alan/Documents/C++/DS_Project/out.xml");
    cout<<"namste";
    while(true){

    }
 //   xmlparser("/home/alan/Documents/C++/DS_Project/out.xml");

    //cout<<getthree(192168001001,0);
  /*  Iplist *iplist = new Iplist();
    iplist->insert(1,2,3,4,5,6,iplist->root,1,192168008001);
    iplist->insert(1,2,3,4,5,7,iplist->root,1,192168008001);
    iplist->insert(1,2,3,4,5,6,iplist->root,1,192168008001);
    iplist->insert(77,66,4,4,6,4,iplist->root,1,192168008002);
    iplist->insert(84,44,55,6,2,1,iplist->root,1,192168008002);
    iplist->insert(85,61,61,25,9,5,iplist->root,1,191168009002);
    iplist->insert(87,88,52,43,26,256,iplist->root,1,192168009003);*/
    ///gotoleafs(55,"",iplist->root);
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
   */ //int n = backcounter(' ',"Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/61.0.3163.100 Safari/537.36");

   /*headlist * khar = new headlist;
    khar->insert(khar->root,1,"GET /ad/ba/ca/dd/df?sg&fdd HTTP/1.0");
    khar->insert(khar->root,1,"GET /mainpage/news?lidmit=10&offset=0&ssssss HTTP/1.1");
    khar->insert(khar->root,1,"GET /mainpage/news?limait=10&offset=0&ssssss&SDASD=454 HTTP/1.0");
    khar->insert(khar->root,1,"GET /mainpage/news?limdit=10&offset=0&sssssddds&SDASD=454 HTTP/1.1");
    cout<<getreq(2,"",khar->root);*/



        return 1;

}




