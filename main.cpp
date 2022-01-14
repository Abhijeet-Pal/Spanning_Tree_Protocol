#include "bridge.h"

#include "bridgesim.h"
#include<string>
#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<set>
#include<sstream>

using namespace std;
map<string, vector<string>> bridge_to_lan;
vector<LAN> lan_list;
vector<Bridge>bridge_list;
map<string,vector<string>> lan_to_bridge;


int get_lan(string nm)
{
    for (int i=0; i<lan_list.size(); i++)
    {
        if(lan_list[i].LAN_Name == nm) return i;
    }
}



void lan_receive(vector<Message> mess_list)
{
    for(Message m : mess_list)
    {
        lan_list[get_lan(m.through_LAN)].receive(m);
    }
}



int get_bridge(string bridge_id)
{
    for (int i=0; i<bridge_list.size(); i++)
        if (bridge_list[i].bridge_name==bridge_id) return i;

}

bool same_root(vector<Message> mess,string root)
{
    bool flag = !(mess.size() == 0);
    for (int i=0; i<mess.size(); i++)
    {
        if (mess[i].root_name_assumed!=root) flag=false;
    }
    return flag;
}

void receive_all(vector<Message> mess_list, int trace, int time)
{
    for(Message mess : mess_list)
    {
        vector<string> bs = lan_to_bridge[mess.through_LAN];
        for(string bridge_id : bs)
        {
            if(bridge_id != mess.assumed_by)
            {
                bridge_list[get_bridge(bridge_id)].receive(mess,trace,time);
            }
        }
    }
}
vector <string> blank;

int main()
{

    int trace;
    cin>>trace;
    string s;
    int number_of_bridges;
    cin>>number_of_bridges;
    getline(cin, s);

    string a;
    string in;
    set <string> lan_names;
    for(int i=0; i<number_of_bridges; i++)
    {
        getline(cin,in);
        stringstream X(in);
        vector<string> words;
        while(getline(X, a, ' ')) words.push_back(a);

        vector<string> lanlist(words.begin()+1,words.end());
        Bridge b(words[0].substr(0,words[0].size()-1), lanlist);
        bridge_list.push_back(b);
        bridge_to_lan[b.bridge_name]=lanlist;

        for(int i=1; i<words.size(); i++) lan_names.insert(words[i]);

    }

    for(string lan : lan_names)
    {
        LAN laan(lan,blank);
        lan_list.push_back(laan);
    }

    for(auto x : bridge_list)
        for(string name : x.port)
        {
            lan_list[get_lan(name)].bridge.push_back(x.bridge_name);
            lan_to_bridge[name].push_back(x.bridge_name);
        }



    vector <Message> received;
    vector <Message> sent;
    int time=0;
    string root_bridge="B1";


    while(!same_root(received,root_bridge))
    {

        receive_all(received,trace,time);
        for (Bridge b: bridge_list)
            for (Message mess: b.send(trace,time))
                sent.push_back(mess);


        received = sent;
        sent.clear();
        time++;

    }


    for(Bridge b : bridge_list) for(string x : b.port)
        {
            if(b.port_type[x] == "DP")
                bridge_list[get_bridge(b.bridge_name)].port_type[x] = "NP";
        }

    lan_receive(received);
    for(LAN l : lan_list)
    {
        string db = l.designated_bridge;
        bridge_list[get_bridge(db)].port_type[l.LAN_Name] = "DP";
    }

    for (int i=0; i<bridge_list.size(); i++)
    {
        sort(bridge_list[i].port.begin(),bridge_list[i].port.end());

    }

    for (Bridge b : bridge_list)
    {
        int count=0;
        for (string x : b.port)
        {
            if (b.port_type[x]=="DP") count++;
        }
        if (count==0)
        {
            for (string x: b.port)
                bridge_list[get_bridge(b.bridge_name)].port_type[x] = "NP";
        }

    }



    for (Bridge b : bridge_list)
    {
        b.print();
    }
    return 0;
}
