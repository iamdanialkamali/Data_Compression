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
string user_changer(string ss){
    for(char c:ss){
        if (c=='/'){
            c=' ';
        }
    }
    return ss;

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


////////////// Structs//////////////////////////////
union mydata{
    int ip;
    unsigned int array[6];
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
        if(path==""){
            return 0;
        }
        short final_lvl = ref_lvl_counter(path);
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
        else if (lvl==final_lvl){
            string data = get_ref_data(path,final_lvl);
            if (sub->child== nullptr) {
                sub->child = new refnode();
                sub->child->name=data;
                count++;
                sub->child->id=count;
                return count;

            } else{
                sub=sub->child;
                while(sub->sibiling!= nullptr){
                    if(sub->name==data){
                        while(sub->child!= nullptr){
                            sub=sub->child;
                        }

                    }
                }

            }
            return sub->id;
        } else {
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
        node *first;
    }
    node *root=new node();
    void insert(unsigned int time , node*sub ,int lvl,long value){
        if (lvl==1){
            short data = getthree(value,lvl-1);
            if(sub->child== nullptr){
                sub->child = new node();
                sub->child->data.ip=data;
                insert(time,sub->child,lvl+2,value);
                return;
            }
            insert(time,sub->child,lvl+1,value);
            return;
        }
        if (lvl==2){
            short data = getthree(value, lvl - 2);
            if(sub== nullptr){
                sub = new node();
                sub->data.ip=data;
                insert(time,sub,lvl+1,value);
                return;
            } else{
                if(data==sub->data.ip){
                    insert(time,sub,lvl+1,value);
                    return;
                } else{
                    while(sub!= nullptr){
                        if(sub->data.ip==data){
                            insert(time,sub,lvl+1,value);
                            return;
                        }
                        if (sub->next != nullptr){
                            sub = sub->next;
                        } else{
                            break;
                        }
                    }

                    sub->next =new node();
                    sub->next->data.ip=data;
                    insert(time,sub->next,lvl+1,value);
                    return;
                }

            }
            /*  short data = getthree(value,lvl-2);
              sub=sub->child;
              if(sub->next==nullptr){
              if(sub->child== nullptr){
                  node * newnode = new node;
                  newnode->data.ip=data;
                  sub->child=newnode;
                  insert(time,newnode,lvl+1,value);

              } else {
                  node *newnode = new node;
                  newnode->data.ip = data;
                  sub->next = newnode;
                  insert(time, newnode, lvl + 1, value);
                  }
              }
              else{
                  while(sub->next!= nullptr){
                      if(sub->data.ip==data){
                          insert(time,sub->child,lvl+1,value);
                      }
                      sub=sub->next;
                  }
                  node *newnode =new node;
                  newnode->data.ip=data;
                  sub->next=newnode;
                  insert(time,newnode,lvl+1,value);
              }*/

        }
        if (lvl==3) {
            short data = getthree(value, lvl - 2);
            if(sub->child== nullptr){
               sub->child = new node();
                sub->child->data.ip=data;
                insert(time,sub->child,lvl+1,value);
                return;
            } else{
                sub = sub->child;
                if(data==sub->data.ip){
                    insert(time,sub,lvl+1,value);
                    return;
                } else{
                    while(sub!= nullptr){
                        if(sub->data.ip==data){
                            insert(time,sub,lvl+1,value);
                            return;
                        }
                        if (sub->next != nullptr){
                            sub = sub->next;
                        } else{
                            break;
                        }
                    }
                    sub->next =new node();
                    sub->next->data.ip=data;
                    insert(time,sub->next,lvl+1,value);
                    return;
                }

            }
            /*
            if (sub->next == nullptr) {
                if (sub->child == nullptr) {
                    node *newnode = new node;
                    newnode->data.ip = data;
                    sub->child = newnode;
                    insert(time, newnode, lvl + 1, value);
                } else {
                    node *newnode = new node;
                    newnode->data.ip = data;
                    sub->next = newnode;
                    insert(time, newnode, lvl + 1, value);
                }
            } else {
                while (sub->next != nullptr) {
                    if (sub->data.ip == data) {
                        insert(time, sub->child, lvl + 1, value);
                    }
                    sub = sub->next;
                }
                node *newnode = new node;
                newnode->data.ip = data;
                sub->next = newnode;
                insert(time, newnode, lvl + 1, value);

            }*/
        }
        if (lvl==4) {
            /*
            short data = getthree(value, lvl - 2);
            sub=sub->child;

            if (sub->next == nullptr) {
                if (sub->child == nullptr) {
                    node *newnode = new node;
                    newnode->data.ip = data;
                    sub->child = newnode;
                    insert(time, newnode, lvl + 1, value);
                } else {
                    node *newnode = new node;
                    newnode->data.ip = data;
                    sub->next = newnode;
                    insert(time, newnode, lvl + 1, value);
                }
            } else {
                while (sub->next != nullptr) {
                    if (sub->data.ip == data) {
                        insert(time, sub->child, lvl + 1, value);
                    }
                    sub = sub->next;
                }
                node *newnode = new node;
                newnode->data.ip = data;
                sub->next = newnode;
                insert(time, newnode, lvl + 1, value);
            }*/
            short data = getthree(value, lvl - 2);
            if(sub->child== nullptr){
                sub->child= new node();
                sub->child->data.ip=data;
                insert(time,sub->child,lvl+1,value);
                return;
            } else{
                sub = sub->child;
                if(data==sub->data.ip){
                    insert(time,sub,lvl+1,value);
                    return;
                } else{
                    while(sub!= nullptr) {
                        if (sub->data.ip == data) {
                            insert(time, sub, lvl + 1, value);
                            return;
                        }
                        if (sub->next != nullptr){
                            sub = sub->next;
                        } else{
                            break;
                        }
                    }

                    sub->next =new node();
                    sub->next->data.ip=data;
                    insert(time,sub->next,lvl+1,value);
                    return;
                }

            }
        }

        if (lvl==5){
            unsigned int data =getthree(value,lvl-2)-1+1;
            if (sub->child== nullptr) {
                node *leaf = new node();
                leaf->data.ip = data;
                sub->child = leaf;
                leaf->isleaf = true;
                node *data_holder = new node();
                data_holder->islog = true;
                leaf->child = data_holder;
                data_holder->data.array[0] = time;
            } else{
                sub=sub->child;
                while(sub->next!= nullptr){
                    if(sub->data.ip==data){
                        while(sub->child!= nullptr){
                            sub=sub->child;
                        }
                        node *newnode = new node();
                        sub->child=newnode;
                        newnode->islog= true;
                        newnode->data.array[0]=time;
                    }
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
                    if(sub->name==data){
                        while(sub->child!= nullptr){
                            sub=sub->child;
                        }

                    }
                }

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



////////////////////////////////////////Parser/////////////////////////////
void xmlparser(string path) {
     userlist *UserAgentList = new userlist();
     Iplist * HostList = new Iplist();
     reflist * RefererList = new reflist();
     namelist * NameList = new namelist();
     addressList * AddressList = new addressList();

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
    bool one = true;
    while (!input.eof()) {
        input >> c;
        switch (c) {
            case '<':
                char buffer[20000];
                char tag[20];
                char w = '0';
                input >> w;
                if (w == 'L') {
                    if(!one) {
                        cout<<"LOG: \n";
                        cout << "head :" << Head << '\n';
                        cout << "useragent: " ;
                        cout<< UserAgentList->insert(UserAgentList->root, 1, UserAgent) << '\n';
                        cout << "referer: " << RefererList->insert(RefererList->root, 1, referer) << '\n';
                        cout << "rq size: " << requestsize << '\n';
                        cout << "res code: " << get_code_index(str_to_int(responsecode)) << '\n';
                        cout << "time : " << convertor(time) << '\n';
                        cout << "host : " << host << '\n';
                        HostList->insert(convertor(time), HostList->root, 1, str_to_ip(host));
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
                    //  input.seekp(2,ios::cur);

                }
                if (w == 'H') {
                    input >> w;
                    if (w == 'e') {
                        //cout << "Head:";
                        input.ignore(3, '>');
                        //input.seekp(3, ios::cur);
                        input.get(buffer, 2000, '<');
                        Head = buffer;
                        //cout << buffer << '\n';

                    }
                    if (w == 'o') {
                       /// cout << "Host:";
                        input.ignore(4, '>');
                        //  input.seekp(3, ios::cur);
                        input.get(buffer, 800, '<');
                        host = buffer;
                        // cout << buffer << '\n';

                    }
                }
                if (w == 'T') {
                    ///cout << "Time:";
                    input.ignore(6, '>');
                    // input.seekp(5,ios::cur);
                    input.get(buffer, 800, '<');
                    time = buffer;
                    //cout<<buffer<<'\n';
                }
                if (w == 'U') {
                    ///cout << "UserAgent:";
                    input.ignore(10, '>');
                    //input.seekp(9,ios::cur);
                    input.get(buffer, 2000, '<');
                    UserAgent = buffer;
                    ///cout<<buffer<<'\n';
                }
                if (w == 'R') {
                    //input.ignore(3, '>');
                    input.seekp(1, ios::cur);
                    input >> w;
                    if (w == 'f') {
                        //cout << "Referer:";
                        input.ignore(6, '>');
                        // input.seekp(5,ios::cur);
                        input.get(buffer, 2000, '<');
                        referer = buffer;
                        //cout<<buffer<<'\n';
                    } else if (w == 's') {
                        //cout << "Response Code:";
                        input.ignore(11, '>');

                        //input.seekp(10,ios::cur);
                        input.get(buffer, 2000, '<');
                        responsecode = buffer;
                        //cout<<buffer<<'\n';
                    } else if (w == 'q') {
                       // cout << "RequestSize:";
                        input.ignore(11, '>');

                        //input.seekp(9,ios::cur);
                        input.get(buffer, 2000, '<');
                        requestsize = buffer;
                        //cout<<buffer<<'\n';
                    }

                }

        }


    }
    cout << "head :" << Head << '\n';
    cout << "useragent: " << UserAgentList->insert(UserAgentList->root,1,UserAgent) << '\n';
    cout << "referer: " << RefererList->insert(RefererList->root,1,referer) << '\n';
    cout << "rq size: " << requestsize << '\n';
    cout << "res code: " << get_code_index( str_to_int(responsecode))  << '\n';
    cout << "time : " << convertor(time) << '\n';
    cout << "host : " << host << '\n';
    HostList->insert(convertor(time),HostList->root,1,str_to_ip(host));

}




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
/*
//long int codes[66]={1010111,2,1010110,01
//
//
//
101000010010,011010001,0110100001000,11000101,101100,01101000011,2,0000000,1011011,0000010,01100010,11000100,01100011,2,011111,1100011,111000,0000011,2,1010101,0110100001010,2,2,111001,00011110,1101001,011011,001,1110111,010001,1010100,10100,01101000010011,0000001,111010,1110110,110101,1110,110000,0110000,01001,11001,10111,1101000,0110100001011,01101001,00011111,0110100000,1011010,0101,01110,2,11011,011110,00010,000110,010000,00001,011001,0001110,0110101,11111,100};

 */

/*char chars[66]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V', 'W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r', 's','t','u','v','w','x','y','z','/','.','\t','1','2','3','4','5','6','7','8','9','0','?'};
short coodes[66]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65};
int counts[66] ={};
/*int findLenght(string str){
    string keys[27] = {"Mozilla/", "Windows/", "NT/", "Win64/", "AppleWebKit/", "KHTML/", "like/", "Gecko/", "Chrome/", "Safari/", "x64/",
                       ".", "(", ")", ",", ";", "0", "1", "2","3","4","5","6","7","8","9"," "};
    int i = 0;
    int counter = 0;
    while (i < str.length()) {
        if (str[i] == 'M' && str[i + 1] == 'o' && str[i + 2] == 'z' && str[i + 3] == 'i') {
            counter++;
            i += 8;
        }
        else if (str[i] == 'W' && str[i + 1] == 'i' && str[i + 3] == 'd') {
            counter++;
            i += 8;
        }
        else if (str[i] == 'N' && str[i + 1] == 'T') {
            counter++;
            i += 8;
        }
        else if (str[i] == 'W' && str[i + 1] == 'i' && str[i + 2] == 'n' && str[i + 3] == '6') {
            counter++;
            i += 8;
        }
        else if (str[i] == 'A' && str[i + 1] == 'p' && str[i + 2] == 'p' && str[i + 3] == 'l' && str[i + 4] == 'e' &&
                 str[i + 5] == 'W' && str[i + 6] == 'e') {
            counter++;
            i += 12;
        }
        else if (str[i] == 'K' && str[i + 1] == 'H' && str[i + 2] == 'T' && str[i + 3] == 'M') {
            counter++;
            i += 6;
        }
        else if (str[i] == 'l' && str[i + 1] == 'i' && str[i + 2] == 'k' && str[i + 3] == 'e') {
            counter++;
            i += 5;
        }
        else if (str[i] == 'G' && str[i + 1] == 'e' && str[i + 2] == 'c' && str[i + 3] == 'k') {
            counter++;
            i += 6;
        }
        else if (str[i] == 'C' && str[i + 1] == 'h' && str[i + 2] == 'r' && str[i + 3] == 'o') {
            counter++;
            i += 7;
        }
        else if (str[i] == 'S' && str[i + 1] == 'a' && str[i + 2] == 'f' && str[i + 3] == 'a') {
            counter++;
            i += 7;
        }
        else if (str[i] == 'x' && str[i + 1] == '6' && str[i + 2] == '4') {
            counter++;
            i += 4;
        }
        else if (str[i] == '.') {
            counter++;
            i++;
        }
        else if (str[i] == '(') {
            counter++;
            i++;
        }
        else if (str[i] == ')') {
            counter++;
            i++;
        }
        else if (str[i] == ',') {
            counter++;
            i++;
        }
        else if (str[i] == ';') {
            counter++;
            i++;
        }
        else if (str[i] == '0') {
            counter++;
            i++;
        }
        else if (str[i] == '1') {
            counter++;
            i++;
        }
        else if (str[i] == '2') {
            counter++;
            i++;
        }
        else if (str[i] == '3') {
            counter++;
            i++;
        }
        else if (str[i] == '4') {
            counter++;
            i++;
        }
        else if (str[i] == '5') {
            counter++;
            i++;
        }
        else if (str[i] == '6') {
            counter++;
            i++;
        }
        else if (str[i] == '7') {
            counter++;
            i++;
        }
        else if (str[i] == '8') {
            counter++;
            i++;
        }
        else if (str[i] == '9') {
            counter++;
            i++;
        }
        else if (str[i] == ' ') {
            counter++;
            i++;
        }
        else {
            counter++;
            i++;
        }
    }
    return counter;

}
void userToCode(string str , bitset<6> result[]) {
    string keys[27] = {"Mozilla/", "Windows/", "NT/", "Win64/", "AppleWebKit/", "KHTML/", "like/", "Gecko/", "Chrome/", "Safari/", "x64/",
                       ".", "(", ")", ",", ";", "0", "1", "2","3","4","5","6","7","8","9"," "};
    int b[27]={128,129,130,131,132,133,134,135,136,137,138,46,40,41,44,59,48,49,50,51,52,53,54,55,56,57,32};
    int i = 0;
    int counter = 0 ;
    while (i < str.length()) {
        if (str[i] == 'M' && str[i + 1] == 'o' && str[i + 2] == 'z' && str[i + 3] == 'i') {
            bitset<6> a(b[0] - 127);
            result[counter] = a;
            counter++;
            i += 8;
        }
        else if (str[i] == 'W' && str[i + 1] == 'i' && str[i + 3] == 'd') {
            bitset<6> a(b[1] - 127);
            result[counter] = a;
            counter++;
            i += 8;
        }
        else if (str[i] == 'N' && str[i + 1] == 'T') {
            bitset<6> a(b[2] - 127);
            result[counter] = a;
            counter++;
            i += 8;
        }
        else if (str[i] == 'W' && str[i + 1] == 'i' && str[i + 2] == 'n' && str[i + 3] == '6') {
            bitset<6> a(b[3] - 127);
            result[counter] = a;
            counter++;
            i += 8;
        }
        else if (str[i] == 'A' && str[i + 1] == 'p' && str[i + 2] == 'p' && str[i + 3] == 'l' && str[i + 4] == 'e' &&
                 str[i + 5] == 'W' && str[i + 6] == 'e') {
            bitset<6> a(b[4] - 127);
            result[counter] = a;
            counter++;
            i += 12;
        }
        else if (str[i] == 'K' && str[i + 1] == 'H' && str[i + 2] == 'T' && str[i + 3] == 'M') {
            bitset<6> a(b[5] - 127);
            result[counter] = a;
            counter++;
            i += 6;
        }
        else if (str[i] == 'l' && str[i + 1] == 'i' && str[i + 2] == 'k' && str[i + 3] == 'e') {
            bitset<6> a(b[6] - 127);
            result[counter] = a;
            counter++;
            i += 5;
        }
        else if (str[i] == 'G' && str[i + 1] == 'e' && str[i + 2] == 'c' && str[i + 3] == 'k') {
            bitset<6> a(b[7] - 127);
            result[counter] = a;
            counter++;
            i += 6;
        }
        else if (str[i] == 'C' && str[i + 1] == 'h' && str[i + 2] == 'r' && str[i + 3] == 'o') {
            bitset<6> a(b[8] - 127);
            result[counter] = a;
            counter++;
            i += 7;
        }
        else if (str[i] == 'S' && str[i + 1] == 'a' && str[i + 2] == 'f' && str[i + 3] == 'a') {
            bitset<6> a(b[9] - 127);
            result[counter] = a;
            counter++;
            i += 7;
        }
        else if (str[i] == 'x' && str[i + 1] == '6' && str[i + 2] == '4') {
            bitset<6> a(b[10] - 127);
            result[counter] = a;
            counter++;
            i += 4;
        }
        else if (str[i] == '.') {
            bitset<6> a(b[11]);
            result[counter] = a;
            counter++;
            i++;

        }
        else if (str[i] == '(') {
            bitset<6> a(b[12]);
            result[counter] = a;
            counter++;
            i++;
        }
        else if (str[i] == ')') {
            bitset<6> a(b[13]);
            result[counter] = a;
            counter++;
            i++;
        }
        else if (str[i] == ',') {
            bitset<6> a(b[14]);
            result[counter] = a;
            counter++;
            i++;
        }
        else if (str[i] == ';') {
            bitset<6> a(b[15]);
            result[counter] = a;
            counter++;
            i++;
        }
        else if (str[i] == '0') {
            bitset<6> a(b[16]);
            result[counter] = a;
            counter++;
            i++;
        }
        else if (str[i] == '1') {
            bitset<6> a(b[17]);
            result[counter] = a;
            counter++;
            i++;
        }
        else if (str[i] == '2') {
            bitset<6> a(b[18]);
            result[counter] = a;
            counter++;
            i++;
        }
        else if (str[i] == '3') {
            bitset<6> a(b[19]);
            result[counter] = a;
            counter++;
            i++;
        }
        else if (str[i] == '4') {
            bitset<6> a(b[20]);
            result[counter] = a;
            counter++;
            i++;
        }
        else if (str[i] == '5') {
            bitset<6> a(b[21]);
            result[counter] = a;
            counter++;
            i++;
        }
        else if (str[i] == '6') {
            bitset<6> a(b[22]);
            result[counter] = a;
            counter++;
            i++;
        }
        else if (str[i] == '7') {
            bitset<6> a(b[23]);
            result[counter] = a;
            counter++;
            i++;
        }
        else if (str[i] == '8') {
            bitset<6> a(b[24]);
            result[counter] = a;
            counter++;
            i++;
        }
        else if (str[i] == '9') {
            bitset<6> a(b[25]);
            result[counter] = a;
            counter++;
            i++;
        }
        else if (str[i] == ' ') {
            bitset<6> a(b[26]);
            result[counter] = a;
            counter++;
            i++;
        }
        else {
            bitset<6> a(0);
            result[counter] = a;
            counter++;
            i++;
        }
    }
}
void encoder (bitset<6> codes[],unsigned int encodedHead[],int len){
    int flag=len%6 ;
    if(flag ==0 ) {
        int counter1 =0 ;
        for (int i = 0; i < len / 6; i++) {
            string res;
            for (int j = i*6;j< (i + 1) * 6; j++) {
                res += codes[j].to_string();
            }
            bitset<48> ress(res);
            unsigned int resultt = ress.to_ulong();
            encodedHead[counter1]=(resultt);
            counter1 ++ ;
        }
    }
    else {
        int counter2 =0 ;
        //     cout << "im here" <<'\n' ;
        string string1;
        for (int i = 0 ; i < flag ; i++){
            //        cout << "done" <<'\n' ;
            string1 += codes[i].to_string();
        }
        bitset<16> ress(string1);
        unsigned int resultt = ress.to_ulong();
        //     cout << resultt <<'\n';
        encodedHead[counter2]=resultt;
        counter2++;
        //     cout <<"now here" <<'\n' ;
        for(int i = 0 ;i < len/6 ; i++ ){
            int counter = 0 ;
            string res ;
            for (int j = i*6+(flag);j < (i+1)*6 + flag;j++ ){
                //cout << "got here"<<j<<" "<<counter <<'\n';
                res += codes[j].to_string();
                counter++;
            }
            bitset<48> ress(res);
            unsigned int resultt=ress.to_ulong();
            //    cout<<ress<< " : "<<resultt<<'\n';
            encodedHead[counter2]=resultt;
            counter2 ++ ;
        }
    }
}
void xmlparser1(string path) {
    fstream input;
    input.open(path);
    char c;
    while (!input.eof()) {
        input >> c;
        switch (c) {
            case '<':
                char buffer[800];
                char w = 's';
                input >> w;

                if (w == 'L') {
                    //     cout<<"Log:"<<'\n';
                    input.seekp(2, ios::cur);
                }
                if (w == 'H') {
                    input >> w;
                    if (w == 'e') {

                        //     cout << "Head:";
                        input.seekp(3, ios::cur);
                        input.get(buffer, 100, '<');
                        string head = buffer;
                        bitset<6> headCode[head.length()];
                        int count = head.length() / 6;
                        if (head.length() % 6 != 0)count++;
                        int i = 0;
                        for (char c :head) {
                            bitset<6> code(c);
                            //  cout << code <<'\n';
                            headCode[i] = code;
                            i++;
                        };
                        // IN MISHE ARRAYE NAHAIIE HEAD
                        unsigned int encodedHead[count];
                        encoder(headCode, encodedHead, head.length());

                    }
                    if (w == 'o') {
                        //       cout << "Host:";
                        input.seekp(3, ios::cur);
                        input.get(buffer, 100, '<');
                        //         cout << buffer << '\n';
                    }
                }
                if (w == 'T') {
                    //        cout<<"Time:";
                    input.seekp(5, ios::cur);
                    input.get(buffer, 100, '<');
                    //        cout<<buffer<<'\n';
                }
                if (w == 'U') {
                    //       cout<<"UserAgent:";
                    input.seekp(9, ios::cur);
                    input.get(buffer, 150, '<');
                    string user = buffer;
                    int len = findLenght(user);
                    int count = len / 6;
                    if (len % 6 != 0)count++;
                    bitset<6> codedUser[len];
                    userToCode(buffer, codedUser);
                    // IN MISHE ARRAYE NAHAIIE USER
                    unsigned int encodedUser[count];
                    encoder(codedUser, encodedUser, len);

                    if (w == 'R') {
                        input.seekp(1, ios::cur);
                        input >> w;
                        if (w == 'f') {
                            //   cout<<"Referer:";
                            input.seekp(5, ios::cur);
                            input.get(buffer, 100, '<');
                            string referer = buffer;
                            bitset<6> refererCode[referer.length()];
                            int count = referer.length() / 6;
                            if (referer.length() % 6 != 0)count++;
                            int i = 0;
                            for (char c :referer) {
                                bitset<6> code(c);
                                refererCode[i] = code;
                                i++;
                            };
                            // IN MISHE ARRAYE NAHAIIE REFERER
                            unsigned int encodedReferer[count];
                            encoder(refererCode, encodedReferer, referer.length());

                        } else if (w == 's') {
                            //         cout<<"Response Code:";
                            input.seekp(10, ios::cur);
                            input.get(buffer, 100, '<');
                            //         cout<<buffer<<'\n';
                        } else if (w == 'q') {
                            //         cout<<"RequestSize:";
                            input.seekp(9, ios::cur);
                            input.get(buffer, 400, '<');
                            //         cout<<buffer<<'\n';
                        }

                    }

                }
        }
    }
}
*/
 int main() {
  /*  namelist  *list = new namelist;
    cout<<list->insert("a")<<'\n';
    cout<<list->insert("a")<<'\n';
    cout<<list->insert("b")<<'\n';
    cout<<list->insert("c")<<'\n';
    cout<<list->insert("a")<<'\n';
    cout<<list->insert("alan")<<'\n';
    cout<<list->insert("documents")<<'\n';
    cout<<list->insert("home")<<'\n';
    cout<<list->insert("Documents")<<'\n';
    cout<<list->insert("slam")<<'\n';
    namenode *temp = list->root;
    while (temp){
        cout<<temp->name<<'\n';
        temp=temp->next;
    }
    */
    xmlparser("/home/alan/Documents/C++/DS_Project/xml.xml");
    /*
    xmlparser("/home/alan/Documents/C++/DS_Project/xml.xml");
    Iplist *iplist = new Iplist();
    iplist->insert(55,iplist->root,1,192168008001);
    iplist->insert(77,iplist->root,1,192168008002);
    iplist->insert(84,iplist->root,1,193168008044);
    iplist->insert(85,iplist->root,1,193168008002);
    iplist->insert(87,iplist->root,1,192168488002);
    iplist->insert(93,iplist->root,1,193168058002);
    iplist->insert(84,iplist->root,1,193165008002);
    iplist->insert(85,iplist->root,1,193165008003);
    iplist->insert(192068001001,iplist->root);
    iplist->insert(192168001005,iplist->root);
    iplist->insert(192168001004,iplist->root);
    iplist->insert(192168001001,iplist->root);
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
    return 1;
}




