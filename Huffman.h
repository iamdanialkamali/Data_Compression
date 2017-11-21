//
// Created by amirhossein on 11/9/17.
//

#ifndef PROJECT2_HUFFMAN_H
#define PROJECT2_HUFFMAN_H

#endif //PROJECT2_HUFFMAN_H
#include <bits/stdc++.h>
using namespace std ;

class Huffman {
    struct MinHeapNode{
        char data;
        int freq ;
        MinHeapNode *left , *right ;
        MinHeapNode(char data , int freq){
            left = right = NULL ;
            this -> data = data ;
            this -> freq = freq ;
        }

    };

    // for comparison of two heap node
    struct  compare {
        bool operator()(MinHeapNode* l ,MinHeapNode* r){
            return (l->freq > r->freq);
        }
    };

public:
    char characters[66]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V', 'W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r', 's','t','u','v','w','x','y','z','/','.','\t','1','2','3','4','5','6','7','8','9','0','?'};
    string codes[66]={};
    //prints huffman code from the root of huffman tree
    int findIndex (char chars[],char c){
        int length = 66 ;
        int counter = 0 ;
        while (counter < length ){
            if(chars[counter]==c){
                return counter ;
            }
            counter++ ;
        }
    }
    void getResult(){

        for(int i = 0 ; i < 66 ; i++){
            cout << characters[i] << ": "<< codes[i] << "\n";
        }

    //    cout << getIndex() ;
    }
    void printCodes(struct MinHeapNode* root , string str){

        if (!root){
            return;
        }

        if (root->data != '$'){
         //   cout << root->data <<": " <<str << "\n" ;
            codes[findIndex(characters , root->data)]=str;
        }

        printCodes(root->left , str + "0");
        printCodes(root->right, str + "1");
    }

    //the main function that builds a Huffman tree and
    //print codes by traversing the built tree
    void HuffmanCodes(char data[] , int freq[] , int size){

        struct MinHeapNode *left , *right , *top ;

        //creat a minheap and insert all characters of data[]
        priority_queue<MinHeapNode*,vector<MinHeapNode*>,compare> minHeap ;
        for (int i = 0 ; i < size ; ++i){
            minHeap.push(new MinHeapNode(data[i],freq[i]));
        }

        //iterate while size of heap doesn't become 1
        while (minHeap.size() !=1){

            left = minHeap.top();
            minHeap.pop();

            right = minHeap.top();
            minHeap.pop();

            //Creat a new internal node with frequency equal to sum of the two nodes frequencies
            //make the two extracted node a childs of this node
            //add the node to the minHeap
            // "$" is a special value for internal nodes not used
            top = new MinHeapNode('$',left->freq + right->freq);
            top->left = left ;
            top->right= right ;
            minHeap.push(top);
        }
        printCodes(minHeap.top() ,"");
        getResult();
    }

};
/*
    Huffman huffman;
    ifstream input;
//    ofstream outputt ("/home/amirhossein/CLionProjects/project2/res.txt",ios_base :: binary);

    input.open("/home/amirhossein/CLionProjects/project2/xml.xml");
    if (!input) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }

    char c;
    while (!input.eof()) {
        input >> c;
        switch (c) {
            case '<':
                char buffer[800];
                char w = 's';
                input >> w;
                if (w == 'H') {
                    input >> w;
                    if (w == 'e') {
                //        cout << "Head:";
                        input.seekg(3, ios::cur);
                        input.get(buffer, 100, '<');
                  //      cout << buffer << '\n';
                        for (char c : buffer){
                            counts[findIndex(chars , c)]++ ;

                        }
                    }
                }
        }
    }



    int indexx = getIndex();
    char data[indexx]={};
    int freq[indexx]={};
    int appendIndex =0 ;
    for (int i = 0 ; i < 66 ; i++){
        if(counts[i] != 0){
            data[appendIndex]=chars[i];
            freq[appendIndex]=counts[i];
            appendIndex++;
        }
    }

    input.close();
    showCounts();
    int size = sizeof(data) / sizeof(data[0]);
    huffman.HuffmanCodes(data , freq ,size);
*/
/*
void getCount (string str ){
    for (char i : str) {
        counts[findIndex (chars , i)] ++ ;
    }
}
void showCounts(){
    for(int i = 0 ; i < 66 ; i++){
        cout << chars[i] << ": "<<counts[i]<<"\n" ;
    }
}
int getIndex(){
    int indexx=0;
    for (int i = 0 ; i < 66; i++){
        if(counts[i] != 0){
            indexx ++;
        }
    }
    return indexx;
}*/



