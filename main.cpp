#include "bridge.h"
#include "bridge.cpp"
#include "bridgesim.cpp"
#include "bridgesim.h"
#include<string>
#include<iostream>
#include<vector>
#include<map>
#include<algorithm>

using namespace std;
vector <string> bridge_ids;
vector<Bridge>bridge_list;
map<string,vector<string>> lan_bridge;
bool compareFunction (std::string a, std::string d)
{
    return a<d;
}

int get_bridge(string bridge_id)
{
    for (int i=0; i<bridge_ids.size(); i++)
        if (bridge_ids[i]==bridge_id) return i;

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

void receive_all(vector<Message> mess, int trace, int time)
{
    for(Message m : mess)
    {
        vector<string> bs = lan_bridge[m.through_LAN];
        for(string bridge_id : bs)
        {
            if(bridge_id != m.assumed_by)
            {
                bridge_list[get_bridge(bridge_id)].receive(m,trace,time);
            }
        }
    }
}


int main()
{

    int trace;
    cin>>trace;

    int number_of_bridges;
    cin>>number_of_bridges;
    for (int z=0; z<number_of_bridges; z++)
    {
        string in;
        cin>>in;
        string name;
        vector<string> port_in;
        char a=in.at(0);
        char b=in.at(1);
        name=a+b;
        for (int y=4; y<in.size()-1; y++)
        {
            char c=in.at(y);
            std::string ctemp(1, c);
            port_in.push_back(ctemp);

        }
        sort(port_in.begin(),port_in.end(),compareFunction);
        Bridge bride_name_is(name,port_in);
        bridge_ids.push_back(name);
       Bridge bridge_list[z];
        bridge_list[z].bridge_name=name;
        bridge_list[z].port=port_in;
        for (int i=0; i<port_in.size(); i++)
        {
            lan_bridge.insert(port_in[i],name);
        }

    }
    vector <Message> received;
    vector <Message> sent;
    int time=0;
    string root_bridge=bridge_ids[0];


    while(!same_root(received,root_bridge))
    {

        receive_all(received,trace,time);
        for (int k=0;k<bridge_ids.size();k++){
             bridge_list[k].send(trace,time);
            sent.push_back(bridge_list[k].send(trace,time));

        }
      /*  for(Bridge brn : bridge_ids){ for(Message m : brn.send(trace,time)) sent.push_back(m);}*/

        received = sent;
        sent.clear();
        time++;

    }
    for (int i=0; i<bridge_ids.size(); i++)
    {
       // bridge_list[i].print();
    cout<<bridge_list[i].bridge_name<<": ";
map<string, string> :: iterator it;
	for (it=bridge_list[i].port_type.begin(); it!=bridge_list[i].port_type.end(); it++)
	{
		cout << it->first << "-" << it->second <<" ";
	}
	cout<<endl;


    }

}
