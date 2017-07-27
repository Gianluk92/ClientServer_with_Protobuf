#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>


#define CLIENT_IMPL(proto) "\n{ \n\
	m_"+ (proto) + " proto_msg; \n\
    string msg; \n\
    char nameF[20]; \n\
    fun selector = f_" + (proto)+ "; \n\
    msg = std::to_string(selector); \n\
    sprintf(nameF,\"%s\",msg.c_str()); \n\
    mysend(general_descriptor, nameF, sizeof(nameF), log_file); \n\
    --fill_msg-- \
    proto_msg.clear_response(); \n\
    proto_msg.SerializeToString(&msg); \n\
    sprintf(buf,\"%s\",msg.c_str()); \n\
    mysend(general_descriptor,buf, sizeof(buf), log_file); \n\
    int num_bytes = receive(general_descriptor, buf, log_file); \n\
    buf[num_bytes] = \'\\0\'; \n\
    msg = buf; \n\
    proto_msg.ParseFromString(msg); \n\
    log_file-> warning_err(\"function " + (proto) + " end\",errno); \n\
    return proto_msg.response(); \n\
} \n\n" 

#define SERVER_IMPL(proto) "\n\
	\t\tcase f_" + (proto) + ": \n\
	\t\t{\n\
	    \t\tm_" + (proto) + " proto_msg; \n\
	    \t\tint num_bytes = receive(session_descriptor, buf, log_file); \n\
	    \t\tbuf[num_bytes] = \'\\0\'; \n\
	    \t\tmsg = buf; \n\
	    \t\tproto_msg.ParseFromString(msg);\n\
	    \t\t--call_function-- \n\
	    \t\tproto_msg.SerializeToString(&msg);\n\
	    \t\tsprintf(buf,\"%s\",msg.c_str()); \n\
	    \t\tmysend(session_descriptor,buf, sizeof(buf), log_file);\n\
    	\t\tlog_file-> warning_err(\"function " + (proto) + " end\",errno); \n\
	    \t\tbreak;\n\
	\t\t}\n\n"

using namespace std;

typedef struct 
{
	string line;
	vector<string> parts;
} fun;

typedef struct 
{
	bool read;
	string name;
	vector<string> line;
	int n_line;
} msg_proto;

void read_declaration(string name, vector<fun>* f, vector<msg_proto>* t);
string write_proto(vector<fun>* f,vector<msg_proto>* t);
void write_class_hh(string name, vector<fun> f);
void write_class_cc(string name, vector<fun> f, vector<msg_proto> t);
void write_make(string name);


