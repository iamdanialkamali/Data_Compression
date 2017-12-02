/*void xmlparser1(string path){
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
}s*/