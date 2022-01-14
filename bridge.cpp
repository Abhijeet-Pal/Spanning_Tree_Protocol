#include "bridge.h"
#include<string>
#include<iostream>
#include<vector>
#include<map>
#include<functional>

using namespace std;



   Message::Message(string root_name_assumed_intake, int distance_intake, string assumed_by_intake, string lan_name_intake){
root_name_assumed=root_name_assumed_intake;
distance=distance_intake;
assumed_by=assumed_by_intake;
through_LAN=lan_name_intake;
}
Bridge::Bridge()
{

}


 Bridge::Bridge(string bridge_name_intake, vector<string> port_intake){
    bridge_name=bridge_name_intake;
    root_name_assumed=bridge_name_intake;
    distance=0;
    root_name_assumed=bridge_name_intake;
    port=port_intake;
    for (int i=0;i<port.size();i++){
    port_type[port[i]]="DP";
    }
 }



void Bridge:: receive(Message Message_received, int trace, int time){
if (trace==1){
cout<<time<<" r "<<this-> bridge_name<<" ("<<Message_received.root_name_assumed<<", "<<Message_received.distance<<", "<<Message_received.assumed_by<<")"<<endl;
}
    string root_port_bridge="";
 for (int i=0;i<port.size();i++){
    if (port_type[port[i]]=="RP")root_port_bridge=port[i];
    }


if (Message_received.root_name_assumed < this->root_name_assumed){
this-> root_name_assumed=Message_received.root_name_assumed;
this->distance=1+Message_received.distance;
this-> best_bridge=Message_received.assumed_by;
this-> port_type[Message_received.through_LAN]="RP";
for (int i=0;i<port.size();i++){
if (port_type[port[i]]=="RP"&& port[i]!=Message_received.through_LAN)
port_type[port[i]]="DP";
}
 int count=0;
 for (int i=0;i<port.size();i++){
    if (port_type[port[i]]=="DP")count++;
    }
    if (count==0){
    for (int j=0;j<port.size();j++){
    port_type[port[j]]="NP";}
}


}



else if (Message_received.root_name_assumed == this->root_name_assumed && 1+Message_received.distance<this-> distance ){
    this->distance=1+Message_received.distance;
    this-> best_bridge=Message_received.assumed_by;
    this-> port_type[Message_received.through_LAN]="RP";
    for (int i=0;i<port.size();i++){
    if (port_type[port[i]]=="RP"&& port[i]!=Message_received.through_LAN )
    port_type[port[i]]="NP";}

 int count=0;
 for (int i=0;i<port.size();i++){
    if (port_type[port[i]]=="DP")count++;
    }
    if (count==0){
    for (int j=0;j<port.size();j++){
    port_type[port[j]]="NP";}
}


}
else if(Message_received.root_name_assumed == this->root_name_assumed && Message_received.distance+1==this-> distance && this->best_bridge>Message_received.assumed_by){
    this->distance=1+Message_received.distance;
    this-> best_bridge=Message_received.assumed_by;
    this-> port_type[Message_received.through_LAN]="RP";
    for (int i=0;i<port.size();i++){
    if (port_type[port[i]]=="RP"&& port[i]!=Message_received.through_LAN)
    port_type[port[i]]="DP";

}
 int count=0;
 for (int i=0;i<port.size();i++){
    if (port_type[port[i]]=="DP")count++;
    }
    if (count==0){
    for (int j=0;j<port.size();j++){
    port_type[port[j]]="NP";}
}


}
else if (Message_received.root_name_assumed == this->root_name_assumed && Message_received.distance+1==this-> distance && Message_received.assumed_by==this->best_bridge && Message_received.through_LAN<root_port_bridge){
port_type[root_port_bridge]="NP";
port_type[Message_received.through_LAN]="RP";
int count=0;
 for (int i=0;i<port.size();i++){
    if (port_type[port[i]]=="DP")count++;
    }
    if (count==0){
    for (int j=0;j<port.size();j++){
    port_type[port[j]]="NP";}
}
}
else if (Message_received.root_name_assumed == this->root_name_assumed && Message_received.distance+1==this-> distance && Message_received.assumed_by==this->best_bridge && Message_received.through_LAN>root_port_bridge)
    {
        port_type[Message_received.through_LAN]="NP";
    int count=0;
 for (int i=0;i<port.size();i++){
    if (port_type[port[i]]=="DP")count++;
    }
    if (count==0){
    for (int j=0;j<port.size();j++){
    port_type[port[j]]="NP";}
}
    }

 else if(Message_received.root_name_assumed == this->root_name_assumed && Message_received.distance+1==this-> distance && this->best_bridge>Message_received.assumed_by)
  {
        port_type[Message_received.through_LAN]="NP";
    int count=0;
 for (int i=0;i<port.size();i++){
    if (port_type[port[i]]=="DP")count++;
    }
    if (count==0){
    for (int j=0;j<port.size();j++){
    port_type[port[j]]="NP";}
}
    }
     int count=0;
 for (int i=0;i<port.size();i++){
    if (port_type[port[i]]=="DP")count++;
    }
    if (count==0){
    for (int j=0;j<port.size();j++){
    port_type[port[j]]="NP";}
}

}

vector<Message> Bridge::send (int  trace, int time){
    vector<Message> ans;
for (int i=0;i<port.size();i++){
if (this->port_type[port[i]]=="DP"){
    if (trace==1)
    cout<<time<<" s "<<this-> root_name_assumed<<" ("<<this->root_name_assumed<<", "<<this-> distance<<", "<<this->bridge_name<<")"<<endl;

    Message msend(this->root_name_assumed, this->distance, this->bridge_name,port[i] );
    ans.push_back(msend);
}
}
return ans;
}

void Bridge:: print(){
cout<<this->bridge_name<<": ";
map<string, string> :: iterator it;
	for (it=this->port_type.begin(); it!=this->port_type.end(); it++)
	{
		cout << it->first << "-" << it->second <<" ";
	}
	cout<<endl;

}


  LAN::LAN(string LAN_Name_intake, vector<string>bridge_intake){
    LAN_Name=LAN_Name_intake;
    bridge=bridge_intake;
    distance=INT_MAX;
    }



void LAN:: receive(Message mess){
if (mess.distance<this->distance){
    this->distance=mess.distance;
    this->designated_bridge=mess.assumed_by;
}
}




