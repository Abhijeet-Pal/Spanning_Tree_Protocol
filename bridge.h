#ifndef bridge_h
#define bridge_h

#include<iostream>
#include<string>
#include<vector>
#include<map>


using namespace std;

class Message{
public:

int distance;
string root_name_assumed;
string assumed_by;
string through_LAN;

Message(string,int,string,string);
};

class Bridge{
public:

    string bridge_name;
    int distance;
     string best_bridge;
    string root_name_assumed;
    string assumed_by;
    vector<string>port;
    map<string,string>port_type;

    Bridge();


    Bridge(string, vector<string>);

    vector <Message> send(int trace, int time);
    void receive(Message Message_received, int trace, int time);
    void print();


};

class LAN{
public:
    string LAN_Name;
    vector<string> bridge;
    int distance;
    string designated_bridge;

    LAN(string, vector<string>);
    void receive(Message);
};

#endif
