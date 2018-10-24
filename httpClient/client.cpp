#include "restclient-cpp/restclient.h"
#include <iostream>
#include <string>
using namespace std;
int main(){
	string rgb = "EE7E00";
	string uri = "http://localhost:3000/";
	RestClient::Response r = RestClient::get(uri.append(rgb));
	cout << r.body << endl;
}
