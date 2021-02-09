#pragma once
#include<string>
#include<map>
#include<stdint.h>
using namespace std;
enum AccessType :uint16_t
{
	R = 01,
	W=02,
	X=04
};
class AuthenticationInfo
{
private:
	map<string, string> user;
public:
	bool validateUser(string name, string password)
	{
		bool validUser = false;
		map<string, string>::iterator it;
		it = user.find(name);
		if (it != user.end())
		{
			if (!(it->second.compare(password)))
			{
				validUser = true;
			}
		}
		return validUser;
	}
	void add(string id, string password)
	{
		user.insert(pair<string, string>(id, password));
	}
	AuthenticationInfo()
	{
		user.insert(pair<string, string>("0123", "1*2*3"));
		user.insert(pair<string, string>("0124", "245*a"));
		user.insert(pair<string, string>("0125", "111*b"));
	}
};
class Role
{
private:
	map< string,string> userRoleAccessMap;
public:
	void add(string id, string roleName)
	{
		userRoleAccessMap.insert(pair<string, string>(id,roleName));
	}
	Role()
	{
		userRoleAccessMap.insert(pair<string, string>("0123", "Admin"));
		userRoleAccessMap.insert(pair<string, string>("0124", "onlyReadAndWrite"));
		userRoleAccessMap.insert(pair<string, string>("0125", "user"));
	}
	string getRoleName(string _id)
	{
		map<string, string>::iterator it;
		it = userRoleAccessMap.find(_id);
		if (it != userRoleAccessMap.end())
		{
			return it->second;
		}
		else
		{
			return "Guest";
		}
	}
};
class promission
{
private:
	map<string, uint16_t>promision{};
public:
	promission()
	{
		promision.insert(pair<string, uint16_t>("Admin", (R | W | X)));
		promision.insert(pair<string, uint16_t>("onlyReadAndWrite", (R | W)));
		promision.insert(pair<string, uint16_t>("user", (R | NULL)));
	}
	uint16_t getPromission(string userType)
	{
		map<string, uint16_t>::iterator it;
		it = promision.find(userType);
		if (it != promision.end())
		{
			return it->second;
		}
		else
		{
			return NULL;
		}
	}
};
class Subject
{
private:
	string id;
	string name;
	string proofID;
public:
	Subject(string _id, string PI,string name) :id(_id)
	{
		Role r;
		r.add(_id, name);
		name = r.getRoleName(_id);
		proofID = PI;
	}
	Subject(void) {};
	string getId(void) const { return id; }
	string getRole(void) const { return name; }
	string getProffId(void) const { return proofID; }
	void enterId(void)
	{
		cout << "\nEnter UserId";
		cin >> id;
	}
	void setProofOfId(string proof)
	{
		proofID = proof;
	}
};
class ProofOfId
{
private:
	string proofId;
public:
	ProofOfId(void) {};
	ProofOfId(string aproofID)
	{
		proofId = aproofID;
	}
	string getProofID(void)
	{
		return proofId;
	}
	void setProofID(string aproofID)
	{
		proofId = aproofID;
	}
};
class Authenticator
{
private:
	string encryptDecrypt(string toEncrypt)
	{
		char key = 'c';
		string output = toEncrypt;
		for (uint16_t i = 0; i < toEncrypt.size(); i++)
		{
			output[i] = toEncrypt[i] ^ key;
		}
		return output;
	}
public:
	ProofOfId authenticateUser(Subject& s)
	{
		AuthenticationInfo ainfo;
		ProofOfId proofofID;
		string id = s.getId();
		string pass;
		string token;
		cout << "\nEnter password";
		cin >> pass;
		if (ainfo.validateUser(id, pass))
		{
			cout << "\nWelcome!";
			cout << "\nAuthenicated\n";
			token = encryptDecrypt(id + pass);
			proofofID = ProofOfId(token);
			s.setProofOfId(token);
		}
		else
		{
			cout << "invalid user id or password,try again";
		}
		return proofofID;
	}
};     


