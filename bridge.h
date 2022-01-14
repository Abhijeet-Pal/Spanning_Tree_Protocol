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

Message(string root_name_assumed_intake, int distance_intake, string assumed_by_intake, string lan_name_intake){
root_name_assumed=root_name_assumed_intake;
distance=distance_intake;
assumed_by=assumed_by_intake;
through_LAN=lan_name_intake;
}
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
     Bridge(string bridge_name_intake, vector<string> port_intake){
    bridge_name=bridge_name_intake;
    root_name_assumed=bridge_name_intake;
    distance=0;
    root_name_assumed=bridge_name_intake;
    port=port_intake;
    for (int i=0;i<port.size();i++){
    port_type[port[i]]="DP";
    }

    }

    Message send(int trace, int time);
    void receive(Message Message_received, int trace, int time);
    void print();


};

class LAN{
public:
    string LAN_Name;
    vector<string> bridge;
    int distance;
    string designated_bridge;
    LAN(string LAN_Name_intake, vector<string>bridge_intake){
    LAN_Name=LAN_Name_intake;
    bridge=bridge_intake;
    distance=INT_MAX;
    }
    void receive(Message);
};

#endif
