/**
Copyright (c) 2019 Dan Orban
*/

#ifndef WebSerVER_H_
#define WebSerVER_H_

#include <string>
#include <vector>
#include <map>
#include <libwebsockets.h>

class WebServerBase {
public:
	WebServerBase(int port = 8081, const std::string& webDir = ".");
	~WebServerBase();

	class Session {
	friend class WebServerBase;
	public:
		Session();
		virtual ~Session();
		virtual int getId() const { return id; }
		virtual void receiveMessage(const std::string& msg) {}
		virtual void sendMessage(const std::string& msg);
		virtual void update() {}
		virtual void onWrite();
	private:
		void* state;
		int id;
	};

	void service(int time = 10);

	virtual void createSession(void* info);
	

protected:
	virtual Session* createSession() { return new Session(); }

public:
	lws_context *context;
	std::vector<Session*> sessions;
	std::map<int, Session*> sessionMap;
	std::string webDir;
};

template <typename T>
class WebServer : public WebServerBase {
public:
	WebServer(int port = 8081, const std::string& webDir = ".") : WebServerBase(port, webDir) {}
protected:
	Session* createSession() { return new T(); }
};

template <typename T, typename STATE>
class WebServerWithState : public WebServerBase {
public:
	WebServerWithState(STATE state, int port = 8081, const std::string& webDir = ".") : WebServerBase(port, webDir), state(state) {}
protected:
	Session* createSession() { return new T(state); }
private:
	STATE state;
};

// JSON support
#include "picojson.h"

class JSONSession : public WebServerBase::Session {
private:
	std::string firsthalf = "";
public:
	virtual void receiveJSON(picojson::value& val) {}
	
	virtual void sendJSON(picojson::value& val) {
		sendMessage(val.serialize());
	}

	void receiveMessage(const std::string& msg) {
		picojson::value val;
		std::string err = picojson::parse(val, msg);
		if (!err.empty() || msg[0] != '{' || msg[msg.length()-1] != '}') {
			if(firsthalf == "") {
				std::cout << "first half is empty, waiting for next msg" << std::endl;
				firsthalf = msg;
				std::cout << firsthalf << std::endl;
				return;
			} else {
				std::cout << "non empty first half" << std::endl;
				std::cout << msg << std::endl;
				std::string msg2 = firsthalf + msg;
				picojson::value val2;
				std::string err2 = picojson::parse(val2, msg2);
				if (!err2.empty() || msg2[0] != '{' || msg2[msg2.length()-1] != '}') {
					std::cerr << msg2 << std::endl;
					std::cerr << "Parse error: " << err << std::endl;
					firsthalf = msg;
				} else {
					receiveJSON(val2);
					firsthalf = "";
				}
			}
			
		}
		else {
			receiveJSON(val);	
		}
	}
};

#endif
